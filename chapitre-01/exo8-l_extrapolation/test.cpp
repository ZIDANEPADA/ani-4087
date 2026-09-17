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

struct Pose {
    Vec3 position;
    Quat orientation;
};

// Opérateurs sur Vec3
Vec3 operator+(const Vec3& a, const Vec3& b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
Vec3 operator*(const Vec3& a, double s) { return {a.x*s, a.y*s, a.z*s}; }

// Produit scalaire (dot product)
double Dot(const Vec3& a, const Vec3& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

// --- Quaternions ---
Quat MultiplierQuat(const Quat& a, const Quat& b) {
    return {
        a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
        a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
        a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w,
        a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z
    };
}

// Extrapole une pose dans le futur à partir de ses vitesses linéaire et angulaire
Pose Extrapoler(const Pose& pose, const Vec3& vitesseLineaire, const Vec3& vitesseAngulaire, double dt) {
    Vec3 nouvellePosition = pose.position + vitesseLineaire * dt;

    double norme = std::sqrt(Dot(vitesseAngulaire, vitesseAngulaire));
    Quat nouvelleOrientation = pose.orientation;

    if (norme > 1e-12) { // évite la division par zéro si la vitesse angulaire est nulle
        Vec3 axe = vitesseAngulaire * (1.0 / norme);
        double angle = norme * dt;
        Quat delta = {
            axe.x * std::sin(angle/2),
            axe.y * std::sin(angle/2),
            axe.z * std::sin(angle/2),
            std::cos(angle/2)
        };
        nouvelleOrientation = MultiplierQuat(delta, pose.orientation);
    }
    // si norme <= 1e-12, l'orientation reste inchangée : c'est le cas traité "sans diviser par zéro"

    return { nouvellePosition, nouvelleOrientation };
}

int main() {
    Pose pose = { {0,0,0}, {0,0,0,1} }; // à l'origine, sans rotation

    Vec3 vitesseLineaire = {1, 0, 0};   // avance à 1 m/s sur X
    Vec3 vitesseAngulaire = {0, 1, 0};  // tourne à 1 rad/s autour de Y
    double dt = 0.1;

    Pose nouvellePose = Extrapoler(pose, vitesseLineaire, vitesseAngulaire, dt);

    cout << fixed << setprecision(6);
    cout << "Position   : " << nouvellePose.position.x << " " << nouvellePose.position.y << " " << nouvellePose.position.z << "\n";
    cout << "Orientation: " << nouvellePose.orientation.x << " " << nouvellePose.orientation.y << " " << nouvellePose.orientation.z << " " << nouvellePose.orientation.w << "\n";

    return 0;
}