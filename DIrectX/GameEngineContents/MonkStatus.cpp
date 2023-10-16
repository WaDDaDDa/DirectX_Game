#include "PreCompile.h"
#include "MonkStatus.h"

MonkStatus MonkStatus::MonkStat;


MonkStatus::MonkStatus()
{
    UnitName = "Monk";
    AttackRange = MonkAttackRange;
    SkillRange = MonkSkillRange;
    SkillColRange = MonkSkillColRange;
    UltRange = MonkUltRange;

    UnitSpeed = MonkSpeed;
    UnitHP = MonkHp;
    UnitMaxHP = MonkHp;
    UnitAtt = MonkAtt;
    UnitDef = MonkDef;
    UnitAbsoluteDef = MonkAbsoluteDef;

    AttackSpeed = MonkAttackSpeed;

    SkillCooltime = MonkSkillCooltime;

    UltCooltime = MonkUltCooltime;
}

MonkStatus::~MonkStatus()
{

}

