#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

string choisi(const string& plateforme, const vector<string>& api) {
    vector<string> ordre;

    if (plateforme == "WINDOWS") {
        ordre = {"VULKAN", "DX12", "DX11", "OPENGL", "SOFTWARE"};
    } else if (plateforme == "MACOS") {
        ordre = {"METAL", "OPENGL", "SOFTWARE"};
    } else if (plateforme == "IOS") {
        ordre = {"METAL", "SOFTWARE"};
    } else if (plateforme == "ANDROID") {
        ordre = {"VULKAN", "OPENGL", "SOFTWARE"};
    } else {
        ordre = {"VULKAN", "OPENGL", "SOFTWARE"};
    }

    unordered_set<string> disponibles(api.begin(), api.end());

    for (const string& nom : ordre) {
        if (nom == "SOFTWARE" || disponibles.count(nom)) {
            if (nom == "VULKAN") return "Vulkan";
            if (nom == "DX12") return "DirectX 12";
            if (nom == "DX11") return "DirectX 11";
            if (nom == "OPENGL") return "OpenGL";
            if (nom == "METAL") return "Metal";
            return "Software";
        }
    }

    return "Software";
}

bool estDansOrdre(const string& plateforme, const string& api) {
    if (api == "SOFTWARE") return true;

    if (plateforme == "WINDOWS")
        return api == "VULKAN" || api == "DX12" || api == "DX11" || api == "OPENGL";
    if (plateforme == "MACOS")
        return api == "METAL" || api == "OPENGL";
    if (plateforme == "IOS")
        return api == "METAL";
    if (plateforme == "ANDROID")
        return api == "VULKAN" || api == "OPENGL";

    return api == "VULKAN" || api == "OPENGL";
}

int main() {
    int n;
    cin >> n;

    int ignorees = 0;
    int logiciel = 0;
    unordered_set<string> differentes;

    for (int i = 0; i < n; ++i) {
        string nom, plateforme;
        int k;
        cin >> nom >> plateforme >> k;

        vector<string> api(k);
        for (string& a : api) {
            cin >> a;
            if (a != "SOFTWARE" && !estDansOrdre(plateforme, a))
                ++ignorees;
        }

        string selection = choisi(plateforme, api);
        cout << nom << ' ' << selection << '\n';

        if (selection == "Software")
            ++logiciel;

        differentes.insert(selection);
    }

    cout << "IGNOREES " << ignorees << '\n';
    cout << "LOGICIEL " << logiciel << '\n';
    cout << "DIFFERENTES " << differentes.size() << '\n';
}
