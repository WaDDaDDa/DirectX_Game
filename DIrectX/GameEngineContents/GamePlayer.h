#pragma once
#include "HouseUnit.h"

class GamePlayer : public HouseUnit
{
public:
    GamePlayer();
    ~GamePlayer();

    GamePlayer(const GamePlayer& _Other) = delete;
    GamePlayer(GamePlayer&& _Other) noexcept = delete;
    GamePlayer& operator=(const GamePlayer& _Other) = delete;
    GamePlayer& operator=(GamePlayer&& _Other) noexcept = delete;

protected:
    void Start() override;
    void LevelStart(GameEngineLevel* _NextLevel) override;
    void Update(float _Delta) override;

private:

};

