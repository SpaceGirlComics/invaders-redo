#ifndef RENDER_OBJECT
#define RENDER_OBJECT

typedef struct TAGVertex
{
	float				fX;
	float				fY;
	float				fZ;
	float				fU;
	float				fV;
	DWORD				dwColor;
} Vertex;

class RenderObject
{
	public:
		Vertex*			GetVerticies();
		virtual void	render() = 0;
	protected:		
		static DX3D*	D3DX;
		Vertex*			Verticies;
};

#endif