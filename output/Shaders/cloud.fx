
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
	float3	Texcoord	:	TEXCOORD1; 
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

cbuffer timer	: register( b1 )
{
    float4 time;
};
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Texture
//--------------------------------------------------------------------

TextureCube txTexture : register( t0 );
Texture2D cloudTexture : register( t1 );

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
	
	Output.Texcoord = Input.Position.xyz * 0.01f;   

	return Output;
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------

float4 ps_main( PS_INPUT Input ) : SV_Target
{
	float4 skyColor = txTexture.Sample( samLinear, Input.ViewDir );
	float cloudSpeed = 0.01f;
    Input.Texcoord.xyz += cloudSpeed * time.x;
    float4 cloudColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
	cloudColor *= cloudTexture.Sample( samLinear, Input.Texcoord.xy );
    cloudColor *= cloudTexture.Sample( samLinear, Input.Texcoord.yz );
    cloudColor *= cloudTexture.Sample( samLinear, Input.Texcoord.xz );
   
	float cloudBias = -0.9f;
	float cloudScale = 20.0f;
    float lrp = cloudScale * cloudColor.r + cloudBias;
 //  
	//float4 cloudColor = float4(0.5f, 0.5f, 0.0f, 1.0f);

    return lerp(cloudColor, skyColor, saturate(lrp));
//	return skyColor;
}
//--------------------------------------------------------------------