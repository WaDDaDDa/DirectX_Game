#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TextArrow : public GameEngineActor
{
public:
    TextArrow();
    ~TextArrow();

    TextArrow(const TextArrow& _Other) = delete;
    TextArrow(TextArrow&& _Other) noexcept = delete;
    TextArrow& operator=(const TextArrow& _Other) = delete;
    TextArrow& operator=(TextArrow&& _Other) noexcept = delete;

protected:
    void Start();
    void Update(float _Delta);

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

