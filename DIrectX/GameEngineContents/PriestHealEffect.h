#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PriestHealEffect : public GameEngineActor
{
public:
    PriestHealEffect();
    ~PriestHealEffect();

    PriestHealEffect(const PriestHealEffect& _Other) = delete;
    PriestHealEffect(PriestHealEffect&& _Other) noexcept = delete;
    PriestHealEffect& operator=(const PriestHealEffect& _Other) = delete;
    PriestHealEffect& operator=(PriestHealEffect&& _Other) noexcept = delete;

protected:
    void Start();
    void Update(float _Delta);
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

