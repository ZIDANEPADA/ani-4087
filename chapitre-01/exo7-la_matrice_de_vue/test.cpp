#include <iostream>
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

// Convertit une pose en matrice 4x4 (colonne-major, 16 doubles)
void PoseVersMatrice(const Pose& pose, double m[16]) {
    double x=pose.orientation.x, y=pose.orientation.y, z=pose.orientation.z, w=pose.orientation.w;
    m[0]=1-2*(y*y+z*z); m[1]=2*(x*y+z*w);   m[2]=2*(x*z-y*w);   m[3]=0;
    m[4]=2*(x*y-z*w);   m[5]=1-2*(x*x+z*z); m[6]=2*(y*z+x*w);   m[7]=0;
    m[8]=2*(x*z+y*w);   m[9]=2*(y*z-x*w);   m[10]=1-2*(x*x+y*y);m[11]=0;
    m[12]=pose.position.x; m[13]=pose.position.y; m[14]=pose.position.z; m[15]=1;
}

// Inversion générale naive avec garde-fou "singulière -> identité"
// (volontairement fidèle au défaut décrit par le texte)
bool InverserMatriceGenerale(const double m[16], double out[16]) {
    double det = m[0]*(m[5]*m[10]-m[6]*m[9]) - m[4]*(m[1]*m[10]-m[2]*m[9]) + m[8]*(m[1]*m[6]-m[2]*m[5]);
    if (std::fabs(det) < 1e-9) {
        for (int i=0;i<16;i++) out[i] = (i%5==0) ? 1.0 : 0.0;
        return false;
    }
    return true;
}

int main() {
    Pose normale = { {1,2,3}, {0,0.7071,0,0.7071} };
    double m1[16]; PoseVersMatrice(normale, m1);

    Pose degeneree = { {1,2,3}, {0,0,0,0} };
    double m2[16]; PoseVersMatrice(degeneree, m2);

    double inv1[16], inv2[16];
    bool ok1 = InverserMatriceGenerale(m1, inv1);
    bool ok2 = InverserMatriceGenerale(m2, inv2);

    cout << "Pose normale, inversion reussie : " << ok1 << "\n";
    cout << "Pose degeneree, inversion reussie : " << ok2 << "\n";
    cout << "Matrice renvoyee pour la pose degeneree :\n";
    for (int i=0;i<16;i++) std::cout << inv2[i] << (i%4==3 ? "\n" : " ");
    return 0;
}