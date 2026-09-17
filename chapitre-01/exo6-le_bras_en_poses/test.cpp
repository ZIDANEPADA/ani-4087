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
Vec3 operator*(const Vec3& a, double s) { return {a.x*s, a.y*s, a.z*s}; }

// Directions de base (repère local)

Vec3 Avant() { return {0, 0, 1}; }
Vec3 Haut()  { return {0, 1, 0}; }
Vec3 Droite(){ return {1, 0, 0}; }

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

// Compose deux poses : "enfant" exprimé dans le repère de "parent"
Pose Composer(const Pose& parent, const Pose& enfant) {
    Quat orientation = MultiplierQuat(parent.orientation, enfant.orientation);
    Vec3 position = AppliquerPose(parent, enfant.position);
    return { position, orientation };
}

int main() {
    const double LONGUEUR_BRAS = 0.30;
    const double LONGUEUR_AVANT_BRAS = 0.25;

    Pose epaule = { {0,0,0}, {0,0,0,1} }; // à l'origine, sans rotation

    // Le coude est à "un bras" de distance devant l'épaule, dans son repère local
    Pose coudeLocal = { Avant() * LONGUEUR_BRAS, {0,0,0,1} };
    // La main est à "un avant-bras" de distance devant le coude, dans son repère local
    Pose mainLocale = { Avant() * LONGUEUR_AVANT_BRAS, {0,0,0,1} };

    Pose coudeMonde = Composer(epaule, coudeLocal);
    Pose mainMonde = Composer(coudeMonde, mainLocale);

    cout << fixed << setprecision(4);
    cout << "Coude : " << coudeMonde.position.x << " " << coudeMonde.position.y << " " << coudeMonde.position.z << "\n";
    cout << "Main  : " << mainMonde.position.x << " " << mainMonde.position.y << " " << mainMonde.position.z << "\n";

    // Test : on fait tourner l'épaule de 90° autour de Haut()
    epaule.orientation = {0, 0.7071, 0, 0.7071};
    coudeMonde = Composer(epaule, coudeLocal);
    mainMonde = Composer(coudeMonde, mainLocale);
    cout << "Main apres rotation epaule : " << mainMonde.position.x << " " << mainMonde.position.y << " " << mainMonde.position.z << "\n";

    return 0;
}