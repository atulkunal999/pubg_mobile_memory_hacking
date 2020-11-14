#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx9.h>
#include <imgui/imgui_impl_win32.h>
#include <render/Device3D9.hpp>
#include <render/Surface3D9.hpp>
#include "../hacks/pch.h"
using namespace render;

//bool show_demo_window = true;
//bool show_another_window = false;
//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

int windowstate = 0;
bool enabled = false;
bool menu = true, norecoil = false, lines = true, allitems = false, drawbox = true, vichlesp = true, lboxshow = true, impitemrs = true, skullshow = true;
bool iconshow = true,draw = true,genkeybool = true,radar = true;
char* mykey = new char[256];
char* genkey = new char[256];
/**/
std::vector<playerData> playerdatar;
std::vector<Item> itemdatar;
std::vector<Vehicle> vehicledatar;
std::vector<Lootbox> lootboxr;
std::vector<Item> boomalertr;
std::vector<Item> impitemr;
/**/
bool gen_random(char* s, const int len) {
	srand(time(NULL));
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len] = 0;
	return false;
}
void CustomImGUIStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowPadding = ImVec2(14, 14);
	style.FramePadding = ImVec2(8, 8);
	style.ItemSpacing = ImVec2(8, 8);
	style.ItemInnerSpacing = ImVec2(8, 8);

	ImVec4* colors = style.Colors;
	colors[ImGuiCol_FrameBg] = ImVec4(0.48f, 0.16f, 0.16f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.98f, 0.26f, 0.26f, 0.67f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.98f, 0.39f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.88f, 0.41f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.47f, 0.98f, 0.26f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.98f, 0.61f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.98f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.98f, 0.26f, 0.26f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.75f, 0.10f, 0.10f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.75f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.98f, 0.26f, 0.26f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.98f, 0.26f, 0.26f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.58f, 0.18f, 0.18f, 0.86f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.68f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.07f, 0.07f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.42f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.98f, 0.26f, 0.26f, 0.35f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
}

void Device3D9::DrawTriangle(Vector2 a, Vector2 b, Vector2 c, drawing::Color col)
{
	
}

void ChangeClickability(bool canclick, HWND ownd)
{
	long style = GetWindowLong(
		ownd, GWL_EXSTYLE);
	if (canclick) {
		style &= ~WS_EX_LAYERED;
		SetWindowLong(ownd,
			GWL_EXSTYLE, style);
		SetForegroundWindow(ownd);
		windowstate = 1;
	}
	else {
		style |= WS_EX_LAYERED;
		SetWindowLong(ownd,
			GWL_EXSTYLE, style);
		windowstate = 0;
	}
}

Device3D9::~Device3D9()
{
    /// Call to a virtual function inside a destructor will be statically resolved
    DTOR_EXECUTE_VIRTUAL( shutdown );
}

