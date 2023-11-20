#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ResultBoard : public GameEngineActor
{
public:
    ResultBoard();
    ~ResultBoard();

    ResultBoard(const ResultBoard& _Other) = delete;
    ResultBoard(ResultBoard&& _Other) noexcept = delete;
    ResultBoard& operator=(const ResultBoard& _Other) = delete;
    ResultBoard& operator=(ResultBoard&& _Other) noexcept = delete;


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

    std::shared_ptr<class GameEngineSpriteRenderer> BlueLogo;
    std::shared_ptr<class GameEngineSpriteRenderer> BlueTeamName;
    std::shared_ptr<class GameEngineSpriteRenderer> BlueTeamWinCount;

    std::shared_ptr<class GameEngineSpriteRenderer> RedLogo;
    std::shared_ptr<class GameEngineSpriteRenderer> RedTeamName;
    std::shared_ptr<class GameEngineSpriteRenderer> RedTeamWinCount;

    std::shared_ptr<class GameEngineSpriteRenderer> MainBlueLogo;
    std::shared_ptr<class GameEngineSpriteRenderer> MainRedLogo;

    std::shared_ptr<class GameEngineSpriteRenderer> MainBlueName;
    std::shared_ptr<class GameEngineSpriteRenderer> MainRedName;

    std::shared_ptr<class GameEngineSpriteRenderer> ResultText;
    std::shared_ptr<class GameEngineSpriteRenderer> WinText;

    std::shared_ptr<class GameEngineSpriteRenderer> Text;

    std::shared_ptr<class GameEngineSpriteRenderer> BlueWinCountText;
    std::shared_ptr<class GameEngineSpriteRenderer> RedWinCountText;

    std::shared_ptr<class Default_Button> Button = nullptr;


    std::vector<class GameUnit*> RedTeam;
    std::vector<class GameUnit*> BlueTeam;
};

