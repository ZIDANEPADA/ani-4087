#include <iostream>
#include <string>
#include <vector>

static std::string trimLineEnd(std::string s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) s.pop_back();
    return s;
}
int main() {
    int k; if (!(std::cin >> k) || k < 0) return 0;
    std::string line; std::getline(std::cin, line);
    for (int i = 1; i <= k; ++i) {
        std::string manifest; std::getline(std::cin, manifest); manifest = trimLineEnd(manifest);
        int l; if (!(std::cin >> l)) return 0; std::getline(std::cin, line);
        std::vector<std::string> lines;
        for (int j = 0; j < l && l >= 0; ++j) { std::getline(std::cin, line); lines.push_back(trimLineEnd(line)); }
        if (manifest == "-") { std::cout << i << " REGISTRE AUCUN\n"; continue; }
        std::cout << i << " MANIFESTE " << manifest << '\n';
        if (l == -1) { std::cout << i << " ECHEC ILLISIBLE\n"; continue; }
        std::string content;
        for (const auto& s : lines) { content += s; content += '\n'; }
        const std::string key = "\"library_path\"";
        std::size_t p = content.find(key);
        if (p == std::string::npos) { std::cout << i << " ECHEC CLE\n"; continue; }
        p = content.find(':', p + key.size());
        if (p == std::string::npos) { std::cout << i << " ECHEC DEUX_POINTS\n"; continue; }
        std::size_t q1 = content.find('"', p + 1);
        if (q1 == std::string::npos) { std::cout << i << " ECHEC GUILLEMET\n"; continue; }
        std::size_t q2 = content.find('"', q1 + 1);
        if (q2 == std::string::npos) { std::cout << i << " ECHEC GUILLEMET\n"; continue; }
        std::string value;
        for (std::size_t x = q1 + 1; x < q2; ++x) {
            if (content[x] == '\\' && x + 1 < q2 && content[x + 1] == '\\') ++x;
            value += content[x];
        }
        if (value.empty()) { std::cout << i << " ECHEC VIDE\n"; continue; }
        const bool absolute = (value.size() >= 2 && value[1] == ':') || value[0] == '\\' || value[0] == '/';
        std::cout << i << " VALEUR " << value << '\n';
        if (absolute) std::cout << i << " ABSOLU\n";
        else {
            const std::size_t sep = manifest.find_last_of("\\/");
            const std::string prefix = sep == std::string::npos ? "" : manifest.substr(0, sep + 1);
            std::cout << i << " RELATIF\n" << i << " CHARGE " << prefix << value << '\n';
            continue;
        }
        std::cout << i << " CHARGE " << value << '\n';
    }
    return 0;
}
