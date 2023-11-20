#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class AwardsState
{
    CurtainOpen,
    CutScene1,
    CutScene2,
    CutScene3,
    CutScene4,
    CutScene5,
    CutScene6,
    CutScene7,
    CutScene8,
    CurtainClose,
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

    void ChangeState(AwardsState _State);

    void ChangeState(int _Value)
    {
        ChangeState(static_cast<AwardsState>(_Value));
    }

    void StateUpdate(float _Delta);

    void CurtainOpenStart();
    void CurtainOpenUpdate(float _Delta);

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

    void CutScene8Start();
    void CutScene8Update(float _Delta);

    void CurtainCloseStart();
    void CurtainCloseUpdate(float _Delta);

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

    float CurtainValue = 0.0f;

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

    std::shared_ptr<GameEngineSpriteRenderer> LeftCurtain;
    std::shared_ptr<GameEngineSpriteRenderer> RightCurtain;

    std::shared_ptr<GameEngineSpriteRenderer> WinnerLogo;
    std::shared_ptr<GameEngineSpriteRenderer> WinnerName;
    std::shared_ptr<GameEngineSpriteRenderer> WinnerText;


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
    // 7Text = 6Text + Winner + 7Text
    std::wstring Scene6Text = L"아마추어 리그 준우승팀은..."; 
    std::wstring Scene6_1Text = L" 입니다! 축하합니다!\n준우승팀에게는 상품으로 아마추어 실버 마우스 및 상금 200G가 수여됩니다.";
    std::wstring Scene7Text = L"";
    std::wstring Scene8Text = L"이상으로 시즌 2023 아마추어 리그의 시상식을 마치도록 하겠습니다.\n다음 시즌에 다시 만납시다!!"; 
};

