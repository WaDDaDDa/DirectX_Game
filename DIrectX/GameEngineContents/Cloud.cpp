#include "PreCompile.h"
#include "Cloud.h"


Cloud::Cloud()
{

}

Cloud::~Cloud()
{

}

void Cloud::Start()
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ 0.0f, 0.0f, 350.0f });
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Water);

	//��������
	GameEngineRandom Rand;
	float PosY = Rand.RandomFloat(100.0f, 300.0f);
	//������ġ
	Transform.AddLocalPosition({ 1400.0f, -PosY });
	// �������
	int Num = Rand.RandomInt(0, 7);
	Renderer->SetSprite("MorningCloud", Num);
	// ���ǵ�
	MoveSpeed = Rand.RandomFloat(100.0f, 200.0f);


	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Water) });
}

void Cloud::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void Cloud::Update(float _Delta)
{
	Transform.AddLocalPosition(-MoveSpeed * _Delta);

	float Posx = Transform.GetWorldPosition().X;
	if (-400.0f >= Posx)
	{
		Death();
	}
}

void Cloud::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}