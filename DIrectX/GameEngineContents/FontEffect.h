#pragma once
#include <GameEngineCore/GameEngineActor.h>

class FontEffect : public GameEngineActor
{
public:
    FontEffect();
    ~FontEffect();

    FontEffect(const FontEffect& _Other) = delete;
    FontEffect(FontEffect&& _Other) noexcept = delete;
    FontEffect& operator=(const FontEffect& _Other) = delete;
    FontEffect& operator=(FontEffect&& _Other) noexcept = delete;

    void Init(float4 _Pos, float _Damage, float4 _Color, bool _Dir);

protected:
    void Start();
    void Update(float _Delta);
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<GameEngineCollision> BodyCol;
    float4 BodyColScale = { 50.0f, 50.0f };

    float GravityPower = 1000.0f;
    float4 GravityVector = float4::ZERO;
};

