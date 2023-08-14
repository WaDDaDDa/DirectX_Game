#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
{
}

GameEngineTransform::~GameEngineTransform()
{
}


void GameEngineTransform::TransformUpdate()
{
	TransData.LocalCalculation();
	TransData.WorldMatrix = TransData.LocalWorldMatrix;

	if (nullptr != Parent)
	{
		TransData.ParentMatrix = Parent->TransData.WorldMatrix;
		TransData.WorldMatrix = TransData.LocalWorldMatrix * TransData.ParentMatrix;
	}

	CalChilds();
}


void GameEngineTransform::CalculationViewAndProjection(const TransformData& _Transform)
{
	CalculationViewAndProjection(_Transform.ViewMatrix, _Transform.ProjectionMatrix);
}

void GameEngineTransform::CalculationViewAndProjection(const float4x4& _View, const float4x4& _Projection)
{
	TransData.ViewMatrix = _View;
	TransData.ProjectionMatrix = _Projection;
	TransData.WorldViewProjectionCalculation();
}

void GameEngineTransform::CalChilds()
{
	// 자식이 없으면 그냥 리턴
	if (0 == Childs.size())
	{
		return;
	}
	// 자식이 있으면 자식의 Trans업데이트해줌
	for (GameEngineTransform* Trans : Childs)
	{
		Trans->TransformUpdate();
	}
}