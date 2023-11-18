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

    std::shared_ptr<class GameEngineSpriteRenderer> BlueOnePlayerBg;
    std::shared_ptr<class GameEngineSpriteRenderer> BlueOnePlayerBody;
    std::shared_ptr<class GameEngineSpriteRenderer> BlueOnePlayerHair;
    std::shared_ptr<class GameEngineSpriteRenderer> BlueOnePlayerName;

    std::shared_ptr<class GameEngineSpriteRenderer> BlueTwoPlayerBg;
    std::shared_ptr<class GameEngineSpriteRenderer> BlueTwoPlayerBody;
    std::shared_ptr<class GameEngineSpriteRenderer> BlueTwoPlayerHair;
    std::shared_ptr<class GameEngineSpriteRenderer> BlueTwoPlayerName;

    std::shared_ptr<class GameEngineSpriteRenderer> RedOnePlayerBg;
    std::shared_ptr<class GameEngineSpriteRenderer> RedOnePlayerBody;
    std::shared_ptr<class GameEngineSpriteRenderer> RedOnePlayerHair;
    std::shared_ptr<class GameEngineSpriteRenderer> RedOnePlayerName;

    std::shared_ptr<class GameEngineSpriteRenderer> RedTwoPlayerBg;
    std::shared_ptr<class GameEngineSpriteRenderer> RedTwoPlayerBody;
    std::shared_ptr<class GameEngineSpriteRenderer> RedTwoPlayerHair;
    std::shared_ptr<class GameEngineSpriteRenderer> RedTwoPlayerName;

    std::shared_ptr<class GameEngineSpriteRenderer> BluePlayerBody1;
    std::shared_ptr<class GameEngineSpriteRenderer> BluePlayerHair1;
    std::shared_ptr<class GameEngineSpriteRenderer> BluePlayerBody2;
    std::shared_ptr<class GameEngineSpriteRenderer> BluePlayerHair2;

    std::shared_ptr<class GameEngineSpriteRenderer> RedPlayerBody1;
    std::shared_ptr<class GameEngineSpriteRenderer> RedPlayerHair1;
    std::shared_ptr<class GameEngineSpriteRenderer> RedPlayerBody2;
    std::shared_ptr<class GameEngineSpriteRenderer> RedPlayerHair2;


};

