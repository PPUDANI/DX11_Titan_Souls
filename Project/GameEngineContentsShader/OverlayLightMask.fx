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

PixelOutPut OverlayLightMask_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D Tex0 : register(t0);
Texture2D Tex1 : register(t1);
Texture2D Tex2 : register(t2);

SamplerState Tex0Sampler : register(s0);
SamplerState Tex1Sampler : register(s1);
SamplerState Tex2Sampler : register(s2);

float4 OverlayLightMask_PS(PixelOutPut _Input) : SV_Target0
{
    // Light
    float4 Color0 = Tex0.Sample(Tex0Sampler, _Input.TEXCOORD.xy);
    
    // Overlay
    float4 Color1 = Tex1.Sample(Tex1Sampler, _Input.TEXCOORD.xy);
    
    // Foreground
    float4 Color2 = Tex2.Sample(Tex2Sampler, _Input.TEXCOORD.xy);
    
    if (Color2.a != 0)
    {
        return Color1;
    }
    
    if (Color0.a != 0)
    {
        return Color0;
    }
    
    return Color1;
}