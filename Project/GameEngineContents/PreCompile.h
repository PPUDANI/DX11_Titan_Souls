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

// 렌더러 실제 데이터
#include <GameEngineCore/GameEngineRenderer.h> 

// 렌더러를 렌더링해주는 곳
#include <GameEngineCore/GameEngineCamera.h>

// 스프라이트 파일 불러오고 렌더러로 쪼갤 때 사용하는거
#include <GameEngineCore/GameEngineSprite.h>

// 렌더러 상속받아서 애니메이션을 만들 때 사용하는것
// 클라이언트는 그림을 띄울 때, 이 클래스를 사용하게 됨
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "GlobalValue.h"
#include "GlobalLoad.h"
#include "ContentEnum.h"
#include "PlayLevelBase.h"
#include "TileMap.h"
#include "TileInfo.h"
#include "Player.h"
#include "Arrow.h"