#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;
struct Action { string name, main, command; };
int main() {
    int a, t;
    if (!(cin >> a >> t)) return 0;
    const unordered_map<string, pair<string,string>> table = {
        {"SELECT", {"DROITE", "SOURIS_G"}}, {"GRAB", {"DROITE", "SOURIS_D"}},
        {"MENU", {"GAUCHE", "TAB"}}, {"MOVE", {"GAUCHE", "FLECHES"}},
        {"AIM_POSE", {"DROITE", "AUCUNE"}}, {"GRIP_POSE", {"DROITE", "AUCUNE"}},
        {"HAPTIC", {"DROITE", "AUCUNE"}}, {"SELECT_LEFT", {"GAUCHE", "SOURIS_M"}},
        {"GRAB_LEFT", {"GAUCHE", "MAJ_G"}}, {"AIM_POSE_LEFT", {"GAUCHE", "AUCUNE"}},
        {"GRIP_POSE_LEFT", {"GAUCHE", "AUCUNE"}}, {"HAPTIC_LEFT", {"GAUCHE", "AUCUNE"}},
        {"MOVE_RIGHT", {"DROITE", "IJKL"}}
    };
    vector<Action> actions;
    int rightCount = 0, leftCount = 0;
    for (int i = 0; i < a; ++i) {
        string name, usage; cin >> name >> usage;
        auto it = table.find(usage);
        pair<string,string> mapping = it == table.end() ? make_pair("DROITE", "AUCUNE") : it->second;
        actions.push_back({name, mapping.first, mapping.second});
        if (mapping.first == "DROITE") ++rightCount; else ++leftCount;
        cout << name << ' ' << mapping.first << ' ' << mapping.second << '\n';
    }
    int headFrames = 0;
    for (int frame = 1; frame <= t; ++frame) {
        int k; cin >> k;
        unordered_set<string> held;
        for (int j = 0; j < k; ++j) { string key; cin >> key; held.insert(key); }
        int fx = (held.count("F_DROITE") ? 1 : 0) - (held.count("F_GAUCHE") ? 1 : 0);
        int fy = (held.count("F_HAUT") ? 1 : 0) - (held.count("F_BAS") ? 1 : 0);
        int ix = (held.count("L") ? 1 : 0) - (held.count("J") ? 1 : 0);
        int iy = (held.count("I") ? 1 : 0) - (held.count("K") ? 1 : 0);
        bool head = false;
        for (const string& key : {string("Z"), string("Q"), string("S"), string("D"), string("W"), string("A")}) if (held.count(key)) head = true;
        if (head) ++headFrames;
        cout << frame;
        for (const auto& action : actions) {
            cout << ' ';
            if (action.command == "AUCUNE") cout << '-';
            else if (action.command == "FLECHES") cout << fx << ',' << fy;
            else if (action.command == "IJKL") cout << ix << ',' << iy;
            else cout << (held.count(action.command) ? 1 : 0);
        }
        cout << '\n';
    }
    cout << "DROITE " << rightCount << '\n' << "GAUCHE " << leftCount << '\n' << "TETE " << headFrames << '\n';
}
