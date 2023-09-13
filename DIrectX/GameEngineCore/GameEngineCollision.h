#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"
#include <vector>
#include <set>

// �ݸ��� �̺�Ʈ
class EventParameter
{
public:
	std::function<void(class GameEngineCollision*, class GameEngineCollision* _Collisions)> Enter = nullptr;
	std::function<void(class GameEngineCollision*, class GameEngineCollision* _Collisions)> Stay = nullptr;
	std::function<void(class GameEngineCollision*, class GameEngineCollision* _Collisions)> Exit = nullptr;
};

// ���� :
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

	// �浹�ߴ� ���ߴٸ� �˰� ������ ���ϰ��� Ȯ���ϸ� �ǰ�.
	// �ش� �׷��̶� �浹�߾�? ���� �Լ�
	template<typename EnumType>
	bool Collision(EnumType _Order)
	{
		return Collision(static_cast<int>(_Order));
	}

	bool Collision(int _Order);

	// NextPos�� ���� �ش�׷��̶� �浹��? ���� �Լ�.
	template<typename EnumType>
	bool Collision(EnumType _Order, const float4& _NextPos)
	{
		return Collision(static_cast<int>(_Order), _NextPos);
	}

	bool Collision(int _Order, const float4& _NextPos);

	// �浹�� �׷��� ��༮�̶� �浹����? �˼��ִ�.
	template<typename EnumType>
	bool Collision(EnumType _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision)
	{
		return Collision(static_cast<int>(_Order), _Collision);
	}

	bool Collision(int _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision);

	// NextPos���� �浹�� �׷��� ��༮�̶� �浹����? �˼��ִ�.
	template<typename EnumType>
	bool Collision(EnumType _Order, const float4& _Next, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision)
	{
		return Collision(static_cast<int>(_Order), _Next, _Collision);
	}

	bool Collision(int _Order, const float4& _Next, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Collision);

	// �浹 ����, �浹 ��, �浹 ��  �� �̺�Ʈ�Ķ���ͷ� ����Ҽ��ִ�.
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

