#ifndef CALLCENTER_HPP
#define CALLCENTER_HPP
#include "date.hpp"
#include "place.hpp"
#include "taxi.hpp"

#include <unordered_set>
#include <unordered_map>
#include <set>

class CallCenter{
    private:
        std::unordered_set<std::string> available_taxis;
        std::set<Taxi> station_available_taxis;
        std::unordered_map<std::string, Taxi> taxis;
        const Place railstation = Place(0.0, 0.0);
    public:
        //Call a taxi
        const Taxi Call(const Place & Source, const Place & Destination);
        //Call a taxi for a ride starting from rail station
        const Taxi CallAtRailStation(const Place & Destination);
        //Call a taxi for a ride towards the rail station
        const Taxi CallToRailStation(const Place & Source);
        //Update data structure when a ride ends
        void Arrived(const std::string & license_id);
        //Register a new taxi
        void RegisterTaxi(const std::string & license_id);
};

#endif