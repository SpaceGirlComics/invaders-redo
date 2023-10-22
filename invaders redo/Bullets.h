#ifndef BULLETS_H
#define BULLETS_H

class bullets
{
	public:
		bullets();
		bullets* killElement(bullets* _head);
		void create(float x, float y, bool _evil);
		void move();
        Vertex vtx[4];
		bullets *prev;
		bullets *next;
		bool evil;
		static int userCount;
		static int myTicks;
};

#endif