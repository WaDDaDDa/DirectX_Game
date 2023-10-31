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

private:
    std::shared_ptr<class GameEngineSpriteRenderer> HeaderRenderer;

    std::shared_ptr<class MenuButton> TeamButton;
    std::shared_ptr<class MenuButton> ManagerButton;
    std::shared_ptr<class MenuButton> BattleButton;
    std::shared_ptr<class MenuButton> GameButton;
    std::shared_ptr<class MenuButton> SystemButton;
    float4 TeamButtonPos = { -550.0f, -310.0f };
    float4 ButtonXInter = { 160.0f };

    std::shared_ptr<class TeamBundle> TeamPopMenu;

};

