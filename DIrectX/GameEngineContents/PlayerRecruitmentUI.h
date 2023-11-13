#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PlayerRecruitmentUI : public GameEngineActor
{
public:
    PlayerRecruitmentUI();
    ~PlayerRecruitmentUI();

    PlayerRecruitmentUI(const PlayerRecruitmentUI& _Other) = delete;
    PlayerRecruitmentUI(PlayerRecruitmentUI&& _Other) noexcept = delete;
    PlayerRecruitmentUI& operator=(const PlayerRecruitmentUI& _Other) = delete;
    PlayerRecruitmentUI& operator=(PlayerRecruitmentUI&& _Other) noexcept = delete;

    void AllOn();

    void AllOff();

protected:
    std::shared_ptr<class GameEngineSpriteRenderer> BoxRenderer;
    std::shared_ptr<class GameEngineSpriteRenderer> CostIcon;
    std::shared_ptr<class GameEngineSpriteRenderer> CostText;
    std::shared_ptr<class GameEngineSpriteRenderer> MainText;

    std::shared_ptr<class GameEngineSpriteRenderer> RockBox;
    std::shared_ptr<class GameEngineSpriteRenderer> RockIcon;
    std::shared_ptr<class GameEngineSpriteRenderer> RockText;

    std::shared_ptr<class GameEngineSpriteRenderer> RockBox2;
    std::shared_ptr<class GameEngineSpriteRenderer> RockIcon2;
    std::shared_ptr<class GameEngineSpriteRenderer> RockText2;

    std::shared_ptr<class GameEngineSpriteRenderer> RockBox3;
    std::shared_ptr<class GameEngineSpriteRenderer> RockIcon3;
    std::shared_ptr<class GameEngineSpriteRenderer> RockText3;


    void Start() override;
    void Update(float _Delta) override;
    void LevelStart(GameEngineLevel* _PrevLevel) override;
    
    std::shared_ptr<class RecruitCard> Card;
    std::shared_ptr<class Default_Button> CancelButton = nullptr;
private:

};

