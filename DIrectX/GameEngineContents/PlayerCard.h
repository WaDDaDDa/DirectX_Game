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

    std::shared_ptr<class GameUnit> GetUnit()
    {
        return Unit;
    }

    void CreateStatus();


protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;
    float StartY = 200.0f;
    static float BlueYInter;
    static float RedYInter;

private:
    std::shared_ptr<class GameUnit> Unit;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;

    std::shared_ptr<class GameEngineSpriteRenderer> UnitImage;
    float4 UnitImagePos = { -49.0f, -8.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> AttIcon;
    float4 AttIconPos = { -65.0f, -32.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> AttText;


    std::shared_ptr<class GameEngineSpriteRenderer> DefIcon;
    float4 DefIconPos = { 10.0f, -32.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> DefText;

    std::shared_ptr<class GameEngineSpriteRenderer> PlayerName;



};

