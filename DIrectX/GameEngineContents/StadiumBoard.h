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
};

