#pragma once
#include <GameEngineCore/GameEngineActor.h>

class House : public GameEngineActor
{
public:
    House();
    ~House();

    House(const House& _Other) = delete;
    House(House&& _Other) noexcept = delete;
    House& operator=(const House& _Other) = delete;
    House& operator=(House&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Ground;
    std::shared_ptr<class GameEngineSpriteRenderer> HouseRenderer;

    std::shared_ptr<class GameEngineSpriteRenderer> Table;
    std::shared_ptr<class GameEngineSpriteRenderer> Cabinet;
    std::shared_ptr<class GameEngineSpriteRenderer> Bed1;
    std::shared_ptr<class GameEngineSpriteRenderer> Bed2;
    std::shared_ptr<class GameEngineSpriteRenderer> Bed3;

    std::shared_ptr<class GameEngineSpriteRenderer> Cpu1;
    std::shared_ptr<class GameEngineSpriteRenderer> Cpu2;
    std::shared_ptr<class GameEngineSpriteRenderer> Cpu3;
    std::shared_ptr<class GameEngineSpriteRenderer> Cpu4;
    std::shared_ptr<class GameEngineSpriteRenderer> Cpu5;
    std::shared_ptr<class GameEngineSpriteRenderer> Cpu6;

    std::shared_ptr<class GameEngineSpriteRenderer> Tolilet;
    std::shared_ptr<class GameEngineSpriteRenderer> ShowerRoom;

};

