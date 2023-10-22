#include "includes.h"

void moveAliens()
{
	if(heads)
	{
		while(currents->next)
		{
			currents=currents->next;
		}

		currents->next = (Sound*)malloc(sizeof(Sound));
		currents->next->next = NULL;
		currents->next->prev = currents;
		currents= currents->next;
		currents->load("7.wav");
		
	}
	else
	{
		heads = (Sound*) malloc(sizeof(Sound));
		heads->next = heads->prev = NULL;
		currents = heads;
		heads->load("7.wav");
	}
	
	while(drone)
	{
		if(drone == mother)
		{
			currents->play();
		}
		if(drone->getState()==ALIEN_ALIVE)
		{
			drone->move();
		}
		
		drone=drone->next;
	}
	
	currents = heads;
	drone=mother;
}

bool checkPlanetFall()
{
	while(drone)
	{
		if((drone->getVtx()[3].fY <= ship.getVtx()[1].fY) && drone->getState()==ALIEN_ALIVE)
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
		if(ship.getState()==SHIP_ALIVE)
		{
			while(drone)
			{
				if(rand()%225==0&&drone->getState()==ALIEN_ALIVE)
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
	}
	else
	{
		if(ship.getState()!=SHIP_ALIVE)
		{
			ship.setState(SHIP_ALIVE);
			if(Cship::lives<0)
			{
				state = STATE_OVER;
				KillCurrentBoard();
			}
		}
		while(drone)
		{
			if(!head)
			{
				if(rand()%225 == 0&&drone->getState()==ALIEN_ALIVE)
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
			if(current->isEvil()&&current->getVtx()[0].fY< ship.getVtx()[2].fY)
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
			if(current->getVtx()[0].fY>2.0f && !current->isEvil())
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
	if(heads)
	{
		while(currents->next)
		{
			currents = currents->next;
		}
		while(currents!=heads)
		{
			currents = currents->prev;
			delete currents->next;
			currents->next=NULL;
		}
		delete currents;
		currents = heads = NULL;
	}
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
	ship.create(D3DX->getDevice());
	return(true);
}

void bulletAlienCollision()
{
	while(drone)
	{
		if(drone->getExplo())
		{
			mother = drone->killElement(mother);
			drone = mother;
		}
		else
		{
			drone = drone->next;
		} 
	}
	drone = mother;

	while(current)
	{
		while(drone&&current&&!current->isEvil())
		{
			if(current->getVtx()[0].fY >= drone->getVtx()[0].fY && current->getVtx()[3].fY <= drone->getVtx()[0].fY ||
				current->getVtx()[0].fY <= drone->getVtx()[0].fY && current->getVtx()[3].fY >= drone->getVtx()[3].fY ||
				current->getVtx()[0].fY >= drone->getVtx()[3].fY && current->getVtx()[3].fY <= drone->getVtx()[3].fY)
			{
				if(current->getVtx()[0].fX <= drone->getVtx()[0].fX && current->getVtx()[3].fX >= drone->getVtx()[0].fX||
					current->getVtx()[0].fX >= drone->getVtx()[0].fX && current->getVtx()[3].fX <= drone->getVtx()[3].fX||
					current->getVtx()[0].fX <= drone->getVtx()[3].fX && current->getVtx()[3].fX >= drone->getVtx()[3].fX)
				{
					//drone->vtx[0].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(0*255), (BYTE)(0*255));
					//drone->vtx[1].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(0*255), (BYTE)(0*255));
					//drone->vtx[2].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(0*255), (BYTE)(0*255));
					//drone->vtx[3].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(0*255), (BYTE)(0*255));						
					if(!current->isEvil()&&drone->getState()==ALIEN_ALIVE)
					{
						if(heads)
						{
							while(currents->next)
							{
								currents=currents->next;
							}

							currents->next = (Sound*)malloc(sizeof(Sound));
							currents->next->next = NULL;
							currents->next->prev = currents;
							currents= currents->next;
							currents->load("invaderkilled.wav");
							
						}
						else
						{
							heads = (Sound*) malloc(sizeof(Sound));
							heads->next = heads->prev = NULL;
							currents = heads;
							heads->load("invaderkilled.wav");
						}
						drone->setState(ALIEN_EXPODING);
						drone->Exploding();
						drone->setExplo(currents);
						currents->play();

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
	if(heads)
	{
		while(currents->next)
		{
			currents=currents->next;
		}

		currents->next = (Sound*)malloc(sizeof(Sound));
		currents->next->next = NULL;
		currents->next->prev = currents;
		currents= currents->next;
		currents->load("12.wav");
	}
	else
	{
		heads = (Sound*) malloc(sizeof(Sound));
		heads->next = heads->prev = NULL;
		currents = heads;
		heads->load("12.wav");
	}

	if(ship.getState()==SHIP_ALIVE)
	{
		while(current)
		{
			float left = ship.getVtx()[0].fX, right = ship.getVtx()[2].fX, bottom = ship.getVtx()[0].fY, top = ship.getVtx()[1].fY;
			float width = right-left, height = top-bottom;
			float top2 = bottom+(height/10);
			while(top2 <= top)
			{
				top2 = bottom+(height/10);
				if(current->getVtx()[3].fY <= top2 && current->getVtx()[0].fY>=bottom)
				{
					if(current->isEvil()&&((current->getVtx()[0].fX <= right && current->getVtx()[0].fX >= left)||
						(current->getVtx()[3].fX >= left && current->getVtx()[3].fX <= right)))
					{
						ship.setState(SHIP_EXPLODING);
						currents->play();
						currents = heads;
						Cship::lives--;
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
		if(ship.getState()==SHIP_EXPLODING)
		{
			ship.Exploding();
		}
	}
}