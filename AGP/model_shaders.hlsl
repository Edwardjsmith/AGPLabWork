cbuffer CB0
{
	matrix WVPMatrix; //64 bytes
    float4 directionalLightVec;
    float4 directionallightColour;
    float4 ambientColour;
};

Texture2D texture0;
SamplerState sampler0;

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

VOut ModelVS(float4 position : POSITION, float2 texcoord : TEXCOORD, float3 normal : NORMAL)
{
	VOut output;

	
	output.position = mul(WVPMatrix, position);

    float diffuse = dot(directionalLightVec, normal);
    diffuse = saturate(diffuse);
	output.texcoord = texcoord;
    output.color = ambientColour + (directionallightColour * diffuse);

	return output;
}

float4 ModelPS(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
	return texture0.Sample(sampler0, texcoord) * color;
}