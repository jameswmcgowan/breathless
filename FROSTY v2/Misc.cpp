﻿#include "Misc.h"
#include "Interfaces.h"
#include "Render.h"
#include <time.h>
#include "BaseClient.h"
#include "Strafer.h"

std::string animatedclantag;
int iLastTime;
bool bDone = false;
void misc::OnCreateMove(CInput::CUserCmd *cmd, C_BaseEntity *local)
{

	if (g_Options.Misc.Bhop && local->IsAlive())
	{
		if (cmd->buttons & IN_JUMP && !(local->GetMoveType() & MOVETYPE_LADDER))
		{

			int iFlags = local->GetFlags();
			if (!(iFlags & FL_ONGROUND))
				cmd->buttons &= ~IN_JUMP;
		}
	}
	if (g_Options.Misc.syncclantag)
	{
		static int counter = 0;
		static int motion = 0;
		int ServerTime = (float)local->GetTickBase() * g_Globals->interval_per_tick * 2.5;

		if (counter % 48 == 0)
			motion++;
		int value = ServerTime % 46;
switch (value)
            {
            case 0:
            {
                setclantag("                  ");
                break;
            }
            case 1:
            {
                setclantag("                 g");
                break;
            }
            case 2:
            {
                setclantag("                ga");
                break;
            }
            case 3:
            {
                setclantag("               gam");
                break;
            }
            case 4:
            {
                setclantag("              game");
                break;
            }
            case 5:
            {
                setclantag("             games");
                break;
            }
            case 6:
            {
                setclantag("            gamese");
                break;
            }
            case 7:
            {
                setclantag("           gamesen");
                break;
            }
            case 8:
            {
                setclantag("          gamesens");
                break;
            }
            case 9:
            {
                setclantag("         gamesense");
                break;
            }
            case 10:
            {
                setclantag("        gamesense ");
                break;
            }
            case 11:
            {
                setclantag("        gamesense ");
                break;
            }
            case 12:
            {
                setclantag("        gamesense ");
                break;
            }
            case 13:
            {
                setclantag("       gamesense  ");
                break;
            }
            case 14:
            {
                setclantag("       gamesense  ");
                break;
            }
            case 15:
            {
                setclantag("       gamesense  ");
                break;
            }
            case 16:
            {
                setclantag("      gamesense   ");
                break;
            }
            case 17:
            {
                setclantag("      gamesense   ");
                break;
            }
            case 18:
            {
                setclantag("      gamesense   ");
                break;
            }
            case 19:
            {
                setclantag("     gamesense    ");
                break;
            }
            case 20:
            {
                setclantag("     gamesense    ");
                break;
            }
            case 21:
            {
                setclantag("     gamesense    ");
                break;
            }
            case 22:
            {
                setclantag("    gamesense     ");
                break;
            }
            case 23:
            {
                setclantag("    gamesense     ");
                break;
            }
            case 24:
            {
                setclantag("    gamesense     ");
                break;
            }
            case 25:
            {
                setclantag("   gamesense      ");
                break;
            }
            case 26:
            {
                setclantag("   gamesense      ");
                break;
            }
            case 27:
            {
                setclantag("   gamesense      ");
                break;
            }
            case 28:
            {
                setclantag("  gamesense       ");
                break;
            }
            case 29:
            {
                setclantag("  gamesense       ");
                break;
            }
            case 30:
            {
                setclantag("  gamesense       ");
                break;
            }
            case 31:
            {
                setclantag(" gamesense        ");
                break;
            }
            case 32:
            {
                setclantag(" gamesense        ");
                break;
            }
            case 33:
            {
                setclantag(" gamesense        ");
                break;
            }
            case 34:
            {
                setclantag("gamesense         ");
                break;
            }
            case 35:
            {
                setclantag("gamesense         ");
                break;
            }
            case 36:
            {
                setclantag("gamesense         ");
                break;
            }
            case 37:
            {
                setclantag("amesense          ");
                break;
            }
            case 38:
            {
                setclantag("mesense           ");
                break;
            }
            case 39:
            {
                setclantag("esense            ");
                break;
            }
            case 40:
            {
                setclantag("sense             ");
                break;
            }
            case 41:
            {
                setclantag("ense              ");
                break;
            }
            case 42:
            {
                setclantag("nse               ");
                break;
            }
            case 43:
            {
                setclantag("se                ");
                break;
            }
            case 44:
            {
                setclantag("e                 ");
                break;
            }
            case 45:
            {
                setclantag("                  ");
                break;
            }
            }
            counter++;
	}
	
	if (g_Options.Misc.breathless_clantag)
		{
		static int counter = 0;
		static int motion = 0;
		int ServerTime = (float)local->GetTickBase() * g_Globals->interval_per_tick * 2.5;

		if (counter % 48 == 0)
			motion++;
		int value = ServerTime % 20;

		switch (value)
		{
			setclantag("negro"); break; //someone fucking do this im to lazy
		}
		counter++;
		}

	if (!g_Options.Misc.animatedclantag && animatedclantag.c_str() != G::AnimatedClantag)
	{
		animatedclantag = G::AnimatedClantag;
	}
	if (g_Options.Misc.animatedclantag && animatedclantag.length() > 1)
	{
		if (int(g_Globals->curtime) != iLastTime)
		{
			auto length = animatedclantag.length();
			animatedclantag.insert(0, 1, animatedclantag[length - 2]);
			animatedclantag.erase(length - 1, 1);

			setclantag(animatedclantag.c_str());
			iLastTime = int(g_Globals->curtime);
		}
	}
	if (g_Options.Misc.namespam)
	{
		char name[151];
		char fucked_char = static_cast<char>(-1);
		for (auto i = 0; i <= 150; i++)
			name[i] = fucked_char;

		const char nick[12] = "frosty.pw";
		memcpy(name, nick, 11);

		SetName(name);
	}

	if (g_Options.Misc.silentstealer)
	{
		bool bDidMeme = false;
		int iNameIndex = -1;
		char chName[130];
		static ConVar* name = g_CVar->FindVar("name");
		{
			for (int iPlayerIndex = 0; iPlayerIndex < g_Engine->GetMaxClients(); iPlayerIndex++)
			{
				C_BaseEntity *pEntity = g_EntityList->GetClientEntity(iPlayerIndex);
				if (!pEntity || pEntity == local || iPlayerIndex == g_Engine->GetLocalPlayer())
					continue;
				if (rand() % 3 == 1)
				{
					iNameIndex = pEntity->GetIndex();
					bDidMeme = true;
				}
			}
			if (bDidMeme)
			{
				player_info_t pInfo;
				g_Engine->GetPlayerInfo(iNameIndex, &pInfo);
				sprintf(chName, "%s ", pInfo.name);
				name->SetValue(chName);
			}
		}

	}
}

