#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){int K;if(!(cin>>K))return 0;for(int s=0;s<K;++s){int n,L,T;cin>>n>>L>>T;vector<int> painted(T+1);int conflicts=0;cout<<"CIBLES "<<n<<' '<<L;for(int u=1;u<=T;++u){int image=(u-1)%n;painted[u]=image;cout<<' '<<image;for(int j=max(1,u-L);j<u;++j)if(painted[j]==image){++conflicts;break;}}cout<<"\nCONFLITS "<<n<<' '<<L<<' '<<conflicts<<'\n';}}
