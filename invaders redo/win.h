class CWinScreen
{
	public:
		Vertex vtx[4];	
		static IDirect3DTexture9 *g_pTexture;
		CWinScreen()
		{
			vtx[0].fX = -2.0f;
			vtx[0].fY = 0.75f;
			vtx[0].fZ = 1.0f;
			vtx[0].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
			vtx[0].fU = 0.0f;
			vtx[0].fV = 0.0f;
			
			vtx[1].fX = 2.0f;
			vtx[1].fY = 0.75f;
			vtx[1].fZ = 1.0f;
			vtx[1].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
			vtx[1].fU = 0.999f;
			vtx[1].fV = 0.0f;
		
			vtx[2].fX = -2.0f;
			vtx[2].fY = 0.0f;
			vtx[2].fZ = 1.0f;
			vtx[2].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
			vtx[2].fU = 0.0f;
			vtx[2].fV = 0.98f;

			vtx[3].fX = 2.0f;
			vtx[3].fY = 0.0f;
			vtx[3].fZ = 1.0f;
			vtx[3].dwColor = D3DCOLOR_ARGB((BYTE)(0*255), (BYTE)(1*255), (BYTE)(1*255), (BYTE)(1*255));
			vtx[3].fU = 0.999f;
			vtx[3].fV = 0.98f;
		}		
};