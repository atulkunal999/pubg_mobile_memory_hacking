#ifndef DRAWINGS_H
#define DRAWINGS_H

#include "Utilities.h"
#include "DirectX.h"

#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )


#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <iostream>

void DrawString(std::string str, int x, int y, int a, int r, int g, int b, ID3DXFont* font,bool centered  = false);
void DrawFilledRectangle(float x, float y, float w, float h, int a, int r, int g, int b);
void DrawBoxFilled(float x, float y, float w, float h, int a, int r, int g, int b);
void DrawBoxText(std::string str, int x, int y, int a, int r, int g, int b, ID3DXFont* font, bool centered = false);
void DrawBorderBox(float x, float y, float w, float h, int thickness, int a, int r, int g, int b);
void DrawLine(float x, float y, float x2, float y2, int a, int r, int g, int b);
void DrawPlayerBlood(float x, float y, float h, float w, float fBlood, int max = 100);
void DrawStringBoderd(std::string str, int x, int y, int a, int r, int g, int b, ID3DXFont* font, bool centered);
void Circle(int X, int Y, int radius, int numSides, D3DCOLOR Color);
HRESULT initdata();
void DrawSprite(Vector3 pos, int id);
#endif