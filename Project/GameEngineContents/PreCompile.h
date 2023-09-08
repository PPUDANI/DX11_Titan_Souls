#pragma once

#include <GameEngineCore/PreCompile.h>

//#include <GameEngineCore/GameEngineCore.h>
//#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineLevel.h>

#include <GameEngineCore/GameEngineCollision.h>


// 렌더러 실제 데이터
#include <GameEngineCore/GameEngineRenderer.h> 

// 렌더러를 렌더링해주는 곳
#include <GameEngineCore/GameEngineCamera.h>

// 스프라이트 파일 불러오고 렌더러로 쪼갤 때 사용하는거
#include <GameEngineCore/GameEngineSprite.h>

// 렌더러 상속받아서 애니메이션을 만들 때 사용하는것
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "GlobalLoad.h"
#include "PlayLevelBase.h"
#include "ContentEnum.h"
#include "Player.h"