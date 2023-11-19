#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
#include "GameUnitStatus.h"
#include "GamePlayer.h"

enum class GameUnitState
{
    Spwan,
    Idle,
    Move,
    BackMove,
    SearchMove,
    CollMove,
    Attack,
    Attack2,
    Skill,
    Skill2,
    Ult,
    Ult2,
    Damage,
    DiePrev,
    Die,
    Max,
};

enum class GameUnitDir
{
    Left,
    Right,

};

class GameUnit : public GameEngineActor
{
public:
    GameUnit();
    ~GameUnit();

    GameUnit(const GameUnit& _Other) = delete;
    GameUnit(GameUnit&& _Other) noexcept = delete;
    GameUnit& operator=(const GameUnit& _Other) = delete;
    GameUnit& operator=(GameUnit&& _Other) noexcept = delete;

    GameUnit* GetPointer()
    {
        return this;
    }

    // �����ֿ��� ���� ���̴� ��� �ϴ°�.
    void EnemyUnitSetting(const std::vector<GameUnit*>& _UnitGroup)
    {
        EnemyGroup = _UnitGroup;
    }

    void TeamUnitSetting(const std::vector<GameUnit*>& _UnitGroup)
    {
        TeamGroup = _UnitGroup;
    }

    void AggroSetting(GameUnit* _Unit)
    {
        AggroUnit = _Unit;
    }

    bool AggroCheck = false;

    void AggroSetting()
    {
        size_t EnemyNum = 0;
        float Pos = 100.0f;

        // �׾����� ���� ���ֵ� �߿��� ����� �������� ��׷� ��´�.
        // ���ֵ��� 100 �������� �ָ������� ��׷� ������ 0���������� �Ѵ�.
        for (size_t i = 0; i < EnemyGroup.size(); i++)
        {
            if (EnemyGroup[i]->GetState() != GameUnitState::Die)
            {
                if (Pos >= (Transform.GetWorldPosition() - EnemyGroup[i]->Transform.GetWorldPosition()).ToABS().X)
                {
                    Pos = (Transform.GetWorldPosition() - EnemyGroup[i]->Transform.GetWorldPosition()).ToABS().X;
                    EnemyNum = i;
                }
            }
        }

        AggroUnit = EnemyGroup[EnemyNum];
        return;
    }

    // �ܼ��ϰ� ����ִ� ���� ���ϸ��� ��׷η� ����.
    // ��׷� Ÿ���� 100 �̳����� �׾����� ���� ��׷� ������ �ܼ��ϰ� ����.
    void NextAggro()
    {
        for (size_t i = 0; i < EnemyGroup.size(); i++)
        {
            if (EnemyGroup[i]->GetState() != GameUnitState::Die)
            {
                AggroUnit = EnemyGroup[i];
                return;
            }
        }
    }

    size_t AggroUnitNum = 0;

    void NextAggroChange()
    {
        AggroUnitNum++;
        if (AggroUnitNum >= EnemyGroup.size())
        {
            AggroUnitNum = 0;
        }

        AggroUnit = EnemyGroup[AggroUnitNum];

        if (AggroUnit->GetState() == GameUnitState::Die || AggroUnit->GetState() == GameUnitState::DiePrev)
        {
            NextAggro();
        }
    }

    bool AllEnemyDieCheck()
    {
        for (size_t i = 0; i < EnemyGroup.size(); i++)
        {
            if (EnemyGroup[i]->GetState() != GameUnitState::Die)
            {
                return false;
            }
        }
        return true;
    }

    GameUnitDir GetDir()
    {
        return Dir;
    }

    void ChangeDir()
    {
        if (Transform.GetWorldPosition().X > AggroUnit->Transform.GetWorldPosition().X)
        {
            ChangeDir(GameUnitDir::Left);
        }
        else if (Transform.GetWorldPosition().X <= AggroUnit->Transform.GetWorldPosition().X)
        {
            ChangeDir(GameUnitDir::Right);
        }
    }

    void ChangeMoveDir()
    {
        if (MoveDir.X < 0.0f)
        {
            ChangeDir(GameUnitDir::Left);
        }
        else if (MoveDir.X > 0.0f)
        {
            ChangeDir(GameUnitDir::Right);
        }
    }

    void ChangeDir(GameUnitDir _Dir)
    {
        if (_Dir != GetDir())
        {
            Transform.AddLocalRotation({ 0.0f, 180.0f });
            Dir = _Dir;
        }
    }

    // ������ �޶�� �ϴ°�,
    // ������ġ.  �ٶ󺸴� ����. �ݸ��� ����. 
    void TeamSet(TeamType _Team);

