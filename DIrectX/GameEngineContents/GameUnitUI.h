#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameUnitUI : public GameEngineActor
{
public:
    GameUnitUI();
    ~GameUnitUI();

    GameUnitUI(const GameUnitUI& _Other) = delete;
    GameUnitUI(GameUnitUI&& _Other) noexcept = delete;
    GameUnitUI& operator=(const GameUnitUI& _Other) = delete;
    GameUnitUI& operator=(GameUnitUI&& _Other) noexcept = delete;

    void SetUnit(std::shared_ptr<class GameUnit> _Unit)
    {
        Unit = _Unit;
        InitUniUI();
    }

    void InitUniUI();

    void AllRendererOff()
    {
        Renderer->Off();
        Renderer2->Off();
        Renderer3->Off();
        Renderer4->Off();
        Renderer5->Off();
        Renderer6->Off();
        Renderer7->Off();
    }

    void AllRendererOn()
    {
        Renderer ->On();
        Renderer2->On();
        Renderer3->On();
        Renderer4->On();
        Renderer5->On();
        Renderer6->On();
        Renderer7->On();
    }

    float MPValue = 0.0f;

protected:
    void Start() override;
    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void Update(float _Delta) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer2;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer3;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer4;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer5;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer6;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer7;
    std::shared_ptr<class GameUnit> Unit;
};

