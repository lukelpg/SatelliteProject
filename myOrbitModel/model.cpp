#include <iostream>

//Will be included when build occurs (not an actual error if red here)
#include <perturb/perturb.hpp>

//state vector holds time-stamp, and a position and velocity
perturb::StateVector getModel(int year, int month, int day, int hour, int min, float sec){
    bool status = true;

    //this is iss tle from 2022-03-12
    std::string TLE_LN1 = "1 25544U 98067A   22071.78032407  .00021395  00000-0  39008-3 0  9996";
    std::string TLE_LN2 = "2 25544  51.6424  94.0370 0004047 256.5103  89.8846 15.49386383330227";
    
    auto sat = perturb::Satellite::from_tle(TLE_LN1, TLE_LN2);

    perturb::StateVector posAndVel;
    perturb::StateVector filler;
    if(sat.last_error() != perturb::Sgp4Error::NONE || sat.epoch().to_datetime().day != 12){
        status = false;
    }else{

        const auto t = perturb::JulianDate(perturb::DateTime { year, month, day, hour, min, sec });
        const double delta_days = t - sat.epoch();

        //check to see if reqested time isnt too far from epoch time ?
        //possibly specific to this tle (checking for requested time to be 2 days since epoch give or take ?)
        if(1 >= delta_days && delta_days >= 3){
            status = false;
        }else{

            const auto err = sat.propagate(t, posAndVel);
            if(err != perturb::Sgp4Error::NONE){
                status = false;
            }
        };
    };

    //if status is false then return error here instead
    if(status == false){
        return filler;
    }else{
        return posAndVel;
    }
}


int main(){
    //request at specifc time
    perturb::StateVector posAndVel = getModel(2022, 3, 14, 1, 59, 26.535);

    //print outputs to make sure working
    std::cout << "Position [km]: { " << posAndVel.position[0] << ", " << posAndVel.position[1] << ", " << posAndVel.position[2] << " }\n";
    std::cout << "Velocity [km/s]: { " << posAndVel.velocity[0] << ", " << posAndVel.velocity[1] << ", " << posAndVel.velocity[2] << " }\n";
}