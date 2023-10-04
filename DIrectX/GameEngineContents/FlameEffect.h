#pragma once
#include <GameEngineCore/GameEngineActor.h>

class FlameEffect : public GameEngineActor
{
public:
    FlameEffect();
    ~FlameEffect();

    FlameEffect(const FlameEffect& _Other) = delete;
    FlameEffect(FlameEffect&& _Other) noexcept = delete;
    FlameEffect& operator=(const FlameEffect& _Other) = delete;
    FlameEffect& operator=(FlameEffect&& _Other) noexcept = delete;

protected:
    void Start();
    void Update(float _Delta);

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

