#pragma once
#include "UI_Button.h"

class Default_Button : public UI_Button
{
public:
    Default_Button();
    ~Default_Button();

    Default_Button(const Default_Button& _Other) = delete;
    Default_Button(Default_Button&& _Other) noexcept = delete;
    Default_Button& operator=(const Default_Button& _Other) = delete;
    Default_Button& operator=(Default_Button&& _Other) noexcept = delete;

    void IsImportantFalse()
    {
        IsImportant = false;

        if (false == IsImportant)
        {
            Renderer->ChangeAnimation("Null");
        }
    }

    void IsImportantTrue()
    {
        IsImportant = true;

        if (true == IsImportant)
        {
            Renderer->ChangeAnimation("Important");
        }
    }

protected:

    void Start() override;

    void IdleStart() override;

    void StayStart() override;

	void EndStart() override;

	void ClickStart() override;

    bool IsImportant = false;

private:

};

