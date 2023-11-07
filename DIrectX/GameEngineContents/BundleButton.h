#pragma once
#include "UI_Button.h"

class BundleButton : public UI_Button
{
public:
    BundleButton();
    ~BundleButton();

    BundleButton(const BundleButton& _Other) = delete;
    BundleButton(BundleButton&& _Other) noexcept = delete;
    BundleButton& operator=(const BundleButton& _Other) = delete;
    BundleButton& operator=(BundleButton&& _Other) noexcept = delete;

    void IsSelectFalse()
    {
        IsSelect = false;

        if (false == IsSelect)
        {
            Renderer->ChangeAnimation("Null");
        }
    }

    void IsSelectTrue()
    {
        IsSelect = true;

        if (true == IsSelect)
        {
            Renderer->ChangeAnimation("Slect");
        }
    }

    void SetButtonText(const std::string& _Text, float4 _Pos = float4::ZERO, FW1_TEXT_FLAG _Flag = FW1_CENTER)
    {
        ButtonText = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Text);
        ButtonText->SetText("Galmuri14", _Text, 16.0f, float4::WHITE, _Flag);
        ButtonText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
        ButtonText->Transform.AddLocalPosition({ 0.0f, 7.0f });
        ButtonText->Transform.AddLocalPosition(_Pos);
        ButtonName = _Text;
        Flag = _Flag;
    }

    void SetIcon(std::string_view _Name, unsigned int _Index /*= 0*/)
    {
        std::shared_ptr<class GameEngineSpriteRenderer> IconRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UIImage);
        IconRenderer->SetSprite(_Name, _Index);
        IconRenderer->AutoSpriteSizeOn();
        IconRenderer->SetAutoScaleRatio(2.0f);

        IconRenderer->Transform.AddLocalPosition({ -45.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
    }

protected:
    void Start() override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    void IdleStart() override;

    void StayStart() override;

	void EndStart() override;

	void ClickStart() override;

    bool IsSelect = false;
    std::shared_ptr<class GameEngineSpriteRenderer> ButtonText = nullptr;
    std::string ButtonName = "";
    FW1_TEXT_FLAG Flag = FW1_LEFT;
private:

};

