#pragma once

using SceneManager = HopStep::SceneManager;
using IScene = HopStep::IScene;

class TitleScene : public IScene
{
public:

	virtual void UpdateScene(const float deltaTime) override;

	virtual bool Init() override;

	virtual bool OnChangeScene(SceneManager* manager) override;
};

