cbuffer cbPerObject
{
	float4x4 gWorldViewProj;
};

float4 VShader(float3 position : POSITION) : SV_POSITION
{
	float4 vOut;

	vOut = mul(float4(position, 1.0f), gWorldViewProj);

	return vOut;
}

float4 PShader(float4 position : SV_POSITION) : SV_Target
{
	return float4(1.0f, 1.0f, 0.0f, 1.0f);
}