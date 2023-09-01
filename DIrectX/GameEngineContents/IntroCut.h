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
	void Start();
	void Update(float _Delta);

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

    void MaxStart();
    void MaxUpdate(float _Delta);

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;
    // 텍스트 박스 임시.
	std::shared_ptr< GameEngineSpriteRenderer> TextBoxRenderer;
    float4 TextBoxScale = { 1280.0f, 170.0f };
    float4 TextBoxPos = { 0.0f, -275.0f };

    // 텍스트 Arrow
    std::shared_ptr<class TextArrow> Arrow = nullptr;
 
    int Scene = 0;

    IntroCutState State = IntroCutState::Max;

};

