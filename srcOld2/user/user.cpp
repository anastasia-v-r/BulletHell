#include "user.hpp"
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

User::User() {
	std::ifstream fileStream("storedSetting.txt");
	if (!fileStream.is_open()) {
		//throw std::runtime_error("No stored profile, loading default profile");
		mProfilePicture.loadFromFile("playerData/Default/pfp.png");
		mUserName = "Unkown";
	} else {
		mProfilePicture.loadFromFile("");
	}
}
