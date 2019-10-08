#include "../LRU-K.hpp"
#include "../LRU.hpp"
#include <ctime>
#include <errno.h>
#include <limits.h>
#include "str_switch.hpp"

std::pair<double, double>
get_hit_percentage(uint32_t Knum, uint32_t cache_size, const std::vector<uint32_t>& requests_vec) {
    LRUK_cache<uint32_t> lrukCache(cache_size, Knum);
    LRU_cache            lruCache(cache_size);

    return {static_cast<double>(lrukCache.cache_hit_num(requests_vec)) / static_cast<double>(requests_vec.size()) * 100,
            static_cast<double>(lruCache.cache_hit_num(requests_vec)) / static_cast<double>(requests_vec.size()) * 100};
}

void generate_rand_vec(std::vector<uint32_t>& rand_vec) {
    static bool flag;
    if(!flag) {
        srand(time(NULL));
        flag = true;
    }

    int req_num = rand_vec.size();

    for(auto& elem : rand_vec)
        elem = rand() % (req_num / 3) + 1;
}

void generate_saw_vec(std::vector<uint32_t>& vec) {
    static bool flag;
    if(!flag) {
        srand(time(NULL));
        flag =  true;
    }

    int req_num = vec.size();
    int rand_range = 0;

    for(int i = 0; i < req_num; ++i) {
        rand_range = rand() % (req_num / 4) + 1;
        vec[i] = 0;
        for(int j = 1; (j <= rand_range) && (i < req_num - 1); ++j)
            vec[++i] = j;
    }
}

void generate_ladder_vec(std::vector<uint32_t>& vec) {
    static bool flag;
    if(!flag) {
        srand(time(NULL));
        flag =  true;
    }

    int req_num = vec.size();
    int base[4] = {10, 100, 1000, 10000};
    int which_base, rand_range;

    for(int i = 0; i < req_num; ++i) {
        rand_range = rand() % (req_num / 10) + 1;
        which_base = rand() % 4;

        for(int j =0; (j < rand_range) && (i < req_num); ++j) {
            vec[i] = (rand() % 5 + 1) +  base[which_base];
            i++;
        }
    }
}

std::vector<uint32_t>& generate_vec(std::vector<uint32_t>& requests, char* str) {
    SWITCH(str) {
        CASE("rand"):
            generate_rand_vec(requests);
            break;

            CASE("saw"):
            generate_saw_vec(requests);
            break;

            CASE("ladder"):
            generate_ladder_vec(requests);
            break;

        DEFAULT:
            fprintf(stderr, "wrong arg: %s", str);
            exit(EXIT_FAILURE);
    }
    return requests;
}

int get_number(char* str) {

    char* str_end;
    long int number = strtol(str, &str_end, 10);

    if(errno == ERANGE || (number == INT_MAX + 1 || number == INT_MIN - 1)) {
        fprintf(stderr, "your number over overflowed int!\n");
        exit(EXIT_FAILURE);
    }

    if((str_end == str) || (errno != 0 && number == 0)) {
        fprintf(stderr, "wrong input!\n");
        exit(EXIT_FAILURE);
    }

    if(number < 0) {
    	fprintf(stderr, "your number less than 0!\n");
    	exit(EXIT_FAILURE);
    }

    return number;
}

int main(int argc, char* argv[]) {
    if(argc != 7) {
    	fprintf(stderr, "wrong number of variables!\n");
    	exit(EXIT_FAILURE);
    }

   	uint32_t Knum            = get_number(argv[2]);
   	uint32_t cache_size      = get_number(argv[3]);
   	uint32_t req_num         = get_number(argv[4]);
   	uint32_t number_of_tests = get_number(argv[5]);

   	std::vector<uint32_t> requests(req_num);

    FILE* file = fopen(argv[1], "a");
    if(!file) {
        fprintf(stderr, "can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

	fprintf(file, "=================== %u  TESTS ===================\n", number_of_tests);
	fprintf(file, "K = %u, Cache size = %u, Requests number = %d, Data type: %s\n",
	        Knum, cache_size, req_num, argv[6]);
	fprintf(file, "================================================\n");

	for(uint32_t i = 0; i < number_of_tests; ++i) {
		std::pair<double, double> percentages =
		        get_hit_percentage(Knum, cache_size, generate_vec(requests, argv[6]));
		fprintf(file, "LRU-K hit percentage: %.3f%% LRU hit percentage: %.3f%%\n",
		        percentages.first, percentages.second);
    }

    fprintf(file, "================================================\n\n");
   	fclose(file);

    return 0;
}