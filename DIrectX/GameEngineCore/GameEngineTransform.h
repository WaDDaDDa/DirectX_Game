#pragma once
#include <GameEngineBase/GameEngineMath.h>

// 기하구조를 표현하고
// 부모자식관계를 처리한다.

// 왜 굳이. 
class TransformData
{
public:
	// 크기 -> 회전 -> 이동
	float4 Scale;
	float4 Rotation;
	float4 Position;

	// 로컬크기 -> 로컬회전 -> 로컬이동
	float4 LocalScale;
	float4 LocalRotation;
	float4 LocalPosition;

	// 월드크기 -> 월드회전 -> 월드이동
	float4 WorldScale;
	float4 WorldRotation;
	float4 WorldPosition;

	// 크기 행렬
	float4 ScaleMatrix;
	// 회전 행렬
	float4 RotationMatrix;
	// 이동 행렬
	float4 PositionMatrix;
	// 로컬->월드 행렬
	float4 LocalWorldMatrix;
	// 월드행렬
	float4 WorldMatrix;
	// 뷰행렬
	float4 View;
	// 투영행렬
	float4 Projection;
	// 뷰포트 행렬
	float4 ViewPort;
	// 통합 FOV
	float4 WorldViewPorjectionMatrix;
};

// 설명 :
class GameEngineTransform
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

protected:

private:
	TransformData TransData;
};

