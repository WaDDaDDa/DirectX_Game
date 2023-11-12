#pragma once
#include "UI_Button.h"

class RecruitCard : public UI_Button
{
public:
    RecruitCard();
    ~RecruitCard();

    RecruitCard(const RecruitCard& _Other) = delete;
    RecruitCard(RecruitCard&& _Other) noexcept = delete;
    RecruitCard& operator=(const RecruitCard& _Other) = delete;
    RecruitCard& operator=(RecruitCard&& _Other) noexcept = delete;

protected:
    void Start() override;

    void IdleStart() override;

    void StayStart() override;

    void EndStart() override;

    void ClickStart() override;

    std::shared_ptr<class GameEngineSpriteRenderer> HeadText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> InText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> InText2 = nullptr;

    std::shared_ptr<class GameEngineSpriteRenderer> DateText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> CostText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> DateIcon = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> CostIcon = nullptr;

    std::shared_ptr<class Default_Button> Button = nullptr;
private:

};

