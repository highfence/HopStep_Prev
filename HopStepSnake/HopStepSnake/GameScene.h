#pragma once

class GameScene : public HopStep::IScene
{
public:

	virtual bool Init() override;

	virtual void UpdateScene(float deltaTime) override;
};
