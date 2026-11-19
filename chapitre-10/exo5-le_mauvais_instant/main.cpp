#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main() {
    long long w;
    int T;
    cin >> w >> T;
    long long fausses = 0, pireCasque = 0, pireSimulateur = 0;
    for (int t = 1; t <= T; ++t) {
        long long P, S, A;
        char M;
        cin >> P >> S >> A >> M;
        long long poseSoumise = w * (M == 'R' ? P : S);
        long long poseRendu = w * P;
        long long casque = poseSoumise - poseRendu;
        long long simulateur = w * A - poseRendu;
        if (casque != 0) ++fausses;
        pireCasque = max(pireCasque, llabs(casque));
        pireSimulateur = max(pireSimulateur, llabs(simulateur));
        cout << t << " CASQUE " << casque << " SIMULATEUR " << simulateur << '\n';
    }
    cout << "FAUSSES " << fausses << '\n'
         << "PIRE CASQUE " << pireCasque << '\n'
         << "PIRE SIMULATEUR " << pireSimulateur << '\n';
    return 0;
}
