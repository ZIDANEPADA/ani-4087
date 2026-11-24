#include <iostream>
#include <cstdint>
using namespace std;
int main(){int N;if(!(cin>>N))return 0;int bad=0,bs=0,bu=0;for(int i=0;i<N;++i){uint64_t n,r;cin>>n>>r;if(n==0||n>4){cout<<n<<' '<<r<<" REFUSEE\n";++bad;continue;}uint64_t next=r%n,good=(next+n-1)%n;int signedWrong=(static_cast<int>(next)-1)%static_cast<int>(n);uint32_t unsignedWrong=(static_cast<uint32_t>(next)-1u)%static_cast<uint32_t>(n);cout<<n<<' '<<r<<' '<<next<<' '<<good<<' '<<signedWrong<<' '<<unsignedWrong<<'\n';if(signedWrong!=static_cast<int>(good))++bs;if(unsignedWrong!=good)++bu;}cout<<"REFUSEES "<<bad<<"\nFAUX SIGNE "<<bs<<"\nFAUX NON SIGNE "<<bu<<'\n';}
