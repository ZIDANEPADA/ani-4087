#include <iostream>
#include <iomanip>

using namespace std;

struct Vec3 {
    double x, y, z;
};

double Dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Avant()  { return { 0.0,  0.0, -1.0 }; }
Vec3 Haut()   { return { 0.0,  1.0,  0.0 }; }
Vec3 Droite() { return { 1.0,  0.0,  0.0 }; }

int main() {
    Vec3 p;
    cin >> p.x >> p.y >> p.z;

    cout << fixed << setprecision(4);
    cout << Dot(p, Avant())  << "\n";
    cout << Dot(p, Haut())   << "\n";
    cout << Dot(p, Droite()) << "\n";
    return 0;
}

les valeurs obtenues sont :
8
4
6
-6.0000
4.0000
8.0000