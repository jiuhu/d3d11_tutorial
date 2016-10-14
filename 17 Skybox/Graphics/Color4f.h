#pragma once

class Color4f
{
public:

	//	Color4f value
	union
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
	
		float c[4];
	};


	/*
		Constructors.
	*/
	Color4f()
		:	r(0),
			g(0),
			b(0),
			a(0)
	{
		//	Empty
	}

	Color4f(const Color4f &c)
		:	r(c.r),
			g(c.g),
			b(c.b),
			a(c.a)
	{
		//	Empty
	}

	Color4f(float cR, float cG, float cB, float cA = 1)
		:	r(cR),
			g(cG),
			b(cB),
			a(cA)
	{
		//	Empty
	}

	Color4f(const float * const rgba)
		:	r(rgba[0]),
			g(rgba[1]),
			b(rgba[2]),
			a(rgba[3])
	{
		//	Empty
	}
	
	/*
		This function is called to retrieve the color value.
	*/
	const float * const getColor() const
	{
		return c;
	}

	/*
		This function is called to set the color value by array.
	*/
	void setColor(const float * const rgba)
	{
		r = rgba[0];
		g = rgba[1];
		b = rgba[2];
		a = rgba[3];
	}

	/*
		This function is called to set the color value by value.
	*/
	void setColor(float r, float g, float b, float a = 1.0f)
	{
		c[0] = r;
		c[1] = g;
		c[2] = b;
		c[3] = a;
	}

	/*
		This function is called to toggle the transparent value.
	*/
	void setTranasparent(bool isTransparent = true)
	{
		a = (isTransparent) ? 0.0f : 1.0f;
	}
	
	/*
		Operator for retrieving data
	*/
	inline const float& operator[](size_t i) const 
	{
		if (i > 4) i = 3;
		return c[i];
	}
	
	/*
		Operator for modifying data
	*/
	inline float& operator[](size_t i) 
	{
		if (i > 4) i = 3;
		return c[i];
	}
	
	/*
		This function is called to return a black color object.
	*/
	static Color4f black()
	{
		return Color4f(0.0f, 0.0f, 0.0f);
	}
	
	/*
		This function is called to return a white color object.
	*/
	static Color4f white()
	{
		return Color4f(1.0f, 1.0f, 1.0f);
	}
	
	/*
		This function is called to return a red color object.
	*/
	static Color4f red()
	{
		return Color4f(1.0f, 0.0f, 0.0f);
	}
	
	/*
		This function is called to return a green color object.
	*/
	static Color4f green()
	{
		return Color4f(0.0f, 1.0f, 0.0f);
	}
	
	/*
		This function is called to return a blue color object.
	*/
	static Color4f blue()
	{
		return Color4f(0.0f, 0.0f, 1.0f);
	}
	
	/*
		This function is called to return a yellow color object.
	*/
	static Color4f yellow()
	{
		return Color4f(1.0f, 1.0f, 0.0f);
	}
	
	/*
		This function is called to return a cyan color object.
	*/
	static Color4f cyan()
	{
		return Color4f(0.0f, 1.0f, 1.0f);
	}
	
	/*
		This function is called to return a purple color object.
	*/
	static Color4f magenta()
	{
		return Color4f(1.0f, 0.0f, 1.0f);
	}
	
	/*
		This function is called to return a grey color object.
	*/
	static Color4f grey()
	{
		return Color4f(0.5f, 0.5f, 0.5f);
	}
	
	/*
		This function is called to return a null color object.
	*/
	static Color4f null()
	{
		return Color4f(0.0f, 0.0f, 0.0f);
	}
};
//--------------------------------------------------------------------