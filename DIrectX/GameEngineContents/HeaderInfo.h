#pragma once
#include <GameEngineCore/GameEngineActor.h>

class HeaderInfo : public GameEngineActor
{
public:
    HeaderInfo();
    ~HeaderInfo();

    HeaderInfo(const HeaderInfo& _Other) = delete;
    HeaderInfo(HeaderInfo&& _Other) noexcept = delete;
    HeaderInfo& operator=(const HeaderInfo& _Other) = delete;
    HeaderInfo& operator=(HeaderInfo&& _Other) noexcept = delete;

    void SetIcon(std::string_view _Name, unsigned int _index)
    {
        Icon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
        Icon->SetSprite(_Name, _index);
        Icon->AutoSpriteSizeOn();
        Icon->SetAutoScaleRatio(2.0f);
        Icon->Transform.AddLocalPosition({-90.0f});
        Icon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
    }

    void SetText(const std::string& _Text)
    {
        Text = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
        Text->SetText("Galmuri14", _Text, 20.0f, float4::WHITE, FW1_RIGHT);
        Text->Transform.AddLocalPosition({ 105.0f });
        Text->Transform.AddLocalPosition({ 0.0f, 10.0f, -static_cast<float>(ContentsOrder::Text) });
    }


protected:
    void Start() override;
    void Update(float _Delta) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> BackGround;
    std::shared_ptr<class GameEngineSpriteRenderer> Icon;
    std::shared_ptr<class GameEngineSpriteRenderer> Text;

};

