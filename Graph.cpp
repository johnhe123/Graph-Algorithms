// Student ID: 20124453

#include <sstream>
#include "Graph.h"

 Graph& Graph::add_edge(int src, int tgt, float wt, bool replace) {
    std::vector<Edge>::iterator itr, itr_end;
    bool found = false;
    int nodes_size = 0;
    int larger = 0;

    nodes_size = _nodes.size();
    larger = src < tgt ? tgt : src;
    if (nodes_size <= larger) {
        _nodes.resize(larger + 1);
    }

    if (src != tgt) {
        for (itr = _nodes[src].begin(), itr_end = _nodes[src].end(); itr != itr_end; ++itr) {
            if (itr->dst == tgt) {
                itr->wt = replace ? wt : itr->wt + wt;
                if (itr->wt <= FLOOR) {
                    _nodes[src].erase(itr);
                }
                found = true;
            }
        }
        if (!found) {
            _nodes[src].push_back(Edge(tgt, wt));
        }
    }

    return *this;
 }


float Graph::find_edge_weight(int src, int tgt) const {
    std::vector<Edge>::const_iterator itr, itr_end;
    int nodes_size = _nodes.size();

    if (src < nodes_size && tgt < nodes_size) {
        for (itr = _nodes[src].begin(), itr_end = _nodes[src].end(); itr != itr_end; ++itr) {
            if (itr->dst == tgt) {
                return itr->wt;
            }
        }
    }
    
    return Graph::FLOOR;
}


std::string Graph::to_string() const {
    std::vector<std::vector<Edge> >::const_iterator s_itr, s_itr_end;
    std::vector<Edge>::const_iterator itr, itr_end;
    int i = 0;
    std::stringstream ss;
    std::string str;

    if (_nodes.empty()) {
        return "";
    }

    ss << "# Graph - " << _nodes.size() << " nodes.\n";
    ss << "# Edge lists:\n";

    for (s_itr = _nodes.begin(), s_itr_end = _nodes.end(); s_itr != s_itr_end; ++s_itr, ++i) {
        if (!_nodes[i].empty()) {
            ss << i << " :";
            for (itr = s_itr->begin(), itr_end = s_itr->end(); itr != itr_end; ++itr) {
                ss << " (" << itr->dst << "," << itr->wt << ")";
            }
            ss << "\n";
        }
    }

    ss << "# End of Graph\n";

    str = ss.str();

    return str;
}