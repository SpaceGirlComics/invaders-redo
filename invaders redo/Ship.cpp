#include "includes.h"

Cship::Cship()
{
	fired = false;
}

void Cship::setFired()
{
	fired = true;
}

void Cship::unsetFired()
{
	fired = !fired;
}

void Cship::create()
{	
	vtx[0].fX = -0.25f;
	vtx[0].fY = -2.3f;
	vtx[0].fZ = 1.0f;
	vtx[0].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
	//vtx[0].fU = 0.0f;
	//vtx[0].fV = 0.0f;

	vtx[2].fX = 0.25f;
	vtx[2].fY = -2.3f;
	vtx[2].fZ = 1.0f;
	vtx[2].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
	//vtx[2].fU = 0.0f;
	//vtx[2].fV = 0.0f;

	vtx[1].fX = 0.0f;
	vtx[1].fY = -2.0f;
	vtx[1].fZ = 1.0f;
	vtx[1].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
	//vtx[1].fU = 0.0f;
	//vtx[1].fV = 0.0f;
}

void Cship::moving(float playerx)
{
	vtx[0].fX=vtx[0].fX+playerx;
	vtx[1].fX=vtx[1].fX+playerx;
	vtx[2].fX=vtx[2].fX+playerx;
}

bullets* Cship::fire()
{
	bullets* i;
	i= new bullets;
	i->create(vtx[1].fX, vtx[1].fY, false);
	return(i);
}