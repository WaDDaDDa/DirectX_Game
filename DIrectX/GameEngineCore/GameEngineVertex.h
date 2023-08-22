#pragma once
#include "GameEngineInputLayOut.h"
// Input LayOut이란 점 1개의 구조에요.

// 설명 : 애가 제일 잘알고 있어야 합니다.
class GameEngineVertex2D
{
public:
	static GameEngineInputLayOutInfo VertexInfo;

	// 내가 얼마든지 순서를 바꿀수 있다.
	// 그렇기 때문에 그래픽 카드에게 LayOutInfo를 통해 
	// 어느곳에 어떤데이터가 있는지 명시해 주어야 GPU는 알수있다.
public:
	float4 POSITION;
	float4 COLOR;
};


class GameEngine3DVertex
{
public:
	static GameEngineInputLayOutInfo VertexInfo;

public:
	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
	float4 NORMAL;
	float4 BINORMAL;
	float4 TANGENT;
	float4 WEIGHT;
	int BLENDINDICES[4];
};