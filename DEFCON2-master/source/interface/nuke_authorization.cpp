#include "lib/universal_include.h"
#include "app/app.h"
#include "app/globals.h"
#include "app/game.h"
#include "lib/gucci/input.h"
#include "lib/gucci/window_manager.h"
#include "lib/language_table.h"
#include "renderer/map_renderer.h"

#include "world/world.h"


#include "nuke_authorization.h"

void gen_random(std::string* s, const int len, const int parts) 
{
	static const char alphanum[] =
				   "0123456789"
				   //"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				   "abcdefghijklmnopqrstuvwxyz";

	s->clear();
	for (int i = 0; i < parts; ++i) {
		for (int j = 0; j < len; ++j) {
			s->push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
			}
		s->push_back('-');
	}
	s->pop_back();
}
std::string nuke_authorization::makeChallengeCode(int teamId)
{
	challengeStr = std::string(len * parts + parts - 1, '0');

	srand(time(NULL));

	gen_random(&challengeStr, len, parts);
	g_app->GetWorld()->GetTeam(teamId)->challengeStr = challengeStr;

	return challengeStr;
}
void nuke_authorization::printCode(std::string challengeStrP,int teamId)
{
	challengeStrP.insert(0,"ENTER AUTHENTICATOR CODE IN FORMAT '/code XXXXX-XXXXX' ... THIS IS THE CHALLENGE CODE: ");
	
	strcpy(char_array, challengeStrP.c_str()); 
	g_app->GetWorld()->AddChatMessage( teamId, CHATCHANNEL_PRIVATE_SYS, char_array, -1, false );
	//float xPos = g_windowManager->WindowW()/2.0f;
           // float yPos = g_windowManager->WindowH()*0.8f;
            //float size = ( g_windowManager->WindowW() / 30.0f );
		//	g_renderer->TextCentre( xPos, yPos, Colour(255,0,0,255), size, LANGUAGEPHRASE("message_placeunits") );
			//g_app->GetInterface()->ShowMessage( 0, 0, -1, LANGUAGEPHRASE("message_ten_minute_warning"), true );

}

bool nuke_authorization::challenge(std::string challengeKeygen, int teamId)
{
	srand(1);
				
	for (int i = 0; i < 10; i++) {
		srandChar[i] = rand() % 10;
		}
	std::string srandStr(srandChar);


	srandStr = "528491";


	std::time(&rawtime);
		
	challengeStr = g_app->GetWorld()->GetTeam(teamId)->challengeStr;

	std::transform(challengeStr.begin(), challengeStr.end(), challengeStr.begin(), ::toupper);

	for(int i=0;i<20;i++)
	{
		memset(&buffer[0], '\0', sizeof(buffer));

		newTime = rawtime - (60 * i);
		timeinfo = std::localtime(&newTime);

		std::strftime(buffer, 80, "%Y%m%d%H%M", timeinfo);
		std::string time(buffer);

		srandStr = "528491";

		activation = sha512(srandStr + time + challengeStr);

		activationShort = std::string(len * parts + parts - 1, '0');
		activationShort.clear();

		for (int i = 0; i < parts; ++i) 
		{
			for (int j = 0; j < len; ++j) 
			{
				activationShort.push_back(activation[len * i + j]);
			}
			activationShort.push_back('-');
		}
		activationShort.pop_back();

		std::transform(activationShort.begin(), activationShort.end(), activationShort.begin(), ::toupper);
		std::transform(challengeKeygen.begin(), challengeKeygen.end(), challengeKeygen.begin(), ::toupper);

		if (challengeKeygen == activationShort) {

			g_app->GetWorld()->GetTeam(teamId)->nuclearCodesAuthenticated = true;

			return true;
		}

	}

	/*	for(int i=0;i>-10;i--)
	{
		memset(&buffer[0], '\0', sizeof(buffer));

		newTime = rawtime - (60 * i);
		timeinfo = std::localtime(&newTime);

		std::strftime(buffer, 80, "%Y%m%d%H%M", timeinfo);
		std::string time(buffer);

		srandStr = "528491";

		activation = sha512(srandStr + time + challengeStr);

		activationShort = std::string(len * parts + parts - 1, '0');
		activationShort.clear();

		for (int i = 0; i < parts; ++i) 
		{
			for (int j = 0; j < len; ++j) 
			{
				activationShort.push_back(activation[len * i + j]);
			}
			activationShort.push_back('-');
		}
		activationShort.pop_back();

		std::transform(activationShort.begin(), activationShort.end(), activationShort.begin(), ::toupper);
		std::transform(challengeKeygen.begin(), challengeKeygen.end(), challengeKeygen.begin(), ::toupper);

		if (challengeKeygen == activationShort) {

			g_app->GetWorld()->GetTeam(teamId)->nuclearCodesAuthenticated = true;

			return true;
		}

	}*/


	return false;
}