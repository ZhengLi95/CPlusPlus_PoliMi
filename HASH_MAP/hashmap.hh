#ifndef HASHMAP_HH
#define HASHMAP_HH

template <typename K, typename T>
class HashMap{
    typedef std::vector<std::list<std::pair<K, T>>> table;
    double max_load_factor; //max_load_factor
    size_t bucket_count = 0; //vector length
    size_t count = 0; //total inserted elements
    std::hash<K> hash_code;
    void resize (void);
    
    public:
    table hashtable;
    HashMap(): max_load_factor(0.75), bucket_count(8), count(0), hashtable(bucket_count) {}
    void add (const K & key, const T & value);
    void remove (const K & key);
};

#endif