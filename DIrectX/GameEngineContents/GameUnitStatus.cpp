#include "PreCompile.h"
#include "GameUnitStatus.h"

// Knight
GameUnitStatus GameUnitStatus::KnightStat =
{
    std::string_view("Knight"), // 유닛 이름
    float4{ 74.0f, 0.0f }, // 공격범위
    float4{ 200.0f, 0.0f }, // 스킬범위
    float4{ 200.0f, 0.0f }, // 스킬범위2
    float4{ 200.0f, 0.0f }, //  궁극기 범위
    100.0f,                 // UnitSpeed 스피드
    200.0f,                 // UnitHP 
    200.0f,                 // UnitMaxHP
    60.0f,                  // UnitDef
    60.0f,                  //_UnitAbsoluteDef
    33.0f,                  // _UnitAtt
    1.7f,                   //_AttackSpeed
    4.2f,                   //_SkillCooltime
    20.0f                   //_UltCooltime
};

// ArcherStat
GameUnitStatus GameUnitStatus::ArcherStat
{
    std::string_view("Archer"), // 유닛 이름
    float4{ 250.0f, 0.0f }, // 공격범위
    float4{ 50.0f, 0.0f }, // 스킬범위
    float4{ 50.0f, 0.0f }, // 스킬범위2
    float4{ 700.0f, 0.0f }, //  궁극기 범위
    60.0f,                 // UnitSpeed 스피드
    80.0f,                 // UnitHP 
    80.0f,                 // UnitMaxHP
    5.0f,                  // UnitDef
    5.0f,                  //_UnitAbsoluteDef
    65.0f,                  // _UnitAtt
    1.5f,                   //_AttackSpeed
    3.0f,                   //_SkillCooltime
    25.0f                   //_UltCooltime
};

GameUnitStatus GameUnitStatus::MonkStat
{
    std::string_view("Monk"), // 유닛 이름
    float4{ 70.0f, 0.0f }, // 공격범위
    float4{ 200.0f, 0.0f }, // 스킬범위
    float4{ 200.0f, 0.0f }, // 스킬범위2
    float4{ 300.0f, 0.0f }, //  궁극기 범위
    100.0f,                 // UnitSpeed 스피드
    210.0f,                 // UnitHP 
    210.0f,                 // UnitMaxHP
    40.0f,                  // UnitDef
    40.0f,                  //_UnitAbsoluteDef
    32.0f,                  // _UnitAtt
    1.4f,                   //_AttackSpeed
    5.4f,                   //_SkillCooltime
    30.0f                   //_UltCooltime
};

GameUnitStatus GameUnitStatus::NinjaStat
{
    std::string_view("Ninja"), // 유닛 이름
    float4{ 70.0f, 0.0f }, // 공격범위
    float4{ 600.0f, 0.0f }, // 스킬범위
    float4{ 600.0f, 0.0f }, // 스킬범위2
    float4{ 700.0f, 0.0f }, //  궁극기 범위
    150.0f,                 // UnitSpeed 스피드
    120.0f,                 // UnitHP 
    120.0f,                 // UnitMaxHP
    10.0f,                  // UnitDef
    10.0f,                  //_UnitAbsoluteDef
    32.0f,                  // _UnitAtt
    1.1f,                   //_AttackSpeed
    3.0f,                   //_SkillCooltime
    20.0f                   //_UltCooltime
};

GameUnitStatus GameUnitStatus::PythonessStat
{
    std::string_view("Pythoness"), // 유닛 이름
    float4{ 300.0f, 0.0f }, // 공격범위
    float4{ 400.0f, 0.0f }, // 스킬범위
    float4{ 400.0f, 0.0f }, // 스킬범위2
    float4{ 500.0f, 0.0f }, //  궁극기 범위
    60.0f,                 // UnitSpeed 스피드
    65.0f,                 // UnitHP 
    65.0f,                 // UnitMaxHP
    3.0f,                  // UnitDef
    3.0f,                  //_UnitAbsoluteDef
    30.0f,                  // _UnitAtt
    1.1f,                   //_AttackSpeed
    6.5f,                   //_SkillCooltime
    24.0f                   //_UltCooltime
};

GameUnitStatus GameUnitStatus::PyromancerStat
{
    std::string_view("Pyromancer"), // 유닛 이름
    float4{ 200.0f, 0.0f }, // 공격범위
    float4{ 200.0f, 0.0f }, // 스킬범위
    float4{ 200.0f, 0.0f }, // 스킬범위2
    float4{ 400.0f, 0.0f }, //  궁극기 범위
    60.0f,                 // UnitSpeed 스피드
    80.0f,                 // UnitHP 
    80.0f,                 // UnitMaxHP
    3.0f,                  // UnitDef
    3.0f,                  //_UnitAbsoluteDef
    40.0f,                  // _UnitAtt
    2.0f,                   //_AttackSpeed
    6.5f,                   //_SkillCooltime
    32.0f                   //_UltCooltime
};

GameUnitStatus GameUnitStatus::PriestStat
{
    std::string_view("Priest"), // 유닛 이름
    float4{ 260.0f, 0.0f }, // 공격범위
    float4{ 400.0f, 0.0f }, // 스킬범위
    float4{ 400.0f, 0.0f }, // 스킬범위2
    float4{ 600.0f, 0.0f }, //  궁극기 범위
    60.0f,                 // UnitSpeed 스피드
    65.0f,                 // UnitHP 
    65.0f,                 // UnitMaxHP
    3.0f,                  // UnitDef
    3.0f,                  //_UnitAbsoluteDef
    45.0f,                  // _UnitAtt
    1.4f,                   //_AttackSpeed
    7.0f,                   //_SkillCooltime
    30.0f                   //_UltCooltime
};

GameUnitStatus GameUnitStatus::SwordmanStat
{
    std::string_view("Swordman"), // 유닛 이름
    float4{ 90.0f, 0.0f }, // 공격범위
    float4{ 80.0f, 0.0f }, // 스킬범위
    float4{ 100.0f, 0.0f }, // 스킬범위2
    float4{ 500.0f, 0.0f }, //  궁극기 범위
    120.0f,                 // UnitSpeed 스피드
    130.0f,                 // UnitHP 
    130.0f,                 // UnitMaxHP
    30.0f,                  // UnitDef
    30.0f,                  //_UnitAbsoluteDef
    24.0f,                  // _UnitAtt
    1.25f,                   //_AttackSpeed
    3.8f,                   //_SkillCooltime
    25.0f                   //_UltCooltime
};


GameUnitStatus::GameUnitStatus()
{

}

GameUnitStatus::~GameUnitStatus()
{

}
