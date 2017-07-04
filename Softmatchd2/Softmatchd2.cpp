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
/**
 
 7/4/2017
 
 10:51-11:37, 13:50-14:05 time up
 15:19 read https://community.topcoder.com/stat?c=problem_solution&rd=16853&rm=329755&cr=23309657&pm=14542
 read https://community.topcoder.com/stat?c=problem_solution&rm=329746&rd=16853&pm=14542&cr=40545885
 
 16:19 cannot understand solution at all
 16:35 copy solution
 */

int dp[51];

class Softmatchd2 {
  public:
  int count(string S, string P) {
    memset(dp,0,sizeof(dp));
    int SN=SZ(S), PN=SZ(P);
//    dump2(S,P);
//    dump2(SN,PN);
    
    dp[PN-1]=1;
    FOR(i,PN,SN) {
      for(int j=i-1; j>=i-PN; --j) {
        int l=i-PN+1,h=j;
        int ok=true;
        for(int k=l; k<=h; ++k) {
//          dump3(i,j,k);
          char c1,c2;
          c1=c2=S[k];
//          dump2(k,S[k]);
          int p1=P[k-(j-PN+1)]-'0';
          int p2=P[k-(i-PN+1)]-'0';
//          dump4(k-(j-PN+1),p1,k-(i-PN+1),p2);
          
          if(c1=='a'&&p1>=2) c1='A';
          if(c1=='b'&&p1%2) c1='B';
          if(c2=='a'&&p2>=2) c2='A';
          if(c2=='b'&&p2%2) c2='B';
          
          if(c1!=c2) { ok=false; break; }
        }
        if (ok) dp[i]=max(dp[i],dp[j]+1);
      }
    }
    
    return *max_element(dp,dp+SN);
  }
};

// CUT begin
ifstream data("Softmatchd2.sample");

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

bool do_test(string S, string pattern, int __expected) {
    time_t startClock = clock();
    Softmatchd2 *instance = new Softmatchd2();
    int __result = instance->count(S, pattern);
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
        string S;
        from_stream(S);
        string pattern;
        from_stream(pattern);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, pattern, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499190676;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Softmatchd2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
