#pragma once
#include <GameEngineCore\GameEngineRenderTarget.h>

struct FadeEffectInfo
{
	int FadeIn = false;
	int Tex = 0;
	float StartColor = -1.0f;
	float FadeSpeed = 1.0f;
};

class FadeEffect : public Effect
{
public:
	// constructer destructer
	FadeEffect();
	~FadeEffect();

	// delete function
	FadeEffect(const FadeEffect& _Ohter) = delete;
	FadeEffect(FadeEffect&& _Ohter) noexcept = delete;
	FadeEffect& operator=(const FadeEffect& _Other) = delete;
	FadeEffect& operator=(FadeEffect&& _Other) noexcept = delete;

	void SetBlackFade()
	{
		FadeEffectInfoValue.StartColor = -1.0f;
	}

	void SetFadeSpeed(float _FadeSpeed)
	{
		FadeEffectInfoValue.FadeSpeed = _FadeSpeed;
	}

	void SetFadeIn()
	{
		FadeEffectInfoValue.FadeIn = true;
		EffectUnit.SetMaterial("FadeInEffect");
		EffectUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
		EffectUnit.ShaderResHelper.SetConstantBufferLink("FadeInfo", FadeEffectInfoValue);
		EffectUnit.ShaderResHelper.SetSampler("FadeTexSampler", "POINT");
		EffectUnit.ShaderResHelper.SetTexture("FadeTex", EffectTarget->GetTexture(0));
	}

	void FadeStart()
	{
		On();
	}

	void SetChangeLevelName(std::string _LevelName)
	{
		LevelName = _LevelName;
	}

protected:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;

	std::string LevelName = "";

private:
	bool IsFadeOn = false;
	FadeEffectInfo FadeEffectInfoValue;
};

