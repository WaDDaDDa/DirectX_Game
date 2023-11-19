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

    // 적유닛에게 내가 적이다 라고 하는것.
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

        // 죽어있지 않은 유닛들 중에서 가까운 유닛으로 어그로 잡는다.
        // 유닛들이 100 범위보다 멀리있으면 어그로 유닛은 0번유닛으로 한다.
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

    // 단순하게 살아있는 유닛 제일먼저 어그로로 본다.
    // 어그로 타겟이 100 이내에서 죽었을때 다음 어그로 유닛을 단순하게 본다.
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

    // 팀마다 달라야 하는것,
    // 스폰위치.  바라보는 방향. 콜리젼 종류. 
    void TeamSet(TeamType _Team);

    // 충돌이벤트
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

        // 들어온 공격력에 유닛의 방어력을 반영해서 계산시킨다.
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

    // 변한 컬러 회복시키는 불값.
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
    // 공격할때 플레이어 유닛 하나만을 단일 타겟팅 하고싶은데..
    // 그렇다면 공격할때마다 콜리젼 위치를 공격범위에 닿은 유닛의 위치에 Set해서
    // 그위치에 충돌체를 작게 생성시키면 단일 타겟팅 느낌이 나지 
    // std::shared_ptr<GameEngineCollision> AttackCol;
    // 바디보다 작은 유닛겹쳤을때 밀어내기 위한 콜리전
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
    // 공격력은 공식에서 *2  - 20% 후 버림
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
    // 궁극기 사용 스킬사용 조건이 다 다르다면 Idle상태에서만 스킬을 사용하게 하고
    // Idle을 오버라이드 하는 방법을 시도해보자.



    float4 SearchMoveTarget = { 0.0f , 0.0f };

};

