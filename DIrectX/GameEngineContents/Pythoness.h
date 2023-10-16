#pragma once
#include "GameUnit.h"

class Pythoness : public GameUnit
{
public:
    Pythoness();
    ~Pythoness();

    Pythoness(const Pythoness& _Other) = delete;
    Pythoness(Pythoness&& _Other) noexcept = delete;
    Pythoness& operator=(const Pythoness& _Other) = delete;
    Pythoness& operator=(Pythoness&& _Other) noexcept = delete;

protected:
    void Start() override;
    // void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    //bool UltCheck() override;

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

    void AttVariableSwitch()
    {
        AttVariable = !AttVariable;
    }

private:


    float PythonessUltInter = 0.05f;

    // true¸é °ø°Ý  false¸é Èú
    bool AttVariable = true;
};

