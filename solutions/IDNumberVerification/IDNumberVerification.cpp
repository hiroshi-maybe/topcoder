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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

/*
 
 11/19/2017
 
 14:45-15:14 system test passed (317.11 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+583
  - http://kmjp.hatenablog.jp/entry/2013/06/20/1000
  - http://torus711.hatenablog.com/entry/20130618/p3
  - http://emkcsharp.hatenablog.com/entry/SRM583/IDNumberVerification
 
 Summary:
  - Just implementation problem
 
 */
bool leapy(int y) {
  bool A=(y%4==0)&&(y%100!=0);
  bool B=(y%400==0);
  return A||B;
}

int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
bool dayok(int m, int d, bool isleap) {
  if(m!=2||!isleap) return 0<d&&d<=days[m-1];
  return 0<d&&d<=29;
}

bool dateok(string D) {
  int y=stoi(D.substr(0,4)),m=stoi(D.substr(4,2)),d=stoi(D.substr(6,2));
  if(y<1900) return false;
  if(y>2011) return false;
  if(m<1||m>12) return false;
  return dayok(m,d,leapy(y));
}

int checksum(string S) {
  LL a=0;
  REP(i,17) {
    a+=(S[i]-'0')*(1LL<<(17-i)),a%=11;
  }
  return (1+11-a)%11;
}

class IDNumberVerification {
  public:
  string no="Invalid",m="Male",f="Female";
  string zero="000";
  string gender(string SQ) {
    return (SQ.back()-'0')%2?m:f;
  }
  string verify(string id, vector<string> DD) {
    unordered_set<string> D(DD.begin(),DD.end());
    char CS=id.back();
    string S=id.substr(0,17);
    string R=S.substr(0,6),BD=S.substr(6,8), SQ=S.substr(14,3);
    if(D.count(R)==0) return no;
    if(!dateok(BD)) return no;
    if(SQ==zero) return no;
    
    int cs=checksum(S);
    if(cs==10&&CS=='X') return gender(SQ);
    if(cs==CS-'0') return gender(SQ);
    return no;
  }
};

// CUT begin
ifstream data("IDNumberVerification.sample");

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

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
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

bool do_test(string id, vector<string> regionCodes, string __expected) {
    time_t startClock = clock();
    IDNumberVerification *instance = new IDNumberVerification();
    string __result = instance->verify(id, regionCodes);
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
        string id;
        from_stream(id);
        vector<string> regionCodes;
        from_stream(regionCodes);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(id, regionCodes, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1511131515;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "IDNumberVerification (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
