
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
	float4	Position		:	SV_POSITION;
	float4	ColorAtVertex	:	COLOR0;
	float2	Texcoord		:	TEXCOORD0;
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
    
	Output.Texcoord = Input.Texcoord;
	   
	float3 LightPos	= float3(10.0f, 0.0f, 0.0f);
	float4 DiffuseLight	= float4(0.8f, 0.0f, 0.0f, 1.0f);

	//Find the light direction: 
	float3 LightDir	= normalize(LightPos - Input.Position.xyz); 
	//Normalize the normal vector: 
	//float3 N		= normalize( mul( float4(Input.Normal, 0.0f), matWorld ).xyz );
	float3 N		= normalize( Input.Normal ); 
	//Find the reflected view direction: 
	float3 R		= reflect(-LightDir, N); 
	//Calculate the dot-production of light direction and normal vector: 
	float LdotN		= max(0.0, dot(LightDir, N)); 

	Output.ColorAtVertex	= DiffuseLight * LdotN;

	return Output;
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------

float4 ps_main( PS_INPUT Input ) : SV_Target
{
    return Input.ColorAtVertex * txTexture.Sample( samLinear, Input.Texcoord );
}
//--------------------------------------------------------------------