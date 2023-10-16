#pragma once
#include "GameUnitStatus.h"

class ArcherStatus : public GameUnitStatus
{
public:
    ArcherStatus();
    ~ArcherStatus();

    ArcherStatus(const ArcherStatus& _Other) = delete;
    ArcherStatus(ArcherStatus&& _Other) noexcept = delete;
    ArcherStatus& operator=(const ArcherStatus& _Other) = delete;
    ArcherStatus& operator=(ArcherStatus&& _Other) noexcept = delete;

    static ArcherStatus ArcherStat;

protected:

private:

    float4 ArcherAttackRange = { 250.0f, 0.0f };
    float4 ArcherSkillRange = { 50.0f, 0.0f };
    float4 ArcherSkillColRange = { 50.0f, 0.0f };
    float4 ArcherUltRange = { 700.0f, 0.0f };
    float ArcherSpeed = 60.0f;
    float ArcherHp = 100.0f;
    float ArcherAtt = 65.0f;
    float ArcherDef = 5.0f;
    float ArcherAbsoluteDef = 30.0f;
    float ArcherAttackSpeed = 1.5f;
    float ArcherSkillCooltime = 3.0f;
    float ArcherUltCooltime = 25.0f;
};

