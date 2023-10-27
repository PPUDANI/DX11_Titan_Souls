#include "Transform.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    uint iInstance : SV_InstanceID;
};


struct PixelOutPut
{
    float4 POSITION : SV_POSITION;
};


PixelOutPut DebugLine_VS(GameEngineVertex2D _Input)
{
    // 쉐이더 문법 모두 0인 자료형으로 초기화 하는것
    PixelOutPut Result = (PixelOutPut) 0;
    float4x4 ViewProjectionMatrix = ViewMatrix * ProjectionMatrix;
    
    // Result.POSITION = mul(_Input.POSITION, ViewMatrix);
    
    Result.POSITION = _Input.POSITION;
    
    //if (_Input.iInstance == 0)
    //{
    //    Result.POSITION = mul(float4(200.0f, 200.0f, 0.0f, 1.0f), ViewProjectionMatrix);
    //}
    //else if (_Input.iInstance == 1)
    //{
    //    Result.POSITION = mul(float4(100.0f, 100.0f, 0.0f, 1.0f), ViewProjectionMatrix);
    //}
    
    
    
    return Result;
}

cbuffer DebugColor : register(b0)
{
    float4 Color;
}

float4 DebugLine_PS(PixelOutPut _Input) : SV_Target0
{
    return Color;
}