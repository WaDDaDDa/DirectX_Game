#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Stadium : public GameEngineActor
{
public:
    Stadium();
    ~Stadium();

    Stadium(const Stadium& _Other) = delete;
    Stadium(Stadium&& _Other) noexcept = delete;
    Stadium& operator=(const Stadium& _Other) = delete;
    Stadium& operator=(Stadium&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> StadiumRenderer;
    std::shared_ptr<class GameEngineSpriteRenderer> BackDesk;
    std::shared_ptr<class GameEngineSpriteRenderer> Chair;
    std::shared_ptr<class GameEngineSpriteRenderer> Desk;
    std::shared_ptr<class GameEngineSpriteRenderer> Frame;

    std::shared_ptr<class GameEngineSpriteRenderer> BlueTeamName;
    std::shared_ptr<class GameEngineSpriteRenderer> BlueTeamLogo;
    std::shared_ptr<class GameEngineSpriteRenderer> BigBlueTeamLogoBg;
    std::shared_ptr<class GameEngineSpriteRenderer> BigBlueTeamLogo;
    std::shared_ptr<class GameEngineSpriteRenderer> BigBlueTeamName;

    std::shared_ptr<class GameEngineSpriteRenderer> VSText;

    std::shared_ptr<class GameEngineSpriteRenderer> RedTeamName;
    std::shared_ptr<class GameEngineSpriteRenderer> RedTeamLogo;
    std::shared_ptr<class GameEngineSpriteRenderer> BigRedTeamLogoBg;
    std::shared_ptr<class GameEngineSpriteRenderer> BigRedTeamLogo;
    std::shared_ptr<class GameEngineSpriteRenderer> BigRedTeamName;

};

