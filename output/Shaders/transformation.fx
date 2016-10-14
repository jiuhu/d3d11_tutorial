
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

//--------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------

PS_INPUT vs_main( VS_INPUT Input )
{
    PS_INPUT Output = ( PS_INPUT )0;
	
	Output.Position = mul( Input.Position, matWorld );
	Output.Position = mul( Output.Position, matView );
	Output.Position = mul( Output.Position, matProjection );
    

	return Output;
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------

float4 ps_main( PS_INPUT Input ) : SV_Target
{
    return float4(0.8f, 0.8f, 0.2f, 1.0f);
}
//--------------------------------------------------------------------