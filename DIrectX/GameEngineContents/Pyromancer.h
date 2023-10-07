#pragma once
#include "GameUnit.h"

class Pyromancer : public GameUnit
{
public:
    Pyromancer();
    ~Pyromancer();

    Pyromancer(const Pyromancer& _Other) = delete;
    Pyromancer(Pyromancer&& _Other) noexcept = delete;
    Pyromancer& operator=(const Pyromancer& _Other) = delete;
    Pyromancer& operator=(Pyromancer&& _Other) noexcept = delete;

    void SetUnitStatus()
    {
        UnitName = "Pyromancer";
        AttackRange = PyromancerAttackRange;
        SkillRange = PyromancerSkillRange;
        SkillColRange = PyromancerSkillColRange;
        UltRange = PyromancerUltRange;

        UnitSpeed = PyromancerSpeed;
        UnitHP = PyromancerHp;
        UnitMaxHP = PyromancerHp;
        UnitAtt = PyromancerAtt;
        UnitDef = PyromancerDef;
        UnitAbsoluteDef = PyromancerAbsoluteDef;

        AttackSpeed = PyromancerAttackSpeed;

        SkillCooltime = PyromancerSkillCooltime;

        UltCooltime = PyromancerUltCooltime;
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
    float PyromancerUltCooltime = 10.0f;

    float PyromancerUltInter = 0.05f;

};

