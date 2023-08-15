#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineVertexBuffer.h"

GameEngineRenderer::GameEngineRenderer() 
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::Start()
{
	// 메인카메라에 들어갔다.
	SetViewCameraSelect(0);

	// 카메라를 찾아서 들어가야 합니다.
	// 카메를 찾으려면? GameEngineLevel
	// Level부터 찾아야해.
	// Level누가 들고 있죠? 나를 들고 있는 Actor가 들고 있어.
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	std::shared_ptr<GameEngineCamera> Camera = Level->GetCamera(_Order);

	if (nullptr == Camera)
	{
		MsgBoxAssert("카메라가 존재하지 않는데 랜더러를 넣으려고 했습니다.");
		return;
	}

	Camera->Renderers[_Order].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
	ViewInfo[Camera.get()] = _Order;
}

int A = 0;

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	{
		std::shared_ptr<GameEngineVertexBuffer> VertexBuffer = GameEngineVertexBuffer::Find("Rect");
		VertexBuffer->Setting();

		//std::vector<int> Index = 
		//{
		//	0, 1, 2, 
		//	0, 2, 3,
		//	0 + 4, 1 + 4, 2 + 4,
		//	0 + 4, 2 + 4, 3 + 4,
		//	0 + 8, 1 + 8, 2 + 8,
		//	0 + 8, 2 + 8, 3 + 8,
		//	0 + 12, 1 + 12, 2 + 12,
		//	0 + 12, 2 + 12, 3 + 12,
		//	0 + 16, 1 + 16, 2 + 16,
		//	0 + 16, 2 + 16, 3 + 16,
		//	0 + 20, 1 + 20, 2 + 20,
		//	0 + 20, 2 + 20, 3 + 20,
		//};

		//float4x4 ViewPort4x4;
		//ViewPort4x4.ViewPort(1280.0f, 720.0f, 0.0f, 0.0f);


		//HDC DC = GameEngineCore::MainWindow.GetBackBuffer()->GetImageDC();

		//for (size_t indexCount = 0; indexCount < Index.size() / 3; indexCount++)
		//{
		//	int ArrIndex[3];
		//	ArrIndex[0] = Index[indexCount * 3 + 0];
		//	ArrIndex[1] = Index[indexCount * 3 + 1];
		//	ArrIndex[2] = Index[indexCount * 3 + 2];

		//	const TransformData& TransDataRef = Transform.GetConstTransformDataRef();

		//	float4 Trifloat4[3];
		//	std::vector<POINT> Tri;
		//	Tri.resize(3);
		//	for (size_t VertexCount = 0; VertexCount < Tri.size(); VertexCount++)
		//	{
		//		// 위치를 더해줌으로해서 월드 상태로 이전시켰다고 한다.
		//		float4 WorldPoint = Vertex[ArrIndex[VertexCount]];

		//		//변환식은 이제 딱 한가지 인것.
		//		WorldPoint = WorldPoint * TransDataRef.WorldViewPorjectionMatrix;

		//		WorldPoint /= WorldPoint.W;
		//		WorldPoint.W = 1.0f;

		//		WorldPoint = WorldPoint * ViewPort4x4;

		//		Trifloat4[VertexCount] = WorldPoint;


		//		Tri[VertexCount] = WorldPoint.WindowPOINT();
		//	}
		//	float4 Dir0 = Trifloat4[0] - Trifloat4[1];
		//	float4 Dir1 = Trifloat4[1] - Trifloat4[2];
		//	float4 Check = float4::Cross3D(Dir1, Dir0);
		//	if (Check.Z < 1.0f)
		//	{
		//		continue;
		//	}
		//	Polygon(DC, &Tri[0], static_cast<int>(Tri.size()));
		//}
	}
}