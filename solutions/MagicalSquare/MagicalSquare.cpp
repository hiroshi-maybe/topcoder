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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 2/25/2018
 
 10:45-10:57 analysis
 10:58-11:42 implement, submit (380.61 pt) but 1WA.
 11:43-11:50 bugfix and ACC
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+525
  - http://kmjp.hatenablog.jp/entry/2014/01/11/0900
  - http://d.hatena.ne.jp/kusano_prog/20111224/1324728084
  - http://topcoder.g.hatena.ne.jp/capythm/20111129/1322587308
 
 The point of pre-computation is that we can compute substring matchin independently for each A[i].
 We have three strings in A and B.
 A[i] = *******, i=0..2
 B[j] = *******, j=0..2
 
 If we want to know mathcing between A[i] and B[j], no need to take care of i'(!=i) and j'(!=j).
 Suppose we want to know mathching of A[i][l1..r1]. Then we know length of B[j] should be r1-l1.
 We can just check B[j][l2..l2+r1-l1]. The combination of variables is (l1,r1,l2) which is O(L^3).
 Substring and equivalance check is O(L). The total check is O(L^4).
 We can do such a check for every combination of i and j. The total time of precomputation is O(3*3*L^4) time.
 
 Once the matching table is pre-computed, we can iterate (i0,j0,i1,j1) for separator index in A[0] and A[1].
 Check against B[0], B[1] and B[2] can be performed in O(1).
 The total runtime O(L^4) can be achieved.
 
 16:08-16:57 add solution with O(L^4) time. Very painful implementation.
 
 Key:
  - Pre-compute substring matching to avoid paying O(L) in every combination of A[0]+A[1]+A[2]
 
 Summary:
  - Brute-force approach with O(L^5) is analysis-wise straightforward though, implementation is complicated
  - Efficient algorithm with O(L^4) is painful as well
  - Pre-compute substring matching table in O(L^4) is nice to learn
   - total O(S*T*L^4) time for every pair of S strings and T strings
 
 */

// A[i][l1..<r1] == B[j][l2..<l2+r1-l1]
bool ok[3][3][51][51][51];
class MagicalSquare {
public:
  long long getCount(vector<string> A, vector<string> B) {
    ZERO(ok);
    REP(i,3)REP(j,3)REPE(l1,SZ(A[i]))FORE(r1,l1,SZ(A[i]))REPE(l2,SZ(B[j])) {
      if(l2+r1-l1>SZ(B[j])) continue;
      string s=A[i].substr(l1,r1-l1),t=B[j].substr(l2,r1-l1);
      ok[i][j][l1][r1][l2]=(s==t);
    }
    
    LL res=0;
    REPE(i0,SZ(A[0]))FORE(j0,i0,SZ(A[0])) REPE(i1,SZ(A[1]))FORE(j1,i1,SZ(A[1])) {
      int L0[3]={0};
      int L1[3]={0};
      
      L0[0]=i0,L0[1]=j0-i0,L0[2]=SZ(A[0])-j0;
      L1[0]=i1,L1[1]=j1-i1,L1[2]=SZ(A[1])-j1;
      
      // A[0]
      if(!ok[0][0][0][i0][0]) continue;
      if(!ok[0][1][i0][j0][0]) continue;
      if(!ok[0][2][j0][SZ(A[0])][0]) continue;

      // A[1]
      if(!ok[1][0][0][i1][L0[0]]) continue;
      if(!ok[1][1][i1][j1][L0[1]]) continue;
      if(!ok[1][2][j1][SZ(A[1])][L0[2]]) continue;
      
      // A[2]
      int l0=SZ(B[0])-L0[0]-L1[0],l1=SZ(B[1])-L0[1]-L1[1],l2=SZ(B[2])-L0[2]-L1[2];
      if(l0<0||l1<0||l2<0) continue;
      if(l0+l1+l2!=SZ(A[2])) continue;
      if(!ok[2][0][0][l0][SZ(B[0])-l0]) continue;
      if(!ok[2][1][l0][l0+l1][SZ(B[1])-l1]) continue;
      if(!ok[2][2][l0+l1][SZ(A[2])][SZ(B[2])-l2]) continue;
      
      ++res;
    }
    return res;
  }
};

// O(L^5) time
class MagicalSquare_org {
  public:
  vector<string> A,B;
  int f(int r, vector<string> cur) {
//    dump(r);
    vector<string> X=cur;
    if(r==2) {
      int l=0;
//      dumpAR(X);
      REP(i,3) {
        int l1=SZ(cur[i]),l2=SZ(B[i]);
        if(l2<l1) return 0;
//        dump3(i,X[i],l);
        if(l>SZ(A[r])) return 0;
        X[i]+=A[r].substr(l,l2-l1);
        l+=l2-l1;
      }
      if(SZ(A[2])!=l) return 0;
//      dumpAR(X);
      return X==B;
    }
    int res=0;
    for(int l1=0; l1<=SZ(A[r]); ++l1) {
      if(l1>0) X[0].push_back(A[r][l1-1]);
      string s1=X[1],s2=X[2];
      for(int l2=0; l1+l2<=SZ(A[r]); ++l2) {
//        dump3(r,l1,l2);
        if(l2>0) X[1].push_back(A[r][l1+l2-1]);
//        dump4(r,l1,l2,A[r].substr(l1+l2));
        X[2]=s2+A[r].substr(l1+l2);
        
        int sum=0; REPE(i,r) sum+=SZ(A[i]);
        assert(SZ(X[0])+SZ(X[1])+SZ(X[2])==sum);
        res+=f(r+1,X);
      }
      X[1]=s1,X[2]=s2;
    }
    return res;
  }
  long long getCount(vector<string> A, vector<string> B) {
    this->A=A,this->B=B;
    vector<string> cur(3,"");
    return f(0,cur);
  }
};

// CUT begin
ifstream data("MagicalSquare.sample");

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

bool do_test(vector<string> rowStrings, vector<string> columnStrings, long long __expected) {
    time_t startClock = clock();
    MagicalSquare *instance = new MagicalSquare();
    long long __result = instance->getCount(rowStrings, columnStrings);
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
        vector<string> rowStrings;
        from_stream(rowStrings);
        vector<string> columnStrings;
        from_stream(columnStrings);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(rowStrings, columnStrings, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519584301;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MagicalSquare (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
