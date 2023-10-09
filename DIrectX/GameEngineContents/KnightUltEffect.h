#pragma once
#include <GameEngineCore/GameEngineActor.h>

class KnightUltEffect : public GameEngineActor
{
public:
    KnightUltEffect();
    ~KnightUltEffect();

    KnightUltEffect(const KnightUltEffect& _Other) = delete;
    KnightUltEffect(KnightUltEffect&& _Other) noexcept = delete;
    KnightUltEffect& operator=(const KnightUltEffect& _Other) = delete;
    KnightUltEffect& operator=(KnightUltEffect&& _Other) noexcept = delete;

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
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer2;
    std::shared_ptr<class GameUnit> Unit;
    float LifeTime = 20.0f;

};

