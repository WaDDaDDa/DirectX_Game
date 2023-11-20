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

// ���� :
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
    // �ؽ�Ʈ �ڽ� �ӽ�.
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
    std::wstring Scene1Text = L"���ݺ��� ���� 2023 �Ƹ��߾� ������ �û���� �����ϰڽ��ϴ�!";
    std::wstring Scene2Text = L"���� ����� �û��� �ְڽ��ϴ�."; 
    std::wstring Scene3Text = L"�Ƹ��߾� ���� �������..."; 
    // 4Text = 3Text + Winner + 4Text
    std::wstring Scene3_1Text = L" �Դϴ�! �����մϴ�!\n��������Դ� ��ǰ���� �Ƹ��߾� ��� ���콺 �� ��� 400G�� �����˴ϴ�."; 
    std::wstring Scene4Text = L""; 
    std::wstring Scene5Text = L"�������δ� �ؿ���� �û��� �ְڽ��ϴ�."; 
    // 7Text = 6Text + Winner + 7Text
    std::wstring Scene6Text = L"�Ƹ��߾� ���� �ؿ������..."; 
    std::wstring Scene6_1Text = L" �Դϴ�! �����մϴ�!\n�ؿ�������Դ� ��ǰ���� �Ƹ��߾� �ǹ� ���콺 �� ��� 200G�� �����˴ϴ�.";
    std::wstring Scene7Text = L"";
    std::wstring Scene8Text = L"�̻����� ���� 2023 �Ƹ��߾� ������ �û���� ��ġ���� �ϰڽ��ϴ�.\n���� ���� �ٽ� �����ô�!!"; 
};

