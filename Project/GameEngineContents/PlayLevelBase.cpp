#include "PreCompile.h"
#include "PlayLevelBase.h"

PlayLevelBase::PlayLevelBase()
{
}

PlayLevelBase::~PlayLevelBase()
{
}

void PlayLevelBase::Start()
{
	LevelBase::Start();
	CreatePlayerElement();
}

void PlayLevelBase::Update(float _Delta)
{
	LevelBase::Update(_Delta);

	//if (true == GameEngineInput::IsDown('R', this))
	//{
	//	SpawnPlayer();
	//}

	// TileMap ViewMode Change Key
	if (true == GameEngineInput::IsDown('1', this))
	{
		TileMapActor->SetViewMode(VIEW_MODE::DEFAULT_MODE);
	}
	if (true == GameEngineInput::IsDown('2', this))
	{
		TileMapActor->SetViewMode(VIEW_MODE::COLLISION_MODE);
	}
	if (true == GameEngineInput::IsDown('3', this))
	{
		TileMapActor->SetViewMode(VIEW_MODE::MATERIAL_MODE1);
	}
	if (true == GameEngineInput::IsDown('4', this))
	{
		TileMapActor->SetViewMode(VIEW_MODE::MATERIAL_MODE2);
	}


	// DebugingMode Key
	if (true == GameEngineInput::IsDown('0', this))
	{
		PlayerActor->DebugingModeSwitch();
		ArrowActor->DebugingModeSwitch();
	}

	// Zoom In, Zoom, Out Key
	if (true == GameEngineInput::IsDown('I', this))
	{
		GetMainCamera()->SetZoomValue(1.0f);
	}
	if (true == GameEngineInput::IsDown('O', this))
	{
		GetMainCamera()->SetZoomValue(0.5f);
	}
	if (true == GameEngineInput::IsDown('P', this))
	{
		GetMainCamera()->SetZoomValue(1.5f);
	}

	CursorDirRotation();
	ArrowDirRotation();

	GetMainCamera()->Transform.SetWorldPosition(CameraManager::GetCameraPos());
	GetMainCamera()->SetZoomValue(CameraManager::GetCameraZoom());
}

void PlayLevelBase::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelBase::LevelStart(_PrevLevel);
	SpawnPlayer();
	SpawnBoss();
}

void PlayLevelBase::LevelEnd(GameEngineLevel* _NextLevel)
{
	LevelBase::LevelEnd(_NextLevel);
}

void PlayLevelBase::CreatePlayerElement()
{
	if (nullptr != PlayerActor)
	{
		MsgBoxAssert("PlayerActor가 이미 생성되어있습니다.");
	}
	if (nullptr != ArrowActor)
	{
		MsgBoxAssert("ArrowActor가 이미 생성되어있습니다.");
	}

	// PlayerActor Setting
	PlayerActor = CreateActor<Player>(static_cast<int>(UPDATE_ORDER::Player), "Player");
	ArrowActor = CreateActor<Arrow>(static_cast<int>(UPDATE_ORDER::Arrow), "Arrow");
	ArrowActor->OwnerPlayerSetting(PlayerActor);
	PlayerActor->ArrowSetting(ArrowActor);
}


     
void PlayLevelBase::CursorDirRotation()
{
	// Arrow Direction Rotation
	float4 PlayerFromArrow = CursorActor->Transform.GetLocalPosition() - PlayerActor->Transform.GetLocalPosition();
	CursorAngle.Z = DirectX::XMConvertToDegrees(atan2f(PlayerFromArrow.Y, PlayerFromArrow.X));

	if (0.0f > CursorAngle.Z)
	{
		while (0.0f > CursorAngle.Z)
		{
			CursorAngle.Z += 360.0f;
		}
	}
	else if (360.0f < CursorAngle.Z)
	{
		while (360.0f < CursorAngle.Z)
		{
			CursorAngle.Z -= 360.0f;
		}
	}

	PlayerActor->SetArrowAngleDeg(CursorAngle.Z);
	CursorAngle.Z += 90.0f;
	CursorActor->Transform.SetLocalRotation(CursorAngle);
}

void PlayLevelBase::ArrowDirRotation()
{
	if (ARROW_STATE::Returning == ArrowActor->GetCurState() ||
		ARROW_STATE::Fallen == ArrowActor->GetCurState() ||
		ARROW_STATE::Pinned == ArrowActor->GetCurState())
	{
		float4 PlayerFromArrow = PlayerActor->Transform.GetLocalPosition() - ArrowActor->Transform.GetLocalPosition();
		float4 Angle = float4::ZERO;
		Angle.Z = DirectX::XMConvertToDegrees(atan2f(PlayerFromArrow.Y, PlayerFromArrow.X));

		PlayerActor->SetArrowAngleDeg(Angle.Z + 180.0f);
		Angle.Z += 90.0f;
		ArrowActor->SetArrowAngleDeg(Angle);
	}
	else if(ARROW_STATE::Aim == ArrowActor->GetCurState())
	{
		ArrowActor->SetArrowAngleDeg(CursorAngle);
	}

	//// Arrow YSotting
	//if (ArrowActor->Transform.GetLocalPosition().Y > PlayerActor->Transform.GetLocalPosition().Y - 3.42f)
	//{
	//	ArrowActor->SetRenderOrder(RENDERING_DEPTH::Arrow);
	//}
	//else
	//{
	//	ArrowActor->SetRenderOrder(RENDERING_DEPTH::Arrow2);
	//}
}
