#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;
struct Point { long long x, y, z; };
Point transform(Point local, const Point& head, int k) {
    long long x = local.x, z = local.z;
    if (k == 1) { x = local.z; z = -local.x; }
    else if (k == 2) { x = -local.x; z = -local.z; }
    else if (k == 3) { x = -local.z; z = local.x; }
    return {head.x + x, head.y + local.y, head.z + z};
}
int nearest(const Point& p, const vector<Point>& objects) {
    long long best = numeric_limits<long long>::max(); int index = -1;
    for (size_t i = 0; i < objects.size(); ++i) {
        long long dx = objects[i].x-p.x, dy=objects[i].y-p.y, dz=objects[i].z-p.z;
        long long d=dx*dx+dy*dy+dz*dz;
        if (d <= 22500 && d < best) { best=d; index=static_cast<int>(i); }
    }
    return index;
}
void printPoint(const string& label, const Point& p) { cout << label << ' ' << p.x << ' ' << p.y << ' ' << p.z << '\n'; }
int main() {
    int h, m; if (!(cin >> h >> m)) return 0;
    vector<Point> heads(static_cast<size_t>(h)), objects(static_cast<size_t>(m));
    vector<int> angles(static_cast<size_t>(h));
    for (int i=0;i<h;++i) cin >> heads[static_cast<size_t>(i)].x >> heads[static_cast<size_t>(i)].y >> heads[static_cast<size_t>(i)].z >> angles[static_cast<size_t>(i)];
    for (auto& p:objects) cin >> p.x >> p.y >> p.z;
    for (int i=0;i<h;++i) {
        const Point& head=heads[static_cast<size_t>(i)]; int k=angles[static_cast<size_t>(i)];
        Point palmD=transform({180,-300,-250},head,k), aimD=transform({180,-250,-400},head,k);
        Point palmG=transform({-180,-300,-250},head,k), aimG=transform({-180,-250,-400},head,k);
        cout << "TETE " << i+1 << '\n';
        printPoint("PAUME D",palmD); printPoint("VISEE D",aimD); printPoint("PAUME G",palmG); printPoint("VISEE G",aimG);
        int p=nearest(palmD,objects), a=nearest(aimD,objects);
        cout << "SAISIE PAUME " << (p<0?"AUCUNE":to_string(p+1)) << '\n';
        cout << "SAISIE VISEE " << (a<0?"AUCUNE":to_string(a+1)) << '\n';
    }
    cout << "ECART " << static_cast<long long>(llround(sqrt(25000.0))) << '\n';
}
