#include <fstream> // for greed plugin
#include <iostream>
#include <algorithm> // max,min
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;

// type alias
typedef long long LL;

typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

// note that the last empty element is trimmed
vector<string> split(const string &s, char c) {
  vector<string> res;
  
  istringstream ss(s);
  string token;
  while(getline(ss,token,c)) {
    res.push_back(token);
  }
  
  return res;
}

/**
 
 7/17/2017
 
 8:25-8:37 passed system test (214.88 pt)
 
 Many people are using sort
 - https://community.topcoder.com/stat?c=problem_solution&rm=329116&rd=16775&pm=14373&cr=40466021
 - https://community.topcoder.com/stat?c=problem_solution&rm=329118&rd=16775&pm=14373&cr=40271137
 - https://community.topcoder.com/stat?c=problem_solution&rm=329126&rd=16775&pm=14373&cr=40466077
 
 Brute force
 - https://community.topcoder.com/stat?c=problem_solution&rm=329118&rd=16775&pm=14373&cr=40455611
 
 23:25 add simpler sort solution
 
 */

class Ropestring {
public:
  string makerope(string s) {
    vector<string> ls = split(s,'.');
    VI es,os;
    FORR(l,ls) {
      if(l.empty()) continue;
      if(SZ(l)&1) os.push_back(SZ(l));
      else es.push_back(SZ(l));
    }
    
    sort(os.begin(),os.end(),std::greater<int>());
    sort(es.begin(),es.end(),std::greater<int>());
    
    string res="";
    FORR(n,es) res.append(n,'-'), res.push_back('.');
    FORR(n,os) res.append(n,'-'), res.push_back('.');
    
    if(SZ(res)>SZ(s)) res.pop_back();
    while(SZ(res)<SZ(s)) res.push_back('.');
    return res;
  }
};

class Ropestring_org {
  public:
  string makerope(string s) {
    vector<string> ls = split(s,'.');
    map<int,int> M;
    FORR(l,ls) if(SZ(l)) M[SZ(l)]++;
    
    string t="";
    for(auto rit=M.rbegin(); rit!=M.rend(); ++rit) {
      if(((rit->first)&1)==0) {
        int n=rit->second;
        while(n-->0) {
          t.append(rit->first,'-');
          t.push_back('.');
        }
      }
    }
    for(auto rit=M.rbegin(); rit!=M.rend(); ++rit) {
      if(((rit->first)&1)==1) {
        int n=rit->second;
        while(n-->0) {
          t.append(rit->first,'-');
          t.push_back('.');
        }
      }
    }
    assert(SZ(t)<=SZ(s)+1);
    if(SZ(t)>SZ(s)) t.pop_back();
    while(SZ(t)<SZ(s)) t.push_back('.');
    
    return t;
  }
};

// CUT begin
ifstream data("Ropestring.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string s, string __expected) {
    time_t startClock = clock();
    Ropestring *instance = new Ropestring();
    string __result = instance->makerope(s);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        string s;
        from_stream(s);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500305090;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "Ropestring (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
