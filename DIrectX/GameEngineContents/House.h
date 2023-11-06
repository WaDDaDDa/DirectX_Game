#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Furniture
{
public:
    float4 Pos = float4::ZERO;
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    bool IsFirstFloor = true;
    bool IsUse = false;
};

class House : public GameEngineActor
{
public:
    House();
    ~House();

    House(const House& _Other) = delete;
    House(House&& _Other) noexcept = delete;
    House& operator=(const House& _Other) = delete;
    House& operator=(House&& _Other) noexcept = delete;

    static std::vector<std::shared_ptr<class Furniture>> FirstFloorFurniture;
    static std::vector<std::shared_ptr<class Furniture>> ScendFloorFurniture;

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class Furniture> CreateFurniture(float4 _Pos, bool _IsFirstFloor, int _Num, float4 _Mulcolor = float4::ONE)
    {
        std::shared_ptr<class Furniture> Gagoo = std::make_shared<class Furniture>();
        Gagoo->Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
        Gagoo->Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
        
        Gagoo->Renderer->SetSprite("furniture", _Num);
        Gagoo->Renderer->AutoSpriteSizeOn();
        Gagoo->Renderer->SetAutoScaleRatio(3.0f);
        Gagoo->Renderer->SetPivotType(PivotType::Bottom);

        Gagoo->Pos = _Pos + float4{ 0.0f, 0.0f, Gagoo->Renderer->Transform.GetWorldPosition().Z};
        Gagoo->IsFirstFloor = _IsFirstFloor;
        Gagoo->Renderer->Transform.SetWorldPosition(Gagoo->Pos);

        Gagoo->Renderer->GetColorData().MulColor = _Mulcolor;

        return Gagoo;
    }

    std::shared_ptr<class GameEngineSpriteRenderer> Ground;
    std::shared_ptr<class GameEngineSpriteRenderer> HouseRenderer;



};

