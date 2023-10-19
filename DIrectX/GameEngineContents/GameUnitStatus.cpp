#include "PreCompile.h"
#include "GameUnitStatus.h"

// Knight
GameUnitStatus GameUnitStatus::KnightStat =
{
    std::string_view("Knight"), // ���� �̸�
    float4{ 74.0f, 0.0f }, // ���ݹ���
    float4{ 200.0f, 0.0f }, // ��ų����
    float4{ 200.0f, 0.0f }, // ��ų����2
    float4{ 200.0f, 0.0f }, //  �ñر� ����
    100.0f,                 // UnitSpeed ���ǵ�
    200.0f,                 // UnitHP 
    200.0f,                 // UnitMaxHP
    60.0f,                  // UnitDef
    60.0f,                  //_UnitAbsoluteDef
    33.0f,                  // _UnitAtt
    1.7f,                   //_AttackSpeed
    4.2f,                   //_SkillCooltime
    20.0f,                   //_UltCooltime
    std::string_view("��� �� ������ ���� �ð����� �����Ͽ� �ش� ���� ���� ����� �ڽ����� ����ϴ�."),
    std::string_view("���� �ð����� �Ʊ� ����� ������ �ڽ��� ���� ��ŭ ��½�ŵ�ϴ�.")
};

// ArcherStat
GameUnitStatus GameUnitStatus::ArcherStat
{
    std::string_view("Archer"), // ���� �̸�
    float4{ 250.0f, 0.0f }, // ���ݹ���
    float4{ 50.0f, 0.0f }, // ��ų����
    float4{ 50.0f, 0.0f }, // ��ų����2
    float4{ 700.0f, 0.0f }, //  �ñر� ����
    60.0f,                 // UnitSpeed ���ǵ�
    80.0f,                 // UnitHP 
    80.0f,                 // UnitMaxHP
    5.0f,                  // UnitDef
    5.0f,                  //_UnitAbsoluteDef
    65.0f,                  // _UnitAtt
    1.5f,                   //_AttackSpeed
    3.0f,                   //_SkillCooltime
    25.0f,                   //_UltCooltime
    std::string_view("������ ��󿡰� ȭ���� �߻��ϸ� �ڷ� �� ��¦ �������ϴ�."),
    std::string_view("������ ���鿡�� ������ ȭ���� �����մϴ�.")
};

GameUnitStatus GameUnitStatus::MonkStat
{
    std::string_view("Monk"), // ���� �̸�
    float4{ 70.0f, 0.0f }, // ���ݹ���
    float4{ 200.0f, 0.0f }, // ��ų����
    float4{ 200.0f, 0.0f }, // ��ų����2
    float4{ 300.0f, 0.0f }, //  �ñر� ����
    100.0f,                 // UnitSpeed ���ǵ�
    210.0f,                 // UnitHP 
    210.0f,                 // UnitMaxHP
    40.0f,                  // UnitDef
    40.0f,                  //_UnitAbsoluteDef
    32.0f,                  // _UnitAtt
    1.4f,                   //_AttackSpeed
    5.4f,                   //_SkillCooltime
    30.0f ,                  //_UltCooltime
    std::string_view("�Ʊ��� ü���� ������ ȸ���մϴ�."),
    std::string_view("�ֺ� ���� ���� �Ʊ����� ����ȿ���� �ִ� ��ȣ���� �ο��մϴ�.")
};

GameUnitStatus GameUnitStatus::NinjaStat
{
    std::string_view("Ninja"), // ���� �̸�
    float4{ 70.0f, 0.0f }, // ���ݹ���
    float4{ 600.0f, 0.0f }, // ��ų����
    float4{ 600.0f, 0.0f }, // ��ų����2
    float4{ 700.0f, 0.0f }, //  �ñر� ����
    150.0f,                 // UnitSpeed ���ǵ�
    120.0f,                 // UnitHP 
    120.0f,                 // UnitMaxHP
    10.0f,                  // UnitDef
    10.0f,                  //_UnitAbsoluteDef
    32.0f,                  // _UnitAtt
    1.1f,                   //_AttackSpeed
    3.0f,                   //_SkillCooltime
    20.0f,                   //_UltCooltime
    std::string_view("�� �Ĺ����� �����̵� �Ͽ� ���� ������ ���մϴ�."),
    std::string_view("���������� ü���� �Ҹ�Ǵ� �н��� ��ȯ�մϴ�.")
};

