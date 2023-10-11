#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PlayerCard : public GameEngineActor
{
public:
    PlayerCard();
    ~PlayerCard();

    PlayerCard(const PlayerCard& _Other) = delete;
    PlayerCard(PlayerCard&& _Other) noexcept = delete;
    PlayerCard& operator=(const PlayerCard& _Other) = delete;
    PlayerCard& operator=(PlayerCard&& _Other) noexcept = delete;

    void SetUnit(std::shared_ptr<class GameUnit> _Unit)
    {
        Unit = _Unit;
        Init();
    }

    void Init();

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;
    float StartY = 280.0f;
    static float BlueYInter;
    static float RedYInter;

private:
    std::shared_ptr<class GameUnit> Unit;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer2;

    std::shared_ptr<class GameEngineSpriteRenderer> UnitImage;

};

