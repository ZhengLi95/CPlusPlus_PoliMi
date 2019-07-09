#include "hashmap.hh"
#include <functional>

template <typename K, typename T>
void HashMap<K, T>::add(const K & key, const T & value){
    const std::size_t idx = std::hash<K>()(key) % bucket_count;
    // look if the key is already inserted
    auto it = hashtable[idx].cbegin ();
    while (it != hashtable[idx].cend () and it->first != key)
        ++it;
    // if you reach the end, you could not find the pair
    if (it == hashtable[idx].cend ()){
        hashtable[idx].push_back ({key, value});
        ++count;
    }
    if (count / bucket_count > max_load_factor)
    resize();
}

template <typename K, typename T>
void HashMap<K, T>::resize(){
    bucket_count *= 2;
    table temp (bucket_count);
    hashtable.swap(temp);
    count = 0;
    // iterate over old hash table and add each entry to a new table.
    for (const auto & bucket: temp){
        for (const auto & couple: bucket){
            add (couple.first, couple.second);
        }
    }
}