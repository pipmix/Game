cbuffer Cbuffer{
	matrix world;
	matrix camera;
	matrix screen;

};


struct Input {
	float4 position : POSITION;
	float4 normal : NORMAL;
	float2 uv : TEXCOORD;

};

struct VOut {

	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord: TEXCOORD;


};





VOut main(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD) {
	VOut output;

	

	output.position = mul(world, position);

	float4 ambientcol = float4(0.5f, 0.5f, 0.5f, 1.0f );
	//float4 pos = float4(input.pos, 1.0f);

	output.color = ambientcol;

	float4 norm = normalize(mul(world, normal));

	float4 lightcol = float4(0.5f, 0.5f, 0.5f, 1.0f);

	float4 lightvec = float4(0.5f, 0.5f, 0.5f, 1.0f );
	float diffusebrightness = saturate(dot(norm, lightvec));

	output.color += lightcol * diffusebrightness;

	output.texcoord = texcoord;    // set the texture coordinates, unmodified

	return output;



}