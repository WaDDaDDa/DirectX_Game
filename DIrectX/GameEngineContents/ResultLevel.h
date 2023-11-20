#pragma once
#include <GameEngineCore/GameEngineLevel.h>


class ResultLevel : public GameEngineLevel
{
public:
    ResultLevel();
    ~ResultLevel();

    ResultLevel(const ResultLevel& _Other) = delete;
    ResultLevel(ResultLevel&& _Other) noexcept = delete;
    ResultLevel& operator=(const ResultLevel& _Other) = delete;
    ResultLevel& operator=(ResultLevel&& _Other) noexcept = delete;

protected:
    void Start() override;

    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:

};

