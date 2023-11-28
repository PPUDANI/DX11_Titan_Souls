#pragma once
#include <GameEngineCore/PreCompile.h>

#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEnginePath.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineTileMap.h>
#include <GameEngineCore/GameEngineComponent.h>
#include <GameEngineCore/GameEngineTransform.h>
#include <GameEngineCore/GameEngineCamera.h>
// 렌더러 실제 데이터
#include <GameEngineCore/GameEngineRenderer.h> 

// 렌더러를 렌더링해주는 곳
#include <GameEngineCore/GameEngineCamera.h>

// 스프라이트 파일 불러오고 렌더러로 쪼갤 때 사용하는거
#include <GameEngineCore/GameEngineSprite.h>

// 렌더러 상속받아서 애니메이션을 만들 때 사용하는것
// 클라이언트는 그림을 띄울 때, 이 클래스를 사용하게 됨
#include <GameEngineCore/GameEngineSpriteRenderer.h>

// Global
#include "GlobalValue.h"
#include "GlobalLoad.h"
#include "ContentEnum.h"
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineFont.h>

// Level
#include "LevelBase.h"
#include "PlayLevelBase.h"

// Post Effect
#include "PlayerMaskEffect.h"
#include "SoundRandomPlayer.h"

// Actor
#include "CameraManager.h"
#include "CameraShakingObject.h"
#include "TileMap.h"
#include "ActorBase.h"
#include "Player.h"
#include "Arrow.h"
#include "BossBase.h"
#include "JumpBoss.h"
#include "TriggerBox.h"
#include "FadeIn.h"
#include "FadeOut.h"
#include "ScreenOverlay.h"
#include "FadeScreenOverlay.h"
#include "OverlayActor.h"
#include "ImageActor.h"
#include "FadeImage.h"
#include "UpParticle.h"
#include "GravityParticle.h"
#include "SpreadParticle.h"

#include "TextActor.h"
#include "SelectText.h"
#include "AncientScript.h"


// UI
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "MouseCursor.h"