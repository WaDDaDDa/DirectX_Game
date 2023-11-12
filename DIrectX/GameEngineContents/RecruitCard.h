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

    void Searching();
    void SearchingCancel();

    void AllOff();
    void AllOn();

protected:
    void Start() override;
    void Update(float _Delta) override;
    void IdleStart() override;

    void StayStart() override;

    void EndStart() override;

    void ClickStart() override;

    bool SearchValue = false;

    std::shared_ptr<class GameEngineSpriteRenderer> HeadText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> InText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> InText2 = nullptr;

    std::shared_ptr<class GameEngineSpriteRenderer> SearchText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> SearchText2 = nullptr;

    std::shared_ptr<class GameEngineSpriteRenderer> DateText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> CostText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> DateIcon = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> CostIcon = nullptr;

    std::shared_ptr<class Default_Button> Button = nullptr;
    std::shared_ptr<class Default_Button> Button2 = nullptr;
private:

};

