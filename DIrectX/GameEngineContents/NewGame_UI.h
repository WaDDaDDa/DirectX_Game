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

protected:
    void Start();
    void Update(float _Delta);

private:
    // NewGame UI юс╫ц
    std::shared_ptr<class GameEngineSpriteRenderer> NewGameBoxRenderer;

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

    std::vector<std::shared_ptr<class UI_Button>> CoachHair;
};

