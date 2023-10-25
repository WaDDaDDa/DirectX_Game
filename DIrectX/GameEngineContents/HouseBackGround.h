#pragma once
#include <GameEngineCore/GameEngineActor.h>

class HouseBackGround : public GameEngineActor
{
public:
    HouseBackGround();
    ~HouseBackGround();

    HouseBackGround(const HouseBackGround& _Other) = delete;
    HouseBackGround(HouseBackGround&& _Other) noexcept = delete;
    HouseBackGround& operator=(const HouseBackGround& _Other) = delete;
    HouseBackGround& operator=(HouseBackGround&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> BackGround;


};

