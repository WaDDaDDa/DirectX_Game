#pragma once
#include "GameUnitStatus.h"

class PythonessStatus : public GameUnitStatus
{
public:
    PythonessStatus();
    ~PythonessStatus();

    PythonessStatus(const PythonessStatus& _Other) = delete;
    PythonessStatus(PythonessStatus&& _Other) noexcept = delete;
    PythonessStatus& operator=(const PythonessStatus& _Other) = delete;
    PythonessStatus& operator=(PythonessStatus&& _Other) noexcept = delete;

    static PythonessStatus PythonessStat;

protected:

private:
    float4 PythonessAttackRange = { 300.0f, 0.0f };
    float4 PythonessSkillRange = { 300.0f, 0.0f };
    float4 PythonessSkillColRange = { 300.0f, 0.0f };
    float4 PythonessUltRange = { 500.0f, 0.0f };

    float PythonessSpeed = 60.0f;
    float PythonessHp = 65.0f;
    float PythonessAtt = 30.0f;
    float PythonessDef = 3.0f;
    float PythonessAbsoluteDef = 30.0f;
    float PythonessAttackSpeed = 1.1f;
    float PythonessSkillCooltime = 6.5f;
    float PythonessUltCooltime = 20.0f;
};

