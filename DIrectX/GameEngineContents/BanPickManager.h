#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BanPickManager : public GameEngineActor
{
public:
    BanPickManager();
    ~BanPickManager();

    BanPickManager(const BanPickManager& _Other) = delete;
    BanPickManager(BanPickManager&& _Other) noexcept = delete;
    BanPickManager& operator=(const BanPickManager& _Other) = delete;
    BanPickManager& operator=(BanPickManager&& _Other) noexcept = delete;

    void CardIntit();

protected:
    void Start() override;
    void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    size_t UnitCount = 8;
    std::vector<std::shared_ptr<class BanPickCard>> Card;
    std::shared_ptr<class UI_Mouse> GameMouse;
    std::shared_ptr<class BanPickBoard> GameBoard;
};

