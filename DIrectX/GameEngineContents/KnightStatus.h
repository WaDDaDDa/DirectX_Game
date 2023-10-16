#pragma once
#include "GameUnitStatus.h"

class KnightStatus : public GameUnitStatus
{
public:
    KnightStatus();
    ~KnightStatus();

    KnightStatus(const KnightStatus& _Other) = delete;
    KnightStatus(KnightStatus&& _Other) noexcept = delete;
    KnightStatus& operator=(const KnightStatus& _Other) = delete;
    KnightStatus& operator=(KnightStatus&& _Other) noexcept = delete;

    static KnightStatus KnightStat;

protected:

private:

    //Knight
    float4 KnightAttackRange = { 74.0f, 0.0f };
    float4 KnightSkillRange = { 200.0f, 0.0f };
    float4 KnightSkillColRange = { 200.0f, 0.0f };
    float4 KnightUltRange = { 200.0f, 0.0f };
    float KnightSpeed = 100.0f;
    float KnightHp = 200.0f;
    float KnightAtt = 33.0f;
    float KnightDef = 60.0f;
    float KnightAbsoluteDef = 60.0f;
    float KnightAttackSpeed = 1.7f;
    float KnightSkillCooltime = 4.2f;
    float KnightUltCooltime = 20.0f;
};

