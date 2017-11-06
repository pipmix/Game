cbuffer cbufferPS {
	float3 AmbientDown;
	float space;
	float3 AmbientRange;
	float space2;
}

Texture2D    DiffuseTexture;
SamplerState ss;

struct OutputVS{
	float4 position	: SV_POSITION;	// vertex position 
	float2 uv		: TEXCOORD0;	// vertex texture coords
	float3 normal	: TEXCOORD1;	// vertex normal
};





float3 CalcAmbient(float3 normal, float3 color){

	float3 aD = float3(0.5, 0.5, 2.5);
	float3 aR = float3(1.0f, 0.5f, 0.5f);

	// Convert from [-1, 1] to [0, 1]
	float up = normal.y * 0.5 + 0.5;

	// Calculate the ambient value
	float3 ambient = AmbientDown + up * AmbientRange;
	//float3 ambient = aD + up * aR;

	// Apply the ambient value to the color
	return ambient * color;
}

float4 main(OutputVS input) : SV_TARGET{
	
	float3 diffuseColor = DiffuseTexture.Sample(ss, input.uv).rgb;
	diffuseColor *= diffuseColor;

	float3 AmbientColor = CalcAmbient(input.normal, diffuseColor);

	return float4(AmbientColor, 1.0);
}