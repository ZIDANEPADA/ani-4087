#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>
using namespace std;

int usageNumber(const string& usage) {
    static const unordered_map<string, int> usages = {
        {"SELECT", 0}, {"GRAB", 1}, {"MENU", 2}, {"MOVE", 3},
        {"AIM_POSE", 4}, {"GRIP_POSE", 5}, {"HAPTIC", 6},
        {"SELECT_LEFT", 7}, {"GRAB_LEFT", 8}, {"AIM_POSE_LEFT", 9},
        {"GRIP_POSE_LEFT", 10}, {"HAPTIC_LEFT", 11}, {"MOVE_RIGHT", 12}
    };
    auto it = usages.find(usage);
    return it == usages.end() ? -1 : it->second;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vector<string> names(1);
    unordered_map<string, int> seen;
    int attached = 0;
    bool isAttached = false;
    for (int i = 0; i < n; ++i) {
        string command;
        cin >> command;
        if (command == "cree") {
            string name, type, usage;
            cin >> name >> type >> usage;
            names.push_back(name);
            int handle = static_cast<int>(names.size()) - 1;
            if (seen[name] > 0) ++seen["#duplicates"];
            ++seen[name];
            cout << "ACTION " << handle << ' ' << name << ' ' << type << ' ' << usageNumber(usage) << '\n';
        } else if (command == "attache") {
            if (!isAttached) {
                isAttached = true;
                attached = static_cast<int>(names.size()) - 1;
                cout << "ATTACHE " << attached << '\n';
            } else {
                cout << "ATTACHE REFUSE\n";
            }
        } else if (command == "lit") {
            uint64_t handle;
            cin >> handle;
            if (handle == 0 || handle >= names.size()) {
                cout << "LIT " << handle << " INVALIDE\n";
            } else if (!isAttached || handle > static_cast<uint64_t>(attached)) {
                cout << "LIT " << handle << " INCONNUE\n";
            } else {
                cout << "LIT " << handle << ' ' << names[static_cast<size_t>(handle)] << '\n';
            }
        }
    }
    cout << "ACTIONS " << names.size() - 1 << '\n';
    cout << "ATTACHEES " << attached << '\n';
    cout << "NOMS EN DOUBLE " << seen["#duplicates"] << '\n';
    return 0;
}
