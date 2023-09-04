#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BattleField : public GameEngineActor
{
public:
    BattleField();
    ~BattleField();

    BattleField(const BattleField& _Other) = delete;
    BattleField(BattleField&& _Other) noexcept = delete;
    BattleField& operator=(const BattleField& _Other) = delete;
    BattleField& operator=(BattleField&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> BackGround;
    std::shared_ptr<GameEngineSpriteRenderer> Fleid;
    std::shared_ptr<GameEngineSpriteRenderer> Water1;
    std::shared_ptr<GameEngineSpriteRenderer> Water2;

};

