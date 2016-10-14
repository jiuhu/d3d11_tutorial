
//--------------------------------------------------------------------
// I/O Structure
//--------------------------------------------------------------------

struct VS_INPUT 
{
	float4	Position	:	POSITION;
};

struct PS_INPUT 
{
	float4	Position	:	SV_POSITION;
	float3	ViewDir		:	TEXCOORD0;  
};
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Constant Buffer
//--------------------------------------------------------------------

cbuffer viewProjection	: register( b0 )
{
    matrix	matView;
    matrix	matProjection;
};
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Texture
//--------------------------------------------------------------------

TextureCube txTexture : register( t0 );
SamplerState samLinear : register( s0 );
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------

PS_INPUT vs_main( VS_INPUT Input )
{
    PS_INPUT Output = ( PS_INPUT )0;
	
	Output.Position = mul( Input.Position, matView );
	Output.Position = mul( Output.Position, matProjection );
    
	Output.ViewDir	= Input.Position.xyz;

	return Output;
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------

float4 ps_main( PS_INPUT Input ) : SV_Target
{
	return txTexture.Sample( samLinear, Input.ViewDir );
}
//--------------------------------------------------------------------