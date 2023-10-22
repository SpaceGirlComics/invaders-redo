#include "includes.h"

void moveAliens()
{
	while(drone)
	{
		drone->move();
		drone=drone->next;
	}
	drone=mother;
}

bool checkPlanetFall()
{
	while(drone)
	{
		if(drone->vtx[3].fY <= ship.vtx[1].fY)
		{
			state = STATE_OVER;
			drone=mother;
			KillCurrentBoard();
			return(true);
		}
		drone=drone->next;
	}
	drone=mother;
	return(false);
}

void bulletMakeAndMove()
{
	if(head)
	{
		while(drone)
		{
			if(rand()%225==0)
			{
				while(current->next)
				{
					current = current->next;
				}
				current->next = drone->fire();
				current->next->prev = current;
				current->next->next = NULL;
			}
			drone=drone->next;
		}
	}
	else
	{
		while(drone)
		{
			if(!head)
			{
				if(rand()%225 == 0)
				{
					head = drone->fire();
					head->prev = head->next = NULL;
				}
			}
			drone=drone->next;
		}
	}
	current = head;
	drone = mother;
	if(head)
	{
		while(current)
		{
			if(current->evil&&current->vtx[0].fY< ship.vtx[2].fY)
			{
				head = current->killElement(head);
				current = head;
			}
			if(head)
			{
				current=current->next;
			}
		}
		current = head;
		while(current)
		{
			if(current->vtx[0].fY>2.0f && !current->evil)
			{
				head = current->killElement(head);
				current = head;
			}
			if(head)
			{
				current=current->next;
			}
		}
		current=head;
		while(current)
		{
			current->move();
			current=current->next;
		}
		current=head;
	}
}

void KillCurrentBoard()
{
	if(head)
	{
		while(current->next!=NULL)
		{
			current = current->next;
		}
		while(current!=head)
		{
			current=current->prev;
			delete(current->next);
			current->next = NULL;
		}
		delete(current, head);
		head = current = NULL;
	}
	bullets::userCount = 0;
	if(mother)
	{
		while(drone->next)
		{
			drone=drone->next;
		}
		while(drone!=mother)
		{
			drone=drone->prev;
			delete(drone->next);
			drone->next=NULL;
		}
		delete(drone);
		drone = mother = NULL;
	}
}

bool doTitle()
{
	state = STATE_TITLE;
	drone= mother;
	KillCurrentBoard();
	return(true);
}

bool InitGame()
{
	for(int x = 11; x > 0; x--)
	{
		for(int y = 5; y>0; y--)
		{
			if(mother)
			{
				while(drone->next)
				{
					drone=drone->next;
				}
				drone->next= new CAlien();
				drone->next->prev=drone;
				drone->next->next=NULL;
				drone->next->create((float(x/2.5f)-3.05f), (float(y/2.2f)+.3f));
				drone=mother;
			}
			else
			{
				mother=new CAlien();
				mother->create((float(x/2.5f)-3.05f), (float(y/2.2f)+.3f));
				mother->next = mother->prev = NULL;
				drone=mother;
			}
		}
	}
	state = STATE_GAMEPLAY;
	ship.create();
	return(true);
}

void bulletAlienCollision()
{
	while(current)
	{
		while(drone&&current&&!current->evil)
		{
			if(current->vtx[0].fY >= drone->vtx[0].fY && current->vtx[3].fY <= drone->vtx[0].fY ||
				current->vtx[0].fY <= drone->vtx[0].fY && current->vtx[3].fY >= drone->vtx[3].fY ||
				current->vtx[0].fY >= drone->vtx[3].fY && current->vtx[3].fY <= drone->vtx[3].fY)
			{
				if(current->vtx[0].fX <= drone->vtx[0].fX && current->vtx[3].fX >= drone->vtx[0].fX||
					current->vtx[0].fX >= drone->vtx[0].fX && current->vtx[3].fX <= drone->vtx[3].fX||
					current->vtx[0].fX <= drone->vtx[3].fX && current->vtx[3].fX >= drone->vtx[3].fX)
				{
					//drone->vtx[0].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(0*255), (BYTE)(0*255));
					//drone->vtx[1].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(0*255), (BYTE)(0*255));
					//drone->vtx[2].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(0*255), (BYTE)(0*255));
					//drone->vtx[3].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(0*255), (BYTE)(0*255));						
					if(!current->evil)
					{
						mother = drone->killElement(mother);
						drone = mother;

						head = current->killElement(head);
						current = head;
					}
					
				}
			}

			if(drone)
			{
				drone = drone->next;
			}
		}
		if(current)
		{
			current = current->next;
		}
	}
	drone = mother;
	current = head;
}

void bulletShipCollision()
{
	//float left = ship.vtx[0].fX, right = ship.vtx[2].fX, bottom = ship.vtx[0].fY, top = ship.vtx[1].fY;
	//float width = right-left, height = top-bottom;
	while(current)
	{
		float left = ship.vtx[0].fX, right = ship.vtx[2].fX, bottom = ship.vtx[0].fY, top = ship.vtx[1].fY;
		float width = right-left, height = top-bottom;
		float top2 = bottom+(height/10);
		while(top2 <= top)
		{
			top2 = bottom+(height/10);
			if(current->vtx[3].fY <= top2 && current->vtx[0].fY>=bottom)
			{
				if(current->evil&&((current->vtx[0].fX <= right && current->vtx[0].fX >= left)||
					(current->vtx[3].fX >= left && current->vtx[3].fX <= right)))
				{
					state = STATE_OVER;
					KillCurrentBoard();
					top2= top+1;
				}
			}
			left+=(width/5)/10;
			right-=(width/5)/10;
			bottom+=height/10;
		}
		if(current)
		{
			current = current->next;
		}
	}
	current = head;
}