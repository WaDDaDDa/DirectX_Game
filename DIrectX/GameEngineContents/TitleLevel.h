#pragma once
#include <GameEngineCore/GameEngineLevel.h>


class TitleLevel : public GameEngineLevel
{
public:
    TitleLevel();
    ~TitleLevel();

    TitleLevel(const TitleLevel& _Other) = delete;
    TitleLevel(TitleLevel&& _Other) noexcept = delete;
    TitleLevel& operator=(const TitleLevel& _Other) = delete;
    TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

    std::vector<class GameUnit*> RedTeam;
    std::vector<class GameUnit*> BlueTeam;

    std::vector<std::string> UseUnitName;

    void BlueUnitSetting();
    void RedUnitSetting();

    std::string CrateUnitName();

    std::shared_ptr<GameUnit> CrateUnit(std::string_view _Name);

    GameEngineRandom Rand;
    long long RandSeed = 0;

protected:
    void Start() override;

    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    class GameEngineSoundPlayer BGMPlayer;

};

