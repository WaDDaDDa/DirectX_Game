#pragma once
#include "GameUnit.h"

class Swordman : public GameUnit
{
public:
    Swordman();
    ~Swordman();

    Swordman(const Swordman& _Other) = delete;
    Swordman(Swordman&& _Other) noexcept = delete;
    Swordman& operator=(const Swordman& _Other) = delete;
    Swordman& operator=(Swordman&& _Other) noexcept = delete;

protected:
    void Start() override;
    // void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;

    bool UltCheck() override;

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
    float SkillTick = 3.0f;
    float SkillDamageDeley = 0.1f;

    bool SwordUlt = false;
};

