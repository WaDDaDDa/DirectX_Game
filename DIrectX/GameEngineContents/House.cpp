#include "PreCompile.h"
#include "House.h"

std::vector<std::shared_ptr<class Furniture>> House::FirstFloorFurniture;
std::vector<std::shared_ptr<class Furniture>> House::ScendFloorFurniture;

House::House()
{

}

House::~House()
{

}

void House::Start()
{

}

void House::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 300.0f});

	Ground = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackGround);
	Ground->SetSprite("House", 0);
	Ground->AutoSpriteSizeOn();
	Ground->SetAutoScaleRatio(3.0f);
	Ground->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackGround) });
	Ground->Transform.AddLocalPosition({ 0.0f, -290.0 });

	HouseRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackGround);
	HouseRenderer->SetSprite("House", 1);
	HouseRenderer->AutoSpriteSizeOn();
	HouseRenderer->SetAutoScaleRatio(3.0f);
	HouseRenderer->Transform.AddLocalPosition({ 0.0f, -2.0f, -static_cast<float>(ContentsOrder::BackGround) });

	// 475 -404
	ScendFloorFurniture.push_back(CreateFurniture({ 475.0f, -404.0f }, false, 8));
	ScendFloorFurniture.push_back(CreateFurniture({ 545.0f, -404.0f }, false, 1));
	ScendFloorFurniture.push_back(CreateFurniture({ 620.0f, -404.0f }, false, 6));
	ScendFloorFurniture.push_back(CreateFurniture({ 715.0f, -404.0f }, false, 6));
	ScendFloorFurniture.push_back(CreateFurniture({ 810.0f, -404.0f }, false, 6));

	FirstFloorFurniture.push_back(CreateFurniture({ 445.0f, -548.0f }, true, 3));
	FirstFloorFurniture.push_back(CreateFurniture({ 494.0f, -548.0f }, true, 3));
	FirstFloorFurniture.push_back(CreateFurniture({ 543.0f, -548.0f }, true, 3));
	FirstFloorFurniture.push_back(CreateFurniture({ 592.0f, -548.0f }, true, 3));
	FirstFloorFurniture.push_back(CreateFurniture({ 641.0f, -548.0f }, true, 3));
	FirstFloorFurniture.push_back(CreateFurniture({ 690.0f, -548.0f }, true, 3));
	FirstFloorFurniture.push_back(CreateFurniture({ 762.0f, -548.0f }, true, 21, { 1.8f, 1.8f, 1.8f }));
	FirstFloorFurniture.push_back(CreateFurniture({ 835.0f, -548.0f }, true, 32, { 1.8f, 1.8f, 1.8f }));

	FirstFloorFurniture[6]->Renderer->CreateAnimation("Idle", "furniture", 0.1f, 21, 21);
	FirstFloorFurniture[6]->Renderer->CreateAnimation("Use", "furniture", 0.1f, 22, 22);
}

void House::Update(float _Delta)
{

}

void House::LevelEnd(GameEngineLevel* _NextLevel)
{

}