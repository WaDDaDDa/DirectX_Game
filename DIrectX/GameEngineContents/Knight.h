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
        AttackRange = KnightAttackRange;
        SkillRange = KnightSkillRange;
        UltRange = KnightUltRange;

        UnitSpeed = KnightSpeed;
        UnitHP = KnightHp;
        UnitDef = KnightDef;

        AttackDelay = KnightAttackDeley;

        SkillCooltime = KnightSkillCooltime;

        UltCooltime = KnightUltCooltime;
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

    void SkillStart() override;
    void SkillUpdate(float _Delta) override;

    void DieStart() override;

private:
    float4 KnightAttackRange = { 55.0f, 55.0f };
    float4 KnightSkillRange = { 55.0f, 55.0f };
    float4 KnightUltRange = { 55.0f, 55.0f };

    float KnightSpeed = 80.0f;
    float KnightHp = 1000.0f;
    float KnightDef = 20.0f;
    float KnightAttackDeley = 3.0f;
    float KnightSkillCooltime = 10.0f;
    float KnightUltCooltime = 30.0f;
};

