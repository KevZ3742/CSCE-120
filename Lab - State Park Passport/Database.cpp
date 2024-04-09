# include "Database.h"

using std::string, std::vector;

// TODO: implement constructor using member initializer list

Database::~Database() {
	for (unsigned int i = 0; i < stateParkList.size(); ++i) {
		delete stateParkList.at(i);
	}
	
	for (unsigned int i = 0; i < camperList.size(); ++i) {
		delete camperList.at(i);
	}
}

void Database::addStatePark(string parkName, double entranceFee, double trailMiles) {
	INFO(parkName)
	INFO(entranceFee)
	INFO(trailMiles)

	// TODO: implement function

	return;
}

void Database::addPassport(string camperName, bool isJuniorPassport) {
	INFO(camperName)
	INFO(isJuniorPassport)

	// TODO: implement function

	return;
}

void Database::addParkToPassport(string camperName, string parkName) {
	INFO(camperName)
	INFO(parkName)

	// TODO: implement function

	return;
}

vector<string> Database::getParksInRevenueRange(double lowerBound, double upperBound) {
	INFO(lowerBound)
	INFO(upperBound)

	// TODO: (optional) implement function
	
	return {};
}

vector<string> Database::getHikersAtLeastLevel(int level) {
	INFO(level)

	// TODO: (optional) implement function

	return {};
}
