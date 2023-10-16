#include "PreCompile.h"
#include "NinjaStatus.h"

NinjaStatus NinjaStatus::NinjaStat;


NinjaStatus::NinjaStatus()
{
    UnitName = "Ninja";
    AttackRange = NinjaAttackRange;
    SkillRange = NinjaSkillRange;
    SkillColRange = NinjaSkillColRange;
    UltRange = NinjaUltRange;

    UnitSpeed = NinjaSpeed;
    UnitHP = NinjaHp;
    UnitMaxHP = NinjaHp;
    UnitAtt = NinjaAtt;
    UnitDef = NinjaDef;
    UnitAbsoluteDef = NinjaAbsoluteDef;

    AttackSpeed = NinjaAttackSpeed;

    SkillCooltime = NinjaSkillCooltime;

    UltCooltime = NinjaUltCooltime;
}

NinjaStatus::~NinjaStatus()
{

}

