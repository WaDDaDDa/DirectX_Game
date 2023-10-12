#pragma once
#include <GameEngineCore/GameEngineActor.h>

class KnightEffect : public GameEngineActor
{
public:
    KnightEffect();
    ~KnightEffect();

    KnightEffect(const KnightEffect& _Other) = delete;
    KnightEffect(KnightEffect&& _Other) noexcept = delete;
    KnightEffect& operator=(const KnightEffect& _Other) = delete;
    KnightEffect& operator=(KnightEffect&& _Other) noexcept = delete;

    //                  도발대상                                         도발시전자
    void SetUnit(std::shared_ptr<class GameUnit> _Unit, std::shared_ptr<class GameUnit> _AgrUnit)
    {
        Unit = _Unit;
        AgrUnit = _AgrUnit;
    }

protected:
    void Start() override;
    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void Update(float _Delta) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<class GameUnit> Unit;
    std::shared_ptr<class GameUnit> AgrUnit;
    float LifeTime = 2.0f;

};

