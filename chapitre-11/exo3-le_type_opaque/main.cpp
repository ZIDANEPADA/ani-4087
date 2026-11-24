#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main() {
    int e;
    if (!(std::cin >> e) || e < 0) return 0;
    std::unordered_set<std::string> external;
    for (int i = 0; i < e; ++i) { std::string name; std::cin >> name; external.insert(name); }
    int f;
    if (!(std::cin >> f) || f < 0) return 0;
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::vector<std::string> order;
    for (int i = 0; i < f; ++i) {
        std::string name; int k; std::cin >> name >> k;
        order.push_back(name);
        auto& edges = graph[name];
        for (int j = 0; j < k; ++j) { std::string child; std::cin >> child; edges.push_back(child); }
    }
    int touched = 0, units = 0;
    for (const auto& unit : order) {
        if (unit.size() < 4 || unit.substr(unit.size() - 4) != ".cpp") continue;
        ++units;
        struct Node { std::string name; std::vector<std::string> path; };
        std::queue<Node> q;
        q.push({unit, {unit}});
        std::unordered_set<std::string> seen{unit};
        bool found = false;
        while (!q.empty() && !found) {
            Node cur = q.front(); q.pop();
            auto it = graph.find(cur.name);
            if (it == graph.end()) continue;
            for (const auto& child : it->second) {
                if (!seen.insert(child).second) continue;
                auto path = cur.path; path.push_back(child);
                if (external.count(child)) {
                    std::cout << unit << " OUI ";
                    for (std::size_t p = 0; p < path.size(); ++p) { if (p) std::cout << '>'; std::cout << path[p]; }
                    std::cout << '\n'; ++touched; found = true; break;
                }
                if (graph.count(child)) q.push({child, path});
            }
        }
        if (!found) std::cout << unit << " NON\n";
    }
    std::cout << "TOUCHEES " << touched << " SUR " << units << '\n';
    return 0;
}
