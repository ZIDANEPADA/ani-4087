#include <algorithm>
#include <cctype>
#include <iostream>
#include <set>
#include <string>
#include <vector>

static bool isHeaderComment(const std::string& line) {
    std::size_t i = 0;
    while (i < line.size() && (line[i] == ' ' || line[i] == '\t')) ++i;
    return line.compare(i, 2, "//") == 0;
}

static bool isNameChar(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

int main() {
    int n;
    if (!(std::cin >> n) || n < 0) return 0;
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> lines;
    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        lines.push_back(line);
    }
    int header = 0;
    std::vector<std::string> variables;
    std::set<std::string> seen;
    for (const std::string& current : lines) {
        if (!isHeaderComment(current)) break;
        ++header;
        for (std::size_t pos = 0; pos + 3 < current.size(); ++pos) {
            if (current.compare(pos, 3, "NK_") != 0) continue;
            if (pos > 0) {
                const unsigned char prev = static_cast<unsigned char>(current[pos - 1]);
                if (std::isalnum(prev) || current[pos - 1] == '_') continue;
            }
            std::size_t end = pos + 3;
            while (end < current.size() && isNameChar(current[end])) ++end;
            if (end == pos + 3 || end >= current.size() || current[end] != '=') continue;
            const std::string name = current.substr(pos, end - pos);
            if (seen.insert(name).second) variables.push_back(name);
        }
    }
    std::cout << "ENTETE " << header << '\n';
    std::cout << "IGNOREES " << n - header << '\n';
    if (variables.empty()) std::cout << "VARIABLE AUCUNE\n";
    else for (const auto& name : variables) std::cout << "VARIABLE " << name << '\n';
    const int part = n == 0 ? 0 : (100 * header) / n;
    std::cout << "PART " << part << '\n';
    return 0;
}
