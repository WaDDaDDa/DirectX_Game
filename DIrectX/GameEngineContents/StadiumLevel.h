#pragma once
#include <GameEngineCore/GameEngineLevel.h>


class StadiumLevel : public GameEngineLevel
{
public:
    StadiumLevel();
    ~StadiumLevel();

    StadiumLevel(const StadiumLevel& _Other) = delete;
    StadiumLevel(StadiumLevel&& _Other) noexcept = delete;
    StadiumLevel& operator=(const StadiumLevel& _Other) = delete;
    StadiumLevel& operator=(StadiumLevel&& _Other) noexcept = delete;

protected:
    void Start() override;

    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    std::shared_ptr<class FadeEffect> FadeInEffect = nullptr;

private:

};

