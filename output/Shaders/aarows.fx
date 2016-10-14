
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

[maxvertexcount(5)]
void gs_main( line GS_INPUT Input[2], inout LineStream<PS_INPUT> OutStream )
{
	PS_INPUT Output = ( PS_INPUT )0;
	
	//	Output default line
	Output.Color	= Input[0].Color;
	Output.Position = Input[0].Position;
	OutStream.Append( Output );
	
	Output.Color	= Input[1].Color;
	Output.Position = Input[1].Position;
	OutStream.Append( Output );

	OutStream.RestartStrip();

	//	Generate new lines
	if ( Input[0].Position.y == Input[1].Position.y )
	{
		//	X-axis
		Output.Position.x -= 0.1f;
		Output.Position.y += 0.1f;
		OutStream.Append( Output );
		
		Output.Position = Input[1].Position;
		OutStream.Append( Output );
		
		Output.Position.x -= 0.1f;
		Output.Position.y -= 0.1f;
		OutStream.Append( Output );

		OutStream.RestartStrip();
	}
	else if ( Input[0].Position.x == Input[1].Position.x )
	{
		//	Y-axis
		Output.Position.x -= 0.1f;
		Output.Position.y -= 0.1f;
		OutStream.Append( Output );
		
		Output.Position = Input[1].Position;
		OutStream.Append( Output );
		
		Output.Position.x += 0.1f;
		Output.Position.y -= 0.1f;
		OutStream.Append( Output );

		OutStream.RestartStrip();
	}

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