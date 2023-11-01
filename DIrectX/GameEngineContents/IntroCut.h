#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class IntroCutState
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
class IntroCut : public GameEngineActor
{
public:
    IntroCut();
    ~IntroCut();

    IntroCut(const IntroCut& _Other) = delete;
    IntroCut(IntroCut&& _Other) noexcept = delete;
    IntroCut& operator=(const IntroCut& _Other) = delete;
    IntroCut& operator=(IntroCut&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    void BlackStart();
    void BlackUpdate(float _Delta);

    void ChangeState(IntroCutState _State);

    void ChangeState(int _Value)
    {
        ChangeState(static_cast<IntroCutState>(_Value));
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

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;
    // 텍스트 박스 임시.
	std::shared_ptr< GameEngineSpriteRenderer> TextBoxRenderer;
    float4 TextBoxPos = { 0.0f, -275.0f };

    // 텍스트 Arrow
    std::shared_ptr<class TextArrow> Arrow = nullptr;
 
    int Scene = 0;
    float SceneTime = 0.0f;
    size_t CurTextNum = 0;

    bool TextSkip = false;

    IntroCutState State = IntroCutState::Max;
    std::string PrintText = "";
    std::wstring CurText = L"";
    std::wstring Scene1Text = L"20xx년, Teamfight Arena는 출시되자마자 전세계적으로 \n선풍적인 인기를 끌었다.";
    std::wstring Scene2Text = L"당연하게도 프로스포츠로서의 인기 또한 대단했고, 나는 \n18살에 이 게임의 프로게이머로 데뷔했다."; 
    std::wstring Scene3Text = L"그 이후로 10년, 나는 프로게이머 생활을 하는 동안 단 한 \n번도 월드 챔피언십 우승 타이틀을 놓치지 않았다."; 
    std::wstring Scene4Text = L"프로 선수를 은퇴하고 감독 생활을 시작한 지 10년. 여전히 \n나는 월드 챔피언십 우승 타이틀을 놓치지 않았다."; 
    std::wstring Scene5Text = L"이렇게 선수 생활, 감독 생활을 하며 쌓인 트로피를 \n보고 있자면 가슴이 웅장해지곤 했다."; 
    std::wstring Scene6Text = L"하지만 내가 정말 천재인걸까? 좋은 동료와 환경 덕분에 이룬 \n결과인 건 아닐까? 나는 새로운 도전을 하고 싶었다."; 
    std::wstring Scene7Text = L"아마추어 최하위 팀을 키워서 월드 챔피언십을 우승해보자. \n그땐 만족할 수 있겠지. 그리고 내가 맡게 된 팀은..."; 
};

