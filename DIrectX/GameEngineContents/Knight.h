#pragma once
#include "GameUnit.h"

class Knight : public GameUnit
{
public:
    Knight();
    ~Knight();

    Knight(const Knight& _Other) = delete;
    Knight(Knight&& _Other) noexcept = delete;
    Knight& operator=(const Knight& _Other) = delete;
    Knight& operator=(Knight&& _Other) noexcept = delete;

    void SetUnitStatus()
    {
        UnitName = "Knight";
        AttackRange = KnightAttackRange;
        SkillRange = KnightSkillRange;
        UltRange = KnightUltRange;

        UnitSpeed = KnightSpeed;
        UnitHP = KnightHp;
        UnitMaxHP = KnightHp;
        UnitAtt = KnightAtt;
        UnitDef = KnightDef;
        UnitAbsoluteDef = KnightAbsoluteDef;

        AttackDelay = KnightAttackSpeed;

        SkillCooltime = KnightSkillCooltime;

        UltCooltime = KnightUltCooltime;
    }

    void CreateUltEffect();


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
    float4 KnightAttackRange = { 37.0f, 0.0f };
    float4 KnightSkillRange = { 200.0f, 0.0f };
    float4 KnightUltRange = { 200.0f, 0.0f };

    float KnightSpeed = 80.0f;
    float KnightHp = 200.0f;
    float KnightAtt = 21.0f;
    float KnightDef = 60.0f;
    float KnightAbsoluteDef = 60.0f;
    float KnightAttackSpeed = 1.7f;
    float KnightSkillCooltime = 4.2f;
    float KnightUltCooltime = 5.0f;
};

