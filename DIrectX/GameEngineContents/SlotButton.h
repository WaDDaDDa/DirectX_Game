#pragma once
#include "UI_Button.h"

class SlotButton : public UI_Button
{
public:
    SlotButton();
    ~SlotButton();

    SlotButton(const SlotButton& _Other) = delete;
    SlotButton(SlotButton&& _Other) noexcept = delete;
    SlotButton& operator=(const SlotButton& _Other) = delete;
    SlotButton& operator=(SlotButton&& _Other) noexcept = delete;

protected:

    void Start() override;

    void IdleStart() override;

    void StayStart() override;

	void EndStart() override;

	void ClickStart() override;

    bool IsSelect = false;

private:

};

