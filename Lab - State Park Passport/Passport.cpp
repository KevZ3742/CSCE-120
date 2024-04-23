#include "Passport.h"

Passport::Passport(std::string camperName, bool isJuniorPassport) : camperName(camperName), isJuniorPassport(isJuniorPassport) {}

std::string Passport::getCamperName() {
    return camperName;
}

bool Passport::checkJuniorPassport() {
    return isJuniorPassport;
}

void Passport::addParkVisited(StatePark* park) {
    parksVisited.push_back(park);
}

double Passport::getMilesHiked() {
    double totalMiles = 0.0;
    for (StatePark* park : parksVisited) {
        totalMiles += park->getTrailMiles();
    }
    return totalMiles;
}

int Passport::getHikerLevel() {
    double milesHiked = getMilesHiked();
    if (milesHiked < 10.0) {
        return 1;
    } else if (milesHiked < 20.0) {
        return 2;
    } else if (milesHiked < 30.0) {
        return 3;
    } else {
        return 4;
    }
}
