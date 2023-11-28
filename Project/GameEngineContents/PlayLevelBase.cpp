#include "PreCompile.h"
#include "PlayLevelBase.h"

bool PlayLevelBase::SludgeIsDeath = true;
bool PlayLevelBase::YetiIsDeath = true;
bool PlayLevelBase::ColossusIsDeath = true;

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
	PlayerEffect = GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<PlayerMaskEffect>();

	SoundLoad();
	GlobalLoad::LoadSound("EnterDoor.ogg", "Resource\\Sound\\Effect\\Door\\");

	GlobalLoad::LoadSpriteCut(2, 1, "Dust.png", "Resource\\Texture\\Particle\\");
}

void PlayLevelBase::Update(float _Delta)
{
	LevelBase::Update(_Delta);

	//if (true == GameEngineInput::IsDown('R', this))
	//{
	//	SpawnPlayer(nullptr);
	//}

	if (PLAYER_STATE::Death == PlayerActor->GetCurState())
	{
		PlayerDeathProcessing(_Delta);
		return;
	}

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

	if (true == GameEngineInput::IsDown('I', this))
	{
		IsDebug = !IsDebug;
	}

	CursorDirRotation();
	ArrowDirRotation();

	GetMainCamera()->Transform.SetWorldPosition(CameraManager::GetCameraPos(TileMapActor->GetTileMapSize()));
	GetMainCamera()->SetZoomValue(CameraManager::GetCameraZoom());
}

void PlayLevelBase::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelBase::LevelStart(_PrevLevel);
	SpawnPlayer(_PrevLevel);
	CameraManager::CameraValueReset();

	PlayerIsDeathValue = false;

	if (nullptr != PlayerActor &&
		nullptr != ArrowActor)
	{
		PlayerActor->GetArrow();
		ArrowActor->ChangeState(ARROW_STATE::Hold);
	}

	if (nullptr == FadeInActor)
	{
		FadeInActor = CreateActor<FadeIn>(UPDATE_ORDER::UI);
		FadeInActor->Init(FadeColor::Black, 1.5f);
	}

	BackFadeInVolumeOn();
	AmbienceFadeInVolumeOn();
	EffectFadeInVolumeOn();
}

void PlayLevelBase::LevelEnd(GameEngineLevel* _NextLevel)
{
	LevelBase::LevelEnd(_NextLevel);

	ReleaseBossName();

	ReleaseTriggerBox();
	ReleaseParticle();

	if (nullptr != FadeOutActor)
	{
		FadeOutActor->Death();
		FadeOutActor = nullptr;
	}

	if (nullptr != FadeInActor)
	{
		FadeInActor->Death();
		FadeInActor = nullptr;
	}
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

void PlayLevelBase::EnterRoomTriggerFunc()
{
	EffectPlay("EnterDoor.ogg");
	BackFadeOutVolumeOn();
	AmbienceFadeOutVolumeOn();
}

void PlayLevelBase::ExitRoomTriggerFunc()
{
	BackFadeOutVolumeOn();
	AmbienceFadeOutVolumeOn();
	EffectFadeOutVolumeOn();
}

void PlayLevelBase::PlayerDeathProcessing(float _Delta)
{
	PlayerIsDeathValue = true;
	if (DeathProcessingStartTime < DeathProcessingStartTimer)
	{
		if (nullptr == FadeOutActor)
		{
			FadeOutActor = CreateActor<FadeOut>(UPDATE_ORDER::UI);
			FadeOutActor->Init(FadeColor::Black, 1.5f);
		}

		if (true == FadeOutActor->FadeIsEnd())
		{
			GameEngineCore::ChangeLevel("01.Floor1");
			DeathProcessingStartTimer = 0.0f;
		}
	}
	else
	{
		DeathProcessingStartTimer += _Delta;
		BackgroundStop();
		Background2Stop();
	}
	
}

void PlayLevelBase::ReleaseParticle()
{
	{
		std::vector<std::shared_ptr<UpParticle>> ObjectType = GetObjectGroupConvert<UpParticle>(UPDATE_ORDER::Particle);
		for (size_t i = 0; i < ObjectType.size(); ++i)
		{
			if (nullptr != ObjectType[i])
			{
				ObjectType[i]->Death();
				ObjectType[i] = nullptr;
			}
		}
		ObjectType.clear();
	}

	{
		std::vector<std::shared_ptr<GravityParticle>> ObjectType = GetObjectGroupConvert<GravityParticle>(UPDATE_ORDER::Particle);
		for (size_t i = 0; i < ObjectType.size(); ++i)
		{
			if (nullptr != ObjectType[i])
			{
				ObjectType[i]->Death();
				ObjectType[i] = nullptr;
			}
		}
		ObjectType.clear();
	}
}
	

void PlayLevelBase::ReleaseBossName()
{
	if (nullptr != BossNameBack)
	{
		BossNameBack->Death();
		BossNameBack = nullptr;
	}

	if (nullptr != BossNameScript)
	{
		BossNameScript->Death();
		BossNameScript = nullptr;
	}

	if (nullptr != BossDescriptionScript)
	{
		BossDescriptionScript->Death();
		BossDescriptionScript = nullptr;
	}
}


void PlayLevelBase::CreateDust(const float4& _Pos, float _Dir)
{
	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++RandomSeedCount);

	UpParticleActor = CreateActor<UpParticle>(UPDATE_ORDER::Particle);
	UpParticleActor->SetRenderer("Dust.png", Inst.RandomInt(0, 1), 16.0f, 0.5f);

	float4 DirBasis = float4::GetUnitVectorFromDeg(_Dir - 90.0f);
	float4 DirBasis2 = float4::GetUnitVectorFromDeg(_Dir);
	
	UpParticleActor->Transform.SetLocalPosition(_Pos + DirBasis * Inst.RandomFloat(-10.0f, 10.0f) + DirBasis2 * Inst.RandomFloat(-3.0f, 3.0f));
}