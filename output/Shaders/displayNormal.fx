
//--------------------------------------------------------------------
// I/O Structure
//--------------------------------------------------------------------

struct VS_INPUT 
{
	float4	Position	:	POSITION;
	float3	Normal		:	NORMAL;
};

struct PS_INPUT 
{
	float4	Position	:	SV_POSITION;
	float3	Normal		:	TEXCOORD0;
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
// Vertex Shader
//--------------------------------------------------------------------

PS_INPUT vs_main( VS_INPUT Input )
{
    PS_INPUT Output = ( PS_INPUT )0;

	Output.Position = mul( Input.Position, matView );
	Output.Position = mul( Output.Position, matProjection );
    
	Output.Normal	= Input.Normal;

	return Output;
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Geometry Shader
//--------------------------------------------------------------------

[maxvertexcount(2)]
void gs_main( point PS_INPUT Input[1], inout LineStream<PS_INPUT> OutputStream )
{	
	OutputStream.Append(Input[0]);
	
	Input[0].Position.xyz += 0.2f * Input[0].Normal;
	
	OutputStream.Append(Input[0]);
	
	OutputStream.RestartStrip();
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------

float4 ps_main( PS_INPUT Input ) : SV_Target
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}
//--------------------------------------------------------------------