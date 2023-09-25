#pragma once
#include "GameUnit.h"

class Ninja : public GameUnit
{
public:
    Ninja();
    ~Ninja();

    Ninja(const Ninja& _Other) = delete;
    Ninja(Ninja&& _Other) noexcept = delete;
    Ninja& operator=(const Ninja& _Other) = delete;
    Ninja& operator=(Ninja&& _Other) noexcept = delete;

    void SetUnitStatus()
    {
        UnitName = "Ninja";
        AttackRange = NinjaAttackRange;
        SkillRange = NinjaSkillRange;
        UltRange = NinjaUltRange;

        UnitSpeed = NinjaSpeed;
        UnitHP = NinjaHp;
        UnitMaxHP = NinjaHp;
        UnitAtt = NinjaAtt;
        UnitDef = NinjaDef;
        UnitAbsoluteDef = NinjaAbsoluteDef;

        AttackDelay = NinjaAttackSpeed;

        SkillCooltime = NinjaSkillCooltime;

        UltCooltime = NinjaUltCooltime;
    }

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

    void Skill2Start() override;
    void Skill2Update(float _Delta) override;

    void UltStart() override;
    void UltUpdate(float _Delta) override;

    void DiePrevStart() override;

private:
    float4 NinjaAttackRange = { 37.0f, 0.0f };
    float4 NinjaSkillRange = { 200.0f, 0.0f };
    float4 NinjaUltRange = { 200.0f, 0.0f };

    float NinjaSpeed = 80.0f;
    float NinjaHp = 1000.0f;
    float NinjaAtt = 150.0f;
    float NinjaDef = 20.0f;
    float NinjaAbsoluteDef = 20.0f;
    float NinjaAttackSpeed = 1.7f;
    float NinjaSkillCooltime = 4.2f;
    float NinjaUltCooltime = 5.0f;

    float SkillTick = 1.0f;
    float SkillDamageDeley = 0.1f;
};

