/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Input Base
Required: none
===============================================================================
*/

#pragma once


namespace Tuxis
{
	/*
	===============================================================================
	Float
	===============================================================================
	*/

	struct floatRect
	{
		float x1,x2;
		float y1,y2;
		inline floatRect() {}
		inline floatRect(float X1,float Y1, float X2, float Y2) : x1(X1), y1(Y1), x2(X2), y2(Y2) {}
	};

	struct float2
	{
		float x,y;
		inline float2() {}
		inline float2(float px,float py) : x(px), y(py) {}

		inline void operator() (float px, float py) { x=px; y=py;}

		void operator -= (const float2& pValue)
		{
			x-=pValue.x;
			y-=pValue.y;
		}

		void operator += (const float2& pValue)
		{
			x+=pValue.x;
			y+=pValue.y;
		}

		bool operator == (const float2& pValue)
		{
			return (x==pValue.x && y==pValue.y); 
		}
	};

	struct float3
	{
		float x,y,z;
		inline float3() {}
		inline float3(float px,float py, float pz) : x(px), y(py), z(pz) {}
	};

	struct float4
	{
		float x,y,z,w;
		inline float4() {}
		inline float4(float px,float py, float pz, float pw) : x(px), y(py), z(pz), w(pw) {}
	};

	struct Color
	{
		float r,g,b,a;
		inline Color() {}
		inline Color(float R, float G, float B,float A) : r(R), g(G), b(B), a(A) {}

		inline void operator () (float R, float G, float B,float A)	{ r=R; g=G; b=B; a=A; }
	};
	
	/*
	===============================================================================
	Integer
	===============================================================================
	*/

	struct int2
	{
		int x,y;
		inline int2() {}
		inline int2(int px,int py) : x(px), y(py) {}
	};

	struct int4
	{
		int x,y,z,w;
		inline int4() {}
		inline int4(int px,int py, int pz, int pw) : x(px), y(py), z(pz), w(pw) {}
	};

	struct intRect
	{
		int x1,x2;
		int y1,y2;
		inline intRect() {}
		inline intRect(int X1,int Y1, int X2, int Y2) : x1(X1), y1(Y1), x2(X2), y2(Y2) {}
	};

}