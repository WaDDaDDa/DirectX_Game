#pragma once
#include "UI_Button.h"
#include "GamePlayer.h"

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

    void RecruitResult();


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
    // true 되면 영입할 선수 정보 보여지는.
    bool SearchEnd = false;

    int EndWeek = 0;

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

    // 선수 서칭 후
    std::shared_ptr<class GameEngineSpriteRenderer> PlayerFaceBG = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> NameText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> BodyRenderer = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> HairRenderer = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> PlayerFaceFG = nullptr;

    std::shared_ptr<class GameEngineSpriteRenderer> AttIcon = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> AttText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> DefIcon = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> DefText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> PayText = nullptr;
    std::shared_ptr<class GameEngineSpriteRenderer> PayIcon = nullptr;

    std::shared_ptr<class Default_Button> Button3 = nullptr;
    std::shared_ptr<class Default_Button> Button4 = nullptr;

    class GamePlayerInfo Info;

private:

};

