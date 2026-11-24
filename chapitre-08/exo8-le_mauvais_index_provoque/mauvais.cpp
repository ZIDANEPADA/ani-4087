#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main(){int n,T;long long x0,v;if(!(cin>>n>>T>>x0>>v))return 0;string modes;cin>>modes;vector<int> slot(n,0);int next=0,minJump=0,maxJump=0,count=0;bool hasPrev=false;long long prev=0;for(int t=1;t<=T;++t){int borrowed=next;slot[borrowed]=t;int submitted=0;if(modes[t-1]=='P')submitted=(next+n-1)%n;next=(next+1)%n;if(modes[t-1]=='D')submitted=(next+n-1)%n;else if(modes[t-1]=='A')submitted=borrowed;int f=slot[submitted];if(f==0)cout<<t<<" NOIR -\n";else{long long pos=x0+v*f;if(!hasPrev||t==1)cout<<t<<' '<<pos<<" -\n";else{long long jump=pos-prev;cout<<t<<' '<<pos<<' '<<jump<<'\n';if(count==0)minJump=maxJump=static_cast<int>(jump);else{minJump=min(minJump,static_cast<int>(jump));maxJump=max(maxJump,static_cast<int>(jump));}++count;}hasPrev=true;prev=pos;}}if(count==0)cout<<"SAUTS AUCUN\n";else cout<<"SAUT MIN "<<minJump<<"\nSAUT MAX "<<maxJump<<"\nTREMBLE "<<(minJump!=maxJump?"OUI":"NON")<<'\n';}
