struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

PixelOutPut ColossusBodyMask_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D Tex0 : register(t0);
Texture2D Tex1 : register(t1);
SamplerState Tex0Sampler : register(s0);
SamplerState Tex1Sampler : register(s1);

float4 ColossusBodyMask_PS(PixelOutPut _Input) : SV_Target0
{
    // 플레이어
    float4 Color0 = Tex0.Sample(Tex0Sampler, _Input.TEXCOORD.xy);
    
    // 벽
    float4 Color1 = Tex1.Sample(Tex1Sampler, _Input.TEXCOORD.xy);
   
    if (Color0.a != 0 && Color1.a != 0)
    {
        return float4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    
    return Color0;
}