#pragma once
#include "ButtonBundle.h"

class ManagerBundle : public ButtonBundle
{
public:
    ManagerBundle();
    ~ManagerBundle();

    ManagerBundle(const ManagerBundle& _Other) = delete;
    ManagerBundle(ManagerBundle&& _Other) noexcept = delete;
    ManagerBundle& operator=(const ManagerBundle& _Other) = delete;
    ManagerBundle& operator=(ManagerBundle&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Delta) override;

private:

};

