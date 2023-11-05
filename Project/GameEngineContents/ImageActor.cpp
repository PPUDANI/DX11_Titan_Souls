#include "PreCompile.h"
#include "ImageActor.h"

ImageActor::ImageActor()
{
}

ImageActor::~ImageActor()
{
}

void ImageActor::SetImage(std::string_view _ImageName, const float4& _Scale)
{
	Renderer->SetSprite(_ImageName);
	Renderer->SetImageScale(_Scale);
}

void ImageActor::AddPlusColor(float _PlusColor)
{
	Renderer->GetColorData().PlusColor += {_PlusColor, _PlusColor, _PlusColor};
}

void ImageActor::AddMulColor(float _MulColor)
{
	Renderer->GetColorData().MulColor += {_MulColor, _MulColor, _MulColor};
}
void ImageActor::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UIFront);
}

void ImageActor::Update(float _Delta)
{

}