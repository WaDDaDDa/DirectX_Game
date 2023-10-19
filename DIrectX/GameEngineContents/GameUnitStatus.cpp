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
    20.0f,                   //_UltCooltime
    std::string_view("모든 적 유닛을 일정 시간동안 도발하여 해당 적의 공격 대상을 자신으로 만듭니다."),
    std::string_view("일정 시간동안 아군 모두의 방어력을 자신의 방어력 만큼 상승시킵니다.")
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
    25.0f,                   //_UltCooltime
    std::string_view("근접한 대상에게 화살을 발사하며 뒤로 한 발짝 물러납니다."),
    std::string_view("무작위 적들에게 빠르게 화살을 연사합니다.")
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
    30.0f ,                  //_UltCooltime
    std::string_view("아군의 체력을 일정량 회복합니다."),
    std::string_view("주변 일정 범위 아군에게 무적효과가 있는 보호막을 부여합니다.")
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
    20.0f,                   //_UltCooltime
    std::string_view("적 후방으로 순간이동 하여 강한 공격을 가합니다."),
    std::string_view("지속적으로 체력이 소모되는 분신을 소환합니다.")
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
    24.0f ,                  //_UltCooltime
    std::string_view("아군 한명의 체력을 회복하고 해당 아군 주변에 범위에 피해를 주는 폭발을 생성합니다."),
    std::string_view("아군을 회복시키거나 적군을 공격하는 영혼을 방출하는 문을 소환합니다.")
};

GameUnitStatus GameUnitStatus::PyromancerStat
{
    std::string_view("Pyromancer"), // 유닛 이름
    float4{ 200.0f, 0.0f }, // 공격범위
    float4{ 300.0f, 0.0f }, // 스킬범위
    float4{ 300.0f, 0.0f }, // 스킬범위2
    float4{ 400.0f, 0.0f }, //  궁극기 범위
    60.0f,                 // UnitSpeed 스피드
    80.0f,                 // UnitHP 
    80.0f,                 // UnitMaxHP
    3.0f,                  // UnitDef
    3.0f,                  //_UnitAbsoluteDef
    40.0f,                  // _UnitAtt
    2.0f,                   //_AttackSpeed
    6.5f,                   //_SkillCooltime
    32.0f        ,           //_UltCooltime
    std::string_view("공격을 보조하는 화염 정령을 소환합니다."),
    std::string_view("주변 일정 범위에 지속적으로 공격을 가하는 영역을 생성합니다.")
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
    30.0f   ,                //_UltCooltime
    std::string_view("일반공격이 아군을 회복하며 스킬 사용시 보다 더 많은 회복을 합니다."),
    std::string_view("주변 일정 범위에 지속적으로 체력을 회복시키는 영역을 생성합니다.")
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
    25.0f    ,               //_UltCooltime
    std::string_view("3연속 베기 공격을 시전합니다."),
    std::string_view("일직선으로 빠르게 이동하며 경로상에 있는 모든 적을 베어버립니다.")
};


GameUnitStatus::GameUnitStatus()
{

}

GameUnitStatus::~GameUnitStatus()
{

}
