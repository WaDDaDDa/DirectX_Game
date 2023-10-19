#pragma once
#include <GameEngineCore/GameEngineLevel.h>


class BattleLevel : public GameEngineLevel
{
public:
    BattleLevel();
    ~BattleLevel();

    BattleLevel(const BattleLevel& _Other) = delete;
    BattleLevel(BattleLevel&& _Other) noexcept = delete;
    BattleLevel& operator=(const BattleLevel& _Other) = delete;
    BattleLevel& operator=(BattleLevel&& _Other) noexcept = delete;

    std::vector<class GameUnit*> RedTeam;
    std::vector<class GameUnit*> BlueTeam;

    void UnitSetting();

    std::shared_ptr<GameUnit> CrateUnit(std::string_view _Name);

protected:
    void Start() override;

    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:

};