    // �浹�̺�Ʈ
    EventParameter Event;
    EventParameter MoveEvent;

    float GetUnitAttack()
    {
        return UnitAtt;
    }

    float GetHP()
    {
        return UnitHP;
    }

    float GetHPRate()
    {
        return UnitHP / UnitMaxHP;
    }

    bool Immune = false;

    void DamageHP(float _Value, std::shared_ptr<class GameUnit> _AttUnit)
    {
        if (true == Immune)
        {
            return;
        }

        // ���� ���ݷ¿� ������ ������ �ݿ��ؼ� ����Ų��.
        //float Result = _Value - (UnitDef * 0.4f);
        float DefRate = (UnitDef / (100.0f + UnitDef));
        float Result = _Value - _Value * DefRate;

        if (Result <= 0.0f)
        {
            UnitHP = 0.0f;
            return;
        }

        UnitHP -= Result;
        _AttUnit->AddAttDamage(Result);
        AddDefDamage(Result);

        if (0.0f >= UnitHP)
        {
            _AttUnit->AddKillCount();
        }    

        if (false == DamageCheck)
        {
            DamageCheck = true;
            MainSpriteRenderer->GetColorData().PlusColor += float4::ONENULL;
        }

    }

    void HealHP(float _Value, std::shared_ptr<class GameUnit> _HealUnit)
    {
        float Result = UnitHP + _Value;

        if (Result >= UnitMaxHP)
        {
            Result = UnitMaxHP;
        }

        float Healling = Result - UnitHP;

        _HealUnit->AddHealling(Healling);

        UnitHP = Result;
    }

    // ���� �÷� ȸ����Ű�� �Ұ�.
    bool DamageCheck = false;
    float DamageDelta = 0.0f;


    void AddDef(float _Value)
    {
        UnitDef += _Value;
    }

    void DefAbsolute()
    {
        UnitDef = UnitAbsoluteDef;
    }

    float GetSkillCooltime()
    {
        return SkillCooltime;
    }

    GameUnitState GetState()
    {
        return State;
    }

    std::string GetUnitName()
    {
        return UnitName.data();
    }

    void AllCollisionOff()
    {
        BodyCol->Off();
        AttackRangeCol->Off();
        SkillRangeCol->Off();
        SkillCol->Off();
        UltRangeCol->Off();
        PushCol->Off();
    }

    void AllCollisionOn()
    {
        BodyCol->On();
        AttackRangeCol->On();
        SkillRangeCol->On();
        SkillCol->On();
        UltRangeCol->On();
        PushCol->On();
    }

    void DieCheck()
    {
        if (true == ImDie)
        {
            AllCollisionOff();
        }
        else if (false == ImDie)
        {
            AllCollisionOn();
        }
    }

    GameUnit* GetAggroUnit()
    {
        return AggroUnit;
    }

    void SetPlayerName(const std::string& _PlayerName)
    {
        PlayerName = _PlayerName;
    }

    void SetPlayerSpec(const GamePlayerInfo& _PlayerSpec)
    {
        PlayerSpec = _PlayerSpec;
    }

    GamePlayerInfo PlayerSpec;
    std::string PlayerName = "Faker";
    TeamType MyTeam = TeamType::Blue;
    bool PlayerTeam = false;
    std::vector<GameUnit*> EnemyGroup;
    std::vector<GameUnit*> TeamGroup;
    bool ImDie = false;

    bool HealTarget = false;

    bool UseUlt = false;

    int GetDieCount()
    {
        return DieCount;
    }

    int GetKillCount()
    {
        return KillCount;
    }

    void AddKillCount()
    {
        KillCount += 1;
    }

    float GetAttDamage()
    {
        return AttDamage;
    }

    void AddAttDamage(float _Damage)
    {
        AttDamage += _Damage;
    }

    float GetDefDamage()
    {
        return DefDamage;
    }

    void AddDefDamage(float _Damage)
    {
        DefDamage += _Damage;
    }

    float GetHealling()
    {
        return Healling;
    }

    void AddHealling(float _Heal)
    {
        Healling += _Heal;
    }

