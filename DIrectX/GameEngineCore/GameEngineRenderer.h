#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"
#include "GameEngineMesh.h"
#include "GameEngineMaterial.h"
#include "GameEngineRenderUnit.h"

struct RenderBaseInfo
{
	float4 BaseColor;
	int IsMask = 0;
	int BaseColorOnly = 0;
	int MaskMode = 0;
	int BaseTemp2 = 0;
	float4 RendererScreenPos;
	float4 RenderScreenScale;
	float4 MaskScreeneScale;
	float4 MaskPivot;
	float4 VertexUVPlus;
	float4 VertexUVMul = float4::ONE;
	float DeltaTime = 0.0f;
	float AccDeltaTime = 0.0f;
	int Target0 = 1;
	int Target1 = 0;
	int Target2 = 0;
	int Target3 = 0;
	int Target4 = 0;
	int Target5 = 0;
	int Target6 = 0;
	int Target7 = 0;
};

// 설명 : GameEngineRenderer에게 Order는 랜더링 되는 순서를 의미합니다.
class GameEngineRenderer : public GameEngineComponent
{
	friend class GameEngineCamera;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// 이걸 좀더 간다면
	// 카메라의 경우에는 
	// 이게 무조건 호출되야 합니다.
	// 하나의 랜더러를 여러개의 여러개의 카메라가 바라볼수 있다.
	// 내가 옴겨다니는 개념이 아니다.
	void SetViewCameraSelect(int _Order);

	// 모든 카메라에서 나를 빼고

	// 나를 봐주는 카메라를 바꾸겠다는 

	// 날바라보던 모든 카메라에서 나를 삭제하고
	// _Order 카메라로 이동하는거.
	// void SetChangeViewCameraAllClear(int _Order);

	void SetRenderOrder(int _Order);

	template <typename EnumType>
	void SetRenderOrder(EnumType _Order)
	{
		SetRenderOrder(static_cast<int>(_Order));
	}

	void SetCameraOrder(ECAMERAORDER _Order)
	{
		SetCameraOrder(static_cast<int>(_Order));
	}
	void SetCameraOrder(int _Order);

	// Create PushBack형식이 아닙니다.
	// 0번 랜더 유니트를 만든다고 치면 0번째에 랜더 유니트가 만들어 집니다.
	// 8번을 하면 vector가 확장되고 8번째에 랜더 유니트를 만들게 됩니다.
	std::shared_ptr<GameEngineRenderUnit> CreateAndFindRenderUnit(int _Index = 0);

	void SetMesh(std::string_view _Name, int _Index = 0);
	void SetMaterial(std::string_view _Name, int _Index = 0);

	GameEngineShaderResHelper& GetShaderResHelper(int _Index = 0);

	RenderBaseInfo RenderBaseInfoValue;

	float4 GetScreenPosition();

protected:
	void Start();
	void Update(float _Delta) override;

	virtual void Render(class GameEngineCamera* _Camera, float _Delta);
	virtual void SetMaterialEvent(std::string_view _Name, int _Index = 0);

	//std::shared_ptr<class GameEngineInputLayOut> LayOut;
	//std::shared_ptr<class GameEngineMesh> Mesh;
	//std::shared_ptr<class GameEngineMaterial> Material;
	//GameEngineShaderResHelper ShaderResHelper;

	std::vector<std::shared_ptr<GameEngineRenderUnit>> Units;

private:
	class GameEngineCamera* Camera = nullptr;
};

