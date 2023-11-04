#pragma once
#include <GameEngineCore/GameEngineActor.h>

class HouseUnit : public GameEngineActor
{
public:
    HouseUnit();
    ~HouseUnit();

    HouseUnit(const HouseUnit& _Other) = delete;
    HouseUnit(HouseUnit&& _Other) noexcept = delete;
    HouseUnit& operator=(const HouseUnit& _Other) = delete;
    HouseUnit& operator=(HouseUnit&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Delta) override;
    void LevelStart(GameEngineLevel* _NextLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    void HairCheck(const SpriteData& _CurSprite);

    std::shared_ptr<class GameEngineSpriteRenderer> BodyRenderer;
    std::shared_ptr<class GameEngineSpriteRenderer> HairRenderer;

    float4 CheckPos = { 32.0f, 0.0f };
    bool IsSleep = false;
    bool IsCpuPlay = false;

    std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> FrameFunction;
private:

};

