#pragma once
#include "CGame.h"

//ƒNƒ‰ƒX‚Ì’è‹`
class CGame;

class SceneBase
{
public:
	virtual ~SceneBase() {};
	virtual void Initialize() = 0;
	virtual void Update(CGame* scene) = 0;
	virtual void Render() = 0;
};