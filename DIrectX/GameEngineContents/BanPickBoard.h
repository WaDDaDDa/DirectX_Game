#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BanPickBoard : public GameEngineActor
{
public:
    BanPickBoard();
    ~BanPickBoard();

    BanPickBoard(const BanPickBoard& _Other) = delete;
    BanPickBoard(BanPickBoard&& _Other) noexcept = delete;
    BanPickBoard& operator=(const BanPickBoard& _Other) = delete;
    BanPickBoard& operator=(BanPickBoard&& _Other) noexcept = delete;

    int BlueDieCount = 0;
    int RedDieCount = 0;

    int BlueKillCount = 0;
    int RedKillCount = 0;

    int BlueWinCount = 0;
    int RedKWinCount = 0;

    float GameTime = 60.0f;

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> BackGround;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;

    // ½ÂÆÐ ÃÊ·ÏºÒ
    std::shared_ptr<class GameEngineSpriteRenderer> BlueWin;
    std::shared_ptr<class GameEngineSpriteRenderer> BlueWin2;

    std::shared_ptr<class GameEngineSpriteRenderer> RedWin;
    std::shared_ptr<class GameEngineSpriteRenderer> RedWin2;

    std::vector<class GameUnit*> RedTeam;
    std::vector<class GameUnit*> BlueTeam;
};

