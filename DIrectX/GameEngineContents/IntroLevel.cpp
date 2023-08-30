#include "PreCompile.h"
#include "IntroLevel.h"
#include "IntroCut.h"


IntroLevel::IntroLevel()
{

}

IntroLevel::~IntroLevel()
{

}

void IntroLevel::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		// 상위폴더를 입력해야 하위 폴더들을 로드할수있다.
		// Intro 로드한다고 치면 Intro상위 폴더를 지정해야한다.
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());

		}

	}

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	std::shared_ptr<IntroCut> NewIntro = CreateActor<IntroCut>();
}

void IntroLevel::Update(float _Delta)
{

}

void IntroLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void IntroLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}