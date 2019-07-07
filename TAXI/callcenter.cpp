#include "callcenter.hpp"

void CallCenter::RegisterTaxi(const std::string & license_id){
    Taxi new_taxi(license_id);
    taxis.insert({license_id, new_taxi});
    available_taxis.insert(license_id);
    if(new_taxi.CGetPosition() == railstation){
        station_available_taxis.insert(new_taxi);
    }
}

const Taxi CallCenter::Call(const Place & source, const Place & destination){
    if (available_taxis.empty()){
        std::cerr << "There is not any available taxi" << std::endl;
        return Taxi("nonexistent");
    }
    auto closest_taxi_id = *(available_taxis.begin());
    float closest_distance = ComputeDistance(taxis.at(closest_taxi_id).CGetPosition(), source);
    for(const auto taxi_id : available_taxis){
        const auto current_distance = ComputeDistance(taxis.at(taxi_id).CGetPosition(), source);
        if (current_distance < closest_distance){
            closest_distance = current_distance;
            closest_taxi_id = taxi_id;
        }
    }
    available_taxis.erase(closest_taxi_id);
    
    Taxi return_taxi = taxis.at(closest_taxi_id);
    if (return_taxi.CGetPosition() == railstation){
        station_available_taxis.erase(return_taxi);
    }
    return_taxi.SetRide(source, destination);
    return return_taxi;
}

const Taxi CallCenter::CallAtRailStation(const Place & destination){
    if (station_available_taxis.size()){
        auto first_taxi = *(station_available_taxis.begin());
        taxis.at(first_taxi.CGetLicenseId()).SetRide(railstation, destination);
        station_available_taxis.erase(first_taxi);
        available_taxis.erase(first_taxi.CGetLicenseId());
        return first_taxi;
    }
    else{
        return Call(railstation, destination);
    }
}

const Taxi CallCenter::CallToRailStation(const Place & source){
    return Call(source, railstation);    
}

void CallCenter::Arrived(const std::string & license_id){
    Taxi taxi = taxis.at(license_id);
    const auto last_ride = taxi.CGetLastRide();
    taxi.AddDistance(ComputeDistance(last_ride.first, last_ride.second));
    if(taxi.CGetPosition() == railstation){
        station_available_taxis.insert(taxi);
    }
    available_taxis.insert(license_id);
}