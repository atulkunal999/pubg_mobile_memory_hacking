#include "Drawings.h"
#define PI 3.14159265

ID3DXLine* pLine = NULL;
LPDIRECT3DTEXTURE9 imagetexList[70];
LPD3DXSPRITE spriteList[70];
void DrawSprite(Vector3 pos, int id)
{
	if (id == -1)
		return;
	D3DXVECTOR3 imagepos;
	imagepos.x = pos.x;
	imagepos.y = pos.y;
	imagepos.z = 0;
	D3DSURFACE_DESC desc;
	imagetexList[id]->GetLevelDesc(0, &desc);
	try {
		float screen_pos_x = pos.x;
		float screen_pos_y = pos.y;
		D3DXVECTOR2 spriteCentre = D3DXVECTOR2(desc.Width / 2, desc.Height / 2);
		D3DXVECTOR2 trans = D3DXVECTOR2(screen_pos_x - (desc.Width/4), screen_pos_y - (desc.Height/2));
		D3DXMATRIX mat;
		D3DXVECTOR2 scaling(0.5f, 0.5f);
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, 0, &trans);
		spriteList[id]->Begin(D3DXSPRITE_ALPHABLEND);
		spriteList[id]->SetTransform(&mat);
		spriteList[id]->Draw(imagetexList[id], NULL, NULL, NULL, 0xFFFFFFFF);
		spriteList[id]->End();
		/*spriteList[id]->Begin(D3DXSPRITE_ALPHABLEND); //begin our sprite with alphablend so it support alpha, like png use alpha
		spriteList[id]->Draw(imagetexList[id], NULL, NULL, &imagepos, 0xFFFFFFFF); //Draw the sprite, first parameter is the image texture, 4th parameter is the position, last parameter is the color change leave to 0xFFFFFFFF for no change
		spriteList[id]->End(); //end the sprite*/
	}
	catch (std::exception ex)
	{
		//lol
	}
}
void DrawString(std::string str, int x, int y, int a, int r, int g, int b, ID3DXFont* font, bool centered)
{
	RECT FontPos;
	char* Stri = const_cast<char*>(str.c_str());
	FontPos.left = x;
	FontPos.top = y;
	if (centered)
	{
		TEXTMETRICA txtmet;

		font->GetTextMetrics(&txtmet);

		int size = (strlen(Stri) * (txtmet.tmAveCharWidth + 1))/2;
		FontPos.left = x - size;
		font->DrawTextA(0, Stri, strlen(Stri), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));
	}
	else
	{
		font->DrawTextA(0, Stri, strlen(Stri), &FontPos, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));
	}
	
}
void DrawStringBoderd(std::string str, int x, int y, int a, int r, int g, int b, ID3DXFont* font, bool centered)
{
	DrawString(str, x-1, y-1, a, 255, 255, 255, font, centered);
	DrawString(str, x-1, y+1, a, 255, 255, 255, font, centered);
	DrawString(str, x+1, y-1, a, 255, 255, 255, font, centered);
	DrawString(str, x+1, y+1, a, 255, 255, 255, font, centered);
	DrawString(str, x, y, a, r, g, b, font, centered);
}
void DrawBoxText(std::string str, int x, int y, int a, int r, int g, int b, ID3DXFont* font, bool centered)
{
	RECT FontPos;
	char* Stri = const_cast<char*>(str.c_str());
	FontPos.left = x;
	FontPos.top = y;
	if (centered)
	{
		TEXTMETRICA txtmet;

		font->GetTextMetrics(&txtmet);

		int size = (strlen(Stri) * (txtmet.tmAveCharWidth + 1)) / 2;
		FontPos.left = x - size;
		DrawBoxFilled(x - size - 1, y, size * 2, 25, 90, 0, 0, 255);
		font->DrawTextA(0, Stri, strlen(Stri), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));
	}
	else
	{
		font->DrawTextA(0, Stri, strlen(Stri), &FontPos, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));
	}
}
void DrawFilledRectangle(float x, float y, float w, float h, int a, int r, int g, int b)
{
	D3DRECT rect = { x, y, x + w, y + h };
	p_Device->Clear(1, &rect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(a, r, g, b), 1.0f, 0);

} 
void DrawBoxFilled(float x, float y, float w, float h, int a, int r, int g, int b)
{
	D3DXVECTOR2 points[2];
	for (int i = 0; i < w;i++)
	{
		points[0].x = x+i;
		points[0].y = y;

		points[1].x = x+i;
		points[1].y = y+h;
		pLine->Draw(points, 2, D3DCOLOR_ARGB(a, r, g, b));
	}
}
HRESULT initdata()
{
	if (FAILED(D3DXCreateLine(p_Device, &pLine)))
		return E_FAIL;
	pLine->SetWidth(1.6f);
	pLine->SetPattern(0xFFFFFFFF);
	pLine->SetAntialias(false);

	for (int i = 1; i < 70; i++)
	{
		std::string path = "icons\\(";
		if (FAILED(D3DXCreateTextureFromFileA(p_Device, path.append(std::to_string(i).append(")").append(".png")).c_str(), &imagetexList[i])))
		{
			//Emsg("Failed to laod the image");
			return E_FAIL; //return it failed
		}
		if (FAILED(D3DXCreateSprite(p_Device, &spriteList[i])))
		{
			//Emsg("Failed to create the sprite");
			return E_FAIL;
		}
	}
	return S_OK;
}
void DrawPlayerBlood(float x, float y, float h, float w, float fBlood, int max )
{
	float thickness = 2;
    if (fBlood > 70.0)
    {
		//DrawBorderBox(x, y, w, h, 1, 255, 0, 255, 0);
		DrawFilledRectangle(x, y, thickness, h * fBlood / max, 255, 0, 255, 0); // y
    }
    if (fBlood > 30.0 && fBlood <= 70.0)
    {
		//DrawBorderBox(x, y, w, h, 1, 255, 0, 255, 0);
		DrawFilledRectangle(x, y, thickness, h * fBlood / max, 255, 255, 255, 0); // y
    }
    if (fBlood > 0.0 && fBlood <= 30.0)
    {
		//DrawBorderBox(x, y, w, h, 1, 255, 0, 255, 0);
		DrawFilledRectangle(x, y, thickness, h * fBlood / max, 255, 255, 0, 0); // y
    }
}
void DrawLine(float x,float y,float x2,float y2,int a,int r,int g,int b)
{
	D3DXVECTOR2 points[2];
	points[0].x = x;
	points[1].x = x2;
	points[0].y = y;
	points[1].y = y2;
	pLine->Draw(points, 2, D3DCOLOR_ARGB(a,r,g,b));

}

void DrawBorderBox(float x, float y, float w, float h, int thickness, int a, int r, int g, int b)
{
	DrawFilledRectangle(x, y, w, thickness, a, r, g, b); // x
	DrawFilledRectangle(x, y, thickness, h, a, r, g, b); // y
	DrawFilledRectangle(x + w, y, thickness, h,a, r, g, b); // w
	DrawFilledRectangle(x, y + h, w + thickness, thickness, a, r, g, b); // h
}
void Circle(int X, int Y, int radius, int numSides, D3DCOLOR Color)
{
	D3DXVECTOR2 Line[128];
	float Step = PI * 2.0 / numSides;
	int Count = 0;
	for (float a = 0; a < PI * 2.0; a += Step)
	{
		float X1 = radius * cos(a) + X;
		float Y1 = radius * sin(a) + Y;
		float X2 = radius * cos(a + Step) + X;
		float Y2 = radius * sin(a + Step) + Y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count + 1].x = X2;
		Line[Count + 1].y = Y2;
		Count += 2;
	}
	pLine->Begin();
	pLine->Draw(Line, Count, Color);
	pLine->End();
}