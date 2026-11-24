#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <cstdint>
#include <climits>
using namespace std;
int main(){size_t n;int N;if(!(cin>>n>>N))return 0;vector<uint64_t> slots(n,0);unordered_set<uint64_t> live;int dead=0,large=0;for(int k=0;k<N;++k){string op;cin>>op;if(op=="cree"){uint64_t h;cin>>h;live.insert(h);}else if(op=="detruit"){uint64_t h;cin>>h;live.erase(h);}else if(op=="set"){uint64_t i,h;cin>>i>>h;if(i>=n)cout<<"SET IGNORE "<<i<<'\n';else{slots[static_cast<size_t>(i)]=h;if(h>UINT32_MAX)++large;}}else if(op=="get"){uint64_t i;cin>>i;uint64_t h=i<n?slots[static_cast<size_t>(i)]:0;if(h==0)cout<<"GET "<<i<<" 0 VIDE\n";else if(live.count(h))cout<<"GET "<<i<<' '<<h<<" VIVANTE\n";else{cout<<"GET "<<i<<' '<<h<<" MORTE\n";++dead;}}}cout<<"MORTES "<<dead<<"\nLARGES "<<large<<'\n';}
