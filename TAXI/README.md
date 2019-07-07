# TAXI CALL CENTER

## Problem

You have to develop the core class `CallCenter` of the MyTaxi application for a small city with one railroad station. CallCenter provides an interface to the user to call taxi and store information about all the taxis of the city. Each taxi is identified in a unique way by the license id (of type `std::string`) of its driver. Since most of the rides are from or to the rail station, ad-hoc functionalities for this type of rides have to be implemented.

The following data structures and functions have already been implemented and are available:
+ `Date`, a class which stores information about a date.
+ `Place`, a class which stores information about a location in the city.
+ `float ComputeDistance(const Place &, const Place &)`, a function which computes the distance between
two locations.
+ `Taxi`, a class which stores information about a taxi, whose implementation follows.

```cpp
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
        void AddDistance(const float distance)
    };
    
//Return first_taxi.CGetOverallDistance() < second_taxi.CGetOverallDistance()
bool operator< (const Taxi & first_taxi, const Taxi & second_taxi);

#endif
```

You are required to complete the following implementation of `CallCenter`:

```cpp
#ifndef CALLCENTER_HPP
#define CALLCENTER_HPP
#include "date.hpp"
#include "place.hpp"
#include "taxi.hpp"

class CallCenter{
    private:
        /* PUT YOUR CODE HERE */ available_taxis;
        /* PUT YOUR CODE HERE */ station_available_taxis;
        std::unordered_map<std::string, Taxi> taxis;
        const Place railstation = Place(0.0, 0.0);
    public:
        //Call a taxi
        const Taxi Call(const Place & source, const Place & destination);
        //Call a taxi for a ride starting from rail station
        const Taxi CallAtRailStation(const Place & Destination);
        //Call a taxi for a ride towards the rail station
        const Taxi CallToRailStation(const Place & Source);
        //Update data structure when a ride ends
        void Arrived(const std::string & license_id);
};

#endif
```

In particular you have to:

1. Specify the types of `available_taxis`, `station_available_taxis`, optimized for the call of `CallAtRailStation`, which has to be implemented with a special focus on the time complexity.

2. Provide the implementation of `Call`, i.e., call for a taxi: the function must return the `taxi`, if any available, which current position is closest to the source of the ride; if there are more than one taxi at the smallest distance, whatever of them can be returned.

3. Provide the implementation of `CallAtRailStation`: the function must return the available `taxi` which: 1) is currently at the rail station, and 2) has run the smallest distance among all available taxis located at the rail station. If there are more than one taxi available at the station with the smallest distance, whatever of them
can be returned. If there is not any available taxi at the rail station, the closest to the rail station must be selected.

4. Provide the implementation of `CallToRailStation`, i.e., call for a taxi for a ride to the rail station: the function must return the `taxi`, if any available, whose current position is closest to the source of the ride; if there are more than one taxi at the smallest distance, whatever of them can be returned.

5. Provide the implementation of `Arrived`: the function must update information about `available_taxis`, overall distance of taxi, and eventually `station_available_taxis`.

6. Provide the complexity of the implemented methods.

Suggestions:
+ License id can be used to identify the taxis.
+ `Call`, `CallAtRailStation`, `CallToRailStation` share part of the functionality, so some code can be reused.
+ `Call`, `CallAtRailStation`, `CallToRailStation`, and `Arrived` must update the data structures about the available
taxis.
+ `railstation` member variable represents the rail station location.
+ `Call`, `CallAtRailStation`, `CallToRailStation` can return a null taxi when there is not any available taxi in this way: `return Taxi("nonexistent")`;

## Comments on Solution

Since the whole information about the single taxi is already stored in taxis, to reduce the number of copies of objects of type taxi, the set of available taxis can be stored by exploiting their license ids (which is of type `std::string`). Since the taxis have not to be ordered we can use unordered set. Please note that also solutions exploiting smart pointers should be preferred, but then smart pointers should be used also as input and as return value of the functions of `CallCenter`. Taxis available at rail station must instead be sorted, so a set should be preferred.

In this case, the value type of `station_available_taxis` cannot be `std::string`. A set storing the license ids indeed would sort the taxis according to their license ids instead of according their overall distances. Please note that the proposed solutions are not the only correct ones.

`Call` iterates over all the taxis looking for the one closest to the source of ride. `CallAtRailStation` takes the first taxi in `station_available_taxis`. Since taxis are sorted according to their overall distance, the first is the one with the smallest distance. If there is not available taxi at the rail station, the closest one is selected by means `Call`. `railstation` is used as first argument since this is the implicit source of the ride. On the contrary, the only difference between a generic ride and a ride towards the rail station is in the fixed destination. For this reason, `CallToRailStation` always exploits Call passing station as second argument. Finally, Arrived updates the overall distance of the taxi, checks if the destination of the ride was rail station and in this case adds the taxi to the `station_available_taxis`. In the first solution the taxi is always added also to the set of the available ones while in the second solution only if it is not at the station.

The complexities (given n taxis) are the following:

+ The complexity of `Call` in worst and average case is O(n) since it iterates over all the taxis.
+ The complexity of `CallAtRailStation` in worst and average case is constant since station_available_taxis is already sorted under the assumption that there is one available taxi.
+ The complexity of `CallToRailStation` is the same of `Call` (O(n) both in worst and average case).
+ The complexity of `Arrived` is O(n) in the worst case (because of `available_taxis.insert()`) and O(log(n)) in the average case (because of `station_available_taxis.insert()`).