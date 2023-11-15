#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Audience : public GameEngineActor
{
public:
    Audience();
    ~Audience();

    Audience(const Audience& _Other) = delete;
    Audience(Audience&& _Other) noexcept = delete;
    Audience& operator=(const Audience& _Other) = delete;
    Audience& operator=(Audience&& _Other) noexcept = delete;

protected:

    void Start() override;
    void Update(float _Delta) override;
    void LevelStart(GameEngineLevel* _NextLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;


    std::shared_ptr<class GameEngineSpriteRenderer> BodyRenderer;
    std::shared_ptr<class GameEngineSpriteRenderer> HairRenderer;

    std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> FrameFunction;
    void HairCheck(const SpriteData& _CurSprite);
    float4 CheckPos = { 32.0f, 0.0f };

    GameEngineRandom Rand;

private:

};

