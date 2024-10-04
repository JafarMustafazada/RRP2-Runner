//#include "RRP2Console64.h"
#include <iostream>
#include <string>
#include <vector>
#include "RRP2.h"
#include "JDevTools.h"

//
//int main() {
//	int pc;
//	RRP2Console64 gamemanager;
//	while (true)
//	{
//		std::string test1 = "2s5s6s1s1s1s1s1s1s1s1s1s0s1s1s1s1s1s1s1s1s1s1s1s25s0s0s16s2s0s1s2s0s0s1s0s0s3s2s1s0s0s0s0s0s0s0s0s1s1s0s0s0s0s0s5s0s1s0s0s1s0s0s2s0s1";
//		try
//		{
//			//std::cout << "\n\nhow many players will be?(max 16): ";
//			//std::cin >> pc;
//		}
//		catch (const std::exception&)
//		{
//			pc = 2;
//		}
//		gamemanager.run_inconsole(0, true, test1);
//	}
//
//	return 0;
//}

extern "C" {
	static RRP2 game1 = RRP2(" ");
	static bool was_loaded = false;

	void loadgame(const char* data) {
		game1 = RRP2(data);
		was_loaded = true;
	}

	const char* savegame() {
		if (was_loaded) return game1.save_game().data();
		else return "-";
	}

	const char* getconfig() {
		if (was_loaded) return game1.get_config_string().data();
		return "-";
	}

	const char* getgeneral() {
		std::string response = "-";

		if (was_loaded) {
			response = "pturn=" + std::to_string(game1.get_pturn());
			response += "&dturn=" + std::to_string(game1.get_dturn());
			response += "&events=" + std::to_string(game1.get_events());
			response += "&cinterface=" + std::to_string(game1.get_cinterface());
		}

		return response.data();
	}

	int getpmax() {
		if (was_loaded) return game1.get_pmax();
		else return 0;
	}

	const char* getplayer(int index) {
		if (was_loaded) return game1.get_player_string(index).data();
		else return "-";
	}

	int gameio(const char* sinput) {
		if (was_loaded) {
			int input = 0;

			try
			{
				input = std::stoi(sinput);
			}
			catch (const std::exception&)
			{
				input = -1;
			}

			return game1.gameio(input);
		}
		else return -3;
	}

	//const char* getdelimetr() {
	//	return "" + RRP2std::delimetr;
	//}

	const char* creategame(int pmax, const char* cdata, const char* cardf) {
		RRP2::RRP2config config;
		std::vector<std::string> vcdata = JDevTools::split(cdata, RRP2std::delimetr);
		std::vector<std::string> vcardf = JDevTools::split(cardf, RRP2std::delimetr);

		if (vcardf.size() == RRP2std::cardsl && vcdata.size() == RRP2std::cdatal) {
			try
			{
				if (pmax < 2) pmax = 2;
				else if (pmax > 31) pmax = 31;
				config.player_max = pmax;

				for (int i = 0; i < vcdata.size(); i++)
				{
					config.data[i] = std::stoi(vcdata[i]);
				}
				for (int i = 0; i < vcardf.size(); i++)
				{
					config.card_freq[i] = std::stoi(vcardf[i]);
				}
			}
			catch (const std::exception&)
			{
				config = RRP2::RRP2config();
			}
		}

		game1.start_new_game(config);
		was_loaded = true;
		return game1.save_game().data();
	}
}
