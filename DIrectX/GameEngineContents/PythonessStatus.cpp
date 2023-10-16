#include "PreCompile.h"
#include "PythonessStatus.h"

PythonessStatus PythonessStatus::PythonessStat;

PythonessStatus::PythonessStatus()
{
    UnitName = "Pythoness";
    AttackRange = PythonessAttackRange;
    SkillRange = PythonessSkillRange;
    SkillColRange = PythonessSkillColRange;
    UltRange = PythonessUltRange;

    UnitSpeed = PythonessSpeed;
    UnitHP = PythonessHp;
    UnitMaxHP = PythonessHp;
    UnitAtt = PythonessAtt;
    UnitDef = PythonessDef;
    UnitAbsoluteDef = PythonessAbsoluteDef;

    AttackSpeed = PythonessAttackSpeed;

    SkillCooltime = PythonessSkillCooltime;

    UltCooltime = PythonessUltCooltime;
}

PythonessStatus::~PythonessStatus()
{

}

