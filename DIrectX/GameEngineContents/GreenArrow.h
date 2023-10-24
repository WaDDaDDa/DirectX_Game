#pragma once
#include "UI_Button.h"

class GreenArrow : public UI_Button
{
public:
    GreenArrow();
    ~GreenArrow();

    GreenArrow(const GreenArrow& _Other) = delete;
    GreenArrow(GreenArrow&& _Other) noexcept = delete;
    GreenArrow& operator=(const GreenArrow& _Other) = delete;
    GreenArrow& operator=(GreenArrow&& _Other) noexcept = delete;

    void DirChange()
    {
        Dir = !Dir;

        if (false == Dir)
        {
            Renderer->ChangeAnimation("Left_Null");
        }
        else if (true == Dir)
        {
            Renderer->ChangeAnimation("Right_Null");
        }
    }

protected:

    void Start() override;

    void IdleStart() override;

    void StayStart() override;

	void EndStart() override;

	void ClickStart() override;

    bool IsSelect = false;
    // false  ¿ÞÂÊ
    bool Dir = false;
private:

};

