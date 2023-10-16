#include "PreCompile.h"
#include "ArcherStatus.h"

ArcherStatus ArcherStatus::ArcherStat;


ArcherStatus::ArcherStatus()
{
    UnitName = "Archer";
    AttackRange = ArcherAttackRange;
    SkillRange = ArcherSkillRange;
    SkillColRange = ArcherSkillColRange;
    UltRange = ArcherUltRange;

    UnitSpeed = ArcherSpeed;
    UnitHP = ArcherHp;
    UnitMaxHP = ArcherHp;
    UnitAtt = ArcherAtt;
    UnitDef = ArcherDef;
    UnitAbsoluteDef = ArcherAbsoluteDef;

    AttackSpeed = ArcherAttackSpeed;

    SkillCooltime = ArcherSkillCooltime;

    UltCooltime = ArcherUltCooltime;
}

ArcherStatus::~ArcherStatus()
{

}

