#include "includes.h"

CAlien::CAlien()
{
}

CAlien* CAlien::killElement(CAlien* _head)
{
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

bullets* CAlien::fire()
{
	bullets* i;
	i=new bullets();
	i->create(vtx[0].fX + 0.1f, vtx[0].fY, true);
	return(i);
}

void CAlien::move()
{
	if(totalCalls < 10)
	{
		for(int x=0;x<4;x++)
		{
			vtx[x].fX = vtx[x].fX + speed;
		}
		totalCalls++;
		if(vtx[0].fU<=0)
		{
			vtx[0].fU+=0.235f;
			vtx[1].fU+=0.25f;
			vtx[2].fU+=0.235f;
			vtx[3].fU+=0.25f;
		}
		else
		{
			vtx[0].fU-=0.235f;
			vtx[1].fU-=0.25f;
			vtx[2].fU-=0.235f;
			vtx[3].fU-=0.25f;
		}
	}
	else
	{
		totalCalls=0;
		speed*=-1;
		for(int x=0;x<4;x++)
		{
			vtx[x].fY=vtx[x].fY-.1f;

		}
		if(vtx[0].fU<=0)
		{
			vtx[0].fU+=0.235f;
			vtx[1].fU+=0.25f;
			vtx[2].fU+=0.235f;
			vtx[3].fU+=0.25f;
		}
		else
		{
			vtx[0].fU-=0.235f;
			vtx[1].fU-=0.25f;
			vtx[2].fU-=0.235f;
			vtx[3].fU-=0.25f;
		}
	}
}

void CAlien::create(float x, float y)
{
	markedForDeath = false;
	speed = 0.1f;
	totalCalls=0;
	vtx[0].fX = x;
	vtx[0].fY = y+ 0.3f;
	vtx[0].fZ = 1.0f;
	vtx[0].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
	vtx[0].fU = 0.0f;
	vtx[0].fV = 0.005f;

	vtx[1].fX = x + 0.3f;
	vtx[1].fY = y+ 0.3f;
	vtx[1].fZ = 1.0f;
	vtx[1].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
	vtx[1].fU = 0.23f;
	vtx[1].fV = 0.005f;

	vtx[2].fX = x;
	vtx[2].fY = y;
	vtx[2].fZ = 1.0f;
	vtx[2].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
	vtx[2].fU = 0.0f;
	vtx[2].fV = 0.95f;

	vtx[3].fX = x + 0.3f;
	vtx[3].fY = y;
	vtx[3].fZ = 1.0f;
	vtx[3].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
	vtx[3].fU = 0.23f;
	vtx[3].fV = 0.95f;
	
}