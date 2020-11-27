//This is an implementation of the money splitwise algorithm.
#include<iostream>
#include<set>
#include<map>
using namespace std;

class person_compare{
    public:
    bool operator()(pair<string,int>p1,pair<string,int>p2){
            return p1.second<p2.second;
    }
};


int main(){

    int no_of_transactions,friends;  //friends=vertices of graph, no_of_transactions=edges of graph
    cin>>no_of_transactions>>friends;

    string x,y;
    int amount; // we are making 3 variables where x gives y some amount.

    map<string,int> net;
    
    while(no_of_transactions--){
       cin>>x>>y>>amount;
        if(net.count(x)==0){
            net[x]=0;
        }
        if(net.count(y)==0){
            net[y]=0;
        }


        net[x]-=amount;
        net[y]+=amount;
    }


    multiset<pair<string,int>,person_compare >m;


    for(auto p:net){
        string person=p.first;
        int amount=p.second;

        if(net[person]!=0){
            m.insert(make_pair(person,amount));

        }
    }

    int count=0;
    //we will pop out two friends from left and right and try to settle them.
    while(!m.empty()){
        auto left=m.begin();
        auto right=prev(m.end());
        
        int debit= left->second;
        string debit_person=left->first;
        int credit= right->second;
        string credit_person=right->first;

        m.erase(left);
        m.erase(right);

        int settlement_amount=min(-debit,credit);
        count++;
        debit+=settlement_amount;
        credit-=settlement_amount;

        cout<<debit_person<<" will pay "<<settlement_amount<<" to "<<credit_person<<endl;


        if(debit!=0){
            m.insert(make_pair(debit_person,debit));
        }
        if(credit!=0){
            m.insert(make_pair(credit_person,credit));
        }
    }
    cout<<"Number of transactions:"<<count;
return 0;
}