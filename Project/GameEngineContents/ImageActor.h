#pragma once

class ImageActor : public GameEngineActor
{
public:
	// Constructor Destructor
	ImageActor();
	~ImageActor();

	// Delete Function
	ImageActor(const ImageActor& _Other) = delete;
	ImageActor(ImageActor&& _Other) noexcept = delete;
	ImageActor& operator=(const ImageActor& _Other) = delete;
	ImageActor& operator=(ImageActor&& _Other) noexcept = delete;

	void SetImage(std::string_view _ImageName);

protected:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
private:

};