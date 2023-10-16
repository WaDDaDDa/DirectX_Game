#pragma once
#include "GameUnitStatus.h"

class MonkStatus : public GameUnitStatus
{
public:
    MonkStatus();
    ~MonkStatus();

    MonkStatus(const MonkStatus& _Other) = delete;
    MonkStatus(MonkStatus&& _Other) noexcept = delete;
    MonkStatus& operator=(const MonkStatus& _Other) = delete;
    MonkStatus& operator=(MonkStatus&& _Other) noexcept = delete;

    static MonkStatus MonkStat;

protected:

private:

    //Monk
    float4 MonkAttackRange = { 70.0f, 0.0f };
    float4 MonkSkillRange = { 200.0f, 0.0f };
    float4 MonkSkillColRange = { 200.0f, 0.0f };
    float4 MonkUltRange = { 300.0f, 0.0f };
    float MonkSpeed = 100.0f;
    float MonkHp = 210.0f;
    float MonkAtt = 32.0f;
    float MonkDef = 40.0f;
    float MonkAbsoluteDef = 40.0f;
    float MonkAttackSpeed = 1.4f;
    float MonkSkillCooltime = 5.4f;
    float MonkUltCooltime = 30.0f;
};

