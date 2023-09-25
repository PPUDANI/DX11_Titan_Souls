#pragma once

// 설명 :
// 랜더링의 최소단위
// 이녀석을 돌리면 랜더링이 된다.
class GameEngineRenderUnit
{
public:
	// constrcuter destructer
	GameEngineRenderUnit();
	~GameEngineRenderUnit();

	// delete Function
	GameEngineRenderUnit(const GameEngineRenderUnit& _Other) = delete;
	GameEngineRenderUnit(GameEngineRenderUnit&& _Other) noexcept = delete;
	GameEngineRenderUnit& operator=(const GameEngineRenderUnit& _Other) = delete;
	GameEngineRenderUnit& operator=(GameEngineRenderUnit&& _Other) noexcept = delete;

protected:

private:
	//std::shared_ptr<class GameEngineInputLayOut> LayOut;
	//std::shared_ptr<class GameEngineMesh> Mesh;
	//std::shared_ptr<class GameEngineMaterial> Material;
	//GameEngineShaderResHelper ShaderResHelper;
};

