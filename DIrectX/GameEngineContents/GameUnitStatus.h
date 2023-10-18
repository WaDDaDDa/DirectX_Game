#pragma once

class GameUnitStatus
{
public:
    GameUnitStatus();
    ~GameUnitStatus();

    GameUnitStatus(
        std::string_view _Name,
        float4 _AttRange,
        float4 _SkillRange,
        float4 _SkillColRange,
        float4 _UltRange,
        float _UnitSpeed,
        float _UnitHP,
        float _UnitMaxHP,
        float _UnitDef,
        float _UnitAbsoluteDef,
        float _UnitAtt,
        float _AttackSpeed,
        float _SkillCooltime,
        float _UltCooltime
    )
        : UnitName(_Name), AttackRange(_AttRange), SkillRange(_SkillRange), SkillColRange(_SkillColRange),
        UltRange(_UltRange), UnitSpeed(_UnitSpeed), UnitHP(_UnitHP), UnitMaxHP(_UnitMaxHP),
        UnitDef(_UnitDef),
        UnitAbsoluteDef(_UnitAbsoluteDef), UnitAtt(_UnitAtt), AttackSpeed(_AttackSpeed),
        SkillCooltime(_SkillCooltime), UltCooltime(_UltCooltime)
    {

    }
   // GameUnitStatus(const GameUnitStatus& _Other) = delete;
  //  GameUnitStatus(GameUnitStatus&& _Other) noexcept = delete;
   // GameUnitStatus& operator=(const GameUnitStatus& _Other) = delete;
   // GameUnitStatus& operator=(GameUnitStatus&& _Other) noexcept = delete;
    std::string_view UnitName = "";
    float4 AttackRange = float4::ZERO;
    float4 SkillRange = float4::ZERO;
    float4 SkillColRange = float4::ZERO;
    float4 UltRange = float4::ZERO;
    float UnitSpeed = 0.0f;
    float UnitHP = 0.0f;
    float UnitMaxHP = 0.0f;
    float UnitDef = 0.0f;
    float UnitAbsoluteDef = 0.0f;
    float UnitAtt = 0.0f;
    float AttackSpeed = 0.0f;
    float SkillCooltime = 0.0f;
    float UltCooltime = 0.0f;

    static GameUnitStatus KnightStat;
    static GameUnitStatus ArcherStat;
    static GameUnitStatus MonkStat;
    static GameUnitStatus NinjaStat;
    static GameUnitStatus PythonessStat;
    static GameUnitStatus PyromancerStat;
    static GameUnitStatus PriestStat;
    static GameUnitStatus SwordmanStat;

protected:

private:

};