static vec_t Normalize_y(vec_t ang)
{
	while (ang < -180.0f)
		ang += 360.0f;
	while (ang > 180.0f)
		ang -= 360.0f;
	return ang;
}

void misc::AutoStrafe(CInput::CUserCmd *cmd, C_BaseEntity *local, QAngle oldangles)
{
	static AutoStrafer Strafer;

	static float move = 450;
	float s_move = move * 0.5065f;
	if (local->GetMoveType() & (MOVETYPE_NOCLIP | MOVETYPE_LADDER))
		return;
	if (cmd->buttons & (IN_FORWARD | IN_MOVERIGHT | IN_MOVELEFT | IN_BACK))
		return;

	if (cmd->buttons & IN_JUMP || !(local->GetFlags() & FL_ONGROUND))
	{
		if (local->GetVelocity().Length2D() == 0 && (cmd->forwardmove == 0 && cmd->sidemove == 0))
		{
			cmd->forwardmove = 450.f;
		}
		else if (cmd->forwardmove == 0 && cmd->sidemove == 0)
		{
			if (cmd->mousedx > 0 || cmd->mousedx > -0)
			{
				cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
			}
			else
			{
				auto airaccel = g_CVar->FindVar("sv_airaccelerate");
				auto maxspeed = g_CVar->FindVar("sv_maxspeed");

				static int zhop = 0;
				double yawrad = Normalize_y(oldangles.y) * PI / 180;

				float speed = maxspeed->GetFloat();
				if (cmd->buttons & IN_DUCK)
					speed *= 0.333;

				double tau = g_Globals->interval_per_tick, MA = speed * airaccel->GetFloat();

				int Sdir = 0, Fdir = 0;
				Vector velocity = local->GetVelocity();
				double vel[3] = { velocity[0], velocity[1], velocity[2] };
				double pos[2] = { 0, 0 };
				double dir[2] = { std::cos((oldangles[1] + 10 * zhop) * PI / 180), std::sin((oldangles[1] + 10 * zhop) * PI / 180) };
				oldangles.y = Normalize_y(yawrad * 180 / PI);
				Strafer.strafe_line_opt(yawrad, Sdir, Fdir, vel, pos, 30.0, tau, MA, pos, dir);
				cmd->sidemove = Sdir * 450;
			}
		}

	}
	movementfix(oldangles, cmd);
}