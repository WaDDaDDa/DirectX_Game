#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"
#include <vector>
#include <set>

// 콜리전 이벤트
class EventParameter
{
public:
	std::function<void(class GameEngineCollision*, class GameEngineCollision* _Collisions)> Enter = nullptr;
	std::function<void(class GameEngineCollision*, class GameEngineCollision* _Collisions)> Stay = nullptr;
	std::function<void(class GameEngineCollision*, class GameEngineCollision* _Collisions)> Exit = nullptr;
};

// 설명 :
class GameEngineCollision : public GameEngineComponent
{
	friend class GameEngineCollisionGroup;
public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	// 충돌했다 안했다를 알고 싶으면 리턴값을 확인하면 되고.
	// 해당 그룹이랑 충돌했어? 식의 함수
	template<typename EnumType>
	bool Collision(EnumType _Order)
	{
		return Collision(static_cast<int>(_Order));
	}

	bool Collision(int _Order);

	// NextPos에 가면 해당그룹이랑 충돌해? 식의 함수.
	template<typename EnumType>
	bool Collision(EnumType _Order, const float4& _NextPos)
	{
		return Collision(static_cast<int>(_Order), _NextPos);
	}

	bool Collision(int _Order, const float4& _NextPos);

	// 충돌한 그룹의 어떤녀석이랑 충돌했지? 알수있다.
	template<typename EnumType>
	bool Collision(EnumType _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision)
	{
		return Collision(static_cast<int>(_Order), _Collision);
	}

	bool Collision(int _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision);

	// NextPos에서 충돌한 그룹의 어떤녀석이랑 충돌했지? 알수있다.
	template<typename EnumType>
	bool Collision(EnumType _Order, const float4& _Next, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision)
	{
		return Collision(static_cast<int>(_Order), _Next, _Collision);
	}

	bool Collision(int _Order, const float4& _Next, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision);

	// 충돌 시작, 충돌 중, 충돌 끝  을 이벤트파라미터로 사용할수있다.
	template<typename EnumType>
	bool CollisionEvent(EnumType _Order, const EventParameter& _Event)
	{
		return CollisionEvent(static_cast<int>(_Order), _Event);
	}

	bool CollisionEvent(int _Order, const EventParameter& _Event);

	// bool CollisionEnter(int _Order, const float4& _Next, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision);

	void SetCollisionType(ColType _CollisionType)
	{
		CollisionType = _CollisionType;
	}

	ColType GetCollisionType()
	{
		return CollisionType;
	}

protected:
	void Start() override;
	void Release() override;

private:
	ColType CollisionType = ColType::SPHERE2D;
	std::set<std::shared_ptr<GameEngineCollision>> Others;
};

