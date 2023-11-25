#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BanEffect : public GameEngineActor
{
public:
    BanEffect();
    ~BanEffect();

    BanEffect(const BanEffect& _Other) = delete;
    BanEffect(BanEffect&& _Other) noexcept = delete;
    BanEffect& operator=(const BanEffect& _Other) = delete;
    BanEffect& operator=(BanEffect&& _Other) noexcept = delete;

    void Init(float4 _Pos);

protected:
    void Start();
    void Update(float _Delta);
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<GameEngineCollision> BodyCol;
    float4 BodyColScale = { 50.0f, 50.0f };

};

