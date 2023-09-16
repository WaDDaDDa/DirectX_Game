#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

enum class GameUnitState
{
    Spwan,
    Idle,
    Move,
    BackMove,
    SearchMove,
    CollMove,
    Attack,
    Skill,
    Ult,
    Damage,
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
    void EnemySetting(const std::vector<GameUnit*>& _UnitGroup)
    {
        EnemyGroup = _UnitGroup;
    }

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

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    GameUnitState GetState()
    {
        return State;
    }

    void ChangeState(GameUnitState _State);
    void StateUpdate(float _Delta);

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

    GameUnitState State = GameUnitState::Max;
    GameUnitDir Dir = GameUnitDir::Right;

    std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;

    std::vector<GameUnit*> EnemyGroup;

    GameUnit* AggroUnit = nullptr;

    float4 TargetPos = float4::ZERO;

private:
    std::shared_ptr<GameEngineSpriteRenderer> SpwanRenderer;
    std::shared_ptr<GameEngineCollision> BodyCol;
    std::shared_ptr<GameEngineCollision> AttackRangeCol;
    // 바디보다 작은 유닛겹쳤을때 밀어내기 위한 콜리전
    std::shared_ptr<GameEngineCollision> PushCol;


    float4 BodyColScale = { 50.0f, 0.0f };
    float4 PushColScale = { 20.0f, 0.0f };

    float4 MoveDir;

    TeamType MyTeam = TeamType::Blue;
    float4 AttackRange = { 55.0f, 0.0f };
    float UnitSpeed = 100.0f;

    float AttackDelay = 3.0f;
    float AttackValue = 0.0f;
    float SkillCooltime = 10.0f;
    float SkillValue = 0.0f;
    float UltCooltime = 30.0f;
    float UltValue = 0.0f;


    float4 SearchMoveTarget = { 0.0f , 0.0f };

};

