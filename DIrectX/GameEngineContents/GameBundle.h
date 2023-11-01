#pragma once
#include "ButtonBundle.h"

class GameBundle : public ButtonBundle
{
public:
    GameBundle();
    ~GameBundle();

    GameBundle(const GameBundle& _Other) = delete;
    GameBundle(GameBundle&& _Other) noexcept = delete;
    GameBundle& operator=(const GameBundle& _Other) = delete;
    GameBundle& operator=(GameBundle&& _Other) noexcept = delete;

protected:
    void Start() override;

private:

};

