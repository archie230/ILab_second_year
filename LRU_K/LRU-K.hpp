#pragma once
#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <vector>
#include <cassert>

template<typename T>
class LRUK_cache {
#ifdef _DEBUG
public:
#endif
    /**
     * cache_node contains cache data and list of times when we met that data
     */
    struct cache_node_t {
        T data_;
        ///очередь из не больше чем Knum_ элементов
        ///элементы в очереди - времена, когда запрос к data_ попал по кешу
        ///времена расположены в порядке возрастания, чем меньше время тем дальше было k-ое попадание по кешу
        std::queue<uint32_t> time_queue_;

        explicit cache_node_t() = default;
        cache_node_t(const T&, const std::queue<uint32_t>&);
        /**
         * @brief comparing times(time_queue_.front())
         * @return true if this time greater
         *              else false
         */
        bool operator>(const cache_node_t&);
    };
    
    using cachelist_t = std::list<cache_node_t>;
    using hash_map_t = std::unordered_map<uint32_t, typename cachelist_t::iterator>;

    ///элементы поддерживаются отсортироваными по времени
    ///в начале списка элемент с наибольшим временем, в конце с наименьшим
    cachelist_t cachelist_;
    hash_map_t hash_map_;

    uint32_t cache_size_;
    uint32_t Knum_;

    bool hash_map_full();
    bool time_queue_full(const cache_node_t&);
    void insert_by_time_in_cache(typename cachelist_t::iterator&);
public:
    explicit LRUK_cache(uint32_t, uint32_t);
    ~LRUK_cache() = default;
    bool lookup(T, uint32_t);
    uint32_t cache_hit_num(const std::vector<T>& requests);
};

template<typename T>
LRUK_cache<T>::cache_node_t::cache_node_t(const T& data, const std::queue<uint32_t>& time_queue)
        :
        data_(data),
        time_queue_(time_queue)
{}

template<typename T>
bool LRUK_cache<T>::cache_node_t::operator>(const LRUK_cache::cache_node_t& other) {
    if(other.time_queue_.empty()) {
        std::cerr << __PRETTY_FUNCTION__ << "  :time list empty\n";
        return false;
    }

    return time_queue_.front() > other.time_queue_.front();
}

template<typename T>
LRUK_cache<T>::LRUK_cache(uint32_t cache_size, uint32_t Knum)
        :
        cachelist_(),
        hash_map_(),
        cache_size_(cache_size),
        Knum_(Knum)
{}

template<typename T>
bool LRUK_cache<T>::hash_map_full() {
    assert(hash_map_.size() <= cache_size_);
    return hash_map_.size() == cache_size_;
}

template<typename T>
bool LRUK_cache<T>::time_queue_full(const cache_node_t& node) {
    assert(node.time_queue_.size() <= Knum_);
    return node.time_queue_.size() == Knum_;
}

template<typename T>
void LRUK_cache<T>::insert_by_time_in_cache(typename cachelist_t::iterator& node) {
    for(auto cachit = cachelist_.begin();  cachit != cachelist_.end(); cachit++) {
        if(*(node) > *(cachit)) {
            cachelist_.splice(cachit, cachelist_, node);
            return;
        }
    }
}

/**
 *
 * @tparam T type of elem
 * @param elem
 * @param time
 * @brief
 * Элемент есть в хеш-таблице?
 *  Да:
 *      Список времен этого элемента полный? {check bool time_queue_full(const cache_node_t&);}
 *          Да:
 *              время встречи элемента в K-ый раз меняется
 *              затем перемещение этого элемента по списку так, чтобы восстановить его порядок
 *                    ^^^{void insert_by_time_in_cache(typename cachelist_t::iterator&);}
 *              (описание порядка списка cachelist_ строка 36)
 *          Нет: вставка в концен списка времени в список элемента
 *  Нет:
 *      Кеш полный?
 *          Да:
 *              удаление последнего элемента списка из кеша
 *      Вставка в начало листа и в хеш таблицу
 *
 *
 * @return
 */
template<typename T>
bool LRUK_cache<T>::lookup(T elem, uint32_t time) {
    auto hashit = hash_map_.find(elem);

    if(hashit == hash_map_.end()) {
        if(hash_map_full()) {
            hash_map_.erase(cachelist_.back().data_);
            cachelist_.pop_back();
        }
        cachelist_.push_front( {elem, ({std::queue<uint32_t> time_q;
                                        time_q.push(time);
                                        time_q;})} );

        hash_map_[elem] = cachelist_.begin();

        return false;
    }

    auto cachit = hashit -> second;

    if(time_queue_full(*cachit)) {
        cachit -> time_queue_.pop();
        cachit -> time_queue_.push(time);

        insert_by_time_in_cache(cachit);
        return true;
    }

    cachit -> time_queue_.push(time);
    return true;
}

template<typename T>
uint32_t LRUK_cache<T>::cache_hit_num(const std::vector<T> &requests) {
    uint32_t hit_num = 0;
    uint32_t time = 1;

    for(const auto& elem : requests) {
        if(lookup(elem, time))
            ++hit_num;
        ++time;
    }

    return hit_num;
}