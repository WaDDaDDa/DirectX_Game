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


protected:
    void Start() override;
    // void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;

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
 

};

