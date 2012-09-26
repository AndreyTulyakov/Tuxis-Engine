/*
* ===============================================================================
* Tuxis Project
* Copyright (C) 2011-2012, Andrew Tulay
* ===============================================================================
* Types
* ===============================================================================
*/
#pragma once


namespace Tuxis
{
	/*
	*=======================================================================
	* Float types
	*=======================================================================
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
                
                float2 operator + (const float2& pValue)
                {
                    float2 t(x+pValue.x,y+pValue.y);
                    return t;
                }
                
                float2 operator - (const float2& pValue)
                {
                    float2 t(x-pValue.x,y-pValue.y);
                    return t;
                }
	};


	struct float4
	{
		float x,y,z,w;
                
		inline float4() : x(0), y(0), z(0), w(0) {}
		inline float4(float px,float py, float pz, float pw) : x(px), y(py), z(pz), w(pw) {}
                inline float4(const float4& p) : x(p.x), y(p.y), z(p.z), w(p.w) {}
                
		inline void operator() (float px, float py, float pz, float pw) { x=px; y=py; z=pz; w=pw;}
                inline void operator() (const float4& p) { x=p.x; y=p.y; z=p.z; w=p.w; }
                
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
                
                float4 operator + (const float4& pValue)
                {
                    float4 t(x+pValue.x, y+pValue.y, z+pValue.z, w+pValue.w);
                    return t;
                }
                
                float4 operator - (const float4& pValue)
                {
                    float4 t(x-pValue.x, y-pValue.y, z-pValue.z, w-pValue.w);
                    return t;
                }
	};


	struct floatRect
	{
		float x1,y1,x2,y2;

		inline floatRect() : x1(0), y1(0), x2(0), y2(0) {}
		inline floatRect(float px1, float py1, float px2, float py2) 
			: x1(px1), y1(py1), x2(px2), y2(py2) {}
		inline floatRect(float2 pPoint1, float2 pPoint2) 
			: x1(pPoint1.x), y1(pPoint1.y), x2(pPoint2.x), y2(pPoint2.y) {}
	
		void operator() (float px1, float py1, float px2, float py2)
		{
			x1=px1;
			y1=py1;
			x2=px2;
			y2=py2;
		}

		void operator() (float2 pPoint1, float2 pPoint2)
		{
			x1=pPoint1.x;
			y1=pPoint1.y;
			x2=pPoint2.x;
			y2=pPoint2.y;
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
                
                Color operator + (const Color& pValue)
                {
                    Color t(r+pValue.r, g+pValue.g, b+pValue.b, a+pValue.a);
                    return t;
                }
                
                Color operator - (const Color& pValue)
                {
                    Color t(r-pValue.r, g-pValue.g, b-pValue.b, a-pValue.a);
                    return t;
                }
	};
	
        
	/*
	*=======================================================================
	* Integer types
	*=======================================================================
	*/

	struct int2
	{
		int x,y;

                inline int2() : x(0), y(0) {}
		inline int2(int px,int py) : x(px), y(py) {}
                inline int2(const int2& p) : x(p.x), y(p.y) {}
                
		inline void operator() (int px, int py) { x=px; y=py;}
                inline void operator() (const int2& p) { x=p.x; y=p.y; }
                
                bool operator == (const int2& pValue)
		{
			return (x==pValue.x && y==pValue.y); 
		}
                
                void operator -= (const int2& pValue)
		{
			x-=pValue.x;
			y-=pValue.y;
		}

		void operator += (const int2& pValue)
		{
			x+=pValue.x;
			y+=pValue.y;
		}
                
                int2 operator + (const int2& pValue)
                {
                    int2 t(x+pValue.x,y+pValue.y);
                    return t;
                }
                
                int2 operator - (const int2& pValue)
                {
                    int2 t(x-pValue.x,y-pValue.y);
                    return t;
                }
	};

	struct int4
	{
		int x,y,z,w;
                
		inline int4() : x(0), y(0), z(0), w(0) {}
		inline int4(int px,int py, int pz, int pw) : x(px), y(py), z(pz), w(pw) {}
                inline int4(const int4& p) : x(p.x), y(p.y), z(p.z), w(p.w) {}
                
		inline void operator() (int px, int py, int pz, int pw) { x=px; y=py; z=pz; w=pw;}
                inline void operator() (const int2& p) { x=p.x; y=p.y; }
                
                bool operator == (const int4& pValue)
		{
			return (
				x==pValue.x && 
				y==pValue.y &&
				z==pValue.z &&
				w==pValue.w); 
		}
                
                void operator -= (const int4& pValue)
		{
			x-=pValue.x;
			y-=pValue.y;
			z-=pValue.z;
			w-=pValue.w;
		}

		void operator += (const int4& pValue)
		{
			x+=pValue.x;
			y+=pValue.y;
			z+=pValue.z;
			w-=pValue.w;
		}
                
                int4 operator + (const int4& pValue)
                {
                    int4 t(x+pValue.x, y+pValue.y, z+pValue.z, w+pValue.w);
                    return t;
                }
                
                int4 operator - (const int4& pValue)
                {
                    int4 t(x-pValue.x, y-pValue.y, z-pValue.z, w-pValue.w);
                    return t;
                }
	};

}