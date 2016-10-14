
//--------------------------------------------------------------------
// I/O Structure
//--------------------------------------------------------------------

struct VS_INPUT 
{
	float4	Position	:	POSITION;
	float4	Color		:	COLOR;
};

struct GS_INPUT 
{
	float4	Position	:	SV_POSITION;
	float4	Color		:	TEXCOORD0;
};

struct PS_INPUT 
{
	float4	Position	:	SV_POSITION;
	float4	Color		:	TEXCOORD0;
};
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------

PS_INPUT vs_main( VS_INPUT Input )
{
    PS_INPUT Output = ( PS_INPUT )0;

	Output.Position = Input.Position;
	Output.Color	= Input.Color;

	return Output;
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Geometry Shader
//--------------------------------------------------------------------

[maxvertexcount(12)]
void gs_main( triangle GS_INPUT Input[3], inout TriangleStream<PS_INPUT> OutStream )
{
	PS_INPUT Output = ( PS_INPUT )0;
	
	Output.Color	= Input[0].Color;
	Output.Position = Input[0].Position;
	OutStream.Append( Output );
	
	Output.Color	= Input[1].Color;
	Output.Position = Input[1].Position;
	OutStream.Append( Output );
	
	Output.Color	= Input[2].Color;
	Output.Position = Input[2].Position;
	OutStream.Append( Output );

    OutStream.RestartStrip();
	

	Output.Color	= Input[0].Color;
	Output.Position = Input[0].Position;
	OutStream.Append( Output );
	
	Output.Position = Input[0].Position + float4 ( -0.2f, 0.2f, 0.0f, 0.0f );
	OutStream.Append( Output );
	
	Output.Position = Input[0].Position + float4 ( 0.2f, 0.2f, 0.0f, 0.0f );
	OutStream.Append( Output );
	
    OutStream.RestartStrip();
	
	
	Output.Color	= Input[1].Color;
	Output.Position = Input[1].Position;
	OutStream.Append( Output );
	
	Output.Position = Input[1].Position + float4 ( 0.2f, 0.2f, 0.0f, 0.0f );
	OutStream.Append( Output );
	
	Output.Position = Input[1].Position + float4 ( 0.2f, -0.2f, 0.0f, 0.0f );
	OutStream.Append( Output );

    OutStream.RestartStrip();
	
	
	Output.Color	= Input[2].Color;
	Output.Position = Input[2].Position;
	OutStream.Append( Output );
	
	Output.Position = Input[2].Position + float4 ( -0.2f, -0.2f, 0.0f, 0.0f );
	OutStream.Append( Output );
	
	Output.Position = Input[2].Position + float4 ( -0.2f, 0.2f, 0.0f, 0.0f );
	OutStream.Append( Output );

    OutStream.RestartStrip();
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------

float4 ps_main( PS_INPUT Input ) : SV_Target
{
	return Input.Color;
}
//--------------------------------------------------------------------