
//--------------------------------------------------------------------
// I/O Structure
//--------------------------------------------------------------------

struct VS_INPUT 
{
	float4	Position	:	POSITION;
	float2	Texcoord	:	TEXCOORD;
};

struct PS_INPUT 
{
	float4	Position	:	SV_POSITION;
	float2	Texcoord	:	TEXCOORD0;
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

Texture2D txTexture : register( t0 );
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
    
	Output.Texcoord = Input.Texcoord;

	return Output;
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------

float4 ps_main( PS_INPUT Input ) : SV_Target
{
    return txTexture.Sample( samLinear, Input.Texcoord );
}
//--------------------------------------------------------------------