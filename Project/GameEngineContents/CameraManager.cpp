#include "PreCompile.h"
#include "CameraManager.h"

float CameraManager::TurmSize = 20.0f;
float4 CameraManager::AddCameraPosFromArrow = float4::ZERO;
float4 CameraManager::AddCameraPosFromPlayer = float4::ZERO;
float4 CameraManager::AddCameraPosFromBoss = float4::ZERO;
float4 CameraManager::AddCameraPosFromShaking = float4::ZERO;

float CameraManager::AddCameraZoomFromArrow = 1.0f;
float CameraManager::AddCameraZoomFromPlayer = 1.0f;
float CameraManager::AddCameraZoomFromBoss = 1.0f;

bool CameraManager::CalCameraPosFromArrow = true;
bool CameraManager::CalCameraPosFromPlayer = true;
bool CameraManager::CalCameraPosFromBoss = true;