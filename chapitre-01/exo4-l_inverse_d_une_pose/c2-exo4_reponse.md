#include <iostream>
#include <iomanip>

using namespace std;


struct Quat {
    double x, y, z, w;
};
struct Vec3 {
    double x, y, z;

    Vec3 operator-() const {
    return Vec3{ -x, -y, -z };
}
};

struct Pose {
    Vec3 position;
    Quat orientation;
};

Vec3 Tourner(const Quat& q, const Vec3& v);

Quat Conjuguer(const Quat& q) {
    return { -q.x, -q.y, -q.z, q.w };
}

Pose Inverser(const Pose& pose) {
    Quat conj = Conjuguer(pose.orientation);
    Vec3 posInverse = Tourner(conj, -pose.position);
    return { posInverse, conj };
}

Vec3 operator+(const Vec3& a, const Vec3& b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
Vec3 operator-(const Vec3& a) { return {-a.x, -a.y, -a.z}; }
Vec3 operator-(const Vec3& a, const Vec3& b) { return {a.x-b.x, a.y-b.y, a.z-b.z}; }

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


Vec3 AppliquerPose(const Pose& pose, const Vec3& point) {
    return Tourner(pose.orientation, point) + pose.position;
}

Vec3 AppliquerPoseInversee(const Pose& pose, const Vec3& point) {
    return Tourner(pose.orientation, point + pose.position);
}

int main() {
    Pose pose;
    cin >> pose.position.x >> pose.position.y >> pose.position.z;
    cin >> pose.orientation.x >> pose.orientation.y >> pose.orientation.z >> pose.orientation.w;

    Vec3 point;
    cin >> point.x >> point.y >> point.z;

    Vec3 transforme = AppliquerPose(pose, point);
    Pose inverse = Inverser(pose);
    Vec3 retour = AppliquerPose(inverse, transforme);

    Vec3 ecart = retour - point; // à définir : soustraction de Vec3
    cout << fixed << setprecision(6);
    cout << "Ecart : " << ecart.x << " " << ecart.y << " " << ecart.z << "\n";
    return 0;
}


L'ecart obtenu est :
- Ecart : **505160.000000 -215904.000000 -175768.000000**