// Student ID: 20124453

#include <iostream>
#include <deque>
#include <queue>
#include <stack>
#include <functional>
#include "Graph_Algorithms.h"


float Gx::_get_capacity_of_this_path(const Graph &g, const std::vector<int> &path) {
    std::priority_queue<float> capacities;
    size_t path_size = path.size();
    size_t edges = 0;
    size_t vertex = 0;
    
    if (path_size == 0 || 1) {
        return 0.0;
    }

    for (size_t i = 0; i < path_size - 1; ++i) {
        vertex = path[i];
        edges = g._nodes[vertex].size();
        for (size_t j = 0; j < edges; ++j) {
            if (g._nodes[vertex][j].dst == path[i + 1]) {
                capacities.push(g._nodes[vertex][j].wt);
            }
        }
    }

    return capacities.top();
}

float Gx::_get_max_capacity_path(const Graph &g, int src, int dst, std::vector<int> &path) {
    int vertex_num = g.get_num_nodes();
    std::priority_queue<NW> max_priority;
    std::vector<NW> vertex_NW(vertex_num);
    std::vector<bool> settled(vertex_num, false);
    std::stack<int> vertex_path;
    NW max_vertex;
    int edges = 0;
    int dest = 0;
    float capacity = 0.0;
    float edge_capacity = 0.0;
    float source_capacity = 0.0;
    int i = 0;
    int top = 0;
    bool found = false;

    if (!path.empty()) {
        path.clear();
    }

    //if (vertex_num == 0 || vertex_num <= src || vertex_num <= dst || src == dst) {
    //    return 0.0;
    //}

    for (i = 0; i < vertex_num; ++i) {
        vertex_NW[i].node = i;
        vertex_NW[i].weight = Gx::MIN;
    }

    vertex_NW[src].weight = Gx::MAX;
    max_priority.push(vertex_NW[src]);

    //std::cout << "size: " << min_priority.size() << std::endl;
    while (!max_priority.empty()) {
        max_vertex = max_priority.top();
        max_priority.pop();
        
        if (max_vertex.node == dst) {
            found = true;
            break;
        }
        if (settled[max_vertex.node]) {
            continue;
        }
        else {
            settled[max_vertex.node] = true;
        }
        //std::cout << "\n\ncurr max node: " <<  max_vertex.node << " weight: " << max_vertex.weight << "\n";
        edges = (g._nodes[max_vertex.node]).size();

        for (i = 0; i < edges; ++i) {
            dest = (g._nodes[max_vertex.node][i]).dst;
            edge_capacity = (g._nodes[max_vertex.node][i]).wt;
            source_capacity = vertex_NW[max_vertex.node].weight;
            capacity = edge_capacity < source_capacity ? edge_capacity : source_capacity;
            //std::cout << "edge capacity " << edge_capacity << std::endl;
            //std::cout << "source capacity " << source_capacity << std::endl;
            //std::cout << "capacity " << capacity << std::endl;
            if (capacity > vertex_NW[dest].weight) {
                vertex_NW[dest].weight = capacity;
                vertex_NW[dest].pred = max_vertex.node;
                //std::cout << "pushing nodes " <<  dest << " weight: " << vertex_NW[dest].weight << "\n";
                max_priority.push(vertex_NW[dest]);
            }
        }
    }

    if (found) {
        top = dst;
        while (top != src) {
            vertex_path.push(top);
            top = vertex_NW[top].pred;
        }
        vertex_path.push(top);

        while(!vertex_path.empty()) {
            path.push_back(vertex_path.top());
            vertex_path.pop();
        }

        return vertex_NW[dst].weight;
    }

    return 0.0;
}

