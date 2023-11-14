#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PlayerSquadUI : public GameEngineActor
{
public:
    PlayerSquadUI();
    ~PlayerSquadUI();

    PlayerSquadUI(const PlayerSquadUI& _Other) = delete;
    PlayerSquadUI(PlayerSquadUI&& _Other) noexcept = delete;
    PlayerSquadUI& operator=(const PlayerSquadUI& _Other) = delete;
    PlayerSquadUI& operator=(PlayerSquadUI&& _Other) noexcept = delete;

    void AllDeath();
protected:

    void Start() override;
    void Update(float _Delta) override;
    void LevelStart(GameEngineLevel* _PrevLevel) override;

    std::shared_ptr<class GameEngineSpriteRenderer> BoxRenderer;
    std::shared_ptr<class GameEngineSpriteRenderer> MainText;
    std::shared_ptr<class GameEngineSpriteRenderer> MainText2;
    std::shared_ptr<class GameEngineSpriteRenderer> MainText3;
    std::shared_ptr<class GameEngineSpriteRenderer> MainText4;
    std::shared_ptr<class GameEngineSpriteRenderer> MainText5;
    std::vector<std::shared_ptr<class PlayerSquadCard>> CardGroup;

    std::shared_ptr<class Default_Button> Button = nullptr;

    float4 StartPos = { 0.0f, 100.0f };
    float4 InterY = { 0.0f, -80.0f };

private:

};

