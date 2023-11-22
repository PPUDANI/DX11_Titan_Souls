#include "PreCompile.h"
#include "ColossusBodyMask.h"

ColossusBodyMask::ColossusBodyMask()
{
}

ColossusBodyMask::~ColossusBodyMask()
{
}

void ColossusBodyMask::Start()
{
	std::shared_ptr<GameEngineRenderTarget> Target = GameEngineCore::GetCurLevel()->GetMainCamera()->GetCameraAllRenderTarget();

	if (nullptr != Target)
	{
		ResultTarget = Target->CreateChildRenderTarget({ 0 });
	}

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("ColossusBodyMask");

	EffectUnit.ShaderResHelper.SetTexture("Tex0", Target->GetTexture(3));
	EffectUnit.ShaderResHelper.SetTexture("Tex1", Target->GetTexture(4));

	EffectUnit.ShaderResHelper.SetSampler("Tex0Sampler", "POINT");
	EffectUnit.ShaderResHelper.SetSampler("Tex1Sampler", "POINT");
}

void ColossusBodyMask::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	GameEngineRenderTarget::RenderTargetReset();
}