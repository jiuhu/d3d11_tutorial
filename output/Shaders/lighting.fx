
//--------------------------------------------------------------------
// I/O Structure
//--------------------------------------------------------------------

struct VS_INPUT 
{
	float4	Position	:	POSITION;
	float3	Normal		:	NORMAL;
	float2	Texcoord	:	TEXCOORD;
};
//--------------------------------------------------------------------

struct PS_INPUT 
{
	float4	Position	:	SV_POSITION;
	float3	Normal		:	TEXCOORD0;
	float2	Texcoord	:	TEXCOORD1;
	float3	LightDir	:	TEXCOORD2;
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

cbuffer light	: register( b2 )
{
	int		iLightStatus;
    float3	fvLightPosition;
    float4	fvAmbientLightColor;
    float4	fvDiffuseLightColor;
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
    PS_INPUT Output = ( PS_INPUT ) 0;
	
	Output.Position = mul( Input.Position, matWorld );
	Output.Position = mul( Output.Position, matView );
	Output.Position = mul( Output.Position, matProjection );
	
	Output.Normal	= Input.Normal;
    
	Output.Texcoord = Input.Texcoord;
	
	if ( iLightStatus )
	{
		//	Find the light direction: 
		float4 fvObjectPosition = mul( Input.Position, matWorld );
		Output.LightDir	= fvLightPosition - fvObjectPosition.xyz;
	}

	return Output;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------

float4 ps_main( PS_INPUT Input ) : SV_Target
{	
	if ( iLightStatus )
	{
		float4 fvBaseColor	= txTexture.Sample( samLinear, Input.Texcoord );

		//	Calculate the total ambient.
		float4 fvTotalAmbient	= fvBaseColor * fvAmbientLightColor;
		
		//	Normalize the light direction vector. 
		float3 L	= normalize( Input.LightDir );
		//	Normalize the normal vector. 
		float3 N	= normalize( Input.Normal ); 
		//	Calculate the lambert term.
		float LdotN	= max(0.0, dot(L, N)); 

		//	Calculate the total diffuse
		float4 fvTotalDiffuse	= fvBaseColor * fvDiffuseLightColor * LdotN;

		return saturate( fvTotalAmbient + fvTotalDiffuse );
	}
	else
		return float4(0.0f, 0.0f, 0.0f, 1.0f);
}
//--------------------------------------------------------------------