#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BanPickManager : public GameEngineActor
{
public:
    BanPickManager();
    ~BanPickManager();

    BanPickManager(const BanPickManager& _Other) = delete;
    BanPickManager(BanPickManager&& _Other) noexcept = delete;
    BanPickManager& operator=(const BanPickManager& _Other) = delete;
    BanPickManager& operator=(BanPickManager&& _Other) noexcept = delete;

    void CardIntit();

    void CardValueReset();


protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> UnitImage;
    float4 UnitImagePos = { 285.0f, -505.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> UnitSkillImage;
    float4 UnitSkillImagePos = { 582.0f, -460.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> UnitUltImage;
    float4 UnitUltImagePos = { 582.0f, -530.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> UniAttBox;
    float4 UnitAttBoxPos = { 336.0f, -428.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UniAttSpeedBox;
    float4 UnitAttSpeedBoxPos = { 336.0f, -474.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UniAttRangeBox;
    float4 UnitAttRangeBoxPos = { 336.0f, -520.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UniDefBox;
    float4 UnitDefBoxPos = { 445.0f, -428.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UniHpBox;
    float4 UnitHpBoxPos = { 445.0f, -474.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UniSpeedBox;
    float4 UnitSpeedBoxPos = { 445.0f, -520.0f };

    size_t UnitCount = 8;
    std::shared_ptr<class BanPickCard> CurCard;
    std::vector<std::shared_ptr<class BanPickCard>> Card;
    std::shared_ptr<class BanPickBoard> GameBoard;
};

