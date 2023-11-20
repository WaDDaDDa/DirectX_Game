#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Title_UI : public GameEngineActor
{
public:
    Title_UI();
    ~Title_UI();

    Title_UI(const Title_UI& _Other) = delete;
    Title_UI(Title_UI&& _Other) noexcept = delete;
    Title_UI& operator=(const Title_UI& _Other) = delete;
    Title_UI& operator=(Title_UI&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Delta) override;
    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;


private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<class GameEngineSpriteRenderer> LogoRenderer;


    std::shared_ptr<class FadeEffect> FadeInEffect = nullptr;
    std::shared_ptr<class FadeEffect> FadeOutEffect = nullptr;


};

