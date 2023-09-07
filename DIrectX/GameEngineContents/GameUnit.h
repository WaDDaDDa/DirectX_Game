#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

enum class GameUnitState
{
    Spwan,
    Idle,
    Move,
    BackMove,
    Att,
    Skill,
    Ult,
    Damage,
    Die,
    SearchMove,
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

    GameUnitState State = GameUnitState::Max;
    GameUnitDir Dir = GameUnitDir::Right;

    std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;

    std::vector<GameUnit*> EnemyGroup;

    GameUnit* AggroUnit = nullptr;

    float4 TargetPos = float4::ZERO;

private:
    std::shared_ptr<GameEngineSpriteRenderer> SpwanRenderer;
    std::shared_ptr<GameEngineCollision> BodyCol;

    float4 BodyColScale = { -100.0f,100.0f };

    float4 MoveDir;

};

