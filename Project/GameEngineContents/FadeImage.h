#pragma once
enum class IMAGE_STATE
{
	FADE_IN,
	RESTING,
	FADE_OUT,
};

class FadeImage : public GameEngineActor
{
public:
	// Constructor Destructor
	FadeImage();
	~FadeImage();

	// Delete Function
	FadeImage(const FadeImage& _Other) = delete;
	FadeImage(FadeImage&& _Other) noexcept = delete;
	FadeImage& operator=(const FadeImage& _Other) = delete;
	FadeImage& operator=(FadeImage&& _Other) noexcept = delete;

	void Init(std::string_view _ImageName, float _FadeSpeed = 1.0f, float _RestingTime = 1.0f);

	inline bool FadeIsEnd() const
	{
		return FadeIsEndValue;
	}

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

private:
	IMAGE_STATE CurState = IMAGE_STATE::FADE_IN;

	void FadeInUpdate(float _Delta);
	void RestingUpdate(float _Delta);
	void FadeOutUpdate(float _Delta);

private:
	float FadeSpeed = 0.0f;

	float RestingTime = 0.0f;
	float RestingTimer = 0.0f;

	bool FadeIsEndValue = false;
};