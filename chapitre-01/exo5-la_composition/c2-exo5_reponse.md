#include <iostream>
#include <iomanip>

using namespace std;

struct Quat {
    double x, y, z, w;
};

struct Vec3 {
    double x, y, z;
};

struct Pose {
    Vec3 position;
    Quat orientation;
};

// Opérateurs sur Vec3
Vec3 operator+(const Vec3& a, const Vec3& b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
Vec3 operator-(const Vec3& a) { return {-a.x, -a.y, -a.z}; }
Vec3 operator-(const Vec3& a, const Vec3& b) { return {a.x-b.x, a.y-b.y, a.z-b.z}; }

// Quaternions
Quat MultiplierQuat(const Quat& a, const Quat& b) {
    return {
        a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
        a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
        a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w,
        a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z
    };
}

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

// Transforme un point du repère local de "pose" vers le repère parent
Vec3 AppliquerPose(const Pose& pose, const Vec3& point) {
    return Tourner(pose.orientation, point) + pose.position;
}

// Compose deux poses : le résultat représente "enfant" exprimé dans le repère de "parent"
Pose Composer(const Pose& parent, const Pose& enfant) {
    Quat orientation = MultiplierQuat(parent.orientation, enfant.orientation);
    Vec3 position = AppliquerPose(parent, enfant.position);
    return { position, orientation };
}

int main() {
    Pose a, b;
    cin >> a.position.x >> a.position.y >> a.position.z;
    cin >> a.orientation.x >> a.orientation.y >> a.orientation.z >> a.orientation.w;

    cin >> b.position.x >> b.position.y >> b.position.z;
    cin >> b.orientation.x >> b.orientation.y >> b.orientation.z >> b.orientation.w;

    Vec3 p;
    cin >> p.x >> p.y >> p.z;

    Pose c = Composer(a, b);
    Vec3 direct = AppliquerPose(c, p);
    Vec3 enChaine = AppliquerPose(a, AppliquerPose(b, p));

    Vec3 ecart = direct - enChaine;

    cout << fixed << setprecision(6);
    cout << "Direct : " << direct.x << " " << direct.y << " " << direct.z << "\n";
    cout << "Chaine : " << enChaine.x << " " << enChaine.y << " " << enChaine.z << "\n";
    cout << "Ecart  : " << ecart.x << " " << ecart.y << " " << ecart.z << "\n";
    return 0;
}

Les points obtenus sont:
- Direct : **-5555.000000 -17214.000000 15177.000000**
- Chaine : **19557.000000 -29770.000000 11561.000000**
- Ecart  : **-25112.000000 12556.000000 3616.000000**