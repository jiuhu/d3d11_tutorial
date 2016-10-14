
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
// Constant Buffer
//--------------------------------------------------------------------

cbuffer CBuffer	:	register ( b0 )
{
	int		rangeX;
	int		rangeY;
	float2	origin;
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

[maxvertexcount(32)]
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

		float step = ( Input[1].Position.x - 0.2f - origin.x ) / rangeX;
		float	x = origin.x,
				y1 = origin.y + 0.05f,
				y2 = origin.y - 0.05f;
		for (int i = 0; i < rangeX; i++)
		{
			x += step;
			Output.Position.x = x;
			Output.Position.y = y1;
			OutStream.Append( Output );

			Output.Position.y = y2;
			OutStream.Append( Output );

			OutStream.RestartStrip();
		}
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

		float step = ( Input[1].Position.y - 0.2f - origin.y ) / rangeY;
		float	y = origin.y,
				x1 = origin.x + 0.05f,
				x2 = origin.x - 0.05f;
		for (int i = 0; i < rangeY; i++)
		{
			y += step;
			Output.Position.x = x1;
			Output.Position.y = y;
			OutStream.Append( Output );

			Output.Position.x = x2;
			OutStream.Append( Output );

			OutStream.RestartStrip();
		}
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