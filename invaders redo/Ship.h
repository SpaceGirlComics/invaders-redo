#ifndef CSHIP_H
#define CSHIP_H
class Cship
{
	public:
		Cship();
		void create();
		void moving(float playerx);
		bullets* fire();
		static int myTicks;
		Vertex vtx[3];
		bool fired;
		void setFired();
		void unsetFired();
};
#endif