#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class GameUnitState
{
    Idle,
    Move,
    Att,
    Skill,
    Ult,
    Damage,
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

    // 적유닛에게 내가 적이다 라고 하는것.
    void EnemySetting(std::shared_ptr<GameUnit>& _Unit)
    {
        _Unit->EnemyUnit1 = this;
    }


protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    void ChangeState(GameUnitState _State);
    void StateUpdate(float _Delta);

    // State
    void MaxStart();
    void MaxUpdate(float _Delta);

    virtual void IdleStart();
    void IdleUpdate(float _Delta);

    virtual void MoveStart();
    void MoveUpdate(float _Delta);

    GameUnitState State = GameUnitState::Max;
    std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;

    GameUnit* EnemyUnit1;

   // std::shared_ptr<GameUnit> EnemyUnit2;

    //std::shared_ptr<GameUnit> TeamUnit;

private:

};

