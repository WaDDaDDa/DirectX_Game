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

protected:
    std::shared_ptr<class GameEngineSpriteRenderer> BoxRenderer;

    void Start() override;
    void Update(float _Delta) override;
    void LevelStart(GameEngineLevel* _PrevLevel) override;
    
    std::shared_ptr<class RecruitCard> Card;
private:

};

