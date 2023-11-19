#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PlayerCard_Status : public GameEngineActor
{
public:
    PlayerCard_Status();
    ~PlayerCard_Status();

    PlayerCard_Status(const PlayerCard_Status& _Other) = delete;
    PlayerCard_Status(PlayerCard_Status&& _Other) noexcept = delete;
    PlayerCard_Status& operator=(const PlayerCard_Status& _Other) = delete;
    PlayerCard_Status& operator=(PlayerCard_Status&& _Other) noexcept = delete;

    void Setting(std::shared_ptr<class PlayerCard> _PlayerCard)
    {
        PCard = _PlayerCard;
        Init();
    }

    void Init();

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;
    float4 StartPos = float4::ZERO;

    std::shared_ptr<class GameEngineSpriteRenderer> InfoText;
    std::shared_ptr<class GameEngineSpriteRenderer> KillText;
    std::shared_ptr<class GameEngineSpriteRenderer> DeathText;
    std::shared_ptr<class GameEngineSpriteRenderer> AsistText;
    std::shared_ptr<class GameEngineSpriteRenderer> KillInfo;
    std::shared_ptr<class GameEngineSpriteRenderer> DeathInfo;
    std::shared_ptr<class GameEngineSpriteRenderer> AsistInfo;

    std::shared_ptr<class GameEngineSpriteRenderer> AttInfo;
    std::shared_ptr<class GameEngineSpriteRenderer> DefInfo;
    std::shared_ptr<class GameEngineSpriteRenderer> HealInfo;


private:
    std::shared_ptr<class PlayerCard> PCard;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;


};

