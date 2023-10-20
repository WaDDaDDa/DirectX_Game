#pragma once
#include "UI_Button.h"


class BanPickCard : public UI_Button
{
public:
    BanPickCard();
    ~BanPickCard();

    BanPickCard(const BanPickCard& _Other) = delete;
    BanPickCard(BanPickCard&& _Other) noexcept = delete;
    BanPickCard& operator=(const BanPickCard& _Other) = delete;
    BanPickCard& operator=(BanPickCard&& _Other) noexcept = delete;

    float4 StartPos = { -370.0f, 125.0f, 100.0f };

    void Init();

    void Init(size_t _Stat)
    {
        switch (_Stat)
        {
        case 0:
            UnitStat = GameUnitStatus::ArcherStat;
            break;
        case 1:
            UnitStat = GameUnitStatus::KnightStat;
            break;
        case 2:
            UnitStat = GameUnitStatus::MonkStat;
            break;
        case 3:
            UnitStat = GameUnitStatus::NinjaStat;
            break;
        case 4:
            UnitStat = GameUnitStatus::PriestStat;
            break;
        case 5:
            UnitStat = GameUnitStatus::PyromancerStat;
            break;
        case 6:
            UnitStat = GameUnitStatus::SwordmanStat;
            break;
        case 7:
            UnitStat = GameUnitStatus::PythonessStat;
            break;
        default:
            break;
        }

        Init();
    }

    
    std::string GetUnitNameToString()
    {
        return UnitName.data();
    }

    std::string_view GetUnitName()
    {
        return UnitName;
    }

    static float XInter;

    TeamType GetPlayerTeam()
    {
        return PlayerTeam;
    }

    void SetPlayerTeam(TeamType _Team)
    {
        PlayerTeam = _Team;
    }

    bool IsSelect = false;
    bool IsStart = false;
    bool IsPick = false;
    bool IsBan = false;

    GameUnitStatus UnitStat;

    int PickNum = 0;

    void SetPickNum(int _Num);

    void SetBan()
    {
        Renderer->ChangeAnimation("BanPickCard_Ban");
        Renderer4->ChangeAnimation("Ban");
        Renderer4->On();
        IsBan = true;
    }

protected:

    void Start() override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    void IdleStart()override;
    void IdleUpdate(float _Delta)override;

    void EnterStart()override;
    void EnterUpdate(float _Delta)override;

    void StayStart()override;
    void StayUpdate(float _Delta)override;

    void EndStart()override;
    void EndUpdate(float _Delta) override;

    void ClickStart()override;
    void ClickUpdate(float _Delta) override;

    std::string_view UnitName = "";

    TeamType PlayerTeam = TeamType::Blue;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer2;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer3;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer4;

    std::shared_ptr<class GameEngineSpriteRenderer> UnitImage;
    float4 UnitImagePos = { 0.0f, -10.0f };

    float4 ColScale = { 76.0f, 104.0f };

};

