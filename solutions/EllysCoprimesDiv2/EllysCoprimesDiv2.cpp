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
 
 12/5/2017
 
 8:52-9:10 analysis
 9:11-9:40 system test passed (424.36 pt)
 
 My greedy solution without proof
 
 1. Sort numbers
 2. In each consecutive numbers ns[i], ns[i+1], do below operation:
 
  1) ns[i] is coprime with ns[i+1] <=> gcd(ns[i],ns[i+1])=1
   do nothing
  2) ns[i] is NOT coprime with ns[i+1] AND there exists only one `n` s.t. ns[i]<n<ns[i+1], gcd(ns[i],n)=gcd(n,ns[i+1])=1
   res+=1
  3) otherwise
   res+=2
 
 It's easy to prove below:
  - ns[i] and ns[i]+1 are co-prime
  - ns[i+1]-1 and ns[i+1] are co-prime
 
 However it's hard to prove this:
 
 ns[i] and ns[i+1] are NOT co-prime => ns[i]+1 and ns[i+1]-1 are co-prime
 
 We cannot say that this greedy algorithm is correct without proving this.
 So editorial is showing DP solution by proving that |ns[i]-ns[i+1]| is smalle enough.
 https://apps.topcoder.com/forums/?module=Thread&threadID=787732&start=0
 
 Proof of upper bound of |A-B|, A=ns[i], B=ns[i+1]
 
 We are trying to prove that |A-B| is small enough in case 3) in above classification.
 Thus gcd(A,B) = p0 > 1 and there exists no x s.t. gcd(A,x)=1 AND gcd(B,x)=1.
 We want to use a fact that there is no prime gap which is larger than 72 in [1,10^5].
 So we try to upper-bound focusing on prime number.
 
 Prime gap:
  - https://en.wikipedia.org/wiki/Prime_gap
  - https://oeis.org/A001223

 We assume below number sequence (p[i] is prime number):
 
 A(=p0*p1*p2),..,p3,..,p4,..,p5,..,p6,..,p7,..,(p8 ❌impossible to have 6-th prime),..,B(=p0*p3*p4*p5*p6*p7)

 Note that any number in (A,B) share some prime number with A or B because this doesn't satisfy condition of case2).
 Since max size of prime set for n in [0,10^5] is 6 because 2*3*5*7*11*13*17 > 10^5.
 We can assume that B can be factorized by at most 6 prime numbers (p[i],i=0,3..7 in our sequence)
 
 Since no number in (A,B) cannot be co-prime to both A and B.
 There should not be p8 which is one of factors of B (p0*p3*p4*p5*p6*p7*p8>10^5).
 Thus we can say 6 primes (p[i],i=3..8) between A and B is strictly more than possible.
 
 Because max prime gap is 72 in [1,10^5], we can say B-A is upper-bounded by 72*7+6=510
 Now we figured out that B-A<=510.
 If we build graph of numbers in [A,B] by relation `co-prime`, we can find shortest path from A to B.
 This is possible by DP or BFS.
 
 Editorial:
 - https://apps.topcoder.com/wiki/display/tc/SRM+577
 - http://kmjp.hatenablog.jp/entry/2013/05/03/0930
 
 12/8/2017
 
 Add proof of DP solution and solution with greedy by gcd, BFS and DP.
 
 Key:
  - Co-prime => gcd(a,b)=1
   - prime factorization is not efficient
  - Proof of greedy is not easy.
  - We need to prove that O(N^2*lg N) is suffient to solve problem with N<=10^5
 
 Summary:
  - Solved by greedy, but I figured out that I didn't have no proof of gcd(a+1,b-1)=1
  - It was not easy to understand the proof of |A-B|<=510
   - Upperbound by number of distinct prime is typical way
   - Upperbound by prime gap is nice to learn. It may be useful technique
  - Interesting that no number in (A,B) cannot be co-prime with both A and B narrows down interval.
 
 */

