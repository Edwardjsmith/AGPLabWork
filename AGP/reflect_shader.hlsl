cbuffer CB0
{
    matrix WVMatrix; //64 bytes
    matrix WVPMatrix;
    float4 directionalLightVec;
    float4 directionallightColour;
    float4 ambientColour;
};

Texture2D texture0;
TextureCube cube0;
SamplerState sampler0;

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 texcoord : TEXCOORD;
};

VOut ReflectVS(float4 position : POSITION, float2 texcoord : TEXCOORD, float3 normal : NORMAL)
{
    VOut output;

    float3 wvpos = mul(WVMatrix, position);
    float3 wvnormal = mul(WVMatrix, normal);
    wvnormal = normalize(wvnormal);

    float3 eyer = -normalize(wvpos);

    output.position = mul(WVPMatrix, position);

    float diffuse = dot(directionalLightVec, normal);
    diffuse = saturate(diffuse);
    output.texcoord = texcoord;
    output.color = ambientColour + (directionallightColour * diffuse);

    return output;
}

float4 ReflectPS(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
    
    return texture0.Sample(sampler0, texcoord) * color;
}