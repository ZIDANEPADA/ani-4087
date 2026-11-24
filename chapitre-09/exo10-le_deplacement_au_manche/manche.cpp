#include <iostream>
#include <string>
using namespace std;
int main() {
    long long speed; int t; if (!(cin >> speed >> t)) return 0;
    long long worldX=0, worldZ=0; int diagonals=0;
    for (int frame=1;frame<=t;++frame) {
        int k,n; cin >> k >> n;
        int right=0,left=0,up=0,down=0;
        for (int i=0;i<n;++i) {
            string arrow; cin >> arrow;
            if (arrow=="F_DROITE") right=1;
            else if (arrow=="F_GAUCHE") left=1;
            else if (arrow=="F_HAUT") up=1;
            else if (arrow=="F_BAS") down=1;
        }
        int x=right-left, y=up-down;
        if (x!=0 && y!=0) ++diagonals;
        int ax=0,az=-1,dx=1,dz=0;
        if (k==1) { ax=-1; az=0; dx=0; dz=-1; }
        else if (k==2) { ax=0; az=1; dx=-1; dz=0; }
        else if (k==3) { ax=1; az=0; dx=0; dz=1; }
        worldX += speed * (y*ax + x*dx);
        worldZ += speed * (y*az + x*dz);
        cout << frame << ' ' << x << ',' << y << ' ' << worldX << ' ' << worldZ << '\n';
    }
    cout << "DECALAGE " << worldX << ' ' << worldZ << '\n' << "DIAGONALES " << diagonals << '\n';
}