bool Device3D9::create( const std::string& target_window_title )
{
    if( !Overlay::create( target_window_title ) ) {
        return false;
    }
    if( FAILED( Direct3DCreate9Ex( D3D_SDK_VERSION, &m_Direct3D9Ex ) ) ) {
        return false;
    }
    
    D3DPRESENT_PARAMETERS params;
    ZeroMemory( &params, sizeof( D3DPRESENT_PARAMETERS ) );

    params.Windowed               = TRUE;
    params.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    params.BackBufferFormat       = D3DFMT_A8R8G8B8;
    params.EnableAutoDepthStencil = TRUE;
    params.AutoDepthStencilFormat = D3DFMT_D16;
    params.MultiSampleType        = D3DMULTISAMPLE_NONE;
    params.PresentationInterval   = 0x80000000L;

    DWORD mulit_sample_quality = 0;
    if( SUCCEEDED( this->m_Direct3D9Ex->CheckDeviceMultiSampleType(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        D3DFMT_A8R8G8B8,
        true,
        D3DMULTISAMPLE_NONMASKABLE,
        &mulit_sample_quality ) ) ) {
        params.MultiSampleType    = D3DMULTISAMPLE_NONMASKABLE;
        params.MultiSampleQuality = mulit_sample_quality - 1;
    }
    if( FAILED( m_Direct3D9Ex->CreateDeviceEx(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        m_WndOverlay,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &params,
        nullptr,
        &m_Direct3D9Device ) ) ) {
        return false;
    }

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	CustomImGUIStyle();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(m_WndOverlay);
	ImGui_ImplDX9_Init(m_Direct3D9Device);

    if( FAILED( D3DXCreateSprite( m_Direct3D9Device, &m_Direct3DXSprite ) ) ) {
        return false;
    }

    m_Surface = std::make_unique<Surface3D9>( m_Direct3DXSprite );
    return m_Surface->initialize( m_Direct3D9Device );
}
void Device3D9::DrawPlayerBlood(float x, float y, float h, float w, float fBlood, int max)
{
	if (fBlood > 70.0)
	{
		//DrawBorderBox(x, y, w, h, 1, 255, 0, 255, 0);
		m_Surface->rect(x, y, w * fBlood / max, h , drawing::Color::Color(0,255,0));
	}
	if (fBlood > 30.0 && fBlood <= 70.0)
	{
		//DrawBorderBox(x, y, w, h, 1, 255, 0, 255, 0);
		m_Surface->rect(x, y, w * fBlood / max, h , drawing::Color::Color(255, 255, 0));
	}
	if (fBlood > 0.0 && fBlood <= 30.0)
	{
		//DrawBorderBox(x, y, w, h, 1, 255, 0, 255, 0);
		m_Surface->rect(x, y, w * fBlood / max, h , drawing::Color::Color(255, 0, 0));
	}
}

