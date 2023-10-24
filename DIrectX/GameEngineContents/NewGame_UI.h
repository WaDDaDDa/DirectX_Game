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

protected:
    void Start();
    void Update(float _Delta);

private:
    // NewGame UI юс╫ц
    std::shared_ptr<class GameEngineSpriteRenderer> NewGameBoxRenderer;

    std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> TeamLogoRenderer;
    std::vector<std::shared_ptr<class SlotButton>> TeamLogoButton;
    float4 TeamLogoStartPos = { -365.0f , -70.0f };
    float4 TeamLogoStartPos2 = { -365.0f , -140.0f };
    float4 XInter = { 70.0f };

    size_t TeamLogoPage = 0;
    size_t LogoSlot = 10;

    std::shared_ptr<class GreenArrow> TeamLogoNextArrow;


    std::vector<std::shared_ptr<class UI_Button>> CoachHair;
};

