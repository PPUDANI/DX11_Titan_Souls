#include "PreCompile.h"
#include "ImageActor.h"

ImageActor::ImageActor()
{
}

ImageActor::~ImageActor()
{
}

void ImageActor::SetImage(std::string_view _ImageName)
{
	Renderer->SetSprite(_ImageName);
	
}

void ImageActor::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI);
}

void ImageActor::Update(float _Delta)
{

}