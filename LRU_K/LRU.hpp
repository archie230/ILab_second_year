#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <cassert>

class LRU_cache {
    using cachelist_t = std::list<uint32_t>;
    using hash_map_t = std::unordered_map<uint32_t, std::list<uint32_t>::iterator>;

    cachelist_t cachelist_;
    hash_map_t hash_map_;
    uint64_t cache_size_;
public:
    explicit LRU_cache(uint64_t);

    ~LRU_cache() = default;

    bool hash_map_full();

    bool lookup(uint32_t);

    uint32_t cache_hit_num(const std::vector<uint32_t>&);
};

LRU_cache::LRU_cache(uint64_t cache_size)
        :
        cache_size_(cache_size)
{}

bool LRU_cache::hash_map_full() {
    assert(hash_map_.size() <= cache_size_);
    return hash_map_.size() == cache_size_;
}

bool LRU_cache::lookup(uint32_t elem) {
    auto hashit = hash_map_.find(elem);

    if(hashit == hash_map_.end()) {
        if(hash_map_full()) {
            hash_map_.erase(cachelist_.back());
            cachelist_.pop_back();
        }
        cachelist_.push_front(elem);
        hash_map_[elem] = cachelist_.begin();

        return false;
    }

    auto cachit = hashit -> second;
    if(cachit != cachelist_.begin())
        cachelist_.splice(cachelist_.begin(), cachelist_, cachit, std::next(cachit));

    return true;
}

uint32_t LRU_cache::cache_hit_num(const std::vector<uint32_t> &requests) {
    uint32_t hit_num = 0;

    for(const auto& elem : requests) {
        if(lookup(elem))
            ++hit_num;
    }

    return hit_num;
}