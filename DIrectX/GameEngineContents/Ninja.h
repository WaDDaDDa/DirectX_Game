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



protected:
    void Start() override;
    // void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;

    virtual void SpwanStart() override;

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
    int SkillTick = 1;
    float SkillDamageDeley = 0.1f;
};

