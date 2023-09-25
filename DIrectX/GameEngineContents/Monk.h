#pragma once
#include "GameUnit.h"

class Monk : public GameUnit
{
public:
    Monk();
    ~Monk();

    Monk(const Monk& _Other) = delete;
    Monk(Monk&& _Other) noexcept = delete;
    Monk& operator=(const Monk& _Other) = delete;
    Monk& operator=(Monk&& _Other) noexcept = delete;

    void SetUnitStatus()
    {
        UnitName = "Monk";
        AttackRange = MonkAttackRange;
        SkillRange = MonkSkillRange;
        UltRange = MonkUltRange;

        UnitSpeed = MonkSpeed;
        UnitHP = MonkHp;
        UnitMaxHP = MonkHp;
        UnitAtt = MonkAtt;
        UnitDef = MonkDef;
        UnitAbsoluteDef = MonkAbsoluteDef;

        AttackDelay = MonkAttackSpeed;

        SkillCooltime = MonkSkillCooltime;

        UltCooltime = MonkUltCooltime;
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

    void UltStart() override;
    void UltUpdate(float _Delta) override;

    void DiePrevStart() override;

private:
    float4 MonkAttackRange = { 37.0f, 0.0f };
    float4 MonkSkillRange = { 200.0f, 0.0f };
    float4 MonkUltRange = { 200.0f, 0.0f };

    float MonkSpeed = 80.0f;
    float MonkHp = 1000.0f;
    float MonkAtt = 150.0f;
    float MonkDef = 20.0f;
    float MonkAbsoluteDef = 20.0f;
    float MonkAttackSpeed = 1.7f;
    float MonkSkillCooltime = 4.2f;
    float MonkUltCooltime = 5.0f;
};

