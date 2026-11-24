#include <iostream>
#include <string>
using namespace std;
int main(){int N;if(!(cin>>N))return 0;int a=0,o=0,g=0,d=0,s=0;for(int i=0;i<N;++i){int w,h,n,e;string name;cin>>w>>h>>n>>e>>name;string label=name=="-"?"SANS-NOM":name;if(w==0||h==0)cout<<"REFUSEE "<<label<<" TAILLE\n";else if(n==0||n>4)cout<<"REFUSEE "<<label<<" IMAGES\n";else{++a;o+=n;if(e==0)++g;else ++d;if(name=="-")++s;cout<<"CHAINE "<<label<<' '<<w<<' '<<h<<' '<<n<<' '<<(e==0?"GAUCHE":"DROIT")<<'\n';}}cout<<"ACCEPTEES "<<a<<"\nEMPLACEMENTS "<<4*a<<"\nOCCUPES "<<o<<"\nGAUCHE "<<g<<"\nDROIT "<<d<<"\nSANS NOM "<<s<<'\n';}
