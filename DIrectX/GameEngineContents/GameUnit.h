#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

private:
    std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;

};

