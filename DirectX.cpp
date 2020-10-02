#include "DirectX.h"
#include "pch.h"
#include "Main.h"
#include <numeric>
#include <future>
#include <string>
#include <mutex>

/**/
/**/

IDirect3D9Ex* p_Object = 0;
IDirect3DDevice9Ex* p_Device = 0;
D3DPRESENT_PARAMETERS p_Params;
RECT rc;
std::string aimplayer;
ID3DXFont* pFont;
ID3DXFont* mFont;
ID3DXFont* bFont;
Vector2 aimpos;
bool menu = true,norecoil = false, lines = true, allitems = false, drawbox = true, vichlesp = true, lboxshow = true, impitemrs = true, skullshow = true;
bool iconshow = false,aimbot = false;
void setvertix(Vector2 vec1,Vector2 vec2)
{
	DrawLine(vec1.x, vec1.y, vec2.x, vec2.y, 255, 255, 255, 255);
}
bool WorldToScreen(Vector3 pos, Vector3& screen, int* distance, D3DMatrix viewMatrix) {
	float screenW = (viewMatrix._14 * pos.x) + (viewMatrix._24 * pos.y) + (viewMatrix._34 * pos.z + viewMatrix._44);
	screen.z = screenW;
	*distance = (screenW / 100);
	if (screenW < 0.0001f) return false;
	screenW = 1 / screenW;
	float sightX = (Width / 2);
	float sightY = (Height / 2);
	screen.x = sightX + (viewMatrix._11 * pos.x + viewMatrix._21 * pos.y + viewMatrix._31 * pos.z + viewMatrix._41) * screenW * sightX;
	screen.y = sightY - (viewMatrix._12 * pos.x + viewMatrix._22 * pos.y + viewMatrix._32 * pos.z + viewMatrix._42) * screenW * sightY;
	return true;
}
bool WorldToScreenBone(D3DMatrix viewMatrix, Vector3 pos, Vector2& screen, int* distance) {
	float screenW = (viewMatrix._14 * pos.x) + (viewMatrix._24 * pos.y) + (viewMatrix._34 * pos.z + viewMatrix._44);
	*distance = (screenW / 100);
	if (screenW < 0.0001f) return false;
	screenW = 1 / screenW;
	float sightX = (Width / 2);
	float sightY = (Height / 2);
	screen.x = sightX + (viewMatrix._11 * pos.x + viewMatrix._21 * pos.y + viewMatrix._31 * pos.z + viewMatrix._41) * screenW * sightX;
	screen.y = sightY - (viewMatrix._12 * pos.x + viewMatrix._22 * pos.y + viewMatrix._32 * pos.z + viewMatrix._42) * screenW * sightY;
	return true;
}
bool WorldToScreenPlayer(Vector3 pos, Vector3& screen, int* distance, D3DMatrix viewMatrix) {
	float screenW = (viewMatrix._14 * pos.x) + (viewMatrix._24 * pos.y) + (viewMatrix._34 * pos.z + viewMatrix._44);
	*distance = (screenW / 100);
	if (screenW < 0.0001f) return false;
	float screenY = (viewMatrix._12 * pos.x) + (viewMatrix._22 * pos.y) + (viewMatrix._32 * (pos.z + 85) + viewMatrix._42);
	float screenX = (viewMatrix._11 * pos.x) + (viewMatrix._21 * pos.y) + (viewMatrix._31 * pos.z + viewMatrix._41);
	screen.y = (Height / 2) - (Height / 2) * screenY / screenW;
	screen.x = (Width / 2) + (Width / 2) * screenX / screenW;
	float y1 = (Height / 2) - (viewMatrix._12 * pos.x + viewMatrix._22 * pos.y + viewMatrix._32 * (pos.z - 95) + viewMatrix._42) * (Height / 2) / screenW;
	screen.z = y1 - screen.y;
	return true;
}
D3DMatrix ToMatrixWithScale(Vector3 translation, Vector3 scale, Vector4 rot) {
	D3DMatrix m;
	m._41 = translation.x;
	m._42 = translation.y;
	m._43 = translation.z;

	float x2 = rot.x + rot.x;
	float y2 = rot.y + rot.y;
	float z2 = rot.z + rot.z;

	float xx2 = rot.x * x2;
	float yy2 = rot.y * y2;
	float zz2 = rot.z * z2;
	m._11 = (1.0f - (yy2 + zz2)) * scale.x;
	m._22 = (1.0f - (xx2 + zz2)) * scale.y;
	m._33 = (1.0f - (xx2 + yy2)) * scale.z;

	float yz2 = rot.y * z2;
	float wx2 = rot.w * x2;
	m._32 = (yz2 - wx2) * scale.z;
	m._23 = (yz2 + wx2) * scale.y;

	float xy2 = rot.x * y2;
	float wz2 = rot.w * z2;
	m._21 = (xy2 - wz2) * scale.y;
	m._12 = (xy2 + wz2) * scale.x;

	float xz2 = rot.x * z2;
	float wy2 = rot.w * y2;
	m._31 = (xz2 + wy2) * scale.z;
	m._13 = (xz2 - wy2) * scale.x;

	m._14 = 0.0f;
	m._24 = 0.0f;
	m._34 = 0.0f;
	m._44 = 1.0f;

	return m;
}
D3DMatrix MatrixMultiplication(D3DMatrix pM1, D3DMatrix pM2) {
	D3DMatrix pOut = {
		pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41,
		pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42,
		pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43,
		pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44,
		pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41,
		pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42,
		pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43,
		pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44,
		pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41,
		pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42,
		pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43,
		pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44,
		pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41,
		pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42,
		pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43,
		pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44
	};

	return pOut;
}
Vector3 GetBoneWorldPosition(DWORD actorAddv, DWORD boneAddv) {
	FTTransform2_t bone = g_pMemoryManager->ReadFTransform2(boneAddv);
	FTTransform2_t actor = g_pMemoryManager->ReadFTransform2(actorAddv);
	D3DMatrix boneMatrix = ToMatrixWithScale(bone.Translation, bone.Scale3D, bone.Rotation);
	D3DMatrix componentToWorldMatrix = ToMatrixWithScale(actor.Translation, actor.Scale3D, actor.Rotation);
	D3DMatrix newMatrix = MatrixMultiplication(boneMatrix, componentToWorldMatrix);
	Vector3 bonePos;
	bonePos.x = newMatrix._41;
	bonePos.y = newMatrix._42;
	bonePos.z = newMatrix._43;
	return bonePos;
}
bool isnull(Vector2 dat)
{
	if (dat.x != NULL)
		if (dat.y != NULL)
			return true;
	return false;
}
void DrawMenu()
{
	if (menu)
	{
		/*------------------------*/
		//DrawFilledRectangle(10, Height / 2 - 20, 110, 160, 128, 128, 128, 128);
		DrawBorderBox(10, Height / 2 - 20, 110, 150, 2, 255, 0, 255, 0);
		DrawBorderBox(10, Height / 2 - 20, 110, 180, 2, 255, 0, 255, 0);

		DrawStringBoderd("RIXOT VIP HACK", 15, Height / 2 - 35, 255, 255, 0, 0, pFont,false);
		DrawString("[INS] To Close The", 15, Height / 2 + 135, 255, 0, 255, 0, mFont);
		DrawString("          Hack", 15, Height / 2 + 145, 255, 0, 255, 0, mFont);
		/*---------------------------*/

		std::string menutxt = "F1 : SHOW MENU ";
		if (menu)
		{
			DrawString(menutxt, 15, Height / 2 - 15, 255, 0, 255, 0, mFont);
		}
		else
		{
			DrawString(menutxt, 15, Height / 2 - 15, 255, 255, 0, 0, mFont);
		}

		/*---------------------------*/

		menutxt = "F2 : SHOW LINES ";
		if (lines)
		{
			DrawString(menutxt, 15, Height / 2 , 255, 0, 255, 0, mFont);
		}
		else
		{
			DrawString(menutxt, 15, Height / 2 , 255, 255, 0, 0, mFont);
		}

		/*---------------------------*/

		menutxt = "F3 : ALL ITEMS ";
		if (allitems)
		{
			DrawString(menutxt, 15, Height / 2 + 15, 255, 0, 255, 0, mFont);
		}
		else
		{
			DrawString(menutxt, 15, Height / 2 + 15, 255, 255, 0, 0, mFont);
		}

		/*---------------------------*/

		menutxt = "F4 : PLAYER BOX ";
		if (drawbox)
		{
			DrawString(menutxt, 15, Height / 2 + 30, 255, 0, 255, 0, mFont);
		}
		else
		{
			DrawString(menutxt, 15, Height / 2 + 30, 255, 255, 0, 0, mFont);
		}

		/*---------------------------*/

		menutxt = "F5 : VEHICLE ESP ";
		if (vichlesp)
		{
			DrawString(menutxt, 15, Height / 2 + 45, 255, 0, 255, 0, mFont);
		}
		else
		{
			DrawString(menutxt, 15, Height / 2 + 45, 255, 255, 0, 0, mFont);
		}
		/*---------------------------*/

		menutxt = "F6 :  lootboxr ";
		if (lboxshow)
		{
			DrawString(menutxt, 15, Height / 2 + 60, 255, 0, 255, 0, mFont);
		}
		else
		{
			DrawString(menutxt, 15, Height / 2 + 60, 255, 255, 0, 0, mFont);
		}
		/*---------------------------*/

		menutxt = "F7 :  Imp Items ";
		if (impitemrs)
		{
			DrawString(menutxt, 15, Height / 2 + 75, 255, 0, 255, 0, mFont);
		}
		else
		{
			DrawString(menutxt, 15, Height / 2 + 75, 255, 255, 0, 0, mFont);
		}

		/*---------------------------*/

		menutxt = "F8 :  Skeleton ";
		if (skullshow)
		{
			DrawString(menutxt, 15, Height / 2 + 90, 255, 0, 255, 0, mFont);
		}
		else
		{
			DrawString(menutxt, 15, Height / 2 + 90, 255, 255, 0, 0, mFont);
		}
		/*---------------------------*/
		menutxt = "F9 :  Icons ";
		if (!iconshow)
		{
			DrawString(menutxt, 15, Height / 2 + 105, 255, 0, 255, 0, mFont);
		}
		else
		{
			DrawString(menutxt, 15, Height / 2 + 105, 255, 255, 0, 0, mFont);
		}
		/*---------------------------*/
		menutxt = "F10 :  AimBot ";
		if (aimbot)
		{
			DrawString(menutxt, 15, Height / 2 + 118, 255, 0, 255, 0, mFont);
		}
		else
		{
			DrawString(menutxt, 15, Height / 2 + 118, 255, 255, 0, 0, mFont);
		}
		
	}
}
void LoadFont()
{
	if (FAILED(D3DXCreateFontA(p_Device, 14, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Rounded MT Bold", &pFont)))
	{
		MessageBoxA(0, "Font Load Error Small", "Error", MB_OK);
	}
	if (FAILED(D3DXCreateFontA(p_Device, 20, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Rounded MT Bold", &bFont)))
	{
		MessageBoxA(0, "Font Load Error Big", "Error", MB_OK);
	}
	if (FAILED(D3DXCreateFontA(p_Device, 12, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Rounded MT Bold", &mFont)))
	{
		MessageBoxA(0, "Font Load Error Mid", "Error", MB_OK);
	}

}
void UpdateHW()
{
	p_Params.BackBufferWidth = Width;
	p_Params.BackBufferHeight = Height;
}
int DirectXInit(HWND hWnd)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
	{
		MessageBox(0, "Unable to create Direct 3D Device", "", 0);
		exit(1);
	}
	ZeroMemory(&p_Params, sizeof(p_Params));    
	p_Params.Windowed = TRUE;
    p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;    
    p_Params.hDeviceWindow = hWnd;    
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
    p_Params.BackBufferFormat = D3DFMT_A8R8G8B8 ;     
    p_Params.BackBufferWidth = Width;    
	p_Params.BackBufferCount = 1;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    p_Params.BackBufferHeight = Height;    
    p_Params.EnableAutoDepthStencil = TRUE;
    p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	
	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device)))
		exit(1);

	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	p_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTCOLOR);
	p_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCALPHA);
	p_Device->SetTexture(0, NULL);
	p_Device->SetPixelShader(0);
	p_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	p_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	p_Device->SetRenderState(D3DRS_ZENABLE, FALSE);
	p_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	p_Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTSS_COLORARG1);
	p_Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

	p_Device->SetRenderState(D3DRS_ZENABLE, true);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, true);
	p_Device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	p_Device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ZERO);
	p_Device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	p_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	p_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	p_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	if (FAILED(initdata()))
	{
		exit(EXIT_FAILURE);
	}
	return 0;
}

