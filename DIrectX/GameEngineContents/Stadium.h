#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Stadium : public GameEngineActor
{
public:
    Stadium();
    ~Stadium();

    Stadium(const Stadium& _Other) = delete;
    Stadium(Stadium&& _Other) noexcept = delete;
    Stadium& operator=(const Stadium& _Other) = delete;
    Stadium& operator=(Stadium&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> StadiumRenderer;
    std::shared_ptr<class GameEngineSpriteRenderer> BackDesk;
    std::shared_ptr<class GameEngineSpriteRenderer> Chair;
    std::shared_ptr<class GameEngineSpriteRenderer> Desk;
    std::shared_ptr<class GameEngineSpriteRenderer> Frame;

};

