#pragma once
#include "HouseUnit.h"

class Coach : public HouseUnit
{
public:
    Coach();
    ~Coach();

    Coach(const Coach& _Other) = delete;
    Coach(Coach&& _Other) noexcept = delete;
    Coach& operator=(const Coach& _Other) = delete;
    Coach& operator=(Coach&& _Other) noexcept = delete;

protected:
    void Start() override;
    void LevelStart(GameEngineLevel* _NextLevel) override;
    void Update(float _Delta) override;

private:

};