int gcd(int a, int b) { return b==0?a:gcd(b,a%b); }

class EllysCoprimesDiv2 {
public:
  const int Inf=600;

  // greedy, O(N*lg N) time to solve P(A,B)
  int f1(int A, int B) {
    if(gcd(A,B)==1) return 0;
    FOR(n,A+1,B) if(gcd(n,A)==1&&gcd(n,B)==1) return 1;
    return 2;
  }
  
  int dist[600];
  // bfs, O(N^2*lg^2 N) time to solve P(A,B)
  int f2(int A, int B) {
    if(gcd(A,B)==1) return 0;
    FOR(n,A+1,B) if(gcd(n,A)==1&&gcd(n,B)==1) return 1;
    // if(B-A) assert(gcd(A+1,B-1)); this is true for all the test cases.

    REP(i,B-A) dist[i]=Inf;
    queue<int> Q;
    Q.emplace(0); dist[0]=0;
    int res=Inf;
    while(SZ(Q)) {
      int o=Q.front(); Q.pop();
      int d=dist[o];
      if(gcd(A+o,B)==1) res=min(res,d);
      REP(o2,B-A) if(o2!=o&&gcd(A+o,A+o2)==1) {
        if(dist[o2]>d+1) {
          dist[o2]=d+1;
          Q.push(o2);
        }
      }
    }
    return res;
  }
  
  int dp[600];
  // dp, O(N^2*lg N) time
  int f(int A, int B) {
    if(gcd(A,B)==1) return 0;
    FOR(n,A+1,B) if(gcd(n,A)==1&&gcd(n,B)==1) return 1;
    REP(i,B-A) dp[i]=Inf;
    dp[0]=0;
    int res=Inf;
    FOR(i,1,B-A) {
      REP(j,i) if(gcd(A+i,A+j)==1) {
        dp[i]=min(dp[i],dp[j]+1);
      }
      if(gcd(A+i,B)==1) res=min(res,dp[i]);
    }
    return res;
  }
  
  int getCount(vector<int> ns) {
    sort(ns.begin(),ns.end());
    int res=0;
    int N=SZ(ns);
    FOR(i,1,N) res+=f(ns[i-1],ns[i]);
    return res;
  }
};

VI distinctPrimeFactors(int n) {
  set<int> res;
  for(int p=2; p*p<=n; ++p) if(n%p==0) {
    res.emplace(p);
    while(n%p==0) n/=p;
  }
  if(n>1) res.emplace(n);
  return VI(res.begin(),res.end());
}

bool hasCommon(VI &xs, VI &ys) {
  FORR(x,xs) {
    if(count(ys.begin(),ys.end(),x)>0) return true;
  }
  return false;
}

class EllysCoprimesDiv2_org {
  public:
  int getCount(vector<int> ns) {
    sort(ns.begin(),ns.end());
    int res=0;
    int N=SZ(ns);
    
    VI prev=distinctPrimeFactors(ns[0]);
    FOR(i,1,N) {
      VI cur=distinctPrimeFactors(ns[i]);

      bool cmn=hasCommon(prev,cur);

      if(!cmn) {
        prev=cur;
        continue;
      }
      bool ok=false;
      FOR(x,ns[i-1]+1,ns[i]) {
        VI D=distinctPrimeFactors(x);
        if(!hasCommon(prev,D)&&!hasCommon(cur,D)) {
          ok=true;
          break;
        }
      }
      if(ok) res+=1;
      else res+=2;
      
      prev=cur;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("EllysCoprimesDiv2.sample");

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

bool do_test(vector<int> numbers, int __expected) {
    time_t startClock = clock();
    EllysCoprimesDiv2 *instance = new EllysCoprimesDiv2();
    int __result = instance->getCount(numbers);
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
        vector<int> numbers;
        from_stream(numbers);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(numbers, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512492720;
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
        cout << "EllysCoprimesDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
