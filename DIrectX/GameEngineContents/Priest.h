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

    bool AttCheck() override;

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

    void Ult2Start() override;
    void Ult2Update(float _Delta) override;

    void DiePrevStart() override;

private:

};

