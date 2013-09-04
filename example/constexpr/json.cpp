#include "../../frozen/string.hpp"

// configuration
static size_t constexpr random_tree_depth = 4;
static size_t constexpr population_size = 100;
static float constexpr mutation_percent = 5.0f;
static float constexpr crossover_percent = 50.0f;

int main()
{
    // make_string json at compile-time from config
    auto constexpr json = frozen::empty_str +
                  '{' +
                      "\"random_tree_depth\" : " + random_tree_depth + ',' +
                      "\"population_size\" : " + population_size + ',' +
                      "\"mutation_percent\" : " + mutation_percent + ',' +
                      "\"crossover_percent\" : " + crossover_percent + ',' +
                  '}';

    static_assert(json == "{\"random_tree_depth\" : 4,\"population_size\" : 100,\"mutation_percent\" : 5,\"crossover_percent\" : 50,}", "");

    return 0;
}
