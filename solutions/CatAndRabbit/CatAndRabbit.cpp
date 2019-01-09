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
 
 1/4/2017
 
 18:27-18:41 analysis
 18:42-19:12 implement, submit and system test passed (408.51 pt)
 
 Size of black tile segment monotinically decreases. This is equivalent to Nim game.
 Corner case is that tiles are all white. However it's part of the samples (#4)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+558
  - http://kmjp.hatenablog.jp/entry/2012/10/19/1000
 
 Key:
  - Problem is reduced to Nim game with multiple piles
 
 Summary:
  - I was not very confident about reduction to Nim
  - I went back and forth, until I try Nim and it works for samples
  - Actually no need to compute even grundy number
   - Grundy number of Nim game with state `n` is `n` 😛
   - Added revised solution
 
 */

class CatAndRabbit {
public:
  string p1="Cat",p2="Rabbit";
  
  string getWinner(string A) {
    int N=SZ(A);
    if(count(A.begin(),A.end(),'.')==N) return p2;
    
    int gr=0;
    int cnt=0;
    REP(i,N) {
      if(A[i]=='#') gr^=cnt,cnt=0;
      else ++cnt;
    }
    gr^=cnt;
    return gr==0?p2:p1;
  }
};

int G[51]; // Grundy number
int grundy(int x) {
  SETI S;
  FOR(i,1,x+1) S.emplace(G[x-i]);
  
  int mex=0;
  while(S.count(mex)) mex++;
  return mex;
}
void calcGrundy(int N) {
  REP(x,N) G[x]=grundy(x);
}

class CatAndRabbit_org {
public:
  string p1="Cat",p2="Rabbit";
  
  string getWinner(string A) {
    int N=SZ(A);
    if(count(A.begin(),A.end(),'.')==N) return p2;
    calcGrundy(N+1);
    
    REP(i,N+1) dump2(i,G[i]);
    
    int gr=0;
    int cnt=0;
    REP(i,N) {
      if(A[i]=='#') {
        if(cnt>0) gr^=G[cnt];
        cnt=0;
      } else {
        ++cnt;
      }
    }
    if(cnt>0) gr^=G[cnt];
    return gr==0?p2:p1;
  }
};

// CUT begin
ifstream data("CatAndRabbit.sample");

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

bool do_test(string tiles, string __expected) {
    time_t startClock = clock();
    CatAndRabbit *instance = new CatAndRabbit();
    string __result = instance->getWinner(tiles);
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
        string tiles;
        from_stream(tiles);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(tiles, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515119256;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "CatAndRabbit (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