bool Device3D9::render()
{
	if (genkeybool)
	{
		gen_random(genkey, 64);
		genkeybool = false;
	}
    /// handle window messages
    if( !Overlay::render() ) {
        return false;
    }

    if( FAILED( m_Direct3D9Device->Clear(
        0,
        nullptr,
        D3DCLEAR_TARGET,
        0x00000000,
        1.f,
        0 )
    ) ) {
        return false;        
    }

	playerdatar = g_pEsp->playerdatar;
	itemdatar = g_pEsp->itemdatar;
	vehicledatar = g_pEsp->vehicledatar;
	lootboxr = g_pEsp->lootboxr;
	boomalertr = g_pEsp->boomalertr;
	impitemr = g_pEsp->impitemr;
	g_pAimbot->g_Height = m_Height;
	g_pAimbot->g_Width = m_Width;
	AimFindBestTarget(g_pEsp->playerdatar);
    /// start the surface scene only when the target window
    /// is in foreground
    if( true)//in_foreground()) 
	{
		if (GetAsyncKeyState(VK_INSERT) & 1) enabled = !enabled;
		if (GetAsyncKeyState(VK_END) & 1) ExitProcess(EXIT_SUCCESS);

		if (enabled)
		{
			// Start the Dear ImGui frame
			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			if (windowstate != 1) //You might need to remove this check and call it every time to get keyboard input working. Mouse input works anyway.
			{
				ChangeClickability(true, m_WndOverlay);
			}

			ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
			if (ImGui::Begin("RIXOT VIP", &enabled, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse))
			{
				if (ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_None))
				{
					if (!draw)
					{
						if (ImGui::BeginTabItem("KEY"))
						{
							ImGui::InputText("Enter Your Key", mykey, 256);
							if (ImGui::Button("Get Key"))
							{
								std::string temp = "start \"\" \"https://shrinkearn.com/st?api=9e7699d679c6140314c6f4cd195fe708a26f4df6&url=http://urlecho.appspot.com/echo?body=";
								temp.append(genkey).append("\"");
								system(temp.c_str());
							}
							ImGui::SameLine();
							if (ImGui::Button("Check Key"))
							{
								if (strcmp(mykey, genkey) == 0)
								{
									draw = true;
								}
							}
							ImGui::EndTabItem();
						}
					}
					else
					{
						if (ImGui::BeginTabItem("ESP"))
						{
							ImGui::Checkbox("SHOW LINES", &lines);
							ImGui::Checkbox("ALL ITEMS", &allitems);
							ImGui::Checkbox("PLAYER BOX", &drawbox);
							ImGui::Checkbox("VEHICLE ESP", &vichlesp);
							ImGui::Checkbox("LOOTBOX", &lboxshow);
							ImGui::Checkbox("IMPORTANT ITEMS", &impitemrs);
							ImGui::Checkbox("SKELETON", &skullshow);
							ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

							ImGui::EndTabItem();
						}
						if (ImGui::BeginTabItem("AIM"))
						{
							ImGui::Checkbox("AIMBOT", &g_pAimbot->aimbot);
							ImGui::SameLine();
							ImGui::Checkbox("AIM HEAD", &g_pAimbot->aimtype);
							ImGui::SliderFloat("AIMBOT SMOOTH", &g_pAimbot->smooth, 10.0f, 100.0f);
							ImGui::SliderFloat("AIMBOT SLEEP", &g_pAimbot->aimsleep, 10.0f, 100.0f);
							ImGui::InputInt("Aim Key Code", &g_pAimbot->aimkey);
							ImGui::EndTabItem();
						}
						if (ImGui::BeginTabItem("MEMORY"))
						{
							ImGui::Checkbox("BOOST ENABLED", &g_pAimbot->boostenabled);
							ImGui::SliderFloat("BOSST SPEED", &g_pAimbot->boostval, 1.0f, 5.0f);
							ImGui::InputInt("BOOST KEY CODE", &g_pAimbot->boostkey);
							ImGui::Text("You Need To Help Me in This\nIf you Are devloper you can\nsend me a offets for making this hack owsome.");
							ImGui::SliderFloat("IPad View", &g_pAimbot->ipadview, 170.0f, 600.0f);
							ImGui::EndTabItem();
						}
						if (ImGui::BeginTabItem("ABOUT"))
						{
							ImGui::TextColored({ 255,0,0,255 }, "INDIAN HACKER X");
							ImGui::Text("\tHello Everyone, I Devloped This Hack For Learn Only. \nI Want To Learn Some Good Game Hacking so I Decided To \nStart Hacking in 2018.");
							ImGui::TextColored({ 0,0,255,255 }, "[ This Hack is Free Not For Sell ]");
							ImGui::TextColored({ 0,175,255,255 }, "---SOCIAL LINKS---");
							ImGui::TextColored({ 0,255,0,255 }, "INSTAGRAM : ");
							ImGui::SameLine();
							ImGui::Text("https://www.instagram.com/indian_hacker_x");
							ImGui::TextColored({ 0,255,0,255 }, "YOUTUBE : ");
							ImGui::SameLine();
							ImGui::Text("http://bit.ly/INDHXYT");
							ImGui::TextColored({ 0,255,0,255 }, "DISCORD : ");
							ImGui::SameLine();
							ImGui::Text("https://discord.gg/yTBhvX5");

							ImGui::EndTabItem();
						}
					}
					ImGui::EndTabBar();
				}
			}
			// Rendering
			ImGui::EndFrame();
		}
		else
		{
			if (windowstate != 0)
			{
				ChangeClickability(false, m_WndOverlay);
			}
		}

        /// if the surface has successfully started a new scene
        if( m_Surface->begin_scene() ) {
            ///-------------------------------------------------------------------------------------------------
            /// begin the rendering here
            ///-------------------------------------------------------------------------------------------------
			
			if (enabled)
			{
				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			}
			
			if(draw)
			{
				if (playerdatar.size() != 0)
				{
					char str[80];
					sprintf(str, "Enemy Near : %d", playerdatar.size());
					
					m_Surface->text(m_Width/2, 10, "18", 0xFFFF0000, str);
				}
				for (int i = 0; i < playerdatar.size(); i++)
				{
					Vector3 screen;
					int distance;
					WorldToScreenPlayer(playerdatar[i].Position, screen, &distance, g_pEsp->vt);

					if (screen.z < 0.001f)
						continue;


					// Adjust Box
					if (playerdatar[i].Pose == 1114636288)
					{
						screen.y = screen.y + screen.z / 5;
						screen.z -= screen.z / 5;
					}
					if (playerdatar[i].Pose == 1112014848 || playerdatar[i].Status == 7)
					{
						screen.y = screen.y + screen.z / 4;
						screen.z -= screen.z / 4;
					}

					std::string temp = "", temp2 = "";
					m_Surface->rect(screen.x - 69, screen.y - 39, 20, 14, drawing::Color::Color(255, 0, 0));
					if (playerdatar[i].IsRobot)
					{
						m_Surface->text(screen.x - 60, screen.y - 40, "18", drawing::Color::Color(0,0,255), "B");
						if (lines)
						{
							m_Surface->line(m_Width / 2, 0, screen.x, screen.y - 5, drawing::Color::Color(0, 204, 255));
						}
					}
					else
					{
						m_Surface->text(screen.x - 60, screen.y - 40, "18", drawing::Color::Color(255, 255, 255), "P");
						if (lines)
						{
							m_Surface->line(m_Width / 2, 0, screen.x, screen.y - 5, drawing::Color::Color(255, 255, 0));
						}
					}
					m_Surface->border_box(screen.x - 70, screen.y - 40, 140, 15, 1, drawing::Color::Color(0, 0, 0));
					
					m_Surface->text(screen.x, screen.y - 39, "14", 0xFFFF0000, playerdatar[i].Name);
					temp = std::to_string(distance );
					temp.append(" M");
					m_Surface->text(screen.x + 55, screen.y - 39, "14", 0xFFFFFFFF, temp);
					DrawPlayerBlood(screen.x - 70, screen.y - 20, 2, 140, playerdatar[i].Health, 100);
					DrawPlayerBlood(screen.x - 70, screen.y - 17, 2, 140, playerdatar[i].energy, 100);


					temp = playerdatar[i].playerW1.displayName;
					temp2 = playerdatar[i].playerW2.displayName;
					if (playerdatar[i].playerW1.itmid > 0)
						m_Surface->text(screen.x + (screen.z / 2), screen.y + 5, "14", 0xFFFF0000, temp.append(" ").append(std::to_string(playerdatar[i].playerW1.ammoCur)));
					if (playerdatar[i].playerW2.itmid > 0)
						m_Surface->text(screen.x + (screen.z / 2), screen.y + 20, "14", 0xFFFF0000, temp2.append(" ").append(std::to_string(playerdatar[i].playerW2.ammoCur)));
					if (radar)
					{
						//Work In Progress
					}
					if (drawbox)
					{
						m_Surface->border_box(screen.x - screen.z / 4 - 3, screen.y - 5, (screen.z / 2) + 3, screen.z + 5, 1,drawing::Color::Color(255,0,0));
					}
					if (skullshow)
					{
						DWORD tmpAddv = g_pMemoryManager->iRead(playerdatar[i].Address + 776);//Mem.ReadMemory<int>(player.Address + tmpOffset);
						DWORD bodyAddv = tmpAddv + 320;
						DWORD boneAddv = g_pMemoryManager->iRead(tmpAddv + 1408) + 48;//Mem.ReadMemory<int>(tmpAddv + boneOffset) + 48;

						/*for (int i = 0; i < 100; i++)
						{
							float sightX = m_Width / 2, sightY = m_Height / 2;

							Vector3 Pos = GetBoneWorldPosition(bodyAddv, boneAddv + i * 48);
							Vector2 posx;
							int distance;
							D3DMatrix viewMatrix = g_pEsp->vt;
							WorldToScreenBone(viewMatrix, Pos, posx, &distance);
							m_Surface->text(posx.x, posx.y, "14", drawing::Color::Color(255, 0, 0), std::to_string(i));
						}*/
						//if(false)
						{
							float sightX = m_Width / 2, sightY = m_Height / 2;

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
							Vector3 lSholderPos = GetBoneWorldPosition(bodyAddv, boneAddv + 11 * 48);
							WorldToScreenBone(viewMatrix, lSholderPos, lSholder, &distance);
							Vector2 rSholder;
							Vector3 rSholderPos = GetBoneWorldPosition(bodyAddv, boneAddv + 32 * 48);
							WorldToScreenBone(viewMatrix, rSholderPos, rSholder, &distance);
							Vector2 lElbow;
							Vector3 lElbowPos = GetBoneWorldPosition(bodyAddv, boneAddv + 12 * 48);
							WorldToScreenBone(viewMatrix, lElbowPos, lElbow, &distance);
							Vector2 rElbow;
							Vector3 rElbowPos = GetBoneWorldPosition(bodyAddv, boneAddv + 33 * 48);
							WorldToScreenBone(viewMatrix, rElbowPos, rElbow, &distance);
							Vector2 lWrist;
							Vector3 lWristPos = GetBoneWorldPosition(bodyAddv, boneAddv + 15 * 48);
							WorldToScreenBone(viewMatrix, lWristPos, lWrist, &distance);
							Vector2 rWrist;
							Vector3 rWristPos = GetBoneWorldPosition(bodyAddv, boneAddv + 36 * 48);
							WorldToScreenBone(viewMatrix, rWristPos, rWrist, &distance);
							Vector2 lThigh;
							Vector3 lThighPos = GetBoneWorldPosition(bodyAddv, boneAddv + 52 * 48);
							WorldToScreenBone(viewMatrix, lThighPos, lThigh, &distance);
							Vector2 rThigh;
							Vector3 rThighPos = GetBoneWorldPosition(bodyAddv, boneAddv + 56 * 48);
							WorldToScreenBone(viewMatrix, rThighPos, rThigh, &distance);
							Vector2 lKnee;
							Vector3 lKneePos = GetBoneWorldPosition(bodyAddv, boneAddv + 53 * 48);
							WorldToScreenBone(viewMatrix, lKneePos, lKnee, &distance);
							Vector2 rKnee;
							Vector3 rKneePos = GetBoneWorldPosition(bodyAddv, boneAddv + 57 * 48);
							WorldToScreenBone(viewMatrix, rKneePos, rKnee, &distance);
							Vector2 lAnkle;
							Vector3 lAnklePos = GetBoneWorldPosition(bodyAddv, boneAddv + 54 * 48);
							WorldToScreenBone(viewMatrix, lAnklePos, lAnkle, &distance);
							Vector2 rAnkle;
							Vector3 rAnklePos = GetBoneWorldPosition(bodyAddv, boneAddv + 58 * 48);
							WorldToScreenBone(viewMatrix, rAnklePos, rAnkle, &distance);

							if (isnull(head) && isnull(chest) && isnull(pelvis) && isnull(lSholder)
								&& isnull(rSholder) && isnull(lElbow) && isnull(rElbow) && isnull(lWrist)
								&& isnull(rWrist) && isnull(lThigh) && isnull(rThigh) && isnull(lKnee)
								&& isnull(rKnee) && isnull(lAnkle) && isnull(rAnkle))
							{
								//DrawBorderBox(head.x - screen.z / 16, head.y - screen.z / 16, screen.z / 8, screen.z / 8, 1, 255, 255, 255, 255);
								//Circle(head.x, head.y, screen.z / 12, 20, D3DCOLOR_ARGB(255, 255, 255, 255));
								m_Surface->line(neck.x, neck.y, chest.x, chest.y, drawing::Color::Color(255, 255, 0));
								m_Surface->line(chest.x, chest.y, pelvis.x, pelvis.y, drawing::Color::Color(255, 255, 0));
								
								m_Surface->line(chest.x, chest.y, lSholder.x, lSholder.y, drawing::Color::Color(255, 255, 0));
								m_Surface->line(chest.x, chest.y, rSholder.x, rSholder.y, drawing::Color::Color(255, 255, 0));

								m_Surface->line(lSholder.x, lSholder.y, lElbow.x, lElbow.y, drawing::Color::Color(255, 255, 0));
								m_Surface->line(rSholder.x, rSholder.y, rElbow.x, rElbow.y, drawing::Color::Color(255, 255, 0));

								m_Surface->line(lElbow.x, lElbow.y, lWrist.x, lWrist.y, drawing::Color::Color(255, 255, 0));
								m_Surface->line(rElbow.x, rElbow.y, rWrist.x, rWrist.y, drawing::Color::Color(255, 255, 0));

								m_Surface->line(pelvis.x, pelvis.y, lThigh.x, lThigh.y, drawing::Color::Color(255, 255, 0));
								m_Surface->line(pelvis.x, pelvis.y, rThigh.x, rThigh.y, drawing::Color::Color(255, 255, 0));

								m_Surface->line(lThigh.x, lThigh.y, lKnee.x, lKnee.y, drawing::Color::Color(255, 255, 0));
								m_Surface->line(rThigh.x, rThigh.y, rKnee.x, rKnee.y, drawing::Color::Color(255, 255, 0));

								m_Surface->line(lKnee.x, lKnee.y, lAnkle.x, lAnkle.y, drawing::Color::Color(255, 255, 0));
								m_Surface->line(rKnee.x, rKnee.y, rAnkle.x, rAnkle.y, drawing::Color::Color(255, 255, 0));
								
							}
						}
					}

				}
				for (int m = 0; m < boomalertr.size(); m++)
				{
					Vector3 screen;
					int distance;
					WorldToScreen(boomalertr[m].Position, screen, &distance, g_pEsp->vt);
					if (screen.z < 0.001f)
						continue;
					std::string alertb = boomalertr[m].displayName;
					m_Surface->text(screen.x, screen.y, "14", 0xFFFF0000, alertb);
				}
				if (lboxshow)
				{
					for (int i = 0; i < lootboxr.size(); i++)
					{
						Vector3 screen;
						int distance;
						WorldToScreen(lootboxr[i].Position, screen, &distance, g_pEsp->vt);

						if (screen.z < 0.001f || distance < 2)
							continue;
						std::string text = ("[ lootbox ]");
						m_Surface->text(screen.x, screen.y, "14", 0xFF00FF0F, text);
						m_Surface->text(screen.x, screen.y, "12", 0xFF00FF0F, std::to_string(distance).append(" M"));
						for (int k = 0; k < lootboxr[i].boxitem.size(); k++)
						{
							m_Surface->text(screen.x, screen.y - (k * 10 + 12), "12", 0xFFE67E22, lootboxr[i].boxitem[k].Displayname);
						}
					}
				}
				if (vichlesp)
				{
					for (int i = 0; i < vehicledatar.size(); i++)
					{
						Vector3 screen;
						int distance;

						WorldToScreen(vehicledatar[i].Position, screen, &distance, g_pEsp->vt);

						if (screen.z < 0.001f || distance < 10)
							continue;

						if (vehicledatar[i].picid == -1 || iconshow)
						{
							std::string text = vehicledatar[i].displayName;
							m_Surface->text(screen.x, screen.y, "14", 0xFF00BDFF, text);
						}
						else
						{
							//DrawSprite(screen, vehicledatar[i].picid);
						}
						std::string text = std::to_string(distance).append(" M").c_str();
						m_Surface->text(screen.x, screen.y + 17, "12", 0xFFFF0000, text);
					}
				}
				if (impitemrs)
				{
					for (int i = 0; i < impitemr.size(); i++)
					{
						Vector3 screen;
						int distance;

						WorldToScreen(impitemr[i].Position, screen, &distance, g_pEsp->vt);

						if (screen.z < 0.001f || distance < 2)
							continue;
						if (impitemr[i].picid == -1 || iconshow)
							m_Surface->text(screen.x, screen.y, "14", 0xFFFF6800, impitemr[i].displayName);
						else
						{
							//DrawSprite(screen, impitemr[i].picid);
						}
					}
				}
				if (allitems)
				{
					for (int i = 0; i < itemdatar.size(); i++)
					{
						Vector3 screen;
						int distance;

						WorldToScreen(itemdatar[i].Position, screen, &distance, g_pEsp->vt);

						if (screen.z < 0.001f || distance < 2)
							continue;
						if (itemdatar[i].picid == -1 || iconshow)
							m_Surface->text(screen.x, screen.y, "14", 0xFF00FF0F, itemdatar[i].displayName);
						else
						{
							//DrawSprite(screen, itemdatar[i].picid);
						}
					}
				}
			}
            execute_callbacks();
            ///-------------------------------------------------------------------------------------------------
            /// stop the rendering here
            ///-------------------------------------------------------------------------------------------------
            m_Surface->end_scene();
        }
		
    }

    m_Direct3D9Device->EndScene();
    m_Direct3D9Device->PresentEx(
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0
    );

    return true;
}

void Device3D9::shutdown()
{
    Overlay::shutdown();
    safe_release( &m_Direct3D9Ex );
    safe_release( &m_Direct3D9Device );
    safe_release( &m_Direct3DXSprite );

    if( m_Surface ) {
        m_Surface->shutdown();
    }
}