#include "PreCompile.h"
#include "KnightStatus.h"

KnightStatus KnightStatus::KnightStat;


KnightStatus::KnightStatus()
{
    UnitName = "Knight";
    AttackRange = KnightAttackRange;
    SkillRange = KnightSkillRange;
    SkillColRange = KnightSkillColRange;
    UltRange = KnightUltRange;

    UnitSpeed = KnightSpeed;
    UnitHP = KnightHp;
    UnitMaxHP = KnightHp;
    UnitAtt = KnightAtt;
    UnitDef = KnightDef;
    UnitAbsoluteDef = KnightAbsoluteDef;

    AttackSpeed = KnightAttackSpeed;

    SkillCooltime = KnightSkillCooltime;

    UltCooltime = KnightUltCooltime;
}

KnightStatus::~KnightStatus()
{

}

