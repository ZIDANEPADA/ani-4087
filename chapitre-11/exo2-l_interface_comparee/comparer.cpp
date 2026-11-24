#include <iostream>
#include <set>
#include <string>
#include <vector>

int main() {
    int na, nb;
    if (!(std::cin >> na) || na < 0) return 0;
    std::vector<std::string> a(static_cast<std::size_t>(na));
    for (auto& name : a) std::cin >> name;
    if (!(std::cin >> nb) || nb < 0) return 0;
    std::vector<std::string> b(static_cast<std::size_t>(nb));
    for (auto& name : b) std::cin >> name;
    std::set<std::string> sa(a.begin(), a.end()), sb(b.begin(), b.end());
    int common = 0;
    for (const auto& name : sa) if (sb.count(name)) ++common;
    std::cout << "DEUX " << common << '\n';
    for (const auto& name : a) if (!sb.count(name)) std::cout << "SEUL_A " << name << '\n';
    for (const auto& name : b) if (!sa.count(name)) std::cout << "SEUL_B " << name << '\n';
    std::set<std::string> united = sa;
    united.insert(sb.begin(), sb.end());
    std::cout << "DIFFERENTES " << (static_cast<int>(sa.size() + sb.size()) - 2 * common)
              << " SUR " << united.size() << '\n';
    return 0;
}
