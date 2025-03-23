//#include "RRP2Console64.h"
#include <iostream>
// #include <vector>
#include <string>
#include "RRP2/RRP2.h"
#include "jdevtools/jdevjsons.h"
#include "nlohmann/json.hpp"


// int main() {
// 	std:: cout << jdevtools::rando(1000, 0, 1) << std::endl;
// 	std:: cout << jdevtools::rando(1000, 0, 2) << std::endl;
// 	std:: cout << jdevtools::rando(1000, 0) << std::endl;
// 	std:: cout << jdevtools::rando(1000, 0) << std::endl;
// 	return 0;
// }


extern "C" {
	static RRP2 game1 = RRP2("");

	const char* creategame(const char* s_config, int isconfig) {
		nlohmann::json j_config = nlohmann::json::parse(jdevtools::base64urlDecode(s_config));
		RRP2::RRP2config r_config;

		try {
			r_config.player_max = j_config["data"]["player_max"];
			if (r_config.player_max < 2) r_config.player_max = 2;
			else if (r_config.player_max > 31) r_config.player_max = 31;

			for (int i = 0; i < RRP2std::cdatal; i++) {
				std::string key1 = RRP2std::getEnumName("cdatai", i);
				if (j_config["data"].contains(key1)) r_config.data[i] = j_config["data"][key1];
			}

			for (int i = 0; i < RRP2std::cardl; i++) {
				std::string key1 = RRP2std::getEnumName("cardi", i);
				if (j_config["card"].contains(key1)) r_config.card_freq[i] = j_config["card"][key1];
			}
		}
		catch(const std::exception&) {
			r_config = RRP2::RRP2config();
		}
		
		game1.start_new_game(r_config);
		return game1.save_game(isconfig).data();
	}

	void loadgame(const char* data) {
		game1 = RRP2(data);
	}

	const char* savegame(int isconfig) {
		return game1.save_game(isconfig).data();
	}

	const char* getconfig() {
		return game1.get_config().data();
	}
	
	int getpmax() {
		return game1.get_pmax();
	}

	// const char* getplayer(int index) {
	// 	return game1.get_player(index).data();
	// }

	int gameio(int input) {
		return game1.gameio(input);
	}

	const char* createjwt(const char* key, const char* data) {
		return jdevtools::createJWT(key, data).data();
	}
}
