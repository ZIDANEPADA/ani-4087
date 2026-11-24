#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
struct Setting { bool declared=false, written=false, env=false, read=false, getenv=false; };
int main() {
    int r; if (!(std::cin >> r) || r < 0) return 0;
    std::vector<std::string> order;
    std::unordered_map<std::string, Setting> settings;
    for (int i=0;i<r;++i) {
        std::string name, action; std::cin >> name >> action;
        if (!settings.count(name)) order.push_back(name);
        Setting& s=settings[name];
        if(action=="DECLARE") s.declared=true;
        else if(action=="ECRIT") s.written=true;
        else if(action=="ENV") s.env=true;
        else if(action=="LIT") s.read=true;
        else if(action=="GETENV") s.getenv=true;
    }
    int menu=0;
    for(const auto& name:order){
        const Setting& s=settings[name]; std::string cls;
        if(s.getenv) cls="CACHE";
        else if(!s.read) cls="FANTOME";
        else if(!s.written && !s.env) cls="CONSTANTE";
        else { cls="MENU"; ++menu; }
        std::cout<<name<<' '<<cls<<'\n';
    }
    std::cout<<"MENU "<<menu<<" SUR "<<order.size()<<'\n';
    return 0;
}
