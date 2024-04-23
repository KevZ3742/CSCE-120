# include "Database.h"

using std::string, std::vector;

// TODO: implement constructor using member initializer list
Database::Database() {}

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
	StatePark* newPark = new StatePark(parkName, entranceFee, trailMiles);
    stateParkList.push_back(newPark);
}

void Database::addPassport(string camperName, bool isJuniorPassport) {
	INFO(camperName)
	INFO(isJuniorPassport)

	// TODO: implement function
	Passport* newPassport = new Passport(camperName, isJuniorPassport);
    camperList.push_back(newPassport);
}

void Database::addParkToPassport(string camperName, string parkName) {
	INFO(camperName)
	INFO(parkName)

	// TODO: implement function
	for (Passport* passport : camperList) {
        if (passport->getCamperName() == camperName) {
            for (StatePark* park : stateParkList) {
                if (park->getParkName() == parkName) {
                    passport->addParkVisited(park);
                    return;
                }
            }
        }
    }
}

vector<string> Database::getParksInRevenueRange(double lowerBound, double upperBound) {
	INFO(lowerBound)
	INFO(upperBound)

	// TODO: (optional) implement function
	std::vector<std::string> parks;

    for (StatePark* park : stateParkList) {
        double revenue = park->getRevenue();
        if (revenue >= lowerBound && revenue <= upperBound) {
            parks.push_back(park->getParkName());
        }
    }

    return parks;
}

vector<string> Database::getHikersAtLeastLevel(int level) {
	INFO(level)

	// TODO: (optional) implement function
	std::vector<std::string> hikers;

    for (Passport* passport : camperList) {
        if (passport->getHikerLevel() >= level) {
            hikers.push_back(passport->getCamperName());
        }
    }

    return hikers;
}
