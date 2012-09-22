/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
In-Engine types
===============================================================================
*/

#pragma once


namespace Tuxis
{
	/*
	===============================================================================
	Float objects
	===============================================================================
	*/

	struct float2
	{
		float x,y;
		inline float2() : x(0), y(0) {}
		inline float2(float px,float py) : x(px), y(py) {}
		inline float2(const float2& p) : x(p.x), y(p.y) {}
		inline void operator() (float px, float py) { x=px; y=py;}
		inline void operator() (const float2& p) { x=p.x; y=p.y;}

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


	struct float4
	{
		float x,y,z,w;
		inline float4() : x(0), y(0), z(0), w(0) {}
		inline float4(float px,float py, float pz, float pw) : x(px), y(py), z(pz), w(pw) {}
		inline void operator() (float px, float py, float pz, float pw) { x=px; y=py; z=pz; w=pw;}

		void operator -= (const float4& pValue)
		{
			x-=pValue.x;
			y-=pValue.y;
			z-=pValue.z;
			w-=pValue.w;
		}

		void operator += (const float4& pValue)
		{
			x+=pValue.x;
			y+=pValue.y;
			z+=pValue.z;
			w-=pValue.w;
		}

		bool operator == (const float4& pValue)
		{
			return (
				x==pValue.x && 
				y==pValue.y &&
				z==pValue.z &&
				w==pValue.w); 
		}
	};


	struct floatRect
	{
		float x1,y1,x2,y2;

		inline floatRect() : x1(0), y1(0), x2(0), y2(0) {}

		inline floatRect(float px1, float py1, float px2, float py2) 
			: x1(px1), y1(py1), x2(px2), y2(py2) {}

		inline floatRect(float2 pLeftTop, float2 pRightBottom) 
			: x1(pLeftTop.x), y1(pLeftTop.y), x2(pRightBottom.x), y2(pRightBottom.y) {}
	
		void operator() (float px1, float py1, float px2, float py2)
		{
			x1=px1;
			y1=py1;
			x2=px2;
			y2=py2;
		}

		void operator() (float2 pLeftTop, float2 pRightBottom)
		{
			x1=pLeftTop.x;
			y1=pLeftTop.y;
			x2=pRightBottom.x;
			y2=pRightBottom.y;
		}
	};


	struct Color
	{
		float r,g,b,a;
		inline Color() : r(0), g(0), b(0), a(0) {}
		inline Color(float R, float G, float B,float A) : r(R), g(G), b(B), a(A) {}
		inline void operator () (float R, float G, float B,float A)	{ r=R; g=G; b=B; a=A; }

		void operator -= (const Color& pValue)
		{
			r-=pValue.r;
			g-=pValue.g;
			b-=pValue.b;
			a-=pValue.a;
		}

		void operator += (const Color& pValue)
		{
			r+=pValue.r;
			g+=pValue.g;
			b+=pValue.b;
			a-=pValue.a;
		}

		bool operator == (const Color& pValue)
		{
			return (
				r==pValue.r && 
				g==pValue.g &&
				b==pValue.b &&
				a==pValue.a); 
		}
	};
	
	/*
	===============================================================================
	Integer objects
	===============================================================================
	*/

	struct int2
	{
		int x,y;
		inline int2() : x(0), y(0) {}
		inline int2(int px,int py) : x(px), y(py) {}
		inline void operator() (int px, int py) { x=px; y=py;}
	};

	struct int4
	{
		int x,y,z,w;
		inline int4() : x(0), y(0), z(0), w(0) {}
		inline int4(int px,int py, int pz, int pw) : x(px), y(py), z(pz), w(pw) {}
		inline void operator() (int px, int py, int pz, int pw) { x=px; y=py; z=pz; w=pw;}
	};

}