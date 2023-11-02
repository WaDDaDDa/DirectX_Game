#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Cloud : public GameEngineActor
{
public:
    Cloud();
    ~Cloud();

    Cloud(const Cloud& _Other) = delete;
    Cloud(Cloud&& _Other) noexcept = delete;
    Cloud& operator=(const Cloud& _Other) = delete;
    Cloud& operator=(Cloud&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    float MoveSpeed = 1.0f;

};

