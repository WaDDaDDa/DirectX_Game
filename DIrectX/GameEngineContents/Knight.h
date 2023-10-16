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

    void CreateUltEffect();

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

