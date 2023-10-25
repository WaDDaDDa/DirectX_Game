#pragma once
#include <GameEngineCore/GameEngineActor.h>

class NewGame_UI : public GameEngineActor
{
public:
    NewGame_UI();
    ~NewGame_UI();

    NewGame_UI(const NewGame_UI& _Other) = delete;
    NewGame_UI(NewGame_UI&& _Other) noexcept = delete;
    NewGame_UI& operator=(const NewGame_UI& _Other) = delete;
    NewGame_UI& operator=(NewGame_UI&& _Other) noexcept = delete;

    void AllButtonOff();
    void AllHairButtonOff();

protected:
    void Start();
    void Update(float _Delta);

private:
    // NewGame UI 임시
    std::shared_ptr<class GameEngineSpriteRenderer> NewGameBoxRenderer;

    // 로고 관련
    std::shared_ptr<class GameEngineSpriteRenderer> MyTeamLogoBg;
    std::shared_ptr<class GameEngineSpriteRenderer> MyTeamLogo;
    float4 MyTeamLogoPos = {-390.0f , 84.0f};

    std::shared_ptr<class SlotButton> CurLogo;
    std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> TeamLogoRenderer;
    std::vector<std::shared_ptr<class SlotButton>> TeamLogoButton;
    float4 TeamLogoStartPos = { -365.0f , -65.0f };
    float4 TeamLogoStartPos2 = { -365.0f , -135.0f };
    float4 XInter = { 70.0f };

    size_t TeamLogoPage = 0;
    size_t LogoSlot = 10;
    size_t LogoCount = 0;
    size_t CurNum = 0;


    std::shared_ptr<class GreenArrow> TeamLogoPrevArrow;
    std::shared_ptr<class GreenArrow> TeamLogoNextArrow;

    float4 TeamLogoPrevArrowPos = { -415.0f , -100.0f };
    float4 TeamLogoNextArrowPos = { -35.0f , -100.0f };

    // 감독 헤어 관련
    std::shared_ptr<class GameEngineSpriteRenderer> MyCoachHairBg;
    std::shared_ptr<class GameEngineSpriteRenderer> MyCoach;
    std::shared_ptr<class GameEngineSpriteRenderer> MyCoachHair;
    float4 MyCoachPos = { 60.0f , 84.0f };
    float4 MyCoachHairPos = { 60.0f , 99.0f };

    std::shared_ptr<class SlotButton> CurHair;
    std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> CoachHairRenderer;
    std::vector<std::shared_ptr<class SlotButton>> CoachHair;

    float4 CoachHairStartPos = { 80.0f , -65.0f };
    float4 CoachHairStartPos2 = { 80.0f , -135.0f };

    size_t HairPage = 0;
    size_t HairSlot = 10;
    size_t HairCount = 0;
    size_t CurHairNum = 0;

    std::shared_ptr<class GreenArrow> HairPrevArrow;
    std::shared_ptr<class GreenArrow> HairNextArrow;

    float4 HairPrevArrowPos = { 30.0f , -100.0f };
    float4 HairNextArrowPos = { 410.0f , -100.0f };


    std::shared_ptr<class Default_Button> StartButton;
    std::shared_ptr<class Default_Button> ExitButton;

    float4 StartButtonPos = { -80.0f , -220.0f };
    float4 ExitButtonPos = { 80.0f , -220.0f };
};

