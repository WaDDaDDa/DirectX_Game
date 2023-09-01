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

protected:
    void Start();
    void Update(float _Delta);

    void ChangeState(GameUnitState _State);
    void StateUpdate(float _Delta);


private:
    std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;
    GameUnitState State = GameUnitState::Max;

};

