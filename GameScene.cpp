

#include "GameScene.h"
#include "ModelEffect.h"
#include "Device.h"

extern void ExitGame();

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Library;

using Microsoft::WRL::ComPtr;

SceneBase* GameScene::m_base = nullptr;

GameScene::GameScene()
{

}

GameScene::~GameScene()
{
	Dispose();
}

void GameScene::Initialize(/*DirectX::Keyboard* keyboard*/)
{
	Device* device = Device::GetInstance();

	//csv�t�@�C���̓ǂݍ���
	importData("stage.csv");

	//�J�����̐���
	m_Camera = std::make_unique<FollowCamera>(device->GetWidth(), device->GetHeight());

	//3D�I�u�W�F�N�g�̐ÓI�����o��������
	Obj3d::InitializeStatic(device->GetDevice(), device->GetContext(), m_Camera.get());

	//�n�`�N���X�̏�����
	LandShapeCommonDef lscdef;
	lscdef.pDevice = device->GetDevice().Get();
	lscdef.pDeviceContext = device->GetContext().Get();
	lscdef.pCamera = m_Camera.get();
	LandShape::InitializeCommon(lscdef);

	//�v���C���[�̐���
	m_Player = std::make_unique<Player>();
	m_Player->Initialize();
	m_Player->SetTrans(START_POS);

	//�J�����Ƀv���C���[���Z�b�g
	m_Camera->SetPlayer(m_Player.get());

	m_batch = std::make_unique<PrimitiveBatch<VertexPositionNormal>>(device->GetContext().Get());

	m_effect = std::make_unique<BasicEffect>(device->GetDevice().Get());

	m_view = Matrix::CreateLookAt(Vector3(0, 2.0f, 5.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.0f, float(device->GetWidth()) / float(device->GetHeight()), 0.1f, 500.f);

	m_effect->SetView(m_view);

	m_effect->SetProjection(m_proj);

	m_effect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	device->GetDevice()->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.GetAddressOf());

	//�G�t�F�N�g�t�@�N�g���̐���
	m_factory = std::make_unique<EffectFactory>(device->GetDevice().Get());

	//�e�N�X�`���̓ǂݍ��݃p�X�̎w��
	m_factory->SetDirectory(L"Resources");

	////�X�v���C�g�o�b�`���쐬
	//m_spriteBatch = std::make_unique<SpriteBatch>(device->GetDeviceContext());

	////�f�o�b�O�e�L�X�g���쐬
	//m_debugText = std::make_unique<DebugText>(device->GetDevice().Get(), m_spriteBatch.get());

	//�R�C���̖����̏�����
	m_coin_num = COIN_NUM;

	//���[�J���ϐ��̐錾�Ə�����
	int a = -1;
	int j = 0;

	//�I�u�W�F�N�g�̐���
	for (int i = 0; i < MAX_CHIP; i++)
	{
		j++;

		if (i % 600 == 0)
		{
			a++;
			j = 0;
		}

		//0�Ԃ̏ꍇ�����������Ȃ�
		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] != 0)
		{
			//�n�`�̏������ƈʒu�̐ݒ�
			m_Landshape_obj[i].Initialize(L"Object01", L"Object01");
			m_Landshape_obj[i].SetTrans(Vector3(i % MAX_X_CHIP * OBJ_SPACE, 
												j / MAX_X_CHIP * -OBJ_SPACE - OBJ_SPACE * 5.0f, 
												a * -OBJ_SPACE));

			//�ǁE���̐���
			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 1)
			{
				m_obj[i].LoadModel(L"Resources/Object01.cmo");
			}

			//�g�Q���̐���
			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 2)
			{
				m_obj[i].LoadModel(L"Resources/Object02.cmo");
			}

			//�R�C���̐���
			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)
			{
				m_obj[i].LoadModel(L"Resources/Object03.cmo");
				m_Landshape_obj[i].SetScale(Vector3(0.5f, 0.5f, 0.5f));
			}
			m_obj[i].SetTranslation(m_Landshape_obj[i].GetTrans());
		}
	}

	//�I���t���O�̏�����
	m_finish_flag = false;

	//�n�ʂ̏������ƈʒu�̐ݒ�
	m_objGround.LoadModel(L"Resources/Graund.cmo");
	m_objGround.SetTranslation(Vector3(-1.0f, -27.6f, 1.0f));

	//�e�̏�����
	m_ObjShadow.LoadModel(L"Resources/shadow.cmo");
	m_ObjShadow.SetTranslation(Vector3(0, SHADOW_OFFSET, 0));

	////�T�E���h�̏������Ɠǂݍ���
	//ADX2Le::Initialize("Sounds\\CueSheet_0.acb");
	//ADX2Le::LoadAcb("Sounds\\CueSheet_0.acb", "Sounds\\CueSheet_0.awb");

	////BGM�̍Đ�
	//ADX2Le::Play(CRI_CUESHEET_0_BGM);	
}

