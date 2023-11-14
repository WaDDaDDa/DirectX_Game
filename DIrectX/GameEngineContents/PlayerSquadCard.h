#pragma once
#include "UI_Button.h"
#include "GamePlayer.h"

class PlayerSquadCard : public UI_Button
{
public:
    PlayerSquadCard();
    ~PlayerSquadCard();

    PlayerSquadCard(const PlayerSquadCard& _Other) = delete;
    PlayerSquadCard(PlayerSquadCard&& _Other) noexcept = delete;
    PlayerSquadCard& operator=(const PlayerSquadCard& _Other) = delete;
    PlayerSquadCard& operator=(PlayerSquadCard&& _Other) noexcept = delete;

    void SetInfo(class GamePlayerInfo _Info);

    void AllDeath();

protected:
    void Start() override;
    void Update(float _Delta) override;
    void IdleStart() override;

    void StayStart() override;

    void EndStart() override;

    void ClickStart() override;

    std::shared_ptr<class GameEngineSpriteRenderer> PlayerFaceBG = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> BodyRenderer = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> HairRenderer = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> PlayerFaceFG = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> NameText = nullptr;

    std::shared_ptr<class GameEngineSpriteRenderer> AgeText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> AttIcon = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> AttText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> DefIcon = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> DefText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> PayText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> PayIcon = nullptr;

    std::shared_ptr<class Default_Button> Button = nullptr;

private:
    class GamePlayerInfo Info;

};