float Gx::_get_capacity_path(const Graph &g, int src, int dst, std::vector<int> &path) {
    int vertex_num = g.get_num_nodes();
    std::stack<NW> vertex_stack;
    std::vector<NW> vertex_NW(vertex_num);
    std::stack<int> vertex_path;
    NW vertex;
    int edges = 0;
    int dest = 0;
    float capacity = 0.0;
    float edge_capacity = 0.0;
    float source_capacity = 0.0;
    int i = 0;
    int top = 0;
    bool found = false;

    if (!path.empty()) {
        path.clear();
    }
    
    //if (vertex_num == 0 || vertex_num <= src || vertex_num <= dst || src == dst) {
    //    return 0.0;
    //}

    for (i = 0; i < vertex_num; ++i) {
        vertex_NW[i].node = i;
        vertex_NW[i].weight = Gx::MIN;
    }

    vertex_NW[src].weight = Gx::MAX;
    vertex_stack.push(vertex_NW[src]);

    //std::cout << "size: " << min_priority.size() << std::endl;
    while (!vertex_stack.empty()) {
        vertex = vertex_stack.top();
        vertex_stack.pop();
        
        if (vertex.node == dst) {
            found = true;
            break;
        }

        //std::cout << "\n\ncurr max node: " <<  max_vertex.node << " weight: " << max_vertex.weight << "\n";
        edges = (g._nodes[vertex.node]).size();

        for (i = 0; i < edges; ++i) {
            dest = (g._nodes[vertex.node][i]).dst;
            edge_capacity = (g._nodes[vertex.node][i]).wt;
            source_capacity = vertex_NW[vertex.node].weight;
            capacity = edge_capacity < source_capacity ? edge_capacity : source_capacity;
            //std::cout << "edge capacity " << edge_capacity << std::endl;
            //std::cout << "source capacity " << source_capacity << std::endl;
            //std::cout << "capacity " << capacity << std::endl;
            if (capacity > vertex_NW[dest].weight) {
                vertex_NW[dest].weight = capacity;
                vertex_NW[dest].pred = vertex.node;
                //std::cout << "pushing nodes " <<  dest << " weight: " << vertex_NW[dest].weight << "\n";
                vertex_stack.push(vertex_NW[dest]);
            }
        }
    }

    if (found) {
        top = dst;
        while (top != src) {
            vertex_path.push(top);
            top = vertex_NW[top].pred;
        }
        vertex_path.push(top);

        while(!vertex_path.empty()) {
            path.push_back(vertex_path.top());
            vertex_path.pop();
        }

        return vertex_NW[dst].weight;
    }

    return 0.0;
}

bool Gx::_is_cyclic(const Graph &g, size_t node, std::vector<bool> &seen, std::vector<bool> &cycle_free) {
    size_t edges =  g._nodes[node].size();

    if (seen[node]) {
        //std::cout << "!!!!!! cyclic\n";
        return true;
    }

    seen[node] = true;

    for (size_t i = 0; i < edges; ++i) {
        //std::cout << node << " is seen\n";
        //std::cout << "checking " << (g._nodes[node][i]).dst << std::endl;
        if(_is_cyclic(g, (g._nodes[node][i]).dst, seen, cycle_free)) {
            return true;
        }
    }

    cycle_free[node] = true;

    return false;
}

bool Gx::is_cyclic(const Graph &g) {
    size_t vertex_num = g.get_num_nodes();
    std::vector<bool> seen(vertex_num, false);
    std::vector<bool> cycle_free(vertex_num, false);

    for (size_t i = 0; i < vertex_num; ++i) {
        if (!cycle_free[i]) {  //first check if vertex is already cycle free, if not, only then do we check with is_cyclic.
            if (_is_cyclic(g, i, seen, cycle_free)) {
                return true;
            }
            seen.clear();
            seen.resize(vertex_num, false);
        }
    }

    return false;
}

bool Gx::prune_unreachables(Graph &g, int src) {
    size_t vertex_num = g.get_num_nodes();
    size_t edges_size = 0;
    size_t source_vertex = 0;
    size_t i = 0;
    std::vector<bool> seen(vertex_num, false);
    std::deque<int> vertex;

    vertex.push_back(src);

    while (!vertex.empty()) {
        source_vertex = vertex.front();
        vertex.pop_front();
        seen[source_vertex] = true;
        edges_size = g._nodes[source_vertex].size();
        for (i = 0; i < edges_size; ++i) {
            if (!seen[(g._nodes[source_vertex][i]).dst]) {
                vertex.push_back((g._nodes[source_vertex][i]).dst);
            }
        }
    }

    for (i = 0; i < vertex_num; ++i) {
        if (!seen[i]) {
            (g._nodes[i]).clear();
        }
    }
   
    return true;
}