void GameScene::Update(CGame* scene)
{
	Device* device = Device::GetInstance();


	//�v���C���[�̍X�V����
	if (m_Camera->GetCameraMoveFlag() == false && m_finish_flag == false)
	{
		m_Player->Update();
	}

	//�J�����̍X�V
	m_Camera->Update();
	m_view = m_Camera->GetView();
	m_proj = m_Camera->GetProj();

	//�I�u�W�F�N�g�̍X�V����
	for (int i = 0; i < MAX_CHIP; i++)
	{
		//0�ԈȊO�̍X�V�������s��
		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] != 0)
		{
			Vector3 Vec = m_Landshape_obj[i].GetTrans() - m_Player->GetTrans();

			float distance_Square;

			distance_Square = Vec.x * Vec.x + Vec.y * Vec.y + Vec.z * Vec.z;

			float radius_Square;

			//���a�̘a�̓��
			radius_Square = JUDGMENT_SPACE + JUDGMENT_SPACE;
			radius_Square = radius_Square * radius_Square;

			if (distance_Square < radius_Square)
			{
				m_obj[i].Update();
				m_Landshape_obj[i].Update();
			}

			//�R�C���̉�]
			if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)
			{
				Vector3 l_angle = m_obj[i].GetRotation();
				m_obj[i].SetRotation(l_angle + Vector3(0.0f, 0.1f, 0.0f));

				//Vector3 Trans = m_obj[i].GetTranslation();
				//m_obj[i].SetTranslation(Trans + Vector3(0.01f, 0.0f, 0.0f));
				//m_Landshape_obj[i].SetTrans(Trans + Vector3(0.01f, 0.0f, 0.0f));
			}
		}
	}

	//�n�ʂ̍X�V����
	m_objGround.Update();

	//���@�̓����蔻�苅���擾
	Sphere sphere = m_Player->GetCollisionNodeBody();

	//���@�̃��[���h���W���擾
	Vector3 trans = m_Player->GetTrans();

	//���̒��S���玩�@�Z���^�[�̃x�N�g��
	Vector3 sphere2player = trans - sphere.Center;

	//�߂荞�ݔr�˃x�N�g��
	Vector3 reject;

	//�I�u�W�F�N�g�̓����蔻��
	for (int i = 0; i < MAX_CHIP; i++)
	{
		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 1 ||
			m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 2)
		{
			while (m_Landshape_obj[i].IntersectSphere(sphere, &reject))
			{
				//�߂荞�݂���������悤�Ɉړ�
				sphere.Center += reject;
			}
		}
	}

	//�e�̍X�V
	Vector3 pos = m_Player->GetTrans();
	pos.y = SHADOW_OFFSET;
	m_ObjShadow.SetTranslation(pos);

	//���@���ړ�
	m_Player->SetTrans(sphere.Center + sphere2player);

	//��_���W
	Vector3 inter;
	float temp_distance;
	bool hit = false;

	//�n�`�Ɛ����̓����蔻��
	if (m_Player->GetVelocity().y <= 0.0f)
	{
		//���@�̓����瑫���ւ̐���
		Segment player_segment;

		//���@�̃��[���h���W���擾
		Vector3 trans = m_Player->GetTrans();

		player_segment.start = trans + Vector3(0, SEGMENT_LENGTH_HEAD, 0);
		player_segment.end = trans + Vector3(0, -SEGMENT_LENGTH_LEG, 0);

		Vector3 temp_inter;

		//���ʂƂ̓�����𔻒�
		for (int i = 0; i < MAX_CHIP; i++)
		{
			if (m_Landshape_obj[i].IntersectSegment(player_segment, &temp_inter))
			{
				if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 1)		//���E�ǂ̏���
				{
					//Y���W�̂݌�_�̈ʒu�Ɉړ�
					trans.y = temp_inter.y;
					// �����I��
					m_Player->StopJump();
				}
				if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 2)		//�g�Q���̏���
				{
					//ADX2Le::Play(CRI_CUESHEET_0_MISS);
					m_Player->Set_Mode(false);
					m_Player->SetFirstPosFlag(false);
					trans = START_POS;
				}
				if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)		//�R�C���̏���
				{
					bool flag = m_obj[i].Get_Coin();

					//�R�C����1�񂾂��G�ꂽ���m�F����
					if (flag == false)
					{
						if (m_coin_num > 1)
						{
							//ADX2Le::Play(CRI_CUESHEET_0_COIN);
						}
						else
						{
							//ADX2Le::Play(CRI_CUESHEET_0_CLEAR);
						}

						m_obj[i].Set_Coin(true);
						m_obj[i].Set_Delete(true);
						m_coin_num--;
					}
				}
			}
		}
		//���@�̈ړ�
		m_Player->SetTrans(trans);
	}

	//���@�̓����瑫���ւ̐���
	Segment player_segment_shadow;

	//���@�̃��[���h���W���擾
	Vector3 trans_shadow = m_Player->GetTrans();

	player_segment_shadow.start = trans_shadow + Vector3(0, SEGMENT_LENGTH_HEAD, 0);
	player_segment_shadow.end = trans_shadow + Vector3(0, -SHADOW_DISTANCE, 0);

	Vector3 temp_inter_shadow;
	float distance = 1.0e5;

	//�e�̏���
	for (int i = 0; i < MAX_CHIP; i++)
	{
		//�R�C���̕��������e�̌v�Z���s��Ȃ�
		if (!(m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3))
		{
			//���ʂƂ̓�����𔻒�
			if (m_Landshape_obj[i].IntersectSegment(player_segment_shadow, &temp_inter_shadow))
			{
				hit = true;

				//�v���C���[�̃Z�O�����g�ƒn�ʂ̍�
				temp_distance = Vector3::Distance(player_segment_shadow.start, temp_inter_shadow);

				if (temp_distance < distance)
				{
					inter = temp_inter_shadow;
					distance = temp_distance;
				}
			}
		}
	}

	//�R�C�������̕\��
	if (m_finish_flag == false)
	{
		//m_debugText->AddText(Vector2(10, 10), L"COIN_NUM = %d", m_coin_num);
	}

	//�e�̈ʒu�X�V
	if (hit)
	{
		Vector3 shadow_pos = trans;
		shadow_pos.y = inter.y + SHADOW_OFFSET;
		m_ObjShadow.SetTranslation(shadow_pos);
	}

	//���������珉���ʒu�ɖ߂�
	if (trans.y <= -40.0f)
	{
		//ADX2Le::Play(CRI_CUESHEET_0_MISS);
		m_Player->Set_Mode(false);
		m_Player->SetFirstPosFlag(false);
		m_Player->SetTrans(START_POS);
	}

	//�R�C����S�ē��肵����Q�[���I��
	if (m_coin_num == 0)
	{
		m_finish_flag = true;
		//m_debugText->AddText(Vector2(340, 290), L"GAMECLEAR!");
	}

	////�Q�[���I������
	//if (m_finish_flag == true && keystate.Enter)
	//{
	//	ExitProcess(0);
	//	ExitGame();
	//}

	//�e�̍s��v�Z
	m_ObjShadow.Calc();

	//�G�t�F�N�g�̍X�V����
	ModelEffectManager::getInstance()->Update();
}

