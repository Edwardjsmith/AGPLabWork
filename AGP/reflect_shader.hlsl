cbuffer CB0
{
    matrix WVMatrix; //64 bytes
    matrix WVPMatrix;
    //float4 directionalLightVec;
    //float4 directionallightColour;
    //float4 ambientColour;
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


VOut ReflectVS(float4 position : POSITION, float3 normal : NORMAL)
{
    VOut output;

    float3 wvpos = mul(WVMatrix, position);
    float3 wvnormal = mul(WVMatrix, normal);
    wvnormal = normalize(wvnormal);

    float3 eyer = -normalize(wvpos);

    output.position = mul(WVPMatrix, position);

    //float diffuse = dot(directionalLightVec, normal);
    //diffuse = saturate(diffuse);
    output.texcoord = 2.0 * dot(eyer, wvnormal) * wvnormal - eyer;
    //output.color = ambientColour + (directionallightColour * diffuse);

    return output;
}

float4 ReflectPS(float4 position : SV_POSITION, float2 texcoord : TEXCOORD0, float3 reflection: TEXCOORD1) : SV_TARGET
{
   float4 reflectionColour = cube0.Sample(sampler0, reflection);

   return texture0.Sample(sampler0, texcoord) / 2 + reflectionColour / 2;
}

/*cbuffer CB0
{
    matrix WVPMatrix; //64 bytes
    matrix WVMatrix;
};

Texture2D texture0;
TextureCube cube0;
SamplerState sampler0;

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float3 texcoord : TEXCOORD;
};

VOut SkyVS(float4 position : POSITION, float2 texcoord : TEXCOORD, float4 normal)//, float3 normal : NORMAL)
{
    VOut output;

    float3 wvpos = mul(WVMatrix, position);
    float3 wvnormal = mul(WVMatrix, normal);
    wvnormal = normalize(wvnormal);
    float3 eyer = -normalize(wvpos);

    float4 default_color = { 1.0, 1.0, 1.0, 1.0 };
    output.position = mul(WVPMatrix, position);
    output.texcoord = 2.0 * dot(eyer, wvnormal) * wvnormal - eyer;
    output.color = default_color;

    return output;
}

float4 SkyPS(float4 position : SV_POSITION, float2 color : COLOR, float3 texcoord : TEXCOORD) : SV_TARGET
{
    float4 reflectionColour = texture0.Sample(sampler0, color);
    return cube0.Sample(sampler0, texcoord) / 2 + reflectionColour / 2; // * color;
}*/