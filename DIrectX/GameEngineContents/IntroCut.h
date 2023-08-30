#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class IntroCut : public GameEngineActor
{
public:
    IntroCut();
    ~IntroCut();

    IntroCut(const IntroCut& _Other) = delete;
    IntroCut(IntroCut&& _Other) noexcept = delete;
    IntroCut& operator=(const IntroCut& _Other) = delete;
    IntroCut& operator=(IntroCut&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta);

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;

};

