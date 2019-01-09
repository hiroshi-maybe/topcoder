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
 
 11/6/2017
 
 9:02-9:48 analysis
 9:49-11:20 pause
 17:00-18:01 redesigned classification and implemented. system test passed.
 
 Brute-force all the pairs (X,Y) takes 10^18 time.
 I started going through X^Y and X by brute forcing possible prefixes.
 We can try those prefixes depending on positions where bit is ON.
 
 A = 1010111001011
     0************
     100**********
     10100********
     101010*******
     1010110******
     1010110000***
     101011100100*
     1010111001010
     1010111001011
 
 * is either 0 or 1. They are all less than or equal to A.
 
 Once X^Y and X patterns are determined, it's possible to count Y patterns.
 I tried to count it without DP though, I got completely confused and in stuck.
 
 In the second try, I did same approach by X and Y. X, Y are X^Y are symmetry. We can try any two of them.
 I finally figured out that I need DP. Otherwise runtime would be O(31^3*2^31).
 I also did detailed classification. System test passed.
 
 f(i,any) = number of pairs of (X,Y) after i-th bit. If `any` is true, X^Y<C is guarateed.
 
 10 cases classification as shown in my original code
 
 1) X^Y<C AND X<A AND Y<B:                    4*f(i-1,1)
 2) X^Y<C AND (X=A AND Y<B) OR (X<A AND Y=B): 2*f(i-1,1)
 3) X^Y<C AND X=A AND Y=B:                      f(i-1,1)
 4) X^Y=C AND X=A AND Y=B
 ....
 
 P = P1 * P2 * P3
 P1: find possible position of prefixes of A
 P2: find possible position of prefixes of B
 P3: count possible pairs based on given prefix of A and B

   T(P)
 = T(P1)*T(P2)*T(P3)
 = 31*31*31*2
 ≈ 6*10^4
 
 However we can simply compare X,Y,X^Y and A,B,C as shown in editorials.
 
 f(i,anya,anyb,anyc): number of pairs by X,Y,X^Y after i-th bit (anya=X<A, anyb=Y<B, anyc=X^Y<C)
 
 We can brute force X[i]={0,1}, Y[i]={0,1} in DP.
 f(i,anya,anyb,anyc) = ∑ { f(i-1,anya',anyb',anyc') : X[i]={0,1}, Y[i]={0,1}, X^Y[i]=X^Y[i] }
  anya' = anya || X[i]<A[i], anyb' = anyb || Y[i]<B[i], anyc' = anyc || X^Y[i]<C[i]
 f(-1) = 1
 
 res = f(30,0,0,0)
 
 This makes a lot of sense. X and Y depends on A and B separatedly.
 In computation of each bit, we can just compute them and get corresponding X^Y for them.
 Counting X s.t. X<=A is also independent subproblem.
 
 P = 31*(P1+P2+P3)
 P1: X[30..i]<=A[30..i]
 P2: Y[30..i]<=B[30..i]
 P3: X^Y[30..i]<=C[30..i]

 Probably ideal analysis process is...
 X depends on A. Y depends on B. Also I know it's possible to count s s.t. s<=N in linear time by bit column DP.
 We can compute them in each column. X^Y depends on X and Y. We can compute in each bit column together.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+595
  - http://torus711.hatenablog.com/entry/20131025/p4
  - http://kmjp.hatenablog.jp/entry/2013/10/30/0930
   - similar to my original solution. complex classification.
 
 Summary:
  - Second time bit column dp
  - Solved by myself though, lost in analysis a lot of times
  - Code by red coders and editorial are pretty impressive compared with my original complex code
    - remember if X<A or X=A, Y<B or Y=B, X^Y=C or X^Y<C
    - try X={0,1} and Y={0,1}. Update X<A,Y<B,X^Y<C flags accordingly
    - remembering if selection of following bit is free or not is typical column bit DP technique
 
 */

LL memo[35][2][2][2];
class LittleElephantAndXor {
public:
  LL A,B,C;
  LL f(int i, bool anya, int anyb, int anyc) {
    if(i==-1) return 1;
    LL &res=memo[i][anya][anyb][anyc];
    if(res>=0) return res;
    res=0;
    
    int a=(A>>i)&1,b=(B>>i)&1,c=(C>>i)&1;
    REP(x,2)REP(y,2) {
      int xy=x^y;
      bool aok=anya||x<=a,bok=anyb||y<=b,cok=anyc||xy<=c;
      if(aok&&bok&&cok) res+=f(i-1,anya||x<a,anyb||y<b,anyc||xy<c);
    }
    return res;
  }
  
  long long getNumber(int A, int B, int C) {
    this->A=A,this->B=B,this->C=C;
    MINUS(memo);
    return f(30,0,0,0);
  }
};

class LittleElephantAndXor_org {
  public:
  LL memo[35][2];
  LL A,B,C;
  int ai,bi;
  LL f(int i, bool anyc) {
    if(i==-1) return 1;
    LL &res=memo[i][anyc];
    if(res>=0) return res;
    
    int anya=ai>i, anyb=bi>i;
//    dump4(i,anya,anyb,anyc);
    if(anyc) {
      if(anya&&anyb) return res=4*f(i-1,anyc);
      if(anya^anyb) return res=2*f(i-1,anyc);
      return res=f(i-1,anyc);
    }
    
    int c=(C>>i)&1;
    int x=ai==i?0:(A>>i)&1;
    int y=bi==i?0:(B>>i)&1;
//    dump4(i,c,x,y);
    if(!anya&&!anyb) {
      int xy=x^y;
//      dump3(i,c,xy);
      if(xy>c) return res=0;
      if(xy<c) return res=f(i-1,1);
      return res=f(i-1,0);
    } else if(anya^anyb) {
      if(!c) return res=f(i-1,0);
      return res=f(i-1,0)+f(i-1,1);
    }
    
    if(!c) return res=2*f(i-1,0);
    return res=2*f(i-1,0)+2*f(i-1,1);
  }
  
  vector<int> zerocol(int n) {
    vector<int> res;
    for(int i=30; i>=0; --i) {
      if(n&(1<<i)) res.emplace_back(i);
    }
    res.push_back(-1);
    return res;
  }
  long long getNumber(int A, int B, int C) {
    this->A=A,this->B=B,this->C=C;
    vector<int> X,Y;
    Y=zerocol(B);
    X=zerocol(A);
    
    LL res=0;
    REP(i,SZ(X)) REP(j,SZ(Y)) {
      MINUS(memo);
      this->ai=X[i],this->bi=Y[j];
//      dump3(ai,bi,f(30,0));
//      REP(i,31) dump3(i,memo[i][0],memo[i][1]);
      res+=f(30,0);
    }
    return res;
  }
};

// CUT begin
ifstream data("LittleElephantAndXor.sample");

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

bool do_test(int A, int B, int C, long long __expected) {
    time_t startClock = clock();
    LittleElephantAndXor *instance = new LittleElephantAndXor();
    long long __result = instance->getNumber(A, B, C);
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
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        int C;
        from_stream(C);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, C, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509987753;
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
        cout << "LittleElephantAndXor (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
