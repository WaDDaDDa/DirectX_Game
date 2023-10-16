#include "PreCompile.h"
#include "PyromancerStatus.h"

PyromancerStatus PyromancerStatus::PyromancerStat;

PyromancerStatus::PyromancerStatus()
{
    UnitName = "Pyromancer";
    AttackRange = PyromancerAttackRange;
    SkillRange = PyromancerSkillRange;
    SkillColRange = PyromancerSkillColRange;
    UltRange = PyromancerUltRange;

    UnitSpeed = PyromancerSpeed;
    UnitHP = PyromancerHp;
    UnitMaxHP = PyromancerHp;
    UnitAtt = PyromancerAtt;
    UnitDef = PyromancerDef;
    UnitAbsoluteDef = PyromancerAbsoluteDef;

    AttackSpeed = PyromancerAttackSpeed;

    SkillCooltime = PyromancerSkillCooltime;

    UltCooltime = PyromancerUltCooltime;
}

PyromancerStatus::~PyromancerStatus()
{

}

