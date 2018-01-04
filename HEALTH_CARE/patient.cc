#include "patient.hh"

void patient::add(medicine med){
    if (!med.is_expired()){

        //Remove all the expired & incompatible medicines
        std::multimap<Date, medicine>::iterator i = prescriptions.begin();
        std::multimap<Date, medicine>::iterator end = prescriptions.end();
        while (i != end){
            if ((*i).second.is_expired() || !(*i).second.is_compatible_with(med)){
                i = prescriptions.erase(i);
            }
            else{
                i++;
            }
        }

        //Insert new element
        Date proposed_end_date = med.get_proposed_end_date();
        prescriptions.insert({proposed_end_date, med});
    }    
}

std::list<medicine> patient::active_prescriptions(){
    std::list<medicine> act_p;
    for(const auto elem : prescriptions){
        act_p.push_back(elem.second);
    }
    for(const auto elem : act_p){
        std::cout << elem.get_name() << std::endl;
    }
    return act_p;
}