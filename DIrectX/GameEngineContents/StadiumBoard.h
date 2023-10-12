#pragma once
#include <GameEngineCore/GameEngineActor.h>

class StadiumBoard : public GameEngineActor
{
public:
    StadiumBoard();
    ~StadiumBoard();

    StadiumBoard(const StadiumBoard& _Other) = delete;
    StadiumBoard(StadiumBoard&& _Other) noexcept = delete;
    StadiumBoard& operator=(const StadiumBoard& _Other) = delete;
    StadiumBoard& operator=(StadiumBoard&& _Other) noexcept = delete;

    void Setting(const std::vector<class GameUnit*>& _BlueTeam, const std::vector<class GameUnit*>& _RedTeam)
    {
        BlueTeam = _BlueTeam;
        RedTeam = _RedTeam;
    }

    int BlueDieCount = 0;
    int RedDieCount = 0;

    int BlueKillCount = 0;
    int RedKillCount = 0;

    int BlueWinCount = 0;
    int RedKWinCount = 0;

    float GameTime = 10.0f;

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;

    // ½ÂÆÐ ÃÊ·ÏºÒ
    std::shared_ptr<class GameEngineSpriteRenderer> BlueWin;
    std::shared_ptr<class GameEngineSpriteRenderer> BlueWin2;

    std::shared_ptr<class GameEngineSpriteRenderer> RedWin;
    std::shared_ptr<class GameEngineSpriteRenderer> RedWin2;

    std::vector<class GameUnit*> RedTeam;
    std::vector<class GameUnit*> BlueTeam;
};

