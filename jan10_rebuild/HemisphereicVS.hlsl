cbuffer cbufferVS {
	matrix  WorldViewProjection;
	matrix  World;
	matrix  World2;
}

struct InputVS{
	float4 position	: POSITION;		// vertex position 
	float3 normal	: NORMAL;		// vertex normal
	float2 uv		: TEXCOORD0;	// vertex texture coords 
};

struct OutputVS{
	float4 position	: SV_POSITION;	// vertex position 
	float2 uv		: TEXCOORD0;	// vertex texture coords
	float3 normal	: TEXCOORD1;	// vertex normal
};


OutputVS main(InputVS input){

	OutputVS output;

	output.position =	mul( WorldViewProjection, input.position);
	output.uv		=	input.uv;
	//output.normal	=	mul(input.normal , (float3x3)World);
	output.normal = mul( (float3x3)World, input.normal);
	return output;

}