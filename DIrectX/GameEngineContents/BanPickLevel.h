#pragma once
#include <GameEngineCore/GameEngineLevel.h>


class BanPickLevel : public GameEngineLevel
{
public:
    BanPickLevel();
    ~BanPickLevel();

    BanPickLevel(const BanPickLevel& _Other) = delete;
    BanPickLevel(BanPickLevel&& _Other) noexcept = delete;
    BanPickLevel& operator=(const BanPickLevel& _Other) = delete;
    BanPickLevel& operator=(BanPickLevel&& _Other) noexcept = delete;

protected:
    void Start() override;

    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:

};

