#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

enum class GameUnitState
{
    Spwan,
    Idle,
    Move,
    Att,
    Skill,
    Ult,
    Damage,
    Die,
    Max,
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
    void EnemySetting(std::vector<GameUnit*>& _UnitGroup)
    {
        EnemyGroup = _UnitGroup;
    }

    void AggroSetting()
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

    GameUnitState State = GameUnitState::Max;
    std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;

    std::vector<GameUnit*> EnemyGroup;

    GameUnit* AggroUnit = nullptr;

private:
    std::shared_ptr<GameEngineSpriteRenderer> SpwanRenderer;

};

