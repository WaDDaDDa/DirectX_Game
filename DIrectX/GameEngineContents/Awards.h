#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class AwardsState
{
    CutScene1,
    CutScene2,
    CutScene3,
    CutScene4,
    CutScene5,
    CutScene6,
    CutScene7,
    NewGame,
    Black,
    Max,
};

// 설명 :
class Awards : public GameEngineActor
{
public:
    Awards();
    ~Awards();

    Awards(const Awards& _Other) = delete;
    Awards(Awards&& _Other) noexcept = delete;
    Awards& operator=(const Awards& _Other) = delete;
    Awards& operator=(Awards&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    void BlackStart();
    void BlackUpdate(float _Delta);

    void ChangeState(AwardsState _State);

    void ChangeState(int _Value)
    {
        ChangeState(static_cast<AwardsState>(_Value));
    }

    void StateUpdate(float _Delta);

    void CutScene1Start();
    void CutScene1Update(float _Delta);

    void CutScene2Start();
    void CutScene2Update(float _Delta);

    void CutScene3Start();
    void CutScene3Update(float _Delta);

    void CutScene4Start();
    void CutScene4Update(float _Delta);

    void CutScene5Start();
    void CutScene5Update(float _Delta);

    void CutScene6Start();
    void CutScene6Update(float _Delta);

    void CutScene7Start();
    void CutScene7Update(float _Delta);

    void NewGameStart();
    void NewGameUpdate(float _Delta);

    void MaxStart();
    void MaxUpdate(float _Delta);

    void CoachHairCheck(const SpriteData& _CurSprite);

    void HairCheck(const SpriteData& _CurSprite);
    void HairCheck2(const SpriteData& _CurSprite);
    void HairCheck3(const SpriteData& _CurSprite);
    float4 CheckPos = { 32.0f, 0.0f };

    void UnitOff();
    void UnitOn();
    void UnitBlack();
    void UnitWhite();
    void UnitIdle();
    void UnitWin();
    void PlayerWinUnit();
    void PlayerLoseUnit();

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;
    // 텍스트 박스 임시.
	std::shared_ptr< GameEngineSpriteRenderer> TextBoxBg;
	std::shared_ptr< GameEngineSpriteRenderer> TextBoxRenderer;
    float4 TextBoxPos = { 0.0f, -275.0f };
 
    std::shared_ptr<GameEngineSpriteRenderer> ModeratorRenderer;

    std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> CoachFrameFunction;

    std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> FrameFunction;
    std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> FrameFunction2;
    std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> FrameFunction3;

    std::shared_ptr<GameEngineSpriteRenderer> CoachBody;
    std::shared_ptr<GameEngineSpriteRenderer> CoachHair;

    std::shared_ptr<GameEngineSpriteRenderer> WinnerUnitBody;
    std::shared_ptr<GameEngineSpriteRenderer> WinnerUnitHair;
    std::shared_ptr<GameEngineSpriteRenderer> WinnerUnitBody2;
    std::shared_ptr<GameEngineSpriteRenderer> WinnerUnitHair2;
    std::shared_ptr<GameEngineSpriteRenderer> WinnerUnitBody3;
    std::shared_ptr<GameEngineSpriteRenderer> WinnerUnitHair3;

    std::shared_ptr<GameEngineSpriteRenderer> LightRenderer;


    int Scene = 0;
    float SceneTime = 0.0f;
    size_t CurTextNum = 0;

    bool TextSkip = false;

    AwardsState State = AwardsState::Max;
    std::string PrintText = "";
    std::wstring CurText = L"";
    std::wstring Scene1Text = L"지금부터 시즌 2023 아마추어 리그의 시상식을 시작하겠습니다!";
    std::wstring Scene2Text = L"먼저 우승팀 시상이 있겠습니다."; 
    std::wstring Scene3Text = L"아마추어 리그 우승팀은..."; 
    // 4Text = 3Text + Winner + 4Text
    std::wstring Scene3_1Text = L" 입니다! 축하합니다!\n우승팀에게는 상품으로 아마추어 골든 마우스 및 상금 400G가 수여됩니다."; 
    std::wstring Scene4Text = L""; 
    std::wstring Scene5Text = L"다음으로는 준우승팀 시상이 있겠습니다."; 
    std::wstring Scene6Text = L"하지만 내가 정말 천재인걸까? 좋은 동료와 환경 덕분에 이룬 \n결과인 건 아닐까? 나는 새로운 도전을 하고 싶었다."; 
    std::wstring Scene7Text = L"아마추어 최하위 팀을 키워서 월드 챔피언십을 우승해보자. \n그땐 만족할 수 있겠지. 그리고 내가 맡게 된 팀은..."; 
};

