#include <iostream>
#include <iomanip>

using namespace std;


struct Quat {
    double x, y, z, w;
};
struct Vec3 {
    double x, y, z;
};



Vec3 operator+(const Vec3& a, const Vec3& b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
Vec3 operator-(const Vec3& a) { return {-a.x, -a.y, -a.z}; }

// Applique une rotation à un vecteur (produit quaternionique q * v * conj(q))
Vec3 Tourner(const Quat& q, const Vec3& v) {
    Vec3 qv = { q.x, q.y, q.z };
    Vec3 t = {
        2 * (qv.y * v.z - qv.z * v.y),
        2 * (qv.z * v.x - qv.x * v.z),
        2 * (qv.x * v.y - qv.y * v.x)
    };
    return {
        v.x + q.w * t.x + (qv.y * t.z - qv.z * t.y),
        v.y + q.w * t.y + (qv.z * t.x - qv.x * t.z),
        v.z + q.w * t.z + (qv.x * t.y - qv.y * t.x)
    };
}

struct Pose {
    Vec3 position;
    Quat orientation;
};


Vec3 AppliquerPoseInversee(const Pose& pose, const Vec3& point) {
    return Tourner(pose.orientation, point + pose.position);
}

int main() {

    Pose pose;
    cin >> pose.position.x >> pose.position.y >> pose.position.z;
    cin >> pose.orientation.x >> pose.orientation.y >> pose.orientation.z >> pose.orientation.w;

    Vec3 point;
    cin >> point.x >> point.y >> point.z;

    Vec3 resultat = AppliquerPoseInversee(pose, point);
    cout << fixed << setprecision(4);
    cout << resultat.x << " " << resultat.y << " " << resultat.z << "\n";
    return 0;
}