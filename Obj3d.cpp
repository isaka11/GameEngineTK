#include "Obj3d.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//静的メンバ変数の実体
//デバイス
Microsoft::WRL::ComPtr<ID3D11Device>            Obj3d::m_d3dDevice;

//デバイスコンテキスト
Microsoft::WRL::ComPtr<ID3D11DeviceContext>     Obj3d::m_d3dContext;

ID3D11BlendState* Obj3d::blendStateSubtract;

//カメラ
Camera* Obj3d::m_Camera;

//汎用描画ステート
std::unique_ptr<DirectX::CommonStates> Obj3d::m_states;

//エフェクトファクトリ
std::unique_ptr<DirectX::EffectFactory> Obj3d::m_factory;

void Obj3d::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;

	//汎用描画ステート生成
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());

	//エフェクトファクトリの生成
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());

	//テクスチャの読み込みパスの指定
	m_factory->SetDirectory(L"Resources");

	// 減算描画用のブレンドステートを作成

	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	HRESULT ret = m_d3dDevice->CreateBlendState(&desc, &blendStateSubtract);
}

Obj3d::Obj3d()
{
	//スケールは1倍がデフォルト
	m_scale = Vector3(1.0f, 1.0f, 1.0f);

	//デフォルトではオイラー角で計算
	m_UseQuaternion = false;

	m_Coin_flag = false;
	m_Delete_flag = false;

	m_parent = nullptr;
}

void Obj3d::LoadModel(const wchar_t * fileName)
{
	//モデルの読み込み、生成
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

void Obj3d::Update()
{
	//行列の計算

	//スケーリング行列
	Matrix scalemat = Matrix::CreateScale(m_scale);

	Matrix rotmat;

	//回転行列
	if (m_UseQuaternion)
	{//クォータニオンで回転を計算
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{//オイラー角で回転を計算(Z→X→Y)
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		rotmat = rotmatZ * rotmatX * rotmatY;
	}

	//平行移動行列
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	//ワールド行列を合成
	m_world = scalemat * rotmat * transmat;

	//親の行列をかける
	if (m_parent)
	{
		m_world *= m_parent->m_world;
	}
}

//行列の計算
void Obj3d::Calc()
{
	Matrix scalem;
	Matrix rotm;
	Matrix transm;

	scalem = Matrix::CreateScale(m_scale);

	if (m_UseQuaternion)
	{
		rotm = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		rotm = Matrix::CreateFromYawPitchRoll(m_rotation.y, m_rotation.x, m_rotation.z);
	}

	transm = Matrix::CreateTranslation(m_translation);

	// ワールド行列をSRTの順に合成
	m_world = Matrix::Identity;
	m_world *= scalem;
	m_world *= rotm;
	m_world *= transm;

	// 親行列があれば
	if (m_parent)
	{
		// 親行列を掛ける
		m_world = m_world * m_parent->GetWorld();
	}
}

//描画
void Obj3d::Draw()
{
	assert(m_Camera);

	//3Dモデルの描画
	if (m_model)
	{
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_Camera->GetView(), m_Camera->GetProj());
	}
}

//オブジェクトの最初の色を設定する
void Obj3d::Set_Init_Color(const DirectX::SimpleMath::Vector4& color_code)
{
	if (m_model)
	{
		// モデル内の全メッシュ分回す
		ModelMesh::Collection::const_iterator it_mesh = m_model->meshes.begin();

		for (; it_mesh != m_model->meshes.end(); it_mesh++)
		{
			ModelMesh* modelmesh = it_mesh->get();
			assert(modelmesh);

			// メッシュ内の全メッシュパーツ分回す
			std::vector<std::unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
			for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
			{
				ModelMeshPart* meshpart = it_meshpart->get();
				assert(meshpart);

				//メッシュパーツにセットされたエフェクトをBasicEffectとして取得
				std::shared_ptr<IEffect> ieff = meshpart->effect;
				BasicEffect* eff = dynamic_cast<BasicEffect*>(ieff.get());

				if (eff != nullptr)
				{
					eff->SetDiffuseColor(Vector4 (color_code.x, color_code.y, color_code.z, color_code.w));
				}
			}
		}
	}
}

//オブジェクトの色を変える
void Obj3d::Set_Color()
{
	if (m_model)
	{
		// モデル内の全メッシュ分回す
		ModelMesh::Collection::const_iterator it_mesh = m_model->meshes.begin();
		for (; it_mesh != m_model->meshes.end(); it_mesh++)
		{
			ModelMesh* modelmesh = it_mesh->get();
			assert(modelmesh);

			// メッシュ内の全メッシュパーツ分回す
			std::vector<std::unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
			for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
			{
				ModelMeshPart* meshpart = it_meshpart->get();
				assert(meshpart);

				// メッシュパーツにセットされたエフェクトをBasicEffectとして取得
				std::shared_ptr<IEffect> ieff = meshpart->effect;
				BasicEffect* eff = dynamic_cast<BasicEffect*>(ieff.get());

				if (eff != nullptr)
				{
					eff->SetDiffuseColor(Vector4(0.0f, 0.0f, 1.0f, 0.0f));
				}
			}
		}
	}
}

//エフェクトを設定する
void Obj3d::Set_Effect()
{
	//ポリゴン描画用のエフェクトを作成
	m_pPolygonEffect.reset(new BasicEffect(m_d3dDevice.Get()));

	if (m_model)
	{
		// モデル内の全メッシュ分回す
		ModelMesh::Collection::const_iterator it_mesh = m_model->meshes.begin();

		for (; it_mesh != m_model->meshes.end(); it_mesh++)
		{
			ModelMesh* modelmesh = it_mesh->get();
			assert(modelmesh);

			// メッシュ内の全メッシュパーツ分回す
			std::vector<std::unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
			for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
			{
				ModelMeshPart* meshpart = it_meshpart->get();
				assert(meshpart);

				meshpart->effect = m_pPolygonEffect;
			}
		}
	}
}

//減算描画設定をセット
void Obj3d::SetSubtractive()
{
	// 減算描画を設定

	m_d3dContext->OMSetBlendState(blendStateSubtract, nullptr, 0xffffff);
}

//減算描画での描画（影用）
void Obj3d::DrawSubtractive()
{

	if (m_model)
	{
		const Matrix& view = m_Camera->GetView();
		const Matrix& projection = m_Camera->GetProj();

		// 減算描画用の設定関数を渡して描画
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, view, projection, false, Obj3d::SetSubtractive);

	}
}
