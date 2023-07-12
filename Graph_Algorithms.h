// Student ID: 20124453

#ifndef Graph_Algorithms_h
#define Graph_Algorithms_h
#include <cfloat>
#include "Graph.h"

class Gx {
    private:
        static constexpr float MAX = FLT_MAX;
        static constexpr float MIN = FLT_MIN;
        struct NW {
            int node, pred;
            float weight;
            NW() : node(0), pred(0), weight(0) {}
            NW(int n, int m, float wt) : node(n), pred(m), weight(wt) {}
            bool operator<(const NW &that) const { return this->weight < that.weight; }
            bool operator>(const NW &that) const { return this->weight > that.weight; }
        };

        static float _get_capacity_of_this_path(const Graph &g, const std::vector<int> &path);
        static float _get_max_capacity_path(const Graph &g, int src, int dst, std::vector<int> &path);
        static float _get_capacity_path(const Graph &g, int src, int dst, std::vector<int> &path);
        static bool _is_cyclic(const Graph &g, size_t node, std::vector<bool> &seen, std::vector<bool> &cycle_free);
    public:
        static bool is_cyclic(const Graph &g);
        static bool prune_unreachables(Graph &g, int src);
        static size_t get_shortest_unweighted_path(const Graph &g, int src, int dst, std::vector<int> &path);
        static size_t get_shortest_weighted_path(const Graph &g, int src, int dst, std::vector<int> &path);

        static float get_max_flow(const Graph &g, int src, int dst);

        friend class Tests;
};

#endif