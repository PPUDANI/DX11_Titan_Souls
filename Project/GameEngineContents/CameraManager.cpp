#include "PreCompile.h"
#include "CameraManager.h"

float4 CameraManager::AddCameraPosFromArrow = float4::ZERO;
float4 CameraManager::AddCameraPosFromPlayer = float4::ZERO;
float4 CameraManager::AddCameraPosFromBoss = float4::ZERO;

float CameraManager::AddCameraZoomFromArrow = 0.0f;
float CameraManager::AddCameraZoomFromPlayer = 0.0f;
float CameraManager::AddCameraZoomFromBoss = 0.0f;