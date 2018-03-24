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
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/23/2018
 
 8:45-8:58 analysis
 8:59-9:02 ACC (385.35 pt)
 
 It was straightforward to figure out that x (mod 10) matters.
 I just manually calculated smallest number of digits to achieve 10 digits.
 Just in case I verified my hand calculation by BFS.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+504.5
  - http://d.hatena.ne.jp/kusano_prog/20110518/1305699767
  - http://d.hatena.ne.jp/shioshiota/20110519/1305816898
  - http://mayokoex.hatenablog.com/entry/2015/06/09/133146
  - http://d.hatena.ne.jp/hotoku/20110519/1305818089
  - http://mainly-coding.blogspot.com/2011/05/topcoder-srm-507.html?m=0
 
 Missing piece in my manual calculation is sufficiency.
 I informally confirmed that larger count of numbers with less sum for specific digit cannot be there.
 However I'm not sure if I checked all the cases.
 
 Official editorial is showing that possible number of 4 and 7 is in range [0..9].
 Modular arithmetic is powerful because we can map large numbers to specific range.
 
 Let's look at num4 = 11 (=4+7) > 10.
 
 11 * 4 (mod 10) = 11 (mod 10) * 4 (mod 10) = 1 * 4 (mod 10) = 1 (mod 10) * 4 (mod 10)
 We can show num4 = 1 is always better choice for us because of modular arithmetic.
 Thus we can brute-force only num4 = [0..9] and num7 = [0..9]
 
 Summary:
  - I solved quickly though, my proof was too weak.
  - I need more training about modular arithmetic.
   - I'm again surprised how useful modular arithmetic is
   - It's powerful to show proof is sufficient. Search space is reduced to [0..N-1] by (mod N)
 
 */

class TheNumbersWithLuckyLastDigit {
public:
  int find(int n) {
    for(int tot=1; tot<=18; ++tot) {
      for(int n4=0; n4<=tot; ++n4) {
        int n7=tot-n4;
        int x=n4*4+n7*7;
        if(x<=n&&x%10==n%10) return tot;
      }
    }
    return -1;
  }
};

class TheNumbersWithLuckyLastDigit_org {
  public:
  int find(int n) {
    /*
    const int Inf=1e8;
    VI dist(10,Inf);
    queue<II> Q; Q.emplace(0,0);
    while(SZ(Q)) {
      int sum,d;
      tie(sum,d)=Q.front(),Q.pop();
      for(int e=4; e<=7; e+=3) {
        int sum2=sum+e,dd=d+1;
        if(dd<dist[sum2%10]) {
          dist[sum2%10]=dd;
          Q.emplace(sum2,dd);
        }
      }
    }
    dumpAR(dist);*/
    
    int m=n%10;
    if(m==4||m==7) return 1;
    if(m==0&&n>=20) return 5;
    if(m==1&&n>=11) return 2;
    if(m==2&&n>=12) return 3;
    if(m==3&&n>=23) return 5;
    if(m==5&&n>=15) return 3;
    if(m==6&&n>=16) return 4;
    if(m==8&&n>=8) return 2;
    if(m==9&&n>=19) return 4;
    return -1;
  }
};

// CUT begin
ifstream data("TheNumbersWithLuckyLastDigit.sample");

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

bool do_test(int n, int __expected) {
    time_t startClock = clock();
    TheNumbersWithLuckyLastDigit *instance = new TheNumbersWithLuckyLastDigit();
    int __result = instance->find(n);
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
        int n;
        from_stream(n);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521819934;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheNumbersWithLuckyLastDigit (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
