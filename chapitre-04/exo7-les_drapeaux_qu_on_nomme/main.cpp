#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <iomanip>

using namespace std;

using U32 = uint32_t;

struct Info {
    U32 value;
    bool simple;
};

int main() {
    unordered_map<string, U32> flags = {
        {"RENDER2D", 1u},
        {"RENDER3D", 2u},
        {"TEXT", 4u},
        {"UI", 8u},
        {"SHADOW", 16u},
        {"POST_PROCESS", 32u},
        {"VFX", 64u},
        {"ANIMATION", 128u},
        {"OVERLAY", 256u},
        {"SIMULATION", 512u},
        {"OFFSCREEN", 1024u},
        {"RAYTRACING", 2048u},
        {"GPU_CULLING", 4096u}
    };

    unordered_map<string, U32> composed = {
        {"NONE", 0u},
        {"2D_ESSENTIALS", 1u | 4u},
        {"3D_BASE", 2u | 16u | 32u},
        {"DEBUG", 256u | 512u},
        {"ALL", 0xFFFFFFFFu}
    };

    vector<string> simple_names = {
        "RENDER2D", "RENDER3D", "TEXT", "UI", "SHADOW",
        "POST_PROCESS", "VFX", "ANIMATION", "OVERLAY",
        "SIMULATION", "OFFSCREEN", "RAYTRACING", "GPU_CULLING"
    };

    int n;
    cin >> n;

    U32 value = 0;
    vector<string> inconnus;

    for (int i = 0; i < n; ++i) {
        string nom;
        cin >> nom;

        auto it = flags.find(nom);
        if (it != flags.end()) {
            value |= it->second;
            continue;
        }

        auto ic = composed.find(nom);
        if (ic != composed.end()) {
            value |= ic->second;
            continue;
        }

        inconnus.push_back(nom);
    }

    if (n == 0)
        value = 0xFFFFFFFFu;

    for (const string& nom : inconnus)
        cout << "INCONNU " << nom << '\n';

    cout << "VALEUR " << static_cast<unsigned long long>(value) << '\n';

    cout << "HEXA 0x"
         << uppercase << hex << setw(8) << setfill('0')
         << static_cast<unsigned long long>(value)
         << nouppercase << dec << setfill(' ') << '\n';

    auto allume = [&](const string& nom) -> bool {
        return (value & flags[nom]) != 0;
    };

    if (allume("TEXT") && !allume("RENDER2D"))
        cout << "MANQUE TEXT RENDER2D\n";

    if (allume("UI")) {
        if (!allume("RENDER2D"))
            cout << "MANQUE UI RENDER2D\n";
        if (!allume("TEXT"))
            cout << "MANQUE UI TEXT\n";
    }

    if (allume("SHADOW") && !allume("RENDER3D"))
        cout << "MANQUE SHADOW RENDER3D\n";

    if (allume("OVERLAY")) {
        if (!allume("RENDER2D"))
            cout << "MANQUE OVERLAY RENDER2D\n";
        if (!allume("TEXT"))
            cout << "MANQUE OVERLAY TEXT\n";
    }

    int allumes = 0;
    for (const string& nom : simple_names) {
        if (allume(nom))
            ++allumes;
    }

    cout << "ALLUMES " << allumes << '\n';
    cout << "ETEINTS " << 13 - allumes << '\n';
}
