#pragma once
#include <GameEngineCore/GameEngineActor.h>

class House_UI : public GameEngineActor
{
public:
    House_UI();
    ~House_UI();

    House_UI(const House_UI& _Other) = delete;
    House_UI(House_UI&& _Other) noexcept = delete;
    House_UI& operator=(const House_UI& _Other) = delete;
    House_UI& operator=(House_UI&& _Other) noexcept = delete;

protected:
    void Start();
    void Update(float _Delta);

private:



};

