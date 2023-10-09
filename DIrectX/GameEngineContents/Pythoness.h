#pragma once
#include "GameUnit.h"

class Pythoness : public GameUnit
{
public:
    Pythoness();
    ~Pythoness();

    Pythoness(const Pythoness& _Other) = delete;
    Pythoness(Pythoness&& _Other) noexcept = delete;
    Pythoness& operator=(const Pythoness& _Other) = delete;
    Pythoness& operator=(Pythoness&& _Other) noexcept = delete;

    void SetUnitStatus()
    {
        UnitName = "Pythoness";
        AttackRange = PythonessAttackRange;
        SkillRange = PythonessSkillRange;
        SkillColRange = PythonessSkillColRange;
        UltRange = PythonessUltRange;

        UnitSpeed = PythonessSpeed;
        UnitHP = PythonessHp;
        UnitMaxHP = PythonessHp;
        UnitAtt = PythonessAtt;
        UnitDef = PythonessDef;
        UnitAbsoluteDef = PythonessAbsoluteDef;

        AttackSpeed = PythonessAttackSpeed;

        SkillCooltime = PythonessSkillCooltime;

        UltCooltime = PythonessUltCooltime;
    }


protected:
    void Start() override;
    // void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    //bool UltCheck() override;

    void SpwanStart() override;

    void IdleStart() override;

    void MoveStart() override;
    void BackMoveStart() override;

    void SearchMoveStart() override;

    void AttackStart() override;
    void AttackUpdate(float _Delta) override;

    void Attack2Start() override;
    void Attack2Update(float _Delta) override;

    void SkillStart() override;
    void SkillUpdate(float _Delta) override;

    void Skill2Start() override;
    void Skill2Update(float _Delta) override;

    void UltStart() override;
    void UltUpdate(float _Delta) override;

    void Ult2Start() override;
    void Ult2Update(float _Delta) override;

    void DiePrevStart() override;

    void AttVariableSwitch()
    {
        AttVariable = !AttVariable;
    }

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
    float PythonessUltCooltime = 2.0f;
    float PythonessUltInter = 0.05f;

    // true¸é °ø°Ý  false¸é Èú
    bool AttVariable = true;
};

