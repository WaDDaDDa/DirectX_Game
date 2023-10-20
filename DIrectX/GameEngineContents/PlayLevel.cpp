#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "BanPickBoard.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	//UI�� ���� ��ġ�����
	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	//{
	//	// ������ ���̴��� ���δ� ���δ� �ε��ϴ� �ڵ带 ģ��.
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("GameEngineResources");
	//	Dir.MoveChild("ContentsResources");
	//	Dir.MoveChild("Texture");
	//	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	//	for (size_t i = 0; i < Files.size(); i++)
	//	{
	//		// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
	//		GameEngineFile& File = Files[i];
	//		GameEngineTexture::Load(File.GetStringPath());
	//	}

	//	GameEngineSprite::CreateCut("TestPlayer.png", 6, 6);
	//}

	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("GameEngineResources");
	//	Dir.MoveChild("ContentsResources");
	//	Dir.MoveChild("FolderTexture");
	//	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	//	for (size_t i = 0; i < Directorys.size(); i++)
	//	{
	//		// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
	//		GameEngineDirectory& Dir = Directorys[i];

	//		GameEngineSprite::CreateFolder(Dir.GetStringPath());

	//		// GameEngineTexture::Load(File.GetStringPath());
	//	}

	//	GameEngineSprite::CreateCut("TestPlayer.png", 6, 6);
	//}

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

}

void PlayLevel::Update(float _Delta)
{

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();
	CreateActor<BanPickBoard>();
	
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}