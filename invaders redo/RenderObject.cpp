#include "RenderObject.h"

LPDIRECT3DDEVICE RenderObject::getDXp()
{
	return(device);
}

void RenderObject::setDXp(LPDIRECT3DDEVICE9 _Device)
{
	device = _Device;
}

Vertex* RenderObject::GetVerticies()
{
	return(Verticies);
}