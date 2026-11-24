#include <cctype>
#include <iostream>
#include <string>
#include <vector>

static bool containsWholeName(const std::string& text, const std::string& name) {
    std::size_t pos = 0;
    while ((pos = text.find(name, pos)) != std::string::npos) {
        const bool left = pos == 0 || !(std::isalnum(static_cast<unsigned char>(text[pos - 1])) || text[pos - 1] == '_');
        const std::size_t end = pos + name.size();
        const bool right = end == text.size() || !(std::isalnum(static_cast<unsigned char>(text[end])) || text[end] == '_');
        if (left && right) return true;
        ++pos;
    }
    return false;
}
int main() {
    std::string tag; int k, m;
    if (!(std::cin >> tag >> k) || tag != "C" || k < 0) return 0;
    std::vector<std::string> c(k); for (auto& s : c) std::cin >> s;
    if (!(std::cin >> tag >> m) || tag != "D" || m < 0) return 0;
    std::vector<std::string> d(m); for (auto& s : d) std::cin >> s;
    int n; if (!(std::cin >> n) || n < 0) return 0;
    std::string line; std::getline(std::cin, line);
    int decisions = 0, leaks = 0, defined = 0;
    for (int i = 1; i <= n; ++i) {
        std::getline(std::cin, line);
        std::size_t p = line.find_first_not_of(' ');
        if (p != std::string::npos && line.compare(p, 2, "//") == 0) continue;
        std::string zone, body;
        const std::size_t sep = line.find(' ');
        if (sep == std::string::npos) zone = line;
        else { zone = line.substr(0, sep); body = line.substr(sep + 1); }
        const std::size_t bodyStart = body.find_first_not_of(' ');
        if (bodyStart != std::string::npos && body.compare(bodyStart, 2, "//") == 0) continue;
        bool hasC = false, hasD = false;
        for (const auto& name : c) if (containsWholeName(body, name)) hasC = true;
        for (const auto& name : d) if (containsWholeName(body, name)) hasD = true;
        if (hasC && zone == "INIT") ++decisions;
        if (hasC && (zone == "BOUCLE" || zone == "SCENE")) { std::cout << "FUITE " << i << ' ' << zone << '\n'; ++leaks; }
        if (hasD && zone != "FABRIQUE") { std::cout << "DEFINI " << i << ' ' << zone << '\n'; ++defined; }
    }
    std::cout << "DECISIONS " << decisions << '\n' << "FUITES " << leaks << '\n' << "DEFINIS " << defined << '\n';
    std::cout << "ABSTRACTION " << ((leaks == 0 && defined == 0) ? "TENUE" : "FUIT") << '\n';
    return 0;
}
