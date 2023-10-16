#pragma once
#include "GameUnitStatus.h"

class PyromancerStatus : public GameUnitStatus
{
public:
    PyromancerStatus();
    ~PyromancerStatus();

    PyromancerStatus(const PyromancerStatus& _Other) = delete;
    PyromancerStatus(PyromancerStatus&& _Other) noexcept = delete;
    PyromancerStatus& operator=(const PyromancerStatus& _Other) = delete;
    PyromancerStatus& operator=(PyromancerStatus&& _Other) noexcept = delete;

    static PyromancerStatus PyromancerStat;

protected:

private:
    float4 PyromancerAttackRange = { 200.0f, 0.0f };
    float4 PyromancerSkillRange = { 200.0f, 0.0f };
    float4 PyromancerSkillColRange = { 200.0f, 0.0f };
    float4 PyromancerUltRange = { 500.0f, 0.0f };

    float PyromancerSpeed = 60.0f;
    float PyromancerHp = 80.0f;
    float PyromancerAtt = 40.0f;
    float PyromancerDef = 3.0f;
    float PyromancerAbsoluteDef = 30.0f;
    float PyromancerAttackSpeed = 2.0f;
    float PyromancerSkillCooltime = 6.5f;
    float PyromancerUltCooltime = 32.0f;
};

