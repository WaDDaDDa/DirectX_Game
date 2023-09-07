#pragma once
#include <list>
#include <memory>
#include "GameEngineCollision.h"

// 설명 :
class GameEngineCollisionGroup : public GameEngineObject
{
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineCollisionGroup();
	~GameEngineCollisionGroup();

	// delete Function
	GameEngineCollisionGroup(const GameEngineCollisionGroup& _Other) = delete;
	GameEngineCollisionGroup(GameEngineCollisionGroup&& _Other) noexcept = delete;
	GameEngineCollisionGroup& operator=(const GameEngineCollisionGroup& _Other) = delete;
	GameEngineCollisionGroup& operator=(GameEngineCollisionGroup&& _Other) noexcept = delete;

	// 해당 그룹이랑 충돌했어? 식의 함수
	bool Collision(std::shared_ptr<GameEngineCollision> _Collision);

	// NextPos에 가면 해당그룹이랑 충돌해? 식의 함수.
	bool Collision(std::shared_ptr<GameEngineCollision> _Collision, const float4& _NextPos);
	
	// 충돌한 그룹의 어떤녀석이랑 충돌했지? 알수있다.
	bool Collision(std::shared_ptr<GameEngineCollision> _Collision, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function);

	// NextPos에서 충돌한 그룹의 어떤녀석이랑 충돌했지? 알수있다.
	bool Collision(std::shared_ptr<GameEngineCollision> _Collision, const float4& _NextPos, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function);

	// 충돌 시작, 충돌 중, 충돌 끝  을 이벤트파라미터로 사용할수있다.
	bool CollisionEvent(std::shared_ptr<GameEngineCollision> _Collision, const EventParameter& _Event);

protected:
	void AllReleaseCheck() override;

private:
	void PushCollision(std::shared_ptr<class GameEngineCollision> _Collision);

	std::list<std::shared_ptr<class GameEngineCollision>> Collisions;
};

