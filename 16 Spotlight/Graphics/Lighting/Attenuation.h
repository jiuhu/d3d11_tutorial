#pragma once

class Attenuation
{
public:

	/*
		Constructor.
	*/
	Attenuation(float constant = 1.0f, float linear = 0.0f, float quadratic = 0.0f)
		:	kc(constant), kl(linear), kq(quadratic)
	{}
	
	//	Constant attenuation.
	float kc;
	
	//	Linear attenuation.
	float kl;
	
	//	Quadratic attenuation.
	float kq;
};
//--------------------------------------------------------------------

class Spotlight	: public Attenuation
{
public:

	/*
		Constructor.
	*/
	Spotlight(float exponent = 2.0f, float constant = 1.0f, float linear = 0.0f, float quadratic = 0.0f)
		:	Attenuation(constant, linear, quadratic), p(exponent)
	{}
	
	//	Spotlight exponent.
	float p;
};
//--------------------------------------------------------------------