#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Bird : public GameEngineActor
{
public:
    Bird();
    ~Bird();

    Bird(const Bird& _Other) = delete;
    Bird(Bird&& _Other) noexcept = delete;
    Bird& operator=(const Bird& _Other) = delete;
    Bird& operator=(Bird&& _Other) noexcept = delete;

protected:
    void Start();
    void Update(float _Delta);

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<GameEngineCollision> BodyCol;
    float4 BodyColScale = { 50.0f, 50.0f };

};

