
//--------------------------------------------------------------------
// I/O Structure
//--------------------------------------------------------------------

struct VS_INPUT 
{
	float4	Position	:	POSITION;
	float3	Normal		:	NORMAL;
	float2	Texcoord	:	TEXCOORD;
};

struct PS_INPUT 
{
	float4	Position	:	SV_POSITION;
	float3	Normal		:	TEXCOORD0;
	float3	LightDir	:	TEXCOORD1;
	float2	Texcoord	:	TEXCOORD2;
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

cbuffer world	: register( b1 )
{
    matrix	matWorld;
};
//--------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Texture
//--------------------------------------------------------------------------------------
Texture2D txTexture : register( t0 );
SamplerState samLinear : register( s0 );
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------

PS_INPUT vs_main( VS_INPUT Input )
{
    PS_INPUT Output = ( PS_INPUT )0;
	
	Output.Position = mul( Input.Position, matWorld );
	Output.Position = mul( Output.Position, matView );
	Output.Position = mul( Output.Position, matProjection );
	
	float3 LightPos	= float3(10.0f, 10.0f, 0.0f);
	Output.LightDir	= LightPos - Input.Position.xyz; 
    
	Output.Texcoord = Input.Texcoord;
	Output.Normal	= Input.Normal;

	return Output;
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------

float4 ps_main( PS_INPUT Input ) : SV_Target
{
	float4 DiffuseLight	= float4(0.8f, 0.0f, 0.0f, 1.0f);

	//Find the light direction: 
	float3 L		= normalize( Input.LightDir );
	//Normalize the normal vector: 
	float3 N		= normalize( Input.Normal ); 
	//Calculate the dot-production of light direction and normal vector: 
	float LdotN		= max(0.0, dot(L, N)); 
	

	float4 colorAtPixel	= DiffuseLight * LdotN;
    return colorAtPixel * txTexture.Sample( samLinear, Input.Texcoord );
}
//--------------------------------------------------------------------