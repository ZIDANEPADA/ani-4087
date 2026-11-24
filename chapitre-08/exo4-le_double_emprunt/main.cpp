#include <iostream>
#include <string>
#include <array>
#include <cstdint>
using namespace std;
int main(){int n,N;uint32_t v;if(!(cin>>n>>v>>N))return 0;array<uint32_t,26>x;x.fill(v);int next=0,held=-1;for(int i=0;i<N;++i){string op;cin>>op;if(op=="acquire"){char c;cin>>c;int j=c-'a';bool ok=held==-1;if(ok){x[j]=static_cast<uint32_t>(next);held=next;}cout<<"ACQUIRE "<<(ok?"VRAI":"FAUX")<<' '<<c<<' '<<x[j]<<'\n';}else if(op=="release"){if(held==-1)cout<<"RELEASE FAUX\n";else{next=(next+1)%n;held=-1;cout<<"RELEASE VRAI\n";}}else if(op=="last")cout<<"LAST "<<(next+n-1)%n<<'\n';}cout<<"EMPRUNTEE "<<(held==-1?"NON":"OUI")<<"\nPROCHAINE "<<next<<'\n';}
