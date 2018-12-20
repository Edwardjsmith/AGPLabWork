cbuffer CB0
{
	matrix WVPMatrix; //64 bytes
    float4 color;
};

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

VOut ParticlesVS(float4 position : POSITION)
{
	VOut output;

	output.position = mul(WVPMatrix, position);
	output.texcoord = position.xy;
	output.color = color;

	return output;
}

float4 ParticlesPS(float4 position : SV_POSITION, float4 pcolor : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
    float distsq = texcoord.x * texcoord.x + texcoord.y * texcoord.y;
    clip(1.0f - distsq);
    return pcolor;
}