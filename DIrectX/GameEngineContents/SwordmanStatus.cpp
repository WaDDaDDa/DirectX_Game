#include "PreCompile.h"
#include "SwordmanStatus.h"

SwordmanStatus SwordmanStatus::SwordmanStat;

SwordmanStatus::SwordmanStatus()
{
    UnitName = "Swordman";
    AttackRange = SwordmanAttackRange;
    SkillRange = SwordmanSkillRange;
    SkillColRange = SwordmanSkillColRange;
    UltRange = SwordmanUltRange;

    UnitSpeed = SwordmanSpeed;
    UnitHP = SwordmanHp;
    UnitMaxHP = SwordmanHp;
    UnitAtt = SwordmanAtt;
    UnitDef = SwordmanDef;
    UnitAbsoluteDef = SwordmanAbsoluteDef;

    AttackSpeed = SwordmanAttackSpeed;

    SkillCooltime = SwordmanSkillCooltime;

    UltCooltime = SwordmanUltCooltime;
}

SwordmanStatus::~SwordmanStatus()
{

}

