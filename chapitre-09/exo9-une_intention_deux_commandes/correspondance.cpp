#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;
int main() {
    int a; if (!(cin >> a)) return 0;
    vector<pair<string,string>> actions(static_cast<size_t>(a));
    for (auto& action:actions) cin >> action.first >> action.second;
    vector<vector<string>> imageLines(2);
    for (int tableIndex=0; tableIndex<2; ++tableIndex) {
        int u; cin >> u;
        unordered_map<string,string> mapping;
        for (int i=0;i<u;++i) { string usage, command; cin >> usage >> command; mapping[usage]=command; }
        int t; cin >> t;
        cout << "TABLE " << tableIndex+1 << '\n';
        for (const auto& action:actions) if (!mapping.count(action.second)) cout << "INACTIVE " << action.first << '\n';
        vector<int> previous(static_cast<size_t>(a),0);
        for (int frame=1;frame<=t;++frame) {
            int k; cin >> k; unordered_set<string> held;
            for (int j=0;j<k;++j) { string command; cin >> command; held.insert(command); }
            vector<int> current(static_cast<size_t>(a),0);
            cout << frame;
            string line=to_string(frame);
            for (int j=0;j<a;++j) {
                auto it=mapping.find(actions[static_cast<size_t>(j)].second);
                if (it!=mapping.end() && held.count(it->second)) current[static_cast<size_t>(j)]=1;
                if (current[static_cast<size_t>(j)] && !previous[static_cast<size_t>(j)]) {
                    cout << ' ' << actions[static_cast<size_t>(j)].first;
                    line += " " + actions[static_cast<size_t>(j)].first;
                }
            }
            if (line==to_string(frame)) { cout << " -"; line += " -"; }
            cout << '\n';
            imageLines[static_cast<size_t>(tableIndex)].push_back(line);
            previous.swap(current);
        }
    }
    cout << "IDENTIQUES " << (imageLines[0]==imageLines[1] ? "OUI" : "NON") << '\n';
}
