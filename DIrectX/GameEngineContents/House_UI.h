#pragma once
#include <GameEngineCore/GameEngineActor.h>

class House_UI : public GameEngineActor
{
public:
    House_UI();
    ~House_UI();

    House_UI(const House_UI& _Other) = delete;
    House_UI(House_UI&& _Other) noexcept = delete;
    House_UI& operator=(const House_UI& _Other) = delete;
    House_UI& operator=(House_UI&& _Other) noexcept = delete;

protected:
    void Start();
    void Update(float _Delta);

    void PopBundle(std::shared_ptr<class MenuButton> _Menu, std::shared_ptr<class ButtonBundle> _Bundle);

private:
    std::shared_ptr<class GameEngineSpriteRenderer> HeaderRenderer;
    std::shared_ptr<class GameEngineSpriteRenderer> GroundRenderer;

    std::shared_ptr<class MenuButton> TeamButton;
    std::shared_ptr<class MenuButton> ManagerButton;
    std::shared_ptr<class MenuButton> BattleButton;
    std::shared_ptr<class MenuButton> GameButton;
    std::shared_ptr<class MenuButton> SystemButton;
    std::shared_ptr<class ProceedButton> Proceed;
    float4 TeamButtonPos = { -550.0f, -310.0f };
    float4 ButtonXInter = { 160.0f };

    std::shared_ptr<class ButtonBundle> TeamPopMenu;
    std::shared_ptr<class ButtonBundle> ManagerPopMenu;
    std::shared_ptr<class ButtonBundle> BattlePopMenu;
    std::shared_ptr<class ButtonBundle> GamePopMenu;
    std::shared_ptr<class ButtonBundle> SystemPopMenu;

};

