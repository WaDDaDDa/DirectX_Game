#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class IntroLevel : public GameEngineLevel
{
public:
    IntroLevel();
    ~IntroLevel();

    IntroLevel(const IntroLevel& _Other) = delete;
    IntroLevel(IntroLevel&& _Other) noexcept = delete;
    IntroLevel& operator=(const IntroLevel& _Other) = delete;
    IntroLevel& operator=(IntroLevel&& _Other) noexcept = delete;

protected:
    void Start() override;

    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
    class GameEngineSoundPlayer BGMPlayer;

};

