#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class AwardsLevel : public GameEngineLevel
{
public:
    AwardsLevel();
    ~AwardsLevel();

    AwardsLevel(const AwardsLevel& _Other) = delete;
    AwardsLevel(AwardsLevel&& _Other) noexcept = delete;
    AwardsLevel& operator=(const AwardsLevel& _Other) = delete;
    AwardsLevel& operator=(AwardsLevel&& _Other) noexcept = delete;

protected:
    void Start() override;

    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;
private:

};

