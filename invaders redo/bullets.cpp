#include "includes.h"

bullets::bullets()
{
}

bullets* bullets::killElement(bullets* _head)
{
	if(!evil)
	{
		userCount--;
	}
	if(next)
	{
		if(prev)
		{
			next->prev = prev;
			prev->next = next;

			delete this;
		}
		else
		{
			if(this == _head)
			{
				_head = _head->next;
			}
			this->next->prev = NULL;
			delete this;
		}
	}
	else
	{
		if(prev)
		{
			prev->next = NULL;
			delete this;
		}
		else
		{
			delete this;
			return NULL;
		}
	}
	return(_head);
}

void bullets::create(float x, float y, bool _evil)
{
	if(!_evil)
	{
		userCount++;
	}
	next=NULL;
	vtx[0].fX = x-0.02f;
	vtx[0].fY = y+0.09f;
	vtx[0].fZ = 1.0f;
	vtx[0].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
	//vtx[0].fU = 0.3f;
	//vtx[0].fV = 0.5f;

	vtx[1].fX = x+0.02f;
	vtx[1].fY = y+0.09f;
	vtx[1].fZ = 1.0f;
	vtx[1].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
	//vtx[1].fU = 0.3f;
	//vtx[1].fV = 0.5f;
	
	vtx[2].fX = x-0.02f;
	vtx[2].fY = y;
	vtx[2].fZ = 1.0f;
	vtx[2].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
	//vtx[2].fU = 0.3f;
	//vtx[2].fV = 0.5f;
	
	vtx[3].fX = x+0.02f;
	vtx[3].fY = y;
	vtx[3].fZ = 1.0f;
	vtx[3].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
	//vtx[3].fU = 0.3f;
	//vtx[3].fV = 0.5f;
	evil = _evil;
}

void bullets::move()
{
	if(evil)
	{
		vtx[0].fY-=0.1f;
		vtx[1].fY-=0.1f;
		vtx[2].fY-=0.1f;
		vtx[3].fY-=0.1f;
	}
	else
	{
		vtx[0].fY+=0.1f;
		vtx[1].fY+=0.1f;
		vtx[2].fY+=0.1f;
		vtx[3].fY+=0.1f;
	}
}