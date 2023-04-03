#pragma once  //for avoiding including twice
#include <perturb/perturb.hpp>

class stateVectorRequesting {
    private:
        // if you do not set a tle to start it will use this one
        std::string defaultTleLine1 = "1 25544U 98067A   22071.78032407  .00021395  00000-0  39008-3 0  9996";
        std::string defaultTleLine2 = "2 25544  51.6424  94.0370 0004047 256.5103  89.8846 15.49386383330227";
        perturb::Satellite sat = perturb::Satellite::from_tle(defaultTleLine1, defaultTleLine2);    
    
    public:
        stateVectorRequesting(std::string tleLine1, std::string tleLine2){
            setTle(tleLine1,tleLine2);
        }

        perturb::StateVector getPositionVelocity(perturb::JulianDate currentTime);
        bool setTle(std::string tleLine1, std::string tleLine2);
};