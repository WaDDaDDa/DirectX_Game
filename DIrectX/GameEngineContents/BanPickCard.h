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

    void Init(const class GameUnitStatus& _Status);

    void Init(size_t _Stat)
    {
        switch (_Stat)
        {
        case 0:
            Init(ArcherStatus::ArcherStat);
            break;
        case 1:
            Init(KnightStatus::KnightStat);
            break;
        case 2:
            Init(MonkStatus::MonkStat);
            break;
        case 3:
            Init(NinjaStatus::NinjaStat);
            break;
        case 4:
            Init(PyromancerStatus::PyromancerStat);
            break;
        case 5:
            Init(PriestStatus::PriestStat);
            break;
        case 6:
            Init(SwordmanStatus::SwordmanStat);
            break;
        case 7:
            Init(PythonessStatus::PythonessStat);
            break;
        default:
            break;
        }
    }

    
    std::string GetUnitName()
    {
        return UnitName.data();
    }

    static float XInter;

protected:

    void Start() override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    void IdleStart()override;
    void IdleUpdate(float _Delta)override;

    void StayStart()override;
    void StayUpdate(float _Delta)override;

    void ClickStart()override;
    void ClickUpdate(float _Delta) override;

    std::string_view UnitName = "";

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;

    std::shared_ptr<class GameEngineSpriteRenderer> UnitImage;
    float4 UnitImagePos = { 0.0f, -10.0f };

    bool IsSelect = false;

    float4 ColScale = { 76.0f, 104.0f };
};

