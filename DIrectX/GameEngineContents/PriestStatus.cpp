#include "PreCompile.h"
#include "PriestStatus.h"

PriestStatus PriestStatus::PriestStat;


PriestStatus::PriestStatus()
{
    UnitName = "Priest";
    AttackRange = PriestAttackRange;
    SkillRange = PriestSkillRange;
    SkillColRange = PriestSkillColRange;
    UltRange = PriestUltRange;

    UnitSpeed = PriestSpeed;
    UnitHP = PriestHp;
    UnitMaxHP = PriestHp;
    UnitAtt = PriestAtt;
    UnitDef = PriestDef;
    UnitAbsoluteDef = PriestAbsoluteDef;

    AttackSpeed = PriestAttackSpeed;

    SkillCooltime = PriestSkillCooltime;

    UltCooltime = PriestUltCooltime;
}

PriestStatus::~PriestStatus()
{

}

