#pragma once
#include "Ninja.h"

class NinjaUlt : public Ninja
{
public:
    NinjaUlt();
    ~NinjaUlt();

    NinjaUlt(const NinjaUlt& _Other) = delete;
    NinjaUlt(NinjaUlt&& _Other) noexcept = delete;
    NinjaUlt& operator=(const NinjaUlt& _Other) = delete;
    NinjaUlt& operator=(NinjaUlt&& _Other) noexcept = delete;

protected:
    void Start() override;

    //void SpwanStart() override;
    void SpwanStart() override;

    void Update(float _Delta) override;

    void DieStart() override;
private:

};

