#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(){int n,N;if(!(cin>>n>>N))return 0;int next=0,held=-1,last=-1;bool drawn=false,fresh=false;int submitted=0,refused=0,outside=0;vector<bool> did(n,false);for(int k=0;k<N;++k){string op;cin>>op;if(op=="acquire"){if(held!=-1){cout<<"ACQUIRE REFUSE\n";++refused;}else{held=next;drawn=false;cout<<"ACQUIRE "<<held<<'\n';}}else if(op=="draw"){if(held==-1){cout<<"DRAW HORS EMPRUNT\n";++outside;}else{cout<<"DRAW "<<held<<'\n';drawn=true;}}else if(op=="release"){if(held==-1){cout<<"RELEASE REFUSE\n";++refused;}else{last=held;did[last]=drawn;next=(next+1)%n;held=-1;fresh=true;cout<<"RELEASE OK\n";}}else if(op=="submit"){if(held!=-1){cout<<"SUBMIT REFUSE EMPRUNTEE\n";++refused;}else if(!fresh){cout<<"SUBMIT REFUSE RIEN\n";++refused;}else{cout<<"SUBMIT "<<last<<(did[last]?"":" VIDE")<<'\n';++submitted;fresh=false;}}}cout<<"SOUMISES "<<submitted<<"\nREFUS "<<refused<<"\nHORS EMPRUNT "<<outside<<'\n';}
