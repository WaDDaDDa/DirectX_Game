#include "Transform.fx"


// 버텍스 쉐이더 입니다.
// 월드뷰프로젝션을 GPU로 넘기기 위해 상수버퍼라는것을 만들게 될것이다.
float4 ColorShader_VS(float4 pos : POSITION) : SV_Position
{
    // mul은 mutiply
    return mul(pos, WorldViewPorjectionMatrix);
}

float4 ColorShader_PS(float4 pos : SV_Position) : SV_Target0
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}