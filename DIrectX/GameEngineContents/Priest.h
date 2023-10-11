#pragma once
#include "GameUnit.h"

class Priest : public GameUnit
{
public:
    Priest();
    ~Priest();

    Priest(const Priest& _Other) = delete;
    Priest(Priest&& _Other) noexcept = delete;
    Priest& operator=(const Priest& _Other) = delete;
    Priest& operator=(Priest&& _Other) noexcept = delete;

    void SetUnitStatus()
    {
        UnitName = "Priest";
        AttackRange = PriestAttackRange;
        SkillRange = PriestSkillRange;
        SkillColRange = PriestSkillColRange;
        UltRange = PriestUltRange;

        UnitSpeed = PriestSpeed;
        UnitHP = PriestHp;
        UnitMaxHP = PriestHp;
        UnitAtt = PriestAtt;
        UnitDef = PriestDef;
        UnitAbsoluteDef = PriestAbsoluteDef;

        AttackSpeed = PriestAttackSpeed;

        SkillCooltime = PriestSkillCooltime;

        UltCooltime = PriestUltCooltime;
    }

    bool AttCheck() override;

protected:
    void Start() override;
    // void Update(float _Delta) override;
    
    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

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

    void UltStart() override;
    void UltUpdate(float _Delta) override;

    void Ult2Start() override;
    void Ult2Update(float _Delta) override;

    void DiePrevStart() override;

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

