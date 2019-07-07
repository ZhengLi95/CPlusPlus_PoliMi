#ifndef TAXI_HPP
#define TAXI_HPP

#include <iostream>
#include <string>
#include "place.hpp"

class Taxi{
    private:
        std::string license_id;
        float total_distance = 0.0;
        Place last_ride_source = Place();
        Place last_ride_destination = Place();
    public:
        //Constructor
        Taxi(const std::string & _license_id);
        //Return the overall distance run by taxi
        float CGetOverallDistance() const;
        //Return the license id associated with the taxi
        const std::string CGetLicenseId() const;
        //Return the current position (if taxi is stopped)
        const Place CGetPosition() const;
        //Update information about current ride
        void SetRide(const Place source, const Place destination);
        //Return the information about last ride
        const std::pair<Place, Place> CGetLastRide() const;
        //Update the overall distance of taxi
        void AddDistance(const float distance);
};
    
//Return first_taxi.CGetOverallDistance() < second_taxi.CGetOverallDistance()
bool operator< (const Taxi & first_taxi, const Taxi & second_taxi);

#endif