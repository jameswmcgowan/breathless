#pragma once
#include "Configuration.hpp"
#include "dropboxes.h"
#include "Variables.h"
#include "Themes.h"
#include <cctype>
#include "Logging.h"
#include "Listener.h"



#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#define BUILDSTAMP ( __DATE__ )
typedef void(*CL_FullUpdate_t) (void);
CL_FullUpdate_t CL_FullUpdate = nullptr;


void FullUpdate()
{
	static auto CL_FullUpdate = reinterpret_cast<CL_FullUpdate_t>(U::FindPattern("engine.dll", reinterpret_cast<PBYTE>("\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x56\xFF\x50\x14\x8B\x34\x85"), "x????x????xxxxxxx"));
	CL_FullUpdate();
}

//--------------------------------------------
//Weapon CFG stuff	

const char* weaponnames(int id)
{
	switch (id)
	{
	case 1:
		return "deagle";
	case 2:
		return "elite";
	case 3:
		return "fiveseven";
	case 4:
		return "glock";
	case 7:
		return "ak47";
	case 8:
		return "aug";
	case 9:
		return "awp";
	case 10:
		return "famas";
	case 11:
		return "g3sg1";
	case 13:
		return "galilar";
	case 14:
		return "m249";
	case 60:
		return "m4a1_silencer";
	case 16:
		return "m4a1";
	case 17:
		return "mac10";
	case 19:
		return "p90";
	case 24:
		return "ump45";
	case 25:
		return "xm1014";
	case 26:
		return "bizon";
	case 27:
		return "mag7";
	case 28:
		return "negev";
	case 29:
		return "sawedoff";
	case 30:
		return "tec9";
	case 32:
		return "hkp2000";
	case 33:
		return "mp7";
	case 34:
		return "mp9";
	case 35:
		return "nova";
	case 36:
		return "p250";
	case 38:
		return "scar20";
	case 39:
		return "sg556";
	case 40:
		return "ssg08";
	case 61:
		return "usp_silencer";
	case 63:
		return "cz75a";
	case 64:
		return "revolver";
	case 508:
		return "knife_m9_bayonet";
	case 500:
		return "bayonet";
	case 505:
		return "knife_flip";
	case 506:
		return "knife_gut";
	case 507:
		return "knife_karambit";
	case 509:
		return "knife_tactical";
	case 512:
		return "knife_falchion";
	case 514:
		return "knife_survival_bowie";
	case 515:
		return "knife_butterfly";
	case 516:
		return "knife_push";

	default:
		return "";
	}
}

bool IsUtility(ItemDefinitionIndexx index)
{
	switch (index)
	{
	case ItemDefinitionIndexx::ITEM_NONE:
	case ItemDefinitionIndexx::WEAPON_C4:
	case ItemDefinitionIndexx::WEAPON_FLASH:
	case ItemDefinitionIndexx::WEAPON_HE:
	case ItemDefinitionIndexx::WEAPON_INC:
	case ItemDefinitionIndexx::WEAPON_MOLOTOV:
	case ItemDefinitionIndexx::WEAPON_SMOKE:
	case ItemDefinitionIndexx::WEAPON_DECOY:
	case ItemDefinitionIndexx::WEAPON_KNIFE_T:
	case ItemDefinitionIndexx::WEAPON_KNIFE_CT:
	case ItemDefinitionIndexx::GLOVE_T_SIDE:
	case ItemDefinitionIndexx::GLOVE_CT_SIDE:
	case ItemDefinitionIndexx::GLOVE_SPORTY:
	case ItemDefinitionIndexx::GLOVE_SLICK:
	case ItemDefinitionIndexx::GLOVE_LEATHER_WRAP:
	case ItemDefinitionIndexx::GLOVE_STUDDED_BLOODHOUND:
	case ItemDefinitionIndexx::GLOVE_MOTORCYCLE:
	case ItemDefinitionIndexx::GLOVE_SPECIALIST:
		return true;
	default:
		return false;
	}
}

bool Contains(const std::string &word, const std::string &sentence) {
	if (word == "" || sentence == "")
		return true;

	return sentence.find(word) != std::string::npos;
}

std::string ToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), (int(*)(int))std::tolower);

	return str;
}
//--------------------------------------------
bool defaultk;
bool bayonet;
bool flip;
bool gut;
bool karambit;
bool m9bayonet;
bool huntsman;
bool falchion;
bool bowie;
bool butterfly;
bool daggers;

void doknives(bool* disknife)
{
	defaultk = false;
	bayonet = false;
	flip = false;
	gut = false;
	karambit = false;
	m9bayonet = false;
	huntsman = false;
	falchion = false;
	bowie = false;
	butterfly = false;
	daggers = false;

	*disknife = true;
}

