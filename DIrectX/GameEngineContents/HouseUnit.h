#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class HouseUnitEnum
{
    Idle,
    Run,
    Eat,
    PlayGame,

};

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

    void Reset()
    {
        IsSleep = false;
        IsCpuPlay = false;
    }

    bool IsSleep = false;
    bool IsCpuPlay = false;

    std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> FrameFunction;
    GameEngineState State;

    float FirstFloarY = -470.0f;
    float ScendFloarY = -615.0f;
    bool IsFirstFloar = false;
    bool IsScendFloar = false;

    void FloarCheck()
    {
        if (true == IsFirstFloar)
        {
            Transform.SetLocalPositionY(FirstFloarY);
        }

        if (true == IsScendFloar)
        {
            Transform.SetLocalPositionY(ScendFloarY);
        }
    }

    void FlipReset()
    {
        BodyRenderer->RightFlip();
        HairRenderer->RightFlip();
    }

    // ������
    float MoveDir = 100.0f;

private:

};

