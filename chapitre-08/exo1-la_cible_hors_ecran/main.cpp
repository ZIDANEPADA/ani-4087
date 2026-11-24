#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;
struct Cible{int w,h;};
int main(){int L,H,F,N;if(!(cin>>L>>H>>F>>N))return 0;string s;getline(cin,s);bool on=false,blocked=false;int zw=L,zh=H,dest=0,images=0;vector<Cible> c;vector<bool> busy(F,false);
for(int i=0;i<N;++i){getline(cin,s);if(blocked)continue;if(s.rfind("allume ",0)==0){if(s.substr(7)=="OFFSCREEN")on=true;}else if(s.rfind("cible ",0)==0){int w,h;sscanf(s.c_str(),"cible %d %d",&w,&h);if(!on)cout<<"CIBLE NULLE\n";else{c.push_back({w,h});cout<<"CIBLE "<<c.size()<<' '<<w<<' '<<h<<'\n';}}else if(s.rfind("vers ",0)==0){int k;sscanf(s.c_str(),"vers %d",&k);if(k<0||k>(int)c.size())cout<<"VERS REFUSE\n";else dest=k;}else if(s.rfind("taille ",0)==0)sscanf(s.c_str(),"taille %d %d",&zw,&zh);else if(s=="image"){int t=images+1,slot=(t-1)%F;if(busy[slot]){cout<<"BLOQUE "<<t<<'\n';blocked=true;continue;}++images;if(dest==0)cout<<"IMAGE "<<t<<" FENETRE\n";else{cout<<"IMAGE "<<t<<" CIBLE "<<dest<<'\n';auto q=c[dest-1];if(zw>q.w||zh>q.h)busy[slot]=true;}}}
cout<<"IMAGES "<<images<<"\nETAT "<<(blocked?"BLOQUE":"LIBRE")<<'\n';}
