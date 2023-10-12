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

private:
    std::shared_ptr<class PlayerCard> PCard;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;


};