GameUnitStatus GameUnitStatus::PythonessStat
{
    std::string_view("Pythoness"), // ���� �̸�
    float4{ 300.0f, 0.0f }, // ���ݹ���
    float4{ 400.0f, 0.0f }, // ��ų����
    float4{ 400.0f, 0.0f }, // ��ų����2
    float4{ 500.0f, 0.0f }, //  �ñر� ����
    60.0f,                 // UnitSpeed ���ǵ�
    65.0f,                 // UnitHP 
    65.0f,                 // UnitMaxHP
    3.0f,                  // UnitDef
    3.0f,                  //_UnitAbsoluteDef
    30.0f,                  // _UnitAtt
    1.1f,                   //_AttackSpeed
    6.5f,                   //_SkillCooltime
    24.0f ,                  //_UltCooltime
    std::string_view("�Ʊ� �Ѹ��� ü���� ȸ���ϰ� �ش� �Ʊ� �ֺ��� ������ ���ظ� �ִ� ������ �����մϴ�."),
    std::string_view("�Ʊ��� ȸ����Ű�ų� ������ �����ϴ� ��ȥ�� �����ϴ� ���� ��ȯ�մϴ�.")
};

GameUnitStatus GameUnitStatus::PyromancerStat
{
    std::string_view("Pyromancer"), // ���� �̸�
    float4{ 200.0f, 0.0f }, // ���ݹ���
    float4{ 300.0f, 0.0f }, // ��ų����
    float4{ 300.0f, 0.0f }, // ��ų����2
    float4{ 400.0f, 0.0f }, //  �ñر� ����
    60.0f,                 // UnitSpeed ���ǵ�
    80.0f,                 // UnitHP 
    80.0f,                 // UnitMaxHP
    3.0f,                  // UnitDef
    3.0f,                  //_UnitAbsoluteDef
    40.0f,                  // _UnitAtt
    2.0f,                   //_AttackSpeed
    6.5f,                   //_SkillCooltime
    32.0f        ,           //_UltCooltime
    std::string_view("������ �����ϴ� ȭ�� ������ ��ȯ�մϴ�."),
    std::string_view("�ֺ� ���� ������ ���������� ������ ���ϴ� ������ �����մϴ�.")
};

GameUnitStatus GameUnitStatus::PriestStat
{
    std::string_view("Priest"), // ���� �̸�
    float4{ 260.0f, 0.0f }, // ���ݹ���
    float4{ 400.0f, 0.0f }, // ��ų����
    float4{ 400.0f, 0.0f }, // ��ų����2
    float4{ 600.0f, 0.0f }, //  �ñر� ����
    60.0f,                 // UnitSpeed ���ǵ�
    65.0f,                 // UnitHP 
    65.0f,                 // UnitMaxHP
    3.0f,                  // UnitDef
    3.0f,                  //_UnitAbsoluteDef
    45.0f,                  // _UnitAtt
    1.4f,                   //_AttackSpeed
    7.0f,                   //_SkillCooltime
    30.0f   ,                //_UltCooltime
    std::string_view("�Ϲݰ����� �Ʊ��� ȸ���ϸ� ��ų ���� ���� �� ���� ȸ���� �մϴ�."),
    std::string_view("�ֺ� ���� ������ ���������� ü���� ȸ����Ű�� ������ �����մϴ�.")
};

GameUnitStatus GameUnitStatus::SwordmanStat
{
    std::string_view("Swordman"), // ���� �̸�
    float4{ 90.0f, 0.0f }, // ���ݹ���
    float4{ 80.0f, 0.0f }, // ��ų����
    float4{ 100.0f, 0.0f }, // ��ų����2
    float4{ 500.0f, 0.0f }, //  �ñر� ����
    120.0f,                 // UnitSpeed ���ǵ�
    130.0f,                 // UnitHP 
    130.0f,                 // UnitMaxHP
    30.0f,                  // UnitDef
    30.0f,                  //_UnitAbsoluteDef
    24.0f,                  // _UnitAtt
    1.25f,                   //_AttackSpeed
    3.8f,                   //_SkillCooltime
    25.0f    ,               //_UltCooltime
    std::string_view("3���� ���� ������ �����մϴ�."),
    std::string_view("���������� ������ �̵��ϸ� ��λ� �ִ� ��� ���� ��������ϴ�.")
};


GameUnitStatus::GameUnitStatus()
{

}

GameUnitStatus::~GameUnitStatus()
{

}
