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
 
 8:37-9:06 (326.73 pt)
 failes system test :(
 
 23:35-24:00 found corner case and passed system test
 
 24:26 add simple solution
 - https://community.topcoder.com/stat?c=problem_solution&rd=16775&rm=329118&cr=40271137&pm=14361

 */

//        **                                              **
// A=882,700,  4,558,999, 22,713,893,882,477, 76,558,893,558,390, 22,601,882,323,999
// B=870,700,511,700,870,882,893,601,390, 22,558,390,511,558,511, 76,652, 76,882,477
// F=601, 76,601,558,477,862,862,870,558

//     *  **                       *           *          **       *               *
// A=870,700,  4,558,999, 22,713,601,882,477,558,558,893,558,390, 76,601,882,323,477
// B=870,700,511,700,870,882,893,601,390, 22,558,390,511,558,511, 76,652, 76,882,477
// F=601,862,862,558

//     *  **                       *           *          **       *               *
// A=870,700,  4,558,999, 22,713,601,882,477,558,558,893,558,390, 76,601,882,323,477
// B=870,700,511,700,870,882,893,601,390, 22,558,390,511,558,511, 76,652, 76,882,477
// F=601,862,862,558

//     *  **   *   *   *   *       *           *          **       *               *
// A=870,700,862,558,862,601,713,601,882,477,558,558,893,558,390, 76,601,882,323,477
// B=870,700,511,700,870,882,893,601,390, 22,558,390,511,558,511, 76,652, 76,882,477
// F={}

class Arrfix {
public:
  int mindiff(vector<int> A, vector<int> B, vector<int> F) {
    VI match,unmatch;
    int N=SZ(A);
    REP(i,N) {
      if(A[i]==B[i]) match.push_back(B[i]);
      else unmatch.push_back(B[i]);
    }
    
    VI fleft;
    FORR(n,F) {
      // using for match and for unmatch are mutually exclusive. Also unmatch should be prioritized.
      auto it1=find(unmatch.begin(),unmatch.end(),n);
      if(it1!=unmatch.end()) {
        unmatch.erase(it1);
        continue;
      }
      auto it2=find(match.begin(),match.end(),n);
      if(it2!=match.end()) {
        match.erase(it2);
        continue;
      }
      fleft.push_back(n);
    }
    
    return max(SZ(fleft), SZ(unmatch));
  }
};

class Arrfix_org {
public:
  int mindiff(vector<int> A, vector<int> B, vector<int> _F) {
    MAPII F;
    FORR(n,_F) ++F[n];
    int N=SZ(A);
    VI visited(N,0);
//    dump(N);
    //dumpAR(A);
    REP(i,N) if(A[i]!=B[i]&&F.count(B[i])>0) {
      A[i]=B[i];
      --F[B[i]]; if(F[B[i]]==0) F.erase(B[i]);
      visited[i]=true;
    }
    //dumpAR(A);
    REP(i,N) {
      if(visited[i]) continue;
      if(F.begin()==F.end()) continue;
      if(A[i]==B[i]&&F.count(A[i])==0) continue;
      
      int n;
      if(F.count(A[i])) {
        n=A[i];
      } else {
        auto it=F.begin();
        n=it->first;
      }
      A[i]=n;
      --F[n]; if(F[n]==0) F.erase(n);
      
      visited[i]=true;
    }
//    dumpAR(A);
    
    int dif=0;
    REP(i,N) if(A[i]!=B[i]) ++dif;
    int rem=0;
    FORR(kvp,F) rem+=kvp.second;
    //    dump2(dif,rem);
    
    return dif+rem;
  }
};

class Arrfix_wrong {
  public:
  int mindiff(vector<int> A, vector<int> B, vector<int> _F) {
    dumpAR(A);
    dumpAR(B);
    dumpAR(_F);

    MAPII F;
    FORR(n,_F) ++F[n];
    int N=SZ(A);
    VI visited(N,0);
//    dumpAR(A);
    REP(i,N) if(A[i]!=B[i]&&F.count(B[i])>0) {
      A[i]=B[i];
      --F[B[i]]; if(F[B[i]]==0) F.erase(B[i]);
      visited[i]=true;
    }
//    dumpAR(A);
    REP(i,N) {
      if(visited[i]) continue;
      if(F.begin()==F.end()) continue;
      
      int n;
      if(A[i]==B[i]&&F.count(n)) {
        n=B[i];
      } else {
        auto it=F.begin();
        n=it->first;
      }
      A[i]=n;
      --F[n]; if(F[n]==0) F.erase(n);
      
      visited[i]=true;
    }
    dumpAR(A);
    
    int dif=0;
    REP(i,N) if(A[i]!=B[i]) ++dif;
    int rem=0;
    FORR(kvp,F) rem+=kvp.second;
//    dump2(dif,rem);
    
    return dif+rem;
  }
};

// CUT begin
ifstream data("Arrfix.sample");

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

bool do_test(vector<int> A, vector<int> B, vector<int> F, int __expected) {
    time_t startClock = clock();
    Arrfix *instance = new Arrfix();
    int __result = instance->mindiff(A, B, F);
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
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        vector<int> F;
        from_stream(F);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, F, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500305842;
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
        cout << "Arrfix (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
