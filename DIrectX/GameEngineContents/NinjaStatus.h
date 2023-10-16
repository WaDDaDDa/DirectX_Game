#pragma once
#include "GameUnitStatus.h"

class NinjaStatus : public GameUnitStatus
{
public:
    NinjaStatus();
    ~NinjaStatus();

    NinjaStatus(const NinjaStatus& _Other) = delete;
    NinjaStatus(NinjaStatus&& _Other) noexcept = delete;
    NinjaStatus& operator=(const NinjaStatus& _Other) = delete;
    NinjaStatus& operator=(NinjaStatus&& _Other) noexcept = delete;

    static NinjaStatus NinjaStat;

protected:

private:
    // Ninja
    float4 NinjaAttackRange = { 80.0f, 40.0f };
    float4 NinjaSkillRange = { 600.0f, 600.0f };
    float4 NinjaSkillColRange = { 600.0f, 600.0f };
    float4 NinjaUltRange = { 200.0f, 200.0f };

    float NinjaSpeed = 150.0f;
    float NinjaHp = 120.0f;
    float NinjaAtt = 32.0f;
    float NinjaDef = 10.0f;
    float NinjaAbsoluteDef = 10.0f;
    float NinjaAttackSpeed = 1.1f;
    float NinjaSkillCooltime = 3.0f;
    float NinjaUltCooltime = 20.0f;
};

