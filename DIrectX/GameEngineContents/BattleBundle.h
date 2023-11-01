#pragma once
#include "ButtonBundle.h"

class BattleBundle : public ButtonBundle
{
public:
    BattleBundle();
    ~BattleBundle();

    BattleBundle(const BattleBundle& _Other) = delete;
    BattleBundle(BattleBundle&& _Other) noexcept = delete;
    BattleBundle& operator=(const BattleBundle& _Other) = delete;
    BattleBundle& operator=(BattleBundle&& _Other) noexcept = delete;

protected:
    void Start() override;

private:

};

