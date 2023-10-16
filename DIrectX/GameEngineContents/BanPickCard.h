#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class BanPickState
{
    Idle,
    Stay,
    Select,
    Max,
};

class BanPickCard : public GameEngineActor
{
public:
    BanPickCard();
    ~BanPickCard();

    BanPickCard(const BanPickCard& _Other) = delete;
    BanPickCard(BanPickCard&& _Other) noexcept = delete;
    BanPickCard& operator=(const BanPickCard& _Other) = delete;
    BanPickCard& operator=(BanPickCard&& _Other) noexcept = delete;

    float4 StartPos = { -370.0f, 75.0f, 100.0f };
    void Init(const class GameUnitStatus& _Status);

    BanPickState State = BanPickState::Max;
    
    std::string GetUnitName()
    {
        return UnitName.data();
    }

    static float XInter;

protected:
    void Start() override;
    void Update(float _Delta) override;

    void ChangeState(BanPickState _State);
    void StateUpdate(float _Delta);

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    void MaxStart();
    void MaxUpdate(float _Delta);

    void IdleStart();
    void IdleUpdate(float _Delta);

    std::string_view UnitName = "";

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;

    std::shared_ptr<class GameEngineSpriteRenderer> UnitImage;
    float4 UnitImagePos = { 0.0f, -10.0f };

};