const char* HitmarkSound[] =
{
	"Disabled",
	"Default",
	"Roblox",
	"Trump",
	"Metallic"
};

const char* AngleStyles[] =
{
	"Disabled",
	"Ground",
	"Crosshair"
};


void RenderInterface() {


	auto& style = ImGui::GetStyle();
	bool is_renderer_active = renderer->IsActive();
	if (is_renderer_active)
	{
		g_Options.Menu.bShowTabs = true;
		if (style.Alpha < 1.f)
			style.Alpha += 0.01f;
	}
	if (!is_renderer_active)
	{

		if (style.Alpha > 0.f)
			style.Alpha -= 0.01f;
		g_Options.Menu.bShowTabs = false;
	}

	if (is_renderer_active)
	{

		if (Globals::error)
		{
			ImGui::SetNextWindowPosCenter(ImGuiSetCond_Appearing);
			ImGui::SetNextWindowSize(ImVec2(200, 50));
			if (ImGui::Begin(XorStr("Warning!"), &g_Options.Menu.Opened, ImVec2(400, 200), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
			{
				ImGui::Text(XorStr("Please dont enable both Builder and Pre-set AAs!"));
				if (ImGui::Button(XorStr("OK!")))
				{
					g_Options.Ragebot.PreAAs = false;
					g_Options.Ragebot.BuilderAAs = false;
					Globals::error = false;
				}
			}ImGui::End();
		}

		if (ImGui::Begin("##chet", &is_renderer_active, ImVec2(750, 608), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
		{
			static float r = 1.0f;
			static float g = 0.f;
			static float b = 0.f;

			if (r == 1.f && g >= 0.f && b <= 0.f)
			{
				g += 0.005f;
				b = 0.f;
			}
			if (r <= 1.f && g >= 1.f && b == 0.f)
			{
				g = 1.f;
				r -= 0.005f;
			}
			if (r <= 0.f && g == 1.f && b >= 0.f)
			{
				r = 0.f;
				b += 0.005f;
			}
			if (r == 0.f && g <= 1.f && b <= 1.f)
			{
				b = 1.f;
				g -= 0.005f;
			}
			if (r >= 0.f && g <= 0.f && b == 1.f)
			{
				g = 0.f;
				r += 0.005f;
			}
			if (r >= 1.f && g >= 0.f && b <= 1.f)
			{
				r = 1.f;
				b -= 0.005f;
			}

			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(r,g,b,1.f));
			ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, ImVec4(r, g, b, 1.f));

			ImGui::BeginChild("##rainbotcrapnignog", ImVec2(733.f, 3.f));
			ImGui::EndChild();
			ImGui::PopStyleColor();

			ImGui::Spacing();
			
			static int tabselected = 0;
			ImGui::BeginChild("##tabshit", ImVec2(100.f, 580.f));
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.07, 0.07, 0.07, 1.0));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.07, 0.07, 0.07, 1.0));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.07, 0.07, 0.07, 1.0));
				ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, ImVec4(0.07f, 0.07f, 0.07f, 1.f));
				ImGui::PushFont(fskeet);
				if (ImGui::Button("a", ImVec2(100, 93)))
					tabselected = 0;
				if (ImGui::Button("b", ImVec2(100, 93)))
					tabselected = 1;
				if (ImGui::Button("c", ImVec2(100, 93)))
					tabselected = 2;
				if (ImGui::Button("d", ImVec2(100, 93)))
					tabselected = 3;
				if (ImGui::Button("e", ImVec2(100, 93)))
					tabselected = 4; 
				if (ImGui::Button("f", ImVec2(100, 93)))
					tabselected = 5;
				ImGui::PopFont();
				

			}
			ImGui::EndChild();

			ImGui::SameLine();
			
			ImGui::BeginChild("##b1g main area", ImVec2(625.f, 580.f));
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.14f, 0.14f, 0.14f, 1.f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.17f, 0.17f, 0.17f, 1.f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.17f, 0.17f, 0.17f, 1.f));
				ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, ImVec4(0.07f, 0.07f, 0.07f, 1.f));
				ImGui::PushFont(fDefault);
				if (tabselected == 0)
				{
					ImGui::BeginChild("##more ragebot stuff", ImVec2(310.f, 288.f));
					{
						//more ragebot settings
						//putting unload here temp
						if (ImGui::Button(XorStr("Unhook")))
						{
							g_Engine->ClientCmd_Unrestricted("cl_mouseenable 1");
							unload = true;
						}
						ImGui::PushItemWidth(150);
						ImGui::Checkbox(XorStr("Active"), &g_Options.Ragebot.MainSwitch);
						ImGui::Combo(XorStr("Hitbox"), &g_Options.Ragebot.Hitbox, aimBones, ARRAYSIZE(aimBones));
						ImGui::PushItemWidth(260);
						ImGui::SliderFloat(XorStr("Snipers"), &g_Options.Ragebot.HitchanceSniper, 0.f, 100.f, "%.1f");
						ImGui::Separator();
						ImGui::Separator();
					}
					ImGui::EndChild();

					ImGui::SameLine();

					ImGui::BeginChild("##aimbot stuff", ImVec2(310.f, 288.f));
					{
						// ragebot misc settings

					}
					ImGui::EndChild();


					ImGui::BeginChild("##ragebot shit.", ImVec2(310.f, 288.f));
					{
						//some stuff
					}
					ImGui::EndChild();

					ImGui::SameLine();

					ImGui::BeginChild("##aa's", ImVec2(310.f, 288.f));
					{
						static int movementtype = 0;
						if (ImGui::Button("Run", ImVec2(55, 25)))
							movementtype = 0;
						ImGui::SameLine();
						if (ImGui::Button("Walk", ImVec2(55, 25)))
							movementtype = 1;
						ImGui::SameLine();
						if (ImGui::Button("Jump", ImVec2(55, 25)))
							movementtype = 2;
						ImGui::SameLine();
						if (ImGui::Button("Fake", ImVec2(55, 25)))
							movementtype = 3;
						ImGui::SameLine();
						if (ImGui::Button("more", ImVec2(55, 25)))
							movementtype = 4;



						//more is placeholder idk what different movements there r i dont hvh at all. if there are no more than what i lsited just resize the buttons to all fit into 300 evenly so 75 (ImGui::Button("Run", ImVec2(75, 25)))
						//also do all ur aa stuff inside of each of these.
						switch (movementtype)
						{
						case 0:
							ImGui::Checkbox(XorStr("AA On Run"), &g_Options.Ragebot.AA_onRun);
							break;
						case 1:
							ImGui::Checkbox(XorStr("AA On Walk"), &g_Options.Ragebot.AA_onWalk);
							break;
						case 2:
							ImGui::Checkbox(XorStr("AA On Jump"), &g_Options.Ragebot.AA_onJump);
							break;
						case 3:
							ImGui::Checkbox(XorStr("AA On FakeWalk"), &g_Options.Ragebot.AA_onFakeWalk);
							break;
						case 4:
							ImGui::Checkbox(XorStr("AA On Crouch"), &g_Options.Ragebot.AA_onCrouch);
							break;
						}

					}
					ImGui::EndChild();


				}
				else if (tabselected == 1)
				{
					ImGui::BeginChild("##sniper", ImVec2(310.f, 288.f));
					{
						ImGui::Text("Snipers:");
					}
					ImGui::EndChild();

					ImGui::SameLine();

					ImGui::BeginChild("##rifles", ImVec2(310.f, 288.f));
					{
						ImGui::Text("Rifles:");
					}
					ImGui::EndChild();


					ImGui::BeginChild("##pistols", ImVec2(310.f, 288.f));
					{
						ImGui::Text("Pistols:");
					}
					ImGui::EndChild();

					ImGui::SameLine();

					ImGui::BeginChild("##shotguns", ImVec2(310.f, 288.f));
					{
						ImGui::Text("Shotguns:");
					}
					ImGui::EndChild();
				}
				else if (tabselected == 2)
				{
					ImGui::BeginChild("##visuals 1", ImVec2(310.f, 580.f));
					{
						ImGui::Text("Visuals");
						//lots of visuals on page 1

					}
					ImGui::EndChild();

					ImGui::SameLine();

					ImGui::BeginChild("##visuals 2", ImVec2(310.f, 580.f));
					{
						ImGui::Text("Visuals Continued");
						//more visual shit

					}
					ImGui::EndChild();
				}
				else if (tabselected == 3)
				{
					ImGui::BeginChild("##misc options", ImVec2(310.f, 580.f));
					{
						ImGui::Text("Misc:");
						//lots of visuals on page 1

					}
					ImGui::EndChild();

					ImGui::SameLine();

					ImGui::BeginChild("##misc options 2", ImVec2(310.f, 580.f));
					{
						ImGui::Text("Misc Continued:");
						//more visual shit

					}
					ImGui::EndChild();
				}
				else if (tabselected == 4)
				{

				}
				else if (tabselected == 5)
				{

				}
				ImGui::EndChild();
			}


			
		}ImGui::End();
	}
}
