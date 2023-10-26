#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class BanPickState
{
    Idle, // 대기 상태
    ChangeBan, // 벤 선택 상태로 가기전
    Ban, // 벤 선택 상태
    ChangePick, // 픽창으로 가기전
    Pick, // 픽 선택 상태
    Max,
};

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

    void ChangeState(BanPickState _State);
    void StateUpdate(float _Delta);

    void IdleStart();
    void IdleUpdate(float _Delta);

    void ChangeBanStart();
    void ChangeBanUpdate(float _Delta);

    void BanStart();
    void BanUpdate(float _Delta);

    void ChangePickStart();
    void ChangePickUpdate(float _Delta);

    void PickStart();
    void PickUpdate(float _Delta);

    void MaxStart() {}
    void MaxUpdate(float _Delta) {}

private:
    std::shared_ptr<class GameEngineSpriteRenderer> UnitImage;
    float4 UnitImagePos = { 285.0f, -505.0f };

    // 글자 기술 궁극기...
    std::shared_ptr<class GameEngineSpriteRenderer> SkillText;
    float4 SkillTextPos = { 660.0f, -440.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> UltText;
    float4 UltTextPos = { 660.0f, -510.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> UnitSkillImage;
    float4 UnitSkillImagePos = { 582.0f, -460.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UnitUltImage;
    float4 UnitUltImagePos = { 582.0f, -530.0f };

    // 유닛 스킬 텍스트 , 텍스트 설명
    std::shared_ptr<class GameEngineSpriteRenderer> UnitSkillText;
    float4 UnitSkillTextPos = { 720.0f, -435.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UnitUltText;
    float4 UnitUltTextPos = { 720.0f, -505.0f };

    // box
    std::shared_ptr<class GameEngineSpriteRenderer> UnitAttBox;
    float4 UnitAttBoxPos = { 336.0f, -428.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UnitAttSpeedBox;
    float4 UnitAttSpeedBoxPos = { 336.0f, -474.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UnitAttRangeBox;
    float4 UnitAttRangeBoxPos = { 336.0f, -520.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UnitDefBox;
    float4 UnitDefBoxPos = { 445.0f, -428.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UnitHpBox;
    float4 UnitHpBoxPos = { 445.0f, -474.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UnitSpeedBox;
    float4 UnitSpeedBoxPos = { 445.0f, -520.0f };

    // icon
    std::shared_ptr<class GameEngineSpriteRenderer> UnitAttIcon;
    float4 UnitAttIconPos = { 338.0f, -430.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UnitAttSpeedIcon;
    float4 UnitAttSpeedIconPos = { 338.0f, -476.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UnitAttRangeIcon;
    float4 UnitAttRangeIconPos = { 338.0f, -522.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UnitDefIcon;
    float4 UnitDefIconPos = { 447.0f, -430.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UnitHpIcon;
    float4 UnitHpIconPos = { 447.0f, -476.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UnitSpeedIcon;
    float4 UnitSpeedIconPos = { 447.0f, -522.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> SkillTimeIcon;
    float4 SkillTimeIconPos = { 622.0f, -472.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UltTimeIcon;
    float4 UltTimeIconPos = { 622.0f, -542.0f };

    // Text제목
    std::shared_ptr<class GameEngineSpriteRenderer> AttText;
    float4 AttTextPos = { 365.0f, -432.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> AttSpeedText;
    float4 AttSpeedTextPos = { 365.0f, -478.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> AttRangeText;
    float4 AttRangeTextPos = { 365.0f, -524.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> DefText;
    float4 DefTextPos = { 474.0f, -432.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> HpText;
    float4 HpTextPos = { 474.0f, -478.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> SpeedText;
    float4 SpeedTextPos = { 474.0f, -524.0f };

    // UnitStat Text
    std::shared_ptr<class GameEngineSpriteRenderer> UnitAttText;
    float4 UnitAttTextPos = { 385.0f, -452.0f };        
    std::shared_ptr<class GameEngineSpriteRenderer> UnitAttSpeedText;
    float4 UnitAttSpeedTextPos = { 385.0f, -498.0f };   
    std::shared_ptr<class GameEngineSpriteRenderer> UnitAttRangeText;
    float4 UnitAttRangeTextPos = { 385.0f, -544.0f };   
    std::shared_ptr<class GameEngineSpriteRenderer> UnitDefText;
    float4 UnitDefTextPos = { 494.0f, -452.0f };        
    std::shared_ptr<class GameEngineSpriteRenderer> UnitHpText;
    float4 UnitHpTextPos = { 494.0f, -498.0f };         
    std::shared_ptr<class GameEngineSpriteRenderer> UnitSpeedText;
    float4 UnitSpeedTextPos = { 494.0f, -544.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> SkillTimeText;
    float4 SkillTimeTextPos = { 638.0f, -465.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> UltTimeText;
    float4 UltTimeTextPos = { 638.0f, -535.0f };

    // 벤 영역
    std::shared_ptr<class GameEngineSpriteRenderer> BlueBan;
    float4 BlueBanPos = { 360.0f, -662.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> BlueBanIcon;
    float4 BlueBanIconPos = { 388.0f, -626.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> BlueBanUnit;
    float4 BlueBanUnitPos = { 360.0f, -667.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> BlueBanUnitText;
    float4 BlueBanUnitTextPos = { 360.0f, -690.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> RedBanUnitText;
    float4 RedBanUnitTextPos = { 920.0f, -690.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> RedBan;
    float4 RedBanPos = { 920.0f, -662.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> RedBanIcon;
    float4 RedBanIconPos = { 948.0f, -626.0f };
    std::shared_ptr<class GameEngineSpriteRenderer> RedBanUnit;
    float4 RedBanUnitPos = { 920.0f, -667.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> TurnColor;
    float4 TurnColorPos = { 640.0f, -125.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> BansText;
    float4 BansTextPos = { 640.0f, -650.0f };

    size_t UnitCount = 8;
    std::shared_ptr<class BanPickCard> CurCard;
    std::shared_ptr<class BanPickCard> BlueBanCard;
    std::shared_ptr<class BanPickCard> RedBanCard;

    std::vector<std::shared_ptr<class BanPickCard>> Card;
    std::shared_ptr<class BanPickBoard> GameBoard;
    BanPickState State = BanPickState::Max;

    int BluePickCount = 0;
    int RedPickCount = 0;
    int BanCount = 0;
};

