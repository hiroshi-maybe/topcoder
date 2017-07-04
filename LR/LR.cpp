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
 
 7/3/2017
 
 22:00 start
 22:32 figured out that LR order doesn't matter. start coding..
 22:50 passed samples and system test (122 pt)
 
 http://kmjp.hatenablog.jp/entry/2017/05/07/0930
 https://www.topcoder.com/blog/single-round-match-712-editorialsl/
 
 */

// inspired by http://kmjp.hatenablog.jp/entry/2017/05/07/0930
class LR {
public:
  string construct(vector<long long> S, vector<long long> T) {
    int N=SZ(S);
    
    if (S==T) return "";
    LL SSUM = accumulate(S.begin(),S.end(),0LL);
    LL TSUM = accumulate(T.begin(),T.end(),0LL);
    if (SSUM==0) return "No solution";
    
    // sum(s,k+1)=sum(s,k)*2
    int k=0;
    while((SSUM<<k)<TSUM) ++k;
    if ((SSUM<<k)!=TSUM) return "No solution";
    
    REP(l, k+1) {
      vector<LL> tmp=S;
      
      string res;
      REP(_,l) {
        res += "L";
        vector<LL> next=tmp;
        REP(i,N) next[i]+=tmp[(i+N-1)%N];
        tmp=next;
      }
      REP(_,k-l) {
        res += "R";
        vector<LL> next=tmp;
        REP(i,N) next[i]+=tmp[(i+1)%N];
        tmp=next;
      }
      
      if (tmp==T) return res;
    }
    
    return "No solution";
  }
};

class LR_org {
  public:
  string construct(vector<long long> S, vector<long long> T) {
    int N=SZ(S);
    
    int ok=0;
    REP(i,N) if(S[i]==T[i]) ++ok;
    if (ok==N) return "";
    
    REP(L,101) {
      int R = 100-L;
      vector<LL> A = S;
      
      REP(ll,L) {
        vector<LL> tmp(N);
        
        int ok=0;
        REP(i,N) {
          tmp[(i+1)%N] = A[i]+A[(i+1)%N];
          if (tmp[(i+1)%N]==T[(i+1)%N]) ++ok;
          if (tmp[(i+1)%N]>T[(i+1)%N]) goto NEXT;
        }
        
        if (ok==N) {
          string res;
          res.append(ll+1,'L');
          
//          dumpAR(tmp);
          return res;
        }
        
        A = tmp;
      }
      
      REP(rr,R) {
        vector<LL> tmp(N);
        
        int ok=0;
        REP(i,N) {
          tmp[i] = A[i]+A[(i+1)%N];
          if (tmp[i]==T[i]) ++ok;
          if (tmp[i]>T[i]) goto NEXT;
        }
        
        if (ok==N) {
          string res;
          res.append(L,'L');
          res.append(rr+1,'R');
          
//          dumpAR(tmp);
          return res;
        }
        
        A = tmp;
      }
      
    NEXT: 1;
    }
    return "No solution";
  }
};

// CUT begin
ifstream data("LR.sample");

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

bool do_test(vector<long long> s, vector<long long> t, string __expected) {
    time_t startClock = clock();
    LR *instance = new LR();
    string __result = instance->construct(s, t);
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
        vector<long long> s;
        from_stream(s);
        vector<long long> t;
        from_stream(t);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, t, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499144161;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "LR (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
