#include <iostream>
#include <string>
using namespace std;
int main(){int N;if(!(cin>>N))return 0;unsigned long long current=0,stored=0,next=101;int frame=0,a=0,b=0,c=0;for(int i=0;i<N;++i){string op;cin>>op;if(op=="cible"){int w,h;cin>>w>>h;current=next++;cout<<"CIBLE "<<current<<' '<<w<<' '<<h<<'\n';}else if(op=="chaine")stored=0;else if(op=="enregistre")stored=current;else if(op=="image"){++frame;if(stored==0){cout<<"IMAGE "<<frame<<" NOIR\n";++b;}else if(stored==current){cout<<"IMAGE "<<frame<<" AFFICHE "<<stored<<'\n';++a;}else{cout<<"IMAGE "<<frame<<" PERIMEE "<<stored<<'\n';++c;}}}cout<<"AFFICHEES "<<a<<"\nNOIRES "<<b<<"\nPERIMEES "<<c<<'\n';}
