#pragma once

class KnightElhananRoom : public PlayLevelBase
{
public:
	// Constructor Destructor
	KnightElhananRoom();
	~KnightElhananRoom();

	// Delete Function
	KnightElhananRoom(const KnightElhananRoom& _Other) = delete;
	KnightElhananRoom(KnightElhananRoom&& _Other) noexcept = delete;
	KnightElhananRoom& operator=(const KnightElhananRoom& _Other) = delete;
	KnightElhananRoom& operator=(KnightElhananRoom&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void SpawnPlayer() override;
};