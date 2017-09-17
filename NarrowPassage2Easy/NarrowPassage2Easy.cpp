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
 
 9/17/2017
 
 8:51-10:42 system test passed (165.42 pt)
 
 editorial:
  - http://apps.topcoder.com/wiki/display/tc/SRM+638
  - http://kmjp.hatenablog.jp/entry/2014/11/03/0930
    - for div1 size N<=50
 
 key:
  - N<=6. just simulate it by BFS or DFS
 
 summary:
  - tried three different approaches. only third one worked.
    - avoid swap during permutation generation (trapped by a corner case)
    - find pair which cannot be swapped (trapped by a corner case)
    - just generate permutations and simulate swap
  - don't try to do something smart which may not be valid 👎
  - brute-force first if applicable
 
 submit solution:
  - BFS
    - https://community.topcoder.com/stat?c=problem_solution&rm=324214&rd=16081&pm=13520&cr=23327007
  - DFS
    - https://community.topcoder.com/stat?c=problem_solution&rm=324207&rd=16081&pm=13520&cr=23127234
    - https://community.topcoder.com/stat?c=problem_solution&rm=324226&rd=16081&pm=13520&cr=23144770
 
 */

// O(N^2*N!) time
class NarrowPassage2Easy {
public:
  int count(vector<int> X, int maxSizeSum) {
    int cap=maxSizeSum;
    int N=SZ(X),res=0;
    VI O(N);
    REP(i,N) O[i]=i;
    do {
      VI work=O;
      bool ok=true;
      REP(i,N) {
        int cur=find(work.begin()+i,work.end(),i)-work.begin();
        while(cur>i) {
          if(X[work[cur]]+X[work[cur-1]]<=cap) {
            swap(work[cur],work[cur-1]);
            --cur;
          } else {
            ok=false;
            break;
          }
        }
        if(!ok) break;
      }
      if(ok) {
        VI XX(N);
        REP(i,N) XX[i]=X[O[i]];
        dumpAR(XX);
        
        ++res;
      }
    } while(next_permutation(O.begin(),O.end()));
    
    return res;
  }
};

// below 4 cases are missing for sample 4 in this solution
// from: [2,4,6,1,3,5] max size: 8
// 1,2,4,6,3,5,
// 1,2,4,6,5,3,
// 2,1,4,6,3,5,
// 2,1,4,6,5,3,
class NarrowPassage2Easy_wrong1 {
public:
  int cap;
  int res=0;
  int N;
  
  set<VI> ps;
  
  // sample 4 doesn't pass
  void perm(int p, VI &X) {
    if(p==N) {
//      ps.insert(X);
//      dumpAR(X);
      ++res;
      return;
    }
    dumpAR(X);
    FOR(i,p,N) {
      bool ok=true;
//      dump4(p,i,X[p],X[i]);
      
      // this check is too strict.
      // in [2,3,1] max size: 4 cannot be [1,2,3]
      for(int j=p+1; j<=i; ++j) {
        if(X[p]+X[j]>cap) { /*dump4(p,j,X[p],X[j]);*/ ok=false; }
      }
      for(int j=i-1; ok&&j>=p; --j) {
        if(X[i]+X[j]>cap) { /*dump4(i,j,X[i],X[j]);*/ ok=false; }
      }
      if(ok) {
        VI Y=X;
        swap(X[i],X[p]);
        perm(p+1,X);
        swap(X[i],X[p]);
      }
    }
  }
  
  // [2,3,1] case doesn't pass in sample 2
  int count(vector<int> X, int maxSizeSum) {
    this->cap=maxSizeSum;
    this->N=SZ(X);
    perm(0,X);

//    FORR(p,ps) dumpAR(p);
    
    return res;
  }
};

int mx[6][6];
class NarrowPassage2Easy_wrong2 {
  public:
  int cap;
  int res=0;
  int N;
  
  // [2,3,1] case doesn't pass in sample 2
  int count(vector<int> X, int maxSizeSum) {
    this->cap=maxSizeSum;
    this->N=SZ(X);
//    perm(0,SS);
    dumpAR(X);
    ZERO(mx);
    REP(i,N) FOR(j,i+1,N) {
      if(i==j) mx[i][j]=1;
      else {
        bool ok=true;
        for(int k=i+1; k<=j; ++k) {
          if(X[i]+X[k]>cap) { /*dump4(p,j,X[p],X[j]);*/ ok=false; }
        }
        mx[i][j]=ok;
        ok=true;
        for(int k=j-1; k>=i; --k) {
          if(X[j]+X[k]>cap) { /*dump4(i,j,X[i],X[j]);*/ ok=false; }
        }
        mx[j][i]=ok;
        dump2(i,j);
        dump3(X[i],X[j],ok);
      }
    }
    VI O(N);
    REP(i,N) O[i]=i;
    do {
      VI XX(N);
      REP(i,N) XX[i]=X[O[i]];
      dumpAR(XX);
      bool ok=true;
      REP(i,N) {
        int cur=O[i];
        FOR(j,i+1,N) if(cur>O[j]&&!mx[cur][O[j]]) ok=false;
      }
      dump(ok);
      if(ok) ++res;
    } while(next_permutation(O.begin(),O.end()));

    return res;
  }
};

// CUT begin
ifstream data("NarrowPassage2Easy.sample");

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

bool do_test(vector<int> size, int maxSizeSum, int __expected) {
    time_t startClock = clock();
    NarrowPassage2Easy *instance = new NarrowPassage2Easy();
    int __result = instance->count(size, maxSizeSum);
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
        vector<int> size;
        from_stream(size);
        int maxSizeSum;
        from_stream(maxSizeSum);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(size, maxSizeSum, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505663485;
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
        cout << "NarrowPassage2Easy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
