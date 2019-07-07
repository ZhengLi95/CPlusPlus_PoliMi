#ifndef PLACE_HPP
#define PLACE_HPP

class Place{
    public:
    Place() = default;
    Place(double x, double y){};
};

bool operator==(const Place & lhs, const Place & rhs);

float ComputeDistance(const Place &, const Place &);

#endif