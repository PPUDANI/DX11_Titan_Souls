

//#define UserLightOn

// 파일명과 함수명을 일치시키고 버텍스 쉐이더면 무조건 뒤에 _VS를 붙입니다.
// 의미있는 버텍스 쉐이더이다.
float4 ColorShader_VS(float4 pos : POSITION) : SV_POSITION
{
//#ifdef UserLightOn
	
//#endif
	return pos;
}

float4 TestShader_VS(float4 pos : POSITION) : SV_POSITION
{
    return pos;
}