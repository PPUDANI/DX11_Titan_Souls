// App.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
#include <GameEngineContents/PreCompile.h>

#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEnginePlatform.lib")
#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

#include <iostream>
#include <Windows.h>
#include <memory>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineContents/ContentsCore.h>
#include <vector>
#include "FileManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
    int IndexX = 101;
    int IndexY = 219;

    int Max = IndexX * IndexY;

    std::vector<unsigned int> LoadData(Max);
    std::vector<unsigned int> SaveData =
    {
    
    };

    // BG.tmd
    // BGA.tmd
    // FG.tmd
    // COL.tmd
    // COLA.tmd
    // MAT.tmd


    FileManager::FileSave(Max, SaveData);
    //FileManager::FileLoad(Max, LoadData);

    int a = 0;
}

