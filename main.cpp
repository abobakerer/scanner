#include <bits/stdc++.h>
 #include <fstream>

using namespace std;

#define IO ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define ll long long
#define YES(x) (x)?cout<<"YES"<<endl : cout<<"NO"<<endl
#define FOR(i,n,s) for(int i=s;i<n;i++)
#define sep " | "
#define vecll vector<ll>
#define pb(x) push_back(x)
#define all(v) v.begin(),v.end()
#define sz(x) x.size()
void output(string s) {
    #ifndef ONLINE_JUDGE
        cout << s;
    #endif
}

vector<string> split(string line,char dil){
    vector<string> res;
    string s;
    int st = 0;
    for(int i=0 ; i<line.size() ; i++){
        if(line[i] == dil){
            s = line.substr(st,i-st);
            res.push_back(s);
            s = "";
            st = i+1;
        }
    }
    res.push_back(line.substr(st));
    return res;
}



int main(){
    fstream in,out;
    //===============================================
    //take all states
    in.open("automaton.txt",ios::in);
    vector<string> states,finalStates,deadStates;
    string startState;
    if(in.is_open()){
        int countt=1;
        string line;
        while(getline(in,line)){
            if(countt == 1){
                states = split(line,' ');
            }
            else if(countt == 2){
                startState = line;
            }
            else if(countt == 3){
                finalStates = split(line,' ');
            }
            else if(countt == 4){
                deadStates = split(line,' ');
            }
        countt++;
        }
        in.close();
    }
    /*
    cout<<"All States : "<<endl;
    for(int i=0;i<states.size();i++)
        cout<<states[i]<<" | ";
    cout<<endl;

    cout<<"Final States : "<<endl;
    for(int i=0;i<finalStates.size();i++)
        cout<<finalStates[i]<<" | ";
    cout<<endl;

    cout<<"Start States : "<<endl;
    cout<<startState<<endl;

    cout<<"Dead States : "<<endl;
    for(int i=0;i<deadStates.size();i++)
        cout<<deadStates[i]<<" | ";
    cout<<endl;
    */
    //===============================================
    // take tokens
    in.open("tokens.txt",ios::in);
    map<string,string> tokens;
    if(in.is_open()){
        string s;
        while(getline(in,s)){
            vector<string> t = split(s,' ');
            tokens[t[0]] = t[1];
        }
        in.close();
    }
    /*
    for(auto token : tokens)
        cout<<token.first<<" | "<<token.second<<endl;
    */

    //===============================================
    // transition table
    in.open("transition.txt",ios::in);
    map<pair<string,string>,string> transitionTable;
    if(in.is_open()){
        string s;
        while(getline(in,s)){
            vector<string> t = split(s,' ');
            transitionTable[{t[0],t[1]}] = t[2];
        }
        in.close();
    }
    /*
    for(auto rule : transitionTable)
        cout<<rule.first.first<<" , "<<rule.first.second<<" -> "<<rule.second<<endl;
    */

    //===============================================
    // Testing input
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    if(in.is_open()){
        string s;
        string currState = startState;
        while(getline(in,s)){
            string pr="";
            for(int i=0;i<s.size();i++){

                string str(1,s[i]);
                pair<string,string> key = {currState,str};
                pr += str;

                if(deadStates.find(currState) != deadStates.end()){
                    cout<<"This String Is Invalid ! "<<endl;
                    break;
                }

                if(transitionTable.find(key) != transitionTable.end()){
                    currState = transitionTable[key];
                }
                else{
                    cout<<"ERROR This Not accepted in this scanner"<<endl;
                }

                if(find(all(finalStates),currState) != finalStates.end()){
                    string cToken = pr + "  |  " + tokens[currState];
                    cout<<cToken<<endl;
                    out << cToken <<endl;
                    currState = startState;
                    pr = "";
                }
            }
        }
        in.close();
        out.close();
    }



    return 0;
}
