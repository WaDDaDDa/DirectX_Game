#include "PreCompile.h"
#include "FadeEffect.h"

FadeEffect::FadeEffect()
{

}

FadeEffect::~FadeEffect()
{

}

void FadeEffect::Start()
{
	EffectUnit.SetMesh("FullRect");
	EffectUnit.SetMaterial("FadeOutEffect");
	EffectUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	EffectUnit.ShaderResHelper.SetConstantBufferLink("FadeInfo", FadeEffectInfoValue);
	EffectUnit.ShaderResHelper.SetSampler("FadeTexSampler", "POINT");
	EffectUnit.ShaderResHelper.SetTexture("FadeTex", EffectTarget->GetTexture(0));

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	ResultTarget = GameEngineRenderTarget::Create();
	ResultTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
}

void FadeEffect::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	if (1.0f <= RenderBaseInfoValue.AccDeltaTime * FadeEffectInfoValue.FadeSpeed && "" != LevelName)
	{
 		GameEngineCore::ChangeLevel(LevelName);
	}

	EffectTarget->Copy(0, ResultTarget, 0);
}