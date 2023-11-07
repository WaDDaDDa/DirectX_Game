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

    void SetButtonText(const std::string& _Text)
    {
        std::shared_ptr<class GameEngineSpriteRenderer> ButtonText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
        ButtonText->SetText("Galmuri14", _Text, 16.0f, float4::WHITE, FW1_CENTER);
        ButtonText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
        ButtonText->Transform.AddLocalPosition({ 0.0f, 5.0f });
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

