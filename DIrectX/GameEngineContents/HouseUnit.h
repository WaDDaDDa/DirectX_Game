#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class HouseUnitEnum
{
    Idle,
    Run,
    Eat,
    PlayGame,
    Toilet,
    Shower,
    Sleep,
    HandWash,
    ToFurniture,
    ToStairs,
    UseStairs,
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

    bool Arrive(const std::shared_ptr<class Furniture>& _Furniture);
    bool Arrive(float4 _Pos);

protected:
    void Start() override;
    void Update(float _Delta) override;
    void LevelStart(GameEngineLevel* _NextLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    void HairCheck(const SpriteData& _CurSprite);

    std::shared_ptr<class GameEngineSpriteRenderer> BodyRenderer;
    std::shared_ptr<class GameEngineSpriteRenderer> HairRenderer;
    std::shared_ptr<class GameEngineSpriteRenderer> ShowerRenderer;

    float4 CheckPos = { 32.0f, 0.0f };
    HouseUnitEnum PrevState = HouseUnitEnum::Idle;
    void Reset()
    {
        IsSleep = false;
        IsCpuPlay = false;
    }

    bool IsSleep = false;
    bool IsCpuPlay = false;

    std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> FrameFunction;
    GameEngineState State;
    int FurnitureNum = 0;

    float FirstFloorY = -615.0f;
    float ScendFloorY = -470.0f;
    bool IsFirstFloor = false;
    bool IsScendFloor = false;
    int EatRight = 0;


    float4 FirstStairsPos = { 450.0f, -615.0f };
    float4 ScendStairsPos = { 710.0f, -470.0f };

    void FloorCheck()
    {
        if (true == IsFirstFloor)
        {
            Transform.SetLocalPositionY(FirstFloorY);
        }

        if (true == IsScendFloor)
        {
            Transform.SetLocalPositionY(ScendFloorY);
        }
    }

    void FlipReset()
    {
        BodyRenderer->RightFlip();
        HairRenderer->RightFlip();
    }

    void DirCheck()
    {
        if (0 <= MoveDir.X)
        {
            BodyRenderer->RightFlip();
            HairRenderer->RightFlip();
        }
        else
        {
            BodyRenderer->LeftFlip();
            HairRenderer->LeftFlip();
        }
    }

    // ¿À¸¥ÂÊ
    float4 MoveDir = { 1.0f };
    float MoveSpeed = 200.0f;

    GameEngineRandom Rand;
private:

};