Vector2 AimFindBestTarget() {
	float targetDistance = 9999.0;
	Vector2 retval;
	retval.x = 0;
	retval.y = 0;
	int dist;
	for (int i = 0; i < g_pEsp->playerdatar.size(); i++) {
		DWORD tmpAddv = g_pMemoryManager->iRead(g_pEsp->playerdatar[i].Address + 776);
		DWORD bodyAddv = tmpAddv + 320;
		DWORD boneAddv = g_pMemoryManager->iRead(tmpAddv + 1408) + 48;

		Vector2 chest;
		Vector3 chestPos = GetBoneWorldPosition(bodyAddv, boneAddv + 4 * 48);
		if (WorldToScreenBone(g_pEsp->vt, chestPos, chest, &dist))
		{
			if (g_pEsp->playerdatar[i].Health > 0) {
				float cross_dist = sqrt(pow(chest.x - Width/2, 2) + pow(chest.y - Height/2, 2));
				if (cross_dist < targetDistance)
				{
						retval = chest;
						targetDistance = cross_dist;
						aimplayer = g_pEsp->playerdatar[i].Name;
				
				}
			}
		}
	}
	return retval;
}
void AimAtPos(float x, float y)
{
	int num = Width / 2;
	int num2 = Height / 2;
	float num3 = (float)10.0f + 1.0f;
	float num4 = 0.0f;
	float num5 = 0.0f;
	if (x != 0.0f)
	{
		if (x > (float)num)
		{
			num4 = -((float)num - x);
			num4 /= num3;
			if (num4 + (float)num > (float)(num * 2))
			{
				num4 = 0.0f;
			}
		}
		if (x < (float)num)
		{
			num4 = x - (float)num;
			num4 /= num3;
			if (num4 + (float)num < 0.0f)
			{
				num4 = 0.0f;
			}
		}
	}
	if (y != 0.0f)
	{
		if (y > (float)num2)
		{
			num5 = -((float)num2 - y);
			num5 /= num3;
			if (num5 + (float)num2 > (float)(num2 * 2))
			{
				num5 = 0.0f;
			}
		}
		if (y < (float)num2)
		{
			num5 = y - (float)num2;
			num5 /= num3;
			if (num5 + (float)num2 < 0.0f)
			{
				num5 = 0.0f;
			}
		}
	}
	

	mouse_event(1U, (int)num4, (int)num5, NULL, NULL);
}
void MoveMouse()
{
	float x = aimpos.x - (Width/2);
	float y = aimpos.y - (Height/2);

	x /= 10;
	y /= 10;
		INPUT input = { 0 };

		input.mi.dx = x * (x > -10 && x < 10 ? 0.1f : 0.5f);
		input.mi.dy = y * (y > -10 && y < 10 ? 0.1f : 0.5f);

		input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK;
		input.type = INPUT_MOUSE;

		SendInput(1, &input, sizeof INPUT);

}

