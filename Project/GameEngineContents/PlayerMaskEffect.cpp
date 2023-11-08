#include "PreCompile.h"
#include "PlayerMaskEffect.h"

PlayerMaskEffect::PlayerMaskEffect()
{
}

PlayerMaskEffect::~PlayerMaskEffect()
{
}

void PlayerMaskEffect::Start()
{
	std::shared_ptr<GameEngineRenderTarget> Target = GameEngineCore::GetCurLevel()->GetMainCamera()->GetCameraAllRenderTarget();

	if (nullptr != Target)
	{
		ResultTarget = Target->CreateChildRenderTarget({ 0 });
	}

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("PlayerMaskEffect");

	EffectUnit.ShaderResHelper.SetTexture("Tex0", Target->GetTexture(1));
	EffectUnit.ShaderResHelper.SetTexture("Tex1", Target->GetTexture(2));

	EffectUnit.ShaderResHelper.SetSampler("Tex0Sampler", "POINT");
	EffectUnit.ShaderResHelper.SetSampler("Tex1Sampler", "POINT");
}

void PlayerMaskEffect::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	GameEngineRenderTarget::RenderTargetReset();
}