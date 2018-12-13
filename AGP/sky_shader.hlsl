cbuffer CB0
{
	matrix WVPMatrix; //64 bytes
};

TextureCube cube0;
SamplerState sampler0;

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float3 texcoord : TEXCOORD;
};

VOut SkyVS(float4 position : POSITION, float2 texcoord : TEXCOORD)//, float3 normal : NORMAL)
{
	VOut output;

	//float4 default_color = { 1.0, 1.0, 1.0, 1.0 };
	//output.position = mul(WVPMatrix, position);
	output.texcoord = position.xyz;
	output.position = mul(WVPMatrix, position);
	//output.color = default_color;

	return output;
}

float4 SkyPS(float4 position : SV_POSITION, float4 color : COLOR, float3 texcoord : TEXCOORD) : SV_TARGET
{
	return texture0.Sample(sampler0, texcoord);// * color;
}