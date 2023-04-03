#include <iostream>

//Will be included when build occurs (not an actual error if red here)
#include <perturb/perturb.hpp>
#include "model.h"


perturb::StateVector stateVectorRequesting::getPositionVelocity(perturb::JulianDate currentTime){
    bool status = true;

    perturb::StateVector posAndVel;
    perturb::StateVector filler;

    if(this->sat.last_error() != perturb::Sgp4Error::NONE || this->sat.epoch().to_datetime().day != 12){
        status = false;
    }else{

        const double delta_days = currentTime - this->sat.epoch();
    
        const auto err = this->sat.propagate(currentTime, posAndVel);
        if(err != perturb::Sgp4Error::NONE){
            status = false;
        }
    }

    //if status is false then return error here instead
    if(status == false){
        return filler;
    }else{
        return posAndVel;
    }
}

bool stateVectorRequesting::setTle(std::string tleLine1, std::string tleLine2){
    sat = perturb::Satellite::from_tle(tleLine1, tleLine2);
    return true;
}


int main(){
    //get julian date of current time
    perturb::JulianDate currentTime = perturb::JulianDate(perturb::DateTime {2022, 3, 14, 1, 59, 26.535});

    std::string tleLine1 = "1 25544U 98067A   22071.78032407  .00021395  00000-0  39008-3 0  9996";
    std::string tleLine2 = "2 25544  51.6424  94.0370 0004047 256.5103  89.8846 15.49386383330227";

    stateVectorRequesting orbit(tleLine1,tleLine2);

    //request position and velovity at current time
    perturb::StateVector posAndVel = orbit.getPositionVelocity(currentTime);

    //print outputs to make sure working
    std::cout << "Position [km]: { " << posAndVel.position[0] << ", " << posAndVel.position[1] << ", " << posAndVel.position[2] << " }\n";
    std::cout << "Velocity [km/s]: { " << posAndVel.velocity[0] << ", " << posAndVel.velocity[1] << ", " << posAndVel.velocity[2] << " }\n";
}

  