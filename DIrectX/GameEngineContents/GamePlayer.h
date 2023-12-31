#pragma once
#include "HouseUnit.h"

class GamePlayerInfo
{
public:
    void Random()
    {
        Namelist.push_back("Faker");
        Namelist.push_back("Deft");
        Namelist.push_back("Peanut");
        Namelist.push_back("Bdd");
        Namelist.push_back("Ruler");
        Namelist.push_back("Chovy");
        Namelist.push_back("Score");
        Namelist.push_back("Lehenhs");
        Namelist.push_back("Kiin");
        Namelist.push_back("ShowMaker");
        Namelist.push_back("Cuzz");
        Namelist.push_back("Kanyon");
        Namelist.push_back("Teddy");
        Namelist.push_back("Kuro");
        Namelist.push_back("Keria");
        Namelist.push_back("Doran");
        Namelist.push_back("Ghost");
        Namelist.push_back("Life");
        Namelist.push_back("Rascal");
        Namelist.push_back("BeryL");
        Namelist.push_back("Mata");
        Namelist.push_back("Khan");
        Namelist.push_back("Clid");
        Namelist.push_back("Aiming");
        Namelist.push_back("Cuvee");
        Namelist.push_back("Effort");
        Namelist.push_back("Canna");
        Namelist.push_back("Viper");
        Namelist.push_back("Gumayusi");
        Namelist.push_back("Oner");
        Namelist.push_back("Kellin");
        Namelist.push_back("Zeus");
        Namelist.push_back("UmTi");
        Namelist.push_back("Crown");
        Namelist.push_back("MadLife");
        Namelist.push_back("Pyosik");
        Namelist.push_back("Nuguri");
        Namelist.push_back("Deokdam");
        Namelist.push_back("Kingen");
        Namelist.push_back("Shy");
        Namelist.push_back("CoreJJ");
        Namelist.push_back("Ucal");
        Namelist.push_back("Tazan");
        Namelist.push_back("Kuzan");
        Namelist.push_back("Zeka");
        Namelist.push_back("PeyZ");
        Namelist.push_back("Lucid");

        GameEngineRandom Rand;
        long long RandSeed = reinterpret_cast<long long>(this);
        RandSeed += Rand.RandomInt(0, 1000);
        Rand.SetSeed(RandSeed);
        size_t i = static_cast<size_t>(Rand.RandomInt(0, static_cast<int>(Namelist.size()) - 1));
        Name = Namelist[i];

        Att = static_cast<float>(Rand.RandomInt(3, 8));
        Def = static_cast<float>(Rand.RandomInt(3, 8));

        if ("Faker" == Name)
        {
            Att = 99;
            Def = 99;
        }

        Cost = Rand.RandomInt(90, 140);

        HairNum = Rand.RandomInt(1, 29);
    }

    void CpuRandom()
    {
        Namelist.push_back("Deft");
        Namelist.push_back("Peanut");
        Namelist.push_back("Bdd");
        Namelist.push_back("Ruler");
        Namelist.push_back("Score");
        Namelist.push_back("Lehenhs");
        Namelist.push_back("Kiin");
        Namelist.push_back("ShowMaker");
        Namelist.push_back("Cuzz");
        Namelist.push_back("Kanyon");
        Namelist.push_back("Teddy");
        Namelist.push_back("Kuro");
        Namelist.push_back("Keria");
        Namelist.push_back("Doran");
        Namelist.push_back("Ghost");
        Namelist.push_back("Life");
        Namelist.push_back("Rascal");
        Namelist.push_back("BeryL");
        Namelist.push_back("Mata");
        Namelist.push_back("Khan");
        Namelist.push_back("Clid");
        Namelist.push_back("Aiming");
        Namelist.push_back("Cuvee");
        Namelist.push_back("Effort");
        Namelist.push_back("Canna");
        Namelist.push_back("Viper");
        Namelist.push_back("Gumayusi");
        Namelist.push_back("Oner");
        Namelist.push_back("Kellin");
        Namelist.push_back("UmTi");
        Namelist.push_back("Crown");
        Namelist.push_back("MadLife");
        Namelist.push_back("Pyosik");
        Namelist.push_back("Nuguri");
        Namelist.push_back("Deokdam");
        Namelist.push_back("Kingen");
        Namelist.push_back("Shy");
        Namelist.push_back("CoreJJ");
        Namelist.push_back("Ucal");
        Namelist.push_back("Tazan");
        Namelist.push_back("Kuzan");
        Namelist.push_back("Zeka");
        Namelist.push_back("Lucid");
        Namelist.push_back("PeyZ");


        GameEngineRandom Rand;
        long long RandSeed = reinterpret_cast<long long>(this);
        RandSeed += Rand.RandomInt(0, 1000);
        Rand.SetSeed(RandSeed);
        size_t i = static_cast<size_t>(Rand.RandomInt(0, static_cast<int>(Namelist.size()) - 1));
        Name = Namelist[i];

        Att = static_cast<float>(Rand.RandomInt(2, 4));
        Def = static_cast<float>(Rand.RandomInt(2, 4));

        Cost = Rand.RandomInt(90, 140);

        HairNum = Rand.RandomInt(1, 29);
    }

    float Att = 0.0f;
    float Def = 0.0f;
    int Cost = 0;
    int HairNum = 0;

    std::string Name = "";
private:
    std::vector<std::string> Namelist;
};

class GamePlayer : public HouseUnit
{
public:
    GamePlayer();
    ~GamePlayer();

    GamePlayer(const GamePlayer& _Other) = delete;
    GamePlayer(GamePlayer&& _Other) noexcept = delete;
    GamePlayer& operator=(const GamePlayer& _Other) = delete;
    GamePlayer& operator=(GamePlayer&& _Other) noexcept = delete;

    void Init(GameEngineLevel* _NextLevel);
    void SpecInit(GamePlayerInfo _Spec);

    GamePlayerInfo GetSpec()
    {
        return Spec;
    }

protected:
    void Start() override;
    void LevelStart(GameEngineLevel* _NextLevel) override;
    void Update(float _Delta) override;

    std::shared_ptr<class GameEngineSpriteRenderer> NameText;
    GamePlayerInfo Spec;
private:

};

