#pragma once

class GameUnitStatus
{
public:
    GameUnitStatus();
    ~GameUnitStatus();

    GameUnitStatus(const GameUnitStatus& _Other) = delete;
    GameUnitStatus(GameUnitStatus&& _Other) noexcept = delete;
    GameUnitStatus& operator=(const GameUnitStatus& _Other) = delete;
    GameUnitStatus& operator=(GameUnitStatus&& _Other) noexcept = delete;

    std::string_view UnitName = "";
    float4 AttackRange;
    float4 SkillRange;
    float4 SkillColRange;
    float4 UltRange;
    float UnitSpeed;
    float UnitHP;
    float UnitMaxHP;
    float UnitDef;
    float UnitAbsoluteDef;
    float UnitAtt;
    float AttackSpeed;
    float SkillCooltime;
    float UltCooltime;

protected:

private:

};

