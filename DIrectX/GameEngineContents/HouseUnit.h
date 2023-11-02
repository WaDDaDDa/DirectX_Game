#pragma once
#include <GameEngineCore/GameEngineActor.h>

class HouseUnit : public GameEngineActor
{
public:
    HouseUnit();
    ~HouseUnit();

    HouseUnit(const HouseUnit& _Other) = delete;
    HouseUnit(HouseUnit&& _Other) noexcept = delete;
    HouseUnit& operator=(const HouseUnit& _Other) = delete;
    HouseUnit& operator=(HouseUnit&& _Other) noexcept = delete;

protected:
    void Start();
    void Update(float _Delta);
    void LevelStart(GameEngineLevel* _NextLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    std::shared_ptr<class GameEngineSpriteRenderer> BodyRenderer;
    std::shared_ptr<class GameEngineSpriteRenderer> HairRenderer;
private:

};

