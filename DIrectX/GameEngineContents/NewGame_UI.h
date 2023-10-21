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
    std::vector<std::shared_ptr<class UI_Button>> TeamLogo;
    std::vector<std::shared_ptr<class UI_Button>> CoachHair;
};

