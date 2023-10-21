#pragma once
#include <GameEngineCore/GameEngineActor.h>

class CharacterCard : public GameEngineActor
{
public:
    CharacterCard();
    ~CharacterCard();

    CharacterCard(const CharacterCard& _Other) = delete;
    CharacterCard(CharacterCard&& _Other) noexcept = delete;
    CharacterCard& operator=(const CharacterCard& _Other) = delete;
    CharacterCard& operator=(CharacterCard&& _Other) noexcept = delete;

    void Init();

    void CreateStatus();


protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;
    float StartY = 200.0f;
    static float BlueYInter;
    static float RedYInter;

private:

    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;

    std::shared_ptr<class GameEngineSpriteRenderer> UnitImage;
    float4 UnitImagePos = { -49.0f, -8.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> AttIcon;
    float4 AttIconPos = { -65.0f, -32.0f };

    std::shared_ptr<class GameEngineSpriteRenderer> DefIcon;
    float4 DefIconPos = { 10.0f, -32.0f };

};

