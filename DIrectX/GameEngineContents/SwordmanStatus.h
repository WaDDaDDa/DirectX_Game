#pragma once
#include "GameUnitStatus.h"

class SwordmanStatus : public GameUnitStatus
{
public:
    SwordmanStatus();
    ~SwordmanStatus();

    SwordmanStatus(const SwordmanStatus& _Other) = delete;
    SwordmanStatus(SwordmanStatus&& _Other) noexcept = delete;
    SwordmanStatus& operator=(const SwordmanStatus& _Other) = delete;
    SwordmanStatus& operator=(SwordmanStatus&& _Other) noexcept = delete;

    static SwordmanStatus SwordmanStat;

protected:

private:
    float4 SwordmanAttackRange = { 90.0f, 0.0f };
    float4 SwordmanSkillRange = { 80.0f, 0.0f };
    float4 SwordmanSkillColRange = { 100.0f, 0.0f };
    float4 SwordmanUltRange = { 500.0f, 0.0f };

    float SwordmanSpeed = 120.0f;
    float SwordmanHp = 130.0f;
    float SwordmanAtt = 24.0f;
    float SwordmanDef = 30.0f;
    float SwordmanAbsoluteDef = 30.0f;
    float SwordmanAttackSpeed = 1.25f;
    float SwordmanSkillCooltime = 3.8f;
    float SwordmanUltCooltime = 25.0f;
};

