#pragma once
#include "ButtonBundle.h"

class SystemBundle : public ButtonBundle
{
public:
    SystemBundle();
    ~SystemBundle();

    SystemBundle(const SystemBundle& _Other) = delete;
    SystemBundle(SystemBundle&& _Other) noexcept = delete;
    SystemBundle& operator=(const SystemBundle& _Other) = delete;
    SystemBundle& operator=(SystemBundle&& _Other) noexcept = delete;

protected:
    void Start() override;

private:

};