    void ChangeState(GameUnitState _State);

protected:
    std::shared_ptr<GameEngineSpriteRenderer> SpwanRenderer;
    std::shared_ptr<GameEngineCollision> BodyCol;
    std::shared_ptr<GameEngineCollision> AttackRangeCol;
    std::shared_ptr<GameEngineCollision> SkillRangeCol;
    std::shared_ptr<GameEngineCollision> SkillCol;
    std::shared_ptr<GameEngineCollision> UltRangeCol;
    // �����Ҷ� �÷��̾� ���� �ϳ����� ���� Ÿ���� �ϰ������..
    // �׷��ٸ� �����Ҷ����� �ݸ��� ��ġ�� ���ݹ����� ���� ������ ��ġ�� Set�ؼ�
    // ����ġ�� �浹ü�� �۰� ������Ű�� ���� Ÿ���� ������ ���� 
    // std::shared_ptr<GameEngineCollision> AttackCol;
    // �ٵ𺸴� ���� ���ְ������� �о�� ���� �ݸ���
    std::shared_ptr<GameEngineCollision> PushCol;

    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    void StateUpdate(float _Delta);

    virtual bool AttCheck();
    virtual bool SkillCheck();
    virtual bool UltCheck();

    void MapOverCheck();

    void SetUnitStatus(const GameUnitStatus& _Status)
    {
        UnitName = _Status.UnitName;
        AttackRange = _Status.AttackRange;
        SkillRange = _Status.SkillRange;
        SkillColRange = _Status.SkillColRange;
        UltRange = _Status.UltRange;

        UnitSpeed = _Status.UnitSpeed;
        UnitHP = _Status.UnitHP;
        UnitMaxHP = _Status.UnitMaxHP;
        UnitAtt = _Status.UnitAtt;
        UnitDef = _Status.UnitDef;
        UnitAbsoluteDef = _Status.UnitAbsoluteDef;

        AttackSpeed = _Status.AttackSpeed;

        SkillCooltime = _Status.SkillCooltime;

        UltCooltime = _Status.UltCooltime;
    }

    // State
    void MaxStart();
    void MaxUpdate(float _Delta);

    virtual void SpwanStart();
    void SpwanUpdate(float _Delta);

    virtual void IdleStart();
    void IdleUpdate(float _Delta);

    virtual void MoveStart();
    void MoveUpdate(float _Delta);

    virtual void BackMoveStart();
    void BackMoveUpdate(float _Delta);

    virtual void SearchMoveStart();
    void SearchMoveUpdate(float _Delta);

    virtual void CollMoveStart();
    void CollMoveUpdate(float _Delta);

    virtual void AttackStart();
    virtual void AttackUpdate(float _Delta);

    virtual void Attack2Start();
    virtual void Attack2Update(float _Delta);

    virtual void SkillStart();
    virtual void SkillUpdate(float _Delta);

    virtual void Skill2Start() {}
    virtual void Skill2Update(float _Delta) {}

    virtual void UltStart();
    virtual void UltUpdate(float _Delta);

    virtual void Ult2Start();
    virtual void Ult2Update(float _Delta);

    virtual void DiePrevStart();
    void DiePrevUpdate(float _Delta);

    virtual void DieStart();
    void DieUpdate(float _Delta);

    GameUnitState State = GameUnitState::Max;
    GameUnitDir Dir = GameUnitDir::Right;

    std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;
    std::shared_ptr<class GameEngineSpriteRenderer> SkillEffectRenderer;

    GameUnit* AggroUnit = nullptr;

    float4 TargetPos = float4::ZERO;
    float4 MoveDir;

    // Status
    // ���ݷ��� ���Ŀ��� *2  - 20% �� ����
    std::string_view UnitName = "";
    float4 AttackRange = { 55.0f, 0.0f };
    float4 SkillRange = { 70.0f, 0.0f };
    float4 SkillColRange = { 70.0f, 0.0f };
    float4 UltRange = { 100.0f, 0.0f };
    float UnitSpeed = 100.0f;
    float UnitHP = 100.0f;
    float UnitMaxHP = 100.0f;
    float UnitDef = 5.0f;
    float UnitAbsoluteDef = 5.0f;
    float UnitAtt = 10.0f;

    float PushDelay = 0.5f;
    float PushValue = 0.0f;

    float AttackSpeed = 3.0f;
    float AttackValue = 0.0f;
    float SkillCooltime = 10.0f;
    float SkillValue = 0.0f;
    float UltCooltime = 30.0f;
    float UltValue = 0.0f;

    int DieCount = 0;
    int KillCount = 0;
    float AttDamage = 0.0f;
    float DefDamage = 0.0f;
    float Healling = 0.0f;

private:
    float RespawnTime = 0.0f;



    float4 BodyColScale = { 40.0f, 0.0f };
    float4 PushColScale = { 20.0f, 0.0f };

    bool BackMoveBool = false;
    // �ñر� ��� ��ų��� ������ �� �ٸ��ٸ� Idle���¿����� ��ų�� ����ϰ� �ϰ�
    // Idle�� �������̵� �ϴ� ����� �õ��غ���.



    float4 SearchMoveTarget = { 0.0f , 0.0f };

};