void GameScene::Render()
{
	Device* device = Device::GetInstance();
	
	//�`�揈��
	DirectX::CommonStates m_states(device->GetDevice().Get());

	device->GetContext()->OMSetBlendState(m_states.Opaque(), nullptr, 0xFFFFFFFF);
	device->GetContext()->OMSetDepthStencilState(m_states.DepthNone(), 0);
	device->GetContext()->RSSetState(m_states.CullNone());
	device->GetContext()->IASetInputLayout(m_inputLayout.Get());

	//�n�ʂ̕`��
	m_objGround.Draw();

	//�I�u�W�F�N�g�̕`��
	for (int i = 0; i < MAX_CHIP; i++)
	{
		//0�ԈȊO�̃I�u�W�F�N�g��`��
		if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] != 0)
		{
			Vector3 Vec = m_Landshape_obj[i].GetTrans() - m_Player->GetTrans();

			float distance_Square;

			distance_Square = Vec.x * Vec.x + Vec.y * Vec.y + Vec.z * Vec.z;

			float radius_Square;

			//���a�̘a�̓��
			radius_Square = JUDGMENT_SPACE + JUDGMENT_SPACE;
			radius_Square = radius_Square * radius_Square;

			if (distance_Square < radius_Square)
			{
				//3�Ԃ̕`��
				if (m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] == 3)
				{
					if (m_obj[i].Get_Delete() == false)
					{
						m_obj[i].Draw();
						//m_Landshape_obj[i].Draw();
					}
				}
				//����ȊO�̕`��
				else
				{
					m_obj[i].Draw();
				}
			}
		}
	}

	//�v���C���[�̕`��
	m_Player->Draw();
	
	//�e�̕`��
	m_ObjShadow.DrawSubtractive();

	//�G�t�F�N�g�̕`�揈��
	ModelEffectManager::getInstance()->Draw();

	//m_spriteBatch->Begin();

	//m_debugText->Draw();

	//m_spriteBatch->End();
}

SceneBase* GameScene::GetInstance()
{
	if (m_base == nullptr)
	{
		m_base = new GameScene();
	}
	return m_base;
}

void GameScene::Dispose()
{
	if (m_base != nullptr)
	{
		delete m_base;
	}
}

//csv�t�@�C���̓ǂݍ���
void GameScene::importData(string filename)
{
	ifstream ifs(filename);

	string str;
	int i;

	if (!ifs)
	{
		//�ǂ߂Ȃ��Ƃ��͑S��0
		for (i = 0; i < MAX_CHIP; i++)
		{
			m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] = 0;
		}
		return;
	}

	i = 0;
	while (getline(ifs, str))
	{
		string token;
		istringstream stream(str);

		//1�s�̂����A������ƃR���}�𕪗􂷂�
		while (getline(stream, token, ','))
		{
			//�S�ĕ�����Ƃ��ēǂݍ��܂�邽��
			//���l�͕ϊ����K�v
			m_map[i / MAX_X_CHIP][i % MAX_X_CHIP] = atoi(token.c_str());
			i++;
		}
	}
}