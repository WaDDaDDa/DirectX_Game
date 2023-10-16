#pragma once
#include "GameUnitStatus.h"

class PriestStatus : public GameUnitStatus
{
public:
    PriestStatus();
    ~PriestStatus();

    PriestStatus(const PriestStatus& _Other) = delete;
    PriestStatus(PriestStatus&& _Other) noexcept = delete;
    PriestStatus& operator=(const PriestStatus& _Other) = delete;
    PriestStatus& operator=(PriestStatus&& _Other) noexcept = delete;

    static PriestStatus PriestStat;

protected:

private:
    float4 PriestAttackRange = { 260.0f, 0.0f };
    float4 PriestSkillRange = { 300.0f, 0.0f };
    float4 PriestSkillColRange = { 300.0f, 0.0f };
    float4 PriestUltRange = { 600.0f, 0.0f };

    float PriestSpeed = 60.0f;
    float PriestHp = 65.0f;
    float PriestAtt = 45.0f;
    float PriestDef = 3.0f;
    float PriestAbsoluteDef = 3.0f;
    float PriestAttackSpeed = 1.4f;
    float PriestSkillCooltime = 7.0f;
    float PriestUltCooltime = 30.0f;
};

