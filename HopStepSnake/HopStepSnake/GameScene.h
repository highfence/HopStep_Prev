#pragma once
#include "../../HopStep/HopStep/HopStep.h"

class GameScene : public HopStep::IScene
{
public:

	virtual bool Init() override;

	virtual void UpdateScene(const float deltaTime) override;
};