void GetKey()
{
	if (GetAsyncKeyState(VK_F1) & 1)
		menu = !menu;
	if (GetAsyncKeyState(VK_F2) & 1)
		lines = !lines;
	if (GetAsyncKeyState(VK_F3) & 1)
		allitems = !allitems;
	if (GetAsyncKeyState(VK_F4) & 1)
		drawbox = !drawbox;
	if (GetAsyncKeyState(VK_F5) & 1)
		vichlesp = !vichlesp;
	if (GetAsyncKeyState(VK_F6) & 1)
		lboxshow = !lboxshow;
	if (GetAsyncKeyState(VK_F7) & 1)
		impitemrs = !impitemrs;
	if (GetAsyncKeyState(VK_F8) & 1)
		skullshow = !skullshow;
	if (GetAsyncKeyState(VK_F9) & 1)
		iconshow = !iconshow;
	if (GetAsyncKeyState(VK_F10) & 1)
		aimbot = !aimbot;
	if (GetAsyncKeyState(VK_INSERT) & 1)
		exit(0);
	//UpdateHW();
}
void skullpointsdraw(DWORD bodyAddv, DWORD boneAddv)
{
	float sightX = Width / 2, sightY = Height / 2;
	int distance;
	D3DMatrix viewMatrix = g_pEsp->vt;
	for (int i = 0; i < 70; i++)
	{
		Vector2 pelvis;
		Vector3 pelvisPos = GetBoneWorldPosition(bodyAddv, boneAddv + i * 48);
		WorldToScreenBone(viewMatrix, pelvisPos, pelvis, &distance);
		if (isnull(pelvis))
		{
			DrawString(std::to_string(i), pelvis.x, pelvis.y, 255, 255, 0, 0, mFont, true);
		}
	}
}
void skulldraw(DWORD bodyAddv,DWORD boneAddv,Vector3 screen)
{
	float sightX = Width / 2, sightY = Height / 2;

	Vector3 headPos = GetBoneWorldPosition(bodyAddv, boneAddv + 5 * 48);
	headPos.z += 7;
	Vector2 head;
	int distance;
	D3DMatrix viewMatrix = g_pEsp->vt;
	WorldToScreenBone(viewMatrix, headPos, head, &distance);
	Vector2 neck = head;
	Vector2 chest;
	Vector3 chestPos = GetBoneWorldPosition(bodyAddv, boneAddv + 4 * 48);
	WorldToScreenBone(viewMatrix, chestPos, chest, &distance);
	Vector2 pelvis;
	Vector3 pelvisPos = GetBoneWorldPosition(bodyAddv, boneAddv + 1 * 48);
	WorldToScreenBone(viewMatrix, pelvisPos, pelvis, &distance);
	Vector2 lSholder;
	Vector3 lSholderPos = GetBoneWorldPosition(bodyAddv, boneAddv + 13 * 48);
	WorldToScreenBone(viewMatrix, lSholderPos, lSholder, &distance);
	Vector2 rSholder;
	Vector3 rSholderPos = GetBoneWorldPosition(bodyAddv, boneAddv + 34 * 48);
	WorldToScreenBone(viewMatrix, rSholderPos, rSholder, &distance);
	Vector2 lElbow;
	Vector3 lElbowPos = GetBoneWorldPosition(bodyAddv, boneAddv + 14 * 48);
	WorldToScreenBone(viewMatrix, lElbowPos, lElbow, &distance);
	Vector2 rElbow;
	Vector3 rElbowPos = GetBoneWorldPosition(bodyAddv, boneAddv + 35 * 48);
	WorldToScreenBone(viewMatrix, rElbowPos, rElbow, &distance);
	Vector2 lWrist;
	Vector3 lWristPos = GetBoneWorldPosition(bodyAddv, boneAddv + 16 * 48);
	WorldToScreenBone(viewMatrix, lWristPos, lWrist, &distance);
	Vector2 rWrist;
	Vector3 rWristPos = GetBoneWorldPosition(bodyAddv, boneAddv + 37 * 48);
	WorldToScreenBone(viewMatrix, rWristPos, rWrist, &distance);
	Vector2 lThigh;
	Vector3 lThighPos = GetBoneWorldPosition(bodyAddv, boneAddv + 54 * 48);
	WorldToScreenBone(viewMatrix, lThighPos, lThigh, &distance);
	Vector2 rThigh;
	Vector3 rThighPos = GetBoneWorldPosition(bodyAddv, boneAddv + 58 * 48);
	WorldToScreenBone(viewMatrix, rThighPos, rThigh, &distance);
	Vector2 lKnee;
	Vector3 lKneePos = GetBoneWorldPosition(bodyAddv, boneAddv + 55 * 48);
	WorldToScreenBone(viewMatrix, lKneePos, lKnee, &distance);
	Vector2 rKnee;
	Vector3 rKneePos = GetBoneWorldPosition(bodyAddv, boneAddv + 59 * 48);
	WorldToScreenBone(viewMatrix, rKneePos, rKnee, &distance);
	Vector2 lAnkle;
	Vector3 lAnklePos = GetBoneWorldPosition(bodyAddv, boneAddv + 56 * 48);
	WorldToScreenBone(viewMatrix, lAnklePos, lAnkle, &distance);
	Vector2 rAnkle;
	Vector3 rAnklePos = GetBoneWorldPosition(bodyAddv, boneAddv + 60 * 48);
	WorldToScreenBone(viewMatrix, rAnklePos, rAnkle, &distance);

	if (isnull(head) && isnull(chest) && isnull(pelvis) && isnull(lSholder)
		&& isnull(rSholder) && isnull(lElbow) && isnull(rElbow) && isnull(lWrist)
		&& isnull(rWrist) && isnull(lThigh) && isnull(rThigh) && isnull(lKnee)
		&& isnull(rKnee) && isnull(lAnkle) && isnull(rAnkle))
	{
		//DrawBorderBox(head.x - screen.z / 16, head.y - screen.z / 16, screen.z / 8, screen.z / 8, 1, 255, 255, 255, 255);
		Circle(head.x, head.y, screen.z / 12, 20, D3DCOLOR_ARGB(255, 255, 255, 255));
		setvertix(neck, chest);
		setvertix(chest, pelvis);

		setvertix(chest, lSholder);
		setvertix(chest, rSholder);

		setvertix(lSholder, lElbow);
		setvertix(rSholder, rElbow);

		setvertix(lElbow, lWrist);
		setvertix(rElbow, rWrist);

		setvertix(pelvis, lThigh);
		setvertix(pelvis, rThigh);
		
		setvertix(lThigh, lKnee);
		setvertix(rThigh, rKnee);
		
		setvertix(lKnee, lAnkle);
		setvertix(rKnee, rAnkle);
		
	}
}
void aimbotload()
{
	while (true)
	{
		if (GetAsyncKeyState(0x1) && aimbot)
		{
			AimAtPos(aimpos.x, aimpos.y);
		}
		Sleep(67);
	}
}
int Render()
{
	try {
		char* value = tWindowName;
		p_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
		p_Device->BeginScene();

		DrawMenu();

		//g_pEsp->update(allitems, vichlesp, lboxshow, impitemrs);
		/*aimpos = AimFindBestTarget();
		if (aimpos.x != 0)
		{
			std::string Enr = "Aim : ";
			Enr.append(aimplayer);
			DrawString(Enr, 20, 20, 255, 255, 0, 0, mFont);
		}*/
		
		/*Start Drawing Stuff*/
		if (g_pEsp->playerdatar.size() != 0)
		{
			std::string Enr = "Enemy Near : ";
			Enr.append(std::to_string(g_pEsp->playerdatar.size()));
			DrawString(Enr, Width / 2 , 10, 255, 255, 0, 0, bFont,true);
			Vector3 screen;
			int distance;
			WorldToScreenPlayer(g_pEsp->playerdatar[0].Position, screen, &distance, g_pEsp->vt);
			if (!(screen.z < 0.001f))
			{
				aimpos.x = screen.x;
				aimpos.y = screen.y;
				DrawString(g_pEsp->playerdatar[0].Name, Width / 4, 20, 255, 255, 0, 0, bFont, true);
			}
		}
		for (int i = 0; i < g_pEsp->playerdatar.size(); i++)
		{
			Vector3 screen;
			int distance;
			WorldToScreenPlayer(g_pEsp->playerdatar[i].Position, screen, &distance, g_pEsp->vt);

			if (screen.z < 0.001f)
				continue;


			// Adjust Box
			if (g_pEsp->playerdatar[i].Pose == 1114636288)
			{
				screen.y = screen.y + screen.z / 5;
				screen.z -= screen.z / 5;
			}
			if (g_pEsp->playerdatar[i].Pose == 1112014848 || g_pEsp->playerdatar[i].Status == 7)
			{
				screen.y = screen.y + screen.z / 4;
				screen.z -= screen.z / 4;
			}

			std::string temp = "", temp2 = "";
			temp.append(std::to_string(g_pEsp->playerdatar[i].TeamID));
			temp.append(" : ");
			if (g_pEsp->playerdatar[i].IsRobot)
			{
				temp.append("[B] ");
				if (lines)
				{
					DrawLine(Width / 2, 0, screen.x, screen.y - 5, 255, 0, 204, 255);
				}
			}
			else
			{
				temp.append("[P] ");
				if (lines)
				{
					DrawLine(Width / 2, 0, screen.x, screen.y - 5, 255, 255, 255, 0);
				}
			}
			temp.append(g_pEsp->playerdatar[i].Name);
			//DrawBoxText(temp, screen.x, screen.y - 30, 255, 255, 0, 0, pFont, true);
			DrawStringBoderd(temp, screen.x , screen.y - 30, 255, 255, 0, 0, pFont,true);
			temp = std::to_string(distance);
			temp.append(" M");
			DrawString(temp, screen.x, screen.y - 18, 255, 255, 255, 255, mFont,true);

			temp = g_pEsp->playerdatar[i].playerW1.displayName;
			temp2 = g_pEsp->playerdatar[i].playerW2.displayName;
			if (g_pEsp->playerdatar[i].playerW1.itmid > 0)
				DrawString(temp.append(" ").append(std::to_string(g_pEsp->playerdatar[i].playerW1.ammoCur)), screen.x + (screen.z / 2), screen.y + 5, 255, 0, 255, 255, mFont);
			if (g_pEsp->playerdatar[i].playerW2.itmid > 0)
				DrawString(temp2.append(" ").append(std::to_string(g_pEsp->playerdatar[i].playerW2.ammoCur)), screen.x + (screen.z / 2), screen.y + 20, 255, 0, 255, 255, mFont);
			if (drawbox)
			{
				DrawBorderBox(screen.x - screen.z / 4 - 3, screen.y - 5, (screen.z / 2) + 3, screen.z + 5, 1, 255, 255, 0, 0);
				DrawPlayerBlood(screen.x - screen.z / 4 - 6, screen.y - 5, screen.z + 5, (screen.z / 20) - 3, g_pEsp->playerdatar[i].Health);
				DrawPlayerBlood(screen.x - screen.z / 4 - 9, screen.y - 5, screen.z + 5, (screen.z / 20) - 3, g_pEsp->playerdatar[i].energy);
			}
			if (skullshow)
			{
				DWORD tmpAddv = g_pMemoryManager->iRead(g_pEsp->playerdatar[i].Address + 776);//Mem.ReadMemory<int>(player.Address + tmpOffset);
				DWORD bodyAddv = tmpAddv + 320;
				DWORD boneAddv = g_pMemoryManager->iRead(tmpAddv + 1408) + 48;//Mem.ReadMemory<int>(tmpAddv + boneOffset) + 48;

				//skullpointsdraw(bodyAddv, boneAddv);
				skulldraw(bodyAddv, boneAddv, screen);
			}

		}
		for (int m = 0; m < g_pEsp->boomalertr.size(); m++)
		{
			Vector3 screen;
			int distance;
			WorldToScreen(g_pEsp->boomalertr[m].Position, screen, &distance, g_pEsp->vt);
			if (screen.z < 0.001f)
				continue;
			std::string alertb = g_pEsp->boomalertr[m].displayName;
			DrawStringBoderd(alertb, screen.x, screen.y, 255, 255, 0, 0, pFont, true);
		}
		p_Device->EndScene();
		if (lboxshow)
		{
			for (int i = 0; i < g_pEsp->lootboxr.size(); i++)
			{
				Vector3 screen;
				int distance;
				WorldToScreen(g_pEsp->lootboxr[i].Position, screen, &distance, g_pEsp->vt);

				if (screen.z < 0.001f || distance < 2)
					continue;
				std::string text = ("[ lootbox ]");
				DrawStringBoderd(text, screen.x, screen.y, 255, 255, 165, 0, pFont, true);
				DrawString(std::to_string(distance).append(" M"), screen.x, screen.y + 17, 255, 0, 0, 255, mFont);
				for (int k = 0; k < g_pEsp->lootboxr[i].boxitem.size(); k++)
				{
					DrawString(g_pEsp->lootboxr[i].boxitem[k].Displayname, screen.x, screen.y - (k * 10 + 12), 255, 255, 77, 77, pFont, true);
				}
			}
		}
		if (vichlesp)
		{
			for (int i = 0; i < g_pEsp->vehicledatar.size(); i++)
			{
				Vector3 screen;
				int distance;

				WorldToScreen(g_pEsp->vehicledatar[i].Position, screen, &distance, g_pEsp->vt);

				if (screen.z < 0.001f || distance < 10)
					continue;

				if (g_pEsp->vehicledatar[i].picid == -1 || iconshow)
				{
					std::string text = g_pEsp->vehicledatar[i].displayName;
					DrawStringBoderd(text, screen.x, screen.y, 155, 0, 127, 8, pFont, true);
				}
				else
				{
					DrawSprite(screen, g_pEsp->vehicledatar[i].picid);
				}
				std::string text = std::to_string(distance).append(" M").c_str();
				DrawString(text, screen.x, screen.y + 17, 255, 0, 0, 255, mFont);
			}
		}
		if (impitemrs)
		{
			for (int i = 0; i < g_pEsp->impitemr.size(); i++)
			{
				Vector3 screen;
				int distance;

				WorldToScreen(g_pEsp->impitemr[i].Position, screen, &distance, g_pEsp->vt);

				if (screen.z < 0.001f || distance < 2)
					continue;
				if (g_pEsp->impitemr[i].picid == -1 || iconshow)
					DrawStringBoderd(g_pEsp->impitemr[i].displayName, screen.x, screen.y, 255, 255, 0, 255, pFont, true);
				else
					DrawSprite(screen, g_pEsp->impitemr[i].picid);
			}
		}
		if (allitems)
		{
			for (int i = 0; i < g_pEsp->itemdatar.size(); i++)
			{
				Vector3 screen;
				int distance;

				WorldToScreen(g_pEsp->itemdatar[i].Position, screen, &distance, g_pEsp->vt);

				if (screen.z < 0.001f || distance < 2)
					continue;
				if (g_pEsp->itemdatar[i].picid == -1 || iconshow)
					DrawString(g_pEsp->itemdatar[i].displayName, screen.x, screen.y, 155, 0, 255, 0, pFont, true);
				else
					DrawSprite(screen, g_pEsp->itemdatar[i].picid);
			}
		}
		/*End Drawing Stuff*/
		p_Device->EndScene();
		p_Device->PresentEx(0, 0, 0, 0, 0);
	}
	catch (const std::out_of_range& oor)
	{
		std::cout << termcolor::red << oor.what()<<"\n";
		//gotexception
	}
	return 0;
}