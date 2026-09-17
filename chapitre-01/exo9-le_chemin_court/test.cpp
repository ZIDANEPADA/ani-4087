#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Quat {
    double x, y, z, w;
};

struct Vec3 {
    double x, y, z;
};

// --- Opérateurs sur Vec3 ---
Vec3 operator*(const Vec3& a, double s) { return {a.x*s, a.y*s, a.z*s}; }

// --- Quaternions ---
Quat Conjuguer(const Quat& q) {
    return { -q.x, -q.y, -q.z, q.w };
}

Quat MultiplierQuat(const Quat& a, const Quat& b) {
    return {
        a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
        a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
        a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w,
        a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z
    };
}

// Calcule la vitesse angulaire moyenne nécessaire pour passer de q1 à q2 en dt secondes
Vec3 VitesseAngulaireMoyenne(Quat q1, Quat q2, double dt, bool forcerCheminCourt) {
    if (forcerCheminCourt) {
        double produit = q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
        if (produit < 0) {
            q2 = { -q2.x, -q2.y, -q2.z, -q2.w };
        }
    }
    Quat delta = MultiplierQuat(q2, Conjuguer(q1)); // rotation de q1 vers q2

    double w = delta.w;
    if (w > 1.0) w = 1.0;
    if (w < -1.0) w = -1.0;
    double angle = 2 * std::acos(w);
    double s = std::sqrt(1 - w*w);

    Vec3 axe;
    if (s < 1e-9) {
        axe = {1, 0, 0};
    } else {
        axe = {delta.x/s, delta.y/s, delta.z/s};
    }

    return axe * (angle / dt);
}

int main() {
    Quat q1 = {0, 0, 0, 1};           // pas de rotation
    Quat q2 = {0, 0.7071, 0, 0.7071}; // 90° autour de Y
    double dt = 0.1;

    Vec3 vitesse = VitesseAngulaireMoyenne(q1, q2, dt, true);

    cout << fixed << setprecision(6);
    cout << "Vitesse angulaire moyenne : " << vitesse.x << " " << vitesse.y << " " << vitesse.z << "\n";

    return 0;
}