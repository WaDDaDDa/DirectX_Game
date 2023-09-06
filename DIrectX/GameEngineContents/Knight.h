#pragma once
#include "GameUnit.h"

class Knight : public GameUnit
{
public:
    Knight();
    ~Knight();

    Knight(const Knight& _Other) = delete;
    Knight(Knight&& _Other) noexcept = delete;
    Knight& operator=(const Knight& _Other) = delete;
    Knight& operator=(Knight&& _Other) noexcept = delete;

protected:
    void Start() override;
    // void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    void SpwanStart() override;

    void IdleStart() override;

    void MoveStart() override;

private:

};

