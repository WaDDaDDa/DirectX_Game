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

    // �����ֿ��� ���� ���̴� ��� �ϴ°�.
    void EnemySetting(const std::vector<GameUnit*>& _UnitGroup)
    {
        EnemyGroup = _UnitGroup;
    }

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
    // ������ �޶�� �ϴ°�,
    // ������ġ.  �ٶ󺸴� ����. �ݸ��� ����. 
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
    // �ٵ𺸴� ���� ���ְ������� �о�� ���� �ݸ���
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

