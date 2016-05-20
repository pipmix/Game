cbuffer cBuffer {
	matrix world;
	matrix camera;
	matrix screen;
};

float4 main( float4 pos : POSITION ) : SV_POSITION
{

	float4 output;

	output = mul(world, pos);
	//output = mul(output, camera);
	//output = mul(output, screen);

	return output;
}



