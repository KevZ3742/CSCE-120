# include "StatePark.h"

StatePark::StatePark(std::string parkName, double entranceFee, double trailMiles) : parkName(parkName), entranceFee(entranceFee), trailMiles(trailMiles) {}

std::string StatePark::getParkName() {
    return parkName;
}

double StatePark::getEntranceFee() {
    return entranceFee;
}

double StatePark::getTrailMiles() {
    return trailMiles;
}

void StatePark::addCamper(Passport* camper) {
    camperLog.push_back(camper);
}

double StatePark::getRevenue() {
    double totalRevenue = 0.0;
    for (Passport* camper : camperLog) {
        totalRevenue += entranceFee;
    }
    return totalRevenue;
}