size_t Gx::get_shortest_unweighted_path(const Graph &g, int src, int dst, std::vector<int> &path) {
    int vertex_num = g.get_num_nodes();
    std::stack<int> path_stack;
    std::vector<NW> vertex_NW(vertex_num);
    std::vector<bool> seen(vertex_num, false);
    std::deque<int> vertex;
    int source_vertex = 0;
    int dest_vertex = 0;
    float cost = 0.0;
    int i = 0;
    int top = 0;
    int edges = 0;
    bool found = false;

    if (!path.empty()) {
        path.clear();
    }
    if (vertex_num == 0 || vertex_num <= src || vertex_num <= dst || src < 0 || dst < 0) {
        return std::string::npos;
    }
    if (src == dst) {
        return 1;
    }
    
    for (i = 0; i < vertex_num; ++i) {
        vertex_NW[i].node = i;
        vertex_NW[i].weight = Gx::MAX;
    }
    vertex_NW[src].weight = 1;
    vertex.push_back(src);

    while (!vertex.empty()) {
        source_vertex = vertex.front();
        vertex.pop_front();

        if (seen[source_vertex]) {
            continue;
        }
        else {
            seen[source_vertex] = true;
        }

        edges = (g._nodes[source_vertex]).size();

        for (i = 0; i < edges; ++i) {
            dest_vertex = (g._nodes[source_vertex][i]).dst;
            cost = vertex_NW[source_vertex].weight + 1;

            if (cost < vertex_NW[dest_vertex].weight) {
                vertex.push_back(dest_vertex);
                vertex_NW[dest_vertex].weight = cost;
                vertex_NW[dest_vertex].pred = source_vertex;

                if (dest_vertex == dst) {
                    found = true;
                    goto stop;
                }
            }
        }
    }

    stop :

    if (found) {
        top = dst;
        while (top != src) {
            path_stack.push(top);
            top = vertex_NW[top].pred;
        }
        path_stack.push(top);

        while(!path_stack.empty()) {
            path.push_back(path_stack.top());
            path_stack.pop();
        }

        return path.size();
    }

    return std::string::npos;
}

size_t Gx::get_shortest_weighted_path(const Graph &g, int src, int dst, std::vector<int> &path) {
    int vertex_num = g.get_num_nodes();
    std::priority_queue<NW, std::vector<NW>, std::greater<NW> > min_priority;
    std::vector<NW> vertex_NW(vertex_num);
    std::vector<bool> settled(vertex_num, false);
    std::stack<int> vertex_path;
    NW min_vertex;
    int edges = 0;
    int dest = 0;
    float weight = 0.0;
    int i = 0;
    int top = 0;
    bool found = false;

    if (!path.empty()) {
        path.clear();
    }
    if (vertex_num == 0 || vertex_num <= src || vertex_num <= dst || src < 0 || dst < 0) {
        return std::string::npos;
    }
    if (src == dst) {
        return 1;
    }

    for (i = 0; i < vertex_num; ++i) {
        vertex_NW[i].node = i;
        vertex_NW[i].weight = Gx::MAX;
    }

    vertex_NW[src].weight = 0.0;
    min_priority.push(vertex_NW[src]);

    while (!min_priority.empty()) {
        min_vertex = min_priority.top();
        min_priority.pop();

        if (min_vertex.node == dst) {
            found = true;
            break;
        }
        if (settled[min_vertex.node]) {
            continue;
        }
        else {
            settled[min_vertex.node] = true;
        }

        edges = (g._nodes[min_vertex.node]).size();
       
        for (i = 0; i < edges; ++i) {
            dest = (g._nodes[min_vertex.node][i]).dst;
            weight = (g._nodes[min_vertex.node][i]).wt + min_vertex.weight;

            if (weight < vertex_NW[dest].weight) {
                vertex_NW[dest].weight = weight;
                vertex_NW[dest].pred = min_vertex.node;
                min_priority.push(vertex_NW[dest]);
            }
        }
    }

    if (found) {
        top = dst;
        while (top != src) {
            vertex_path.push(top);
            top = vertex_NW[top].pred;
        }
        vertex_path.push(top);

        while(!vertex_path.empty()) {
            path.push_back(vertex_path.top());
            vertex_path.pop();
        }

        return path.size();
    }

    return std::string::npos;
}

float Gx::get_max_flow(const Graph &g, int src, int dst) {
    Graph residual_graph = g;
    std::vector<int> path;
    size_t path_size = 0;
    size_t i = 0;
    int vertex_num = g.get_num_nodes();
    float max_flow = 0.0;
    float current_flow = 1.0;

    if (vertex_num == 0 || vertex_num <= src || vertex_num <= dst || src < 0 || dst < 0 || src == dst) {
        return 0.0;
    }

    while (current_flow != 0.0) {
        //std::cout << "current flow: " << current_flow << std::endl;
        current_flow = _get_max_capacity_path(residual_graph, src, dst, path);
        //current_flow = _get_capacity_path(residual_graph, src, dst, path);
        path_size = path.size();

        for (i = 1; i < path_size; ++i) {
            residual_graph.add_edge(path[i], path[i - 1], current_flow, false);
            residual_graph.add_edge(path[i - 1], path[i], -current_flow, false);
        }

        max_flow += current_flow;
    }

    return max_flow;
}