#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BanPickInfo
{
public:
    static BanPickInfo Info;
    std::map<int, std::string_view> BlueTeamPick;
    std::map<int, std::string_view> RedTeamPick;

    void Clear()
    {
        if (false == BlueTeamPick.empty())
        {
            BlueTeamPick.clear();
        }

        if (false == RedTeamPick.empty())
        {
            RedTeamPick.clear();
        }
    }
};

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
    // box
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
    // icon
    std::shared_ptr<class GameEngineSpriteRenderer> UniAttIcon;
    float4 UnitAttIconPos = { 338.0f, -430.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UniAttSpeedIcon;
    float4 UnitAttSpeedIconPos = { 338.0f, -476.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UniAttRangeIcon;
    float4 UnitAttRangeIconPos = { 338.0f, -522.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UniDefIcon;
    float4 UnitDefIconPos = { 447.0f, -430.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UniHpIcon;
    float4 UnitHpIconPos = { 447.0f, -476.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UniSpeedIcon;
    float4 UnitSpeedIconPos = { 447.0f, -522.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> SkillTimeIcon;
    float4 SkillTimeIconPos = { 622.0f, -472.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UltTimeIcon;
    float4 UltTimeIconPos = { 622.0f, -542.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> BlueBan;
    float4 BlueBanPos = { 360.0f, -662.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> BlueBanIcon;
    float4 BlueBanIconPos = { 388.0f, -626.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> BlueBanUnit;
    float4 BlueBanUnitPos = { 360.0f, -657.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> RedBan;
    float4 RedBanPos = { 920.0f, -662.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> RedBanIcon;
    float4 RedBanIconPos = { 948.0f, -626.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> RedBanUnit;
    float4 RedBanUnitPos = { 920.0f, -657.0f };

    size_t UnitCount = 8;
    std::shared_ptr<class BanPickCard> CurCard;
    std::shared_ptr<class BanPickCard> BlueBanCard;
    std::shared_ptr<class BanPickCard> RedBanCard;

    std::vector<std::shared_ptr<class BanPickCard>> Card;
    std::shared_ptr<class BanPickBoard> GameBoard;

    int BluePickCount = 0;
    int RedPickCount = 0;
    int BanCount = 0;
};

