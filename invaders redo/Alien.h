#ifndef CALIEN_H
#define CALIEN_H
class CAlien
{
	public:
		CAlien();
		CAlien* killElement(CAlien* _head);
		bullets* fire();
		void move();
		void create(float x, float y);
		bullets* collision(bullets* _head);
		static int myTicks;
		CAlien* next;
		CAlien* prev;
		Vertex vtx[4];
		static IDirect3DTexture9 *g_pTexture;
		bool markedForDeath;

	private:
		float speed; 
		int totalCalls;
};

#endif