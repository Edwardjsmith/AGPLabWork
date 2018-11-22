cbuffer CBuffer0
{
	matrix WVPMatrix;
	float red_fraction;
	float scale;
	float2 packing;
};

struct VOut
{
	float4 position : SV_POSITION;
	float4 color	: COLOR;//Note the spelling of this and all instances below
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
	VOut output;
	color.r *= red_fraction;
	output.position = mul(WVPMatrix, position);
	output.color = color;

	return output;
}

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	return color;
}
