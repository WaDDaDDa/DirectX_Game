#pragma once
#include "GameUnit.h"

class Archer : public GameUnit
{
public:
    Archer();
    ~Archer();

    Archer(const Archer& _Other) = delete;
    Archer(Archer&& _Other) noexcept = delete;
    Archer& operator=(const Archer& _Other) = delete;
    Archer& operator=(Archer&& _Other) noexcept = delete;

    void SetUnitStatus()
    {
        UnitName = "Archer";
        AttackRange = ArcherAttackRange;
        SkillRange = ArcherSkillRange;
        SkillColRange = ArcherSkillColRange;
        UltRange = ArcherUltRange;

        UnitSpeed = ArcherSpeed;
        UnitHP = ArcherHp;
        UnitMaxHP = ArcherHp;
        UnitAtt = ArcherAtt;
        UnitDef = ArcherDef;
        UnitAbsoluteDef = ArcherAbsoluteDef;

        AttackSpeed = ArcherAttackSpeed;

        SkillCooltime = ArcherSkillCooltime;

        UltCooltime = ArcherUltCooltime;
    }


protected:
    void Start() override;
    // void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;

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

    float ArcherUltInter = 0.1f;

};

