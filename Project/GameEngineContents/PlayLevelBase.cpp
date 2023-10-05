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

	if (true == GameEngineInput::IsDown('1'))
	{
		TileMapActor->SetViewMode(VIEW_MODE::DEFAULT_MODE);
	}
	if (true == GameEngineInput::IsDown('2'))
	{
		TileMapActor->SetViewMode(VIEW_MODE::COLLISION_MODE);
	}
	if (true == GameEngineInput::IsDown('3'))
	{
		TileMapActor->SetViewMode(VIEW_MODE::MATERIAL_MODE1);
	}
	if (true == GameEngineInput::IsDown('4'))
	{
		TileMapActor->SetViewMode(VIEW_MODE::MATERIAL_MODE2);
	}

	if (true == GameEngineInput::IsDown('R'))
	{
		SpawnPlayer();
	}

	if (true == GameEngineInput::IsDown('I'))
	{
		GetMainCamera()->SetZoomValue(1.0f);
	}
	if (true == GameEngineInput::IsDown('O'))
	{
		GetMainCamera()->SetZoomValue(0.5f);
	}
	if (true == GameEngineInput::IsDown('P'))
	{
		GetMainCamera()->SetZoomValue(1.5f);
	}

	if (PLAYER_STATE::Aim == PlayerActor->GetCurState())
	{
		ArrowActor->ChangeState(ARROW_STATE::Aim);
	}

	ArrowDirectionRotation();
}

void PlayLevelBase::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelBase::LevelStart(_PrevLevel);
	PlayerActor->ChangeState(PLAYER_STATE::StandUp);
	PlayerActor->SetTileMap(TileMapActor);
	SpawnPlayer();
}

void PlayLevelBase::LevelEnd(GameEngineLevel* _NextLevel)
{
	LevelBase::LevelEnd(_NextLevel);
}

void PlayLevelBase::CreatePlayerElement()
{
	// PlayerActor Setting
	if (nullptr == PlayerActor)
	{
		PlayerActor = CreateActor<Player>(UPDATE_ORDER::Player);
		ArrowActor = CreateActor<Arrow>(UPDATE_ORDER::Player);
		ArrowActor->OwnerPlayerSetting(PlayerActor);
	}
}

void PlayLevelBase::SpawnPlayer()
{
	PlayerActor->Transform.SetLocalPosition(PlayerSpawnPos);
	ArrowActor->Transform.SetLocalPosition(PlayerSpawnPos);
	PlayerActor->ChangeState(PLAYER_STATE::StandUp);
	return;
}
           
void PlayLevelBase::ArrowDirectionRotation()
{
	// Arrow Direction Rotation
	float4 PlayerFromArrow = CursurActor->Transform.GetLocalPosition() - PlayerActor->Transform.GetWorldPosition();
	float Degree = DirectX::XMConvertToDegrees(atan2f(PlayerFromArrow.Y, PlayerFromArrow.X));
	float4 Angle = float4::ZERO;
	Angle.Z = Degree;

	if (0.0f > Angle.Z)
	{
		while (0.0f > Angle.Z)
		{
			Angle.Z += 360.0f;
		}
	}
	else if (360.0f < Angle.Z)
	{
		while (360.0f < Angle.Z)
		{
			Angle.Z -= 360.0f;
		}
	}

	PlayerActor->SetArrowAngleDeg(Angle.Z);

	Angle.Z += 90.0f;

	CursurActor->Transform.SetLocalRotation(Angle);

	ArrowActor->SetArrowAngleDeg(Angle);

	// Arrow YSotting
	if (ArrowActor->Transform.GetLocalPosition().Y > PlayerActor->Transform.GetWorldPosition().Y - 4.0f)
	{
		ArrowActor->SetRenderOrder(RENDERING_ORDER::ArrowBack);
	}
	else
	{
		ArrowActor->SetRenderOrder(RENDERING_ORDER::Arrow);
	}
}
