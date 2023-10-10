#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MonkShield : public GameEngineActor
{
public:
    MonkShield();
    ~MonkShield();

    MonkShield(const MonkShield& _Other) = delete;
    MonkShield(MonkShield&& _Other) noexcept = delete;
    MonkShield& operator=(const MonkShield& _Other) = delete;
    MonkShield& operator=(MonkShield&& _Other) noexcept = delete;

    void SetUnit(std::shared_ptr<class GameUnit> _Unit)
    {
        Unit = _Unit;
    }

protected:
    void Start() override;
    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void Update(float _Delta) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<class GameUnit> Unit;
    float LifeTime = 3.0f;

};

