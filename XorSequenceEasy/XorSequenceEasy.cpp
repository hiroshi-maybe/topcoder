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
 
 9/6/2017
 
 9:23-9:56 basic design
 9:57-10:40 samples don't pass. pause.
 17:55-18:00 fixed a bug to compute K and system test passed
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+649
  - http://kmjp.hatenablog.jp/entry/2015/02/13/1000
 
 when we compare a = 1101011 with b = 1101101, the most significant bit `k` which is different determines it.
 
   a = 1101011
   b = 1101101
           ^
 
 so looking at each bit from left to right is typical way to compare numbers in bit-wise.
 
 if we apply x ^ n, n=0101010...
 
 a^n = 1000111
 b^n = 1000001
           ^
 
 even if we apply ^n, we can still look at k-th bit.
 a^n < b^n or a^n > b^n depends on `n` that we chosse.
 
 so we can look at i-th bit in i = K-1..0. select i-th of `n` so that it maximizes number of pairs s.t. i<j&&C[i]<C[j].
 
 key:
  - bit manipulation + number comparison => binary digit column DP or recursion
   - look at each column from left to right
   - we keep comparing only elements which have same columns
   - otherwise order is already determined because we are looking at more significant bits first
  - brute-forcing all the pairs and going through from left to right bits is easier to implement
   - no need to do complex bit masking
  - decision of each i-th bit of B is independent
 
 summary:
  - I had an idea to check from left to right bits though, I've not analyzed how pending elements are reduced
    - thus I was not sure why the original code works
    - this is very typical bit column DP. I've seen it in LeetCode too, I should have figured out quickly.
  - typical approach to number comparison and bit manipulation
   - iterate from left to right to determine result of comparison earlier
   - decision of each bit is sometimes indendent. i-th bit does not affect selection of (i-1)-th bit
 
 submit solutions:
  - https://community.topcoder.com/stat?c=problem_solution&rm=325152&rd=16313&pm=13657&cr=22931169
  - https://community.topcoder.com/stat?c=problem_solution&rm=325149&rd=16313&pm=13657&cr=22835034
  - https://community.topcoder.com/stat?c=problem_solution&rm=325142&rd=16313&pm=13657&cr=40043950
    - almost same as my original solution
    - instead of keeping B, keeping modified array by XOR
    - modified elements should have more 1s than discarded array at i-th bit
    - eventually array should be optimal
  - https://community.topcoder.com/stat?c=problem_solution&rm=325161&rd=16313&pm=13657&cr=23137570
    - same as official editorial
 
 */

// O(M^2*K) time < 8*10^4
int p[32][2];
class XorSequenceEasy {
public:
  int getmax(vector<int> A, int N) {
    int K=(int)log2(N+0.1);
    int M=SZ(A);
    
    ZERO(p);
    REP(i,M) FOR(j,i+1,M) {
      // brute-force all the pairs of (i,j), look at the first different bit and try {0,1}
      for(int k=K-1; k>=0; --k) {
        int a=(A[i]>>k)&1,b=(A[j]>>k)&1;
        if(a!=b) {
          // (a,b)=(1,0) => (a^1,b^1)=(0,1)
          // (a,b)=(0,1) => (a^0,b^0)=(0,1)
          p[k][a>b]++;
          break;
        }
      }
    }
    
    int res=0;
    REP(i,K) res+=max(p[i][0],p[i][1]);
    return res;
  }
};

class XorSequenceEasy_org {
  public:
  int K,N;
  VI A;
  // keep B mask which gives us more pairs
  int f(int i, int B) {
    int r[2]={0,0};
    int mask=((1<<K)-1)-((1<<i)-1);
    assert(B>=0);
//    dump2(i,B);

    REP(j,2) {
      int x=B|(j<<i);
      VI C(N);
      REP(k,N) C[k]=(A[k]^x)&mask;
      REP(l,N) FOR(m,l+1,N) if(C[l]<C[m]) ++r[j];
    }
    if(i==0) return max(r[0],r[1]);
    // system test passed though, I couldn't figure out why this is not necessary
    //  -> K..i-th bits are already considered, so B[K..i] doesn't affect in subsequent calls
    //if(r[0]==r[1]) return max(f(i-1,B),f(i-1,B|(1<<i)));
    else if(r[0]<r[1]) B|=(1<<i);
    return f(i-1,B);
  }
  
  int getmax(vector<int> A, int N) {
    this->K=(int)log2(N+0.1);
    this->A=A;
    this->N=SZ(A);
    
//    dump(K);
    
    return f(K-1,0);
  }
};

// CUT begin
ifstream data("XorSequenceEasy.sample");

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

bool do_test(vector<int> A, int N, int __expected) {
    time_t startClock = clock();
    XorSequenceEasy *instance = new XorSequenceEasy();
    int __result = instance->getmax(A, N);
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
        int N;
        from_stream(N);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504715016;
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
        cout << "XorSequenceEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
