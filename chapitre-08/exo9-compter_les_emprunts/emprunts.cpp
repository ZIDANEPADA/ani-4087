#include <iostream>
#include <string>
using namespace std;
int main(){int n,N;if(!(cin>>n>>N))return 0;int ok=0,ref=0,release=0,firstLeak=0;bool held=false;for(int t=1;t<=N;++t){string mode;cin>>mode;if(held){++ref;cout<<t<<" BLOQUEE\n";continue;}++ok;held=true;if(mode=="sortie"){cout<<t<<" FUITE\n";if(firstLeak==0)firstLeak=t;}else if(mode=="double"){++ref;cout<<t<<" DOUBLE\n";held=false;++release;}else{cout<<t<<" OK\n";held=false;++release;}}cout<<"REUSSIES "<<ok<<"\nREFUSEES "<<ref<<"\nLIBERATIONS "<<release<<"\nECART "<<ok-release<<'\n';if(firstLeak==0)cout<<"PREMIERE FUITE AUCUNE\n";else cout<<"PREMIERE FUITE "<<firstLeak<<'\n';}
