#pragma once

enum class FONT_TYPE
{
	ANCIENT,
	ENGLISH,
};

enum class FADE_STATE
{
	FADE_IN,
	RESTING,
	FADE_OUT,
};

class AncientScript : public GameEngineActor
{
public:
	// Constructor Destructor
	AncientScript();
	~AncientScript();

	// Delete Function
	AncientScript(const AncientScript& _Other) = delete;
	AncientScript(AncientScript&& _Other) noexcept = delete;
	AncientScript& operator=(const AncientScript& _Other) = delete;
	AncientScript& operator=(AncientScript&& _Other) noexcept = delete;

	void Init(std::string_view _Text, FONT_TYPE _Type, const float4& _TextSize, float _Interval = 0);

	void FadeInit(float _FadeSpeed = 1.0f, float _RestingTime = 1.0f);

	inline bool FadeIsEnd() const
	{
		return FadeIsEndValue;
	}

	inline FADE_STATE GetCurState() const
	{
		return CurState;
	}

	inline void SetCamera() const
	{
		for (int i = 0; i < TextNum; ++i)
		{
			Renderers[i]->SetCameraOrder(ECAMERAORDER::Main);
		}
	}

private:
	void Start() override;
	void Update(float _Delta) override;

private:
	FADE_STATE CurState = FADE_STATE::FADE_IN;

	void FadeInUpdate(float _Delta);
	void RestingUpdate(float _Delta);
	void FadeOutUpdate(float _Delta);

private:
	int ChangeAsciiToIndex(int _AsciiNum);

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> Renderers;
	FONT_TYPE Type;
	size_t TextNum = 0;

private:
	float AlphaValue = 0.0f;
	float FadeSpeed = 0.0f;

	float RestingTime = 0.0f;
	float RestingTimer = 0.0f;


	bool FadeIsEndValue = false;

};