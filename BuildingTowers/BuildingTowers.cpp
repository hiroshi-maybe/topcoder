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
 
 9/8/2017
 
 20:33-21:05 designed to compute t'[i] in LTR order, binary search and trenary search
 21:06-22:03 it turned out binary search is unnecessary. trenary search in each interval works
 22:03 samples passed but (3/78) failed in system test :(
 ok RTL constraint is missing :D
 22:18 system test passed
 
 trenary search: https://apps.topcoder.com/wiki/display/tc/SRM+647
 
 summary:
 - approach is not tough to come up with. it's not tricky.
 - I spent 20 mins to normalize input x and t 👎
 - my first trenary search copied from Wikipedia
 - infinite loop in first implementation due to precision 1
 - time loss to figure out that binary search is not necessary 👎
 - started coding without analyzing interval computation
 - I was not confident how trenary search works
 - right to left constraint was completely missing
 - anyway solved by myself with 1 WA 👍
 
 9/9/2017
 
 editorial:
 - http://kmjp.hatenablog.jp/entry/2015/01/26/1000
 - height limitation increases by K for interval 1.
 - we can compute maximal value in the interval by constant slope K in O(1)
 - https://apps.topcoder.com/wiki/display/tc/SRM+647
 - binary search solution
 
 23:14-23:50 add @kmjp's approach
 
 we can insert (x,t)=(1,0) and (N,1LL<<60).
 we don't need to be worried about duplicated x elements
 because we'll eventually get same value for interval of same `x`.
 It does not affect our result. I took the idea from @kmjp solution.
 
 firstly pre-compute H[i] as I did in my original solution.
 note that H[i] is upperbounded by both left and right. We should iterate in both direction.
 thus H[i] = min(H[i],H[i-1]+K*(X[i]-X[i-1],H[i+1]+K*(X[i+1]-X[i]))
 
 then we can compute maximal height in each interval X[i] and X[i+1].
 straight line from (X[i],H[i]) intersects the line from (X[i+1],H[i+1]).
 suppose they intersect at p, X[i]<=p<=X[i+1].
 
 then H[i]+K*(p-X[i]) = H[i+1]+K*(X[i+1]-p)
 <=> p = (K*(X[i+1]+X[i])+H[i+1]-H[i])/(2*K)
 
 p is not real number, let's take p-1 and p+1 as well as a candidate. we name them as p[0],p[1],p[2].
 note that p0,p1,p2 should be in range of [X[i],X[i+1]].
 if maximal height in interval [X[i],X[i+1]] is defined as h(i),
 h(i) = max { min(H[i]+K*(p[i]-x[i], H[i+1]+K*(X[i+1]-p)) : i=0..2 }
 
 res = max { h(i) : i=0..SZ(X)-1 }
 
 24:20-25:46 add binary search solution in official editorial
 
 */

class BuildingTowers_binarysearch {
public:
  LL K,N;
  vector<LL> H,X;
  
  bool ok(LL h) {
    vector<pair<LL,LL>> rs;
    rs.emplace_back(1,1);
    rs.emplace_back(N+1,-1);
    REP(i,SZ(X)) {
      if(H[i]<h) {
        LL l=(h-H[i]-1)/K;
        rs.emplace_back(max(X[i]-l,1LL),-1LL);
        rs.emplace_back(min(X[i]+l+1LL,N+1),1LL);
      }
    }
    
    sort(rs.begin(),rs.end());
    int cur=0;
    REP(i,SZ(rs)) {
      cur+=rs[i].second;
      if(cur>0) return true; // ng interval found
    }
    return false;
  }
  
  long long maxHeight(int N,
                  int K,
                  vector<int> &x,
                  vector<int> const &t) {
    this->K=K;
    this->N=N;
    X.push_back(1),H.push_back(0);
    REP(i,SZ(x)) X.push_back(x[i]),H.push_back(t[i]);
    X.push_back(N),H.push_back(1e18);
    
    FOR(i,1,SZ(X)) H[i]=min(H[i],H[i-1]+K*(X[i]-X[i-1]));
    for(int i=SZ(X)-2; i>=0; --i) H[i]=min(H[i], H[i+1]+K*(X[i+1]-X[i]));
    
    LL good=0,bad=1e18;
    while(abs(good-bad)>1LL) {
      LL mid=good+(bad-good)/2LL;
      
      if(ok(mid)) good=mid;
      else bad=mid;
    }
    
    return good;
  }
};

// O(N) time
class BuildingTowers_linear {
public:
  LL K;
  vector<LL> H,X;
  LL top(LL li, LL ri, LL lh, LL rh) {
    LL p1=(K*(ri+li)+rh-lh)/(2LL*K);
    p1=min(max(p1,li),ri);
    LL p2=min(max(p1+1,li),ri);
    LL p0=min(max(p1-1,li),ri);
    
    vector<LL> is={p0,p1,p2};
    vector<LL> vs;
    for(LL p : is) {
      vs.push_back(min(lh+K*(p-li),rh+K*(ri-p)));
    }
    
    return *max_element(vs.begin(),vs.end());
  }
  
  long long maxHeight(int N,
                  int K,
                  vector<int> &x,
                  vector<int> const &t) {
    this->K=K;
    X.push_back(1),H.push_back(0);
    REP(i,SZ(x)) X.push_back(x[i]),H.push_back(t[i]);
    X.push_back(N),H.push_back(1e18);
    
    FOR(i,1,SZ(X)) H[i]=min(H[i],H[i-1]+K*(X[i]-X[i-1]));
    for(int i=SZ(X)-2; i>=0; --i) H[i]=min(H[i], H[i+1]+K*(X[i+1]-X[i]));
    
    LL res=0;
    REP(i,SZ(X)-1) res=max(res, top(X[i],X[i+1],H[i],H[i+1]));
    return res;
  }
};

// O(N*lg I) time, where I is average interval between X[i] and X[i+1].
class BuildingTowers {
public:
  LL K;
  vector<LL> P,T;
  
  LL top(LL li, LL ri, LL lh, LL rh) {
    // my first trenary search
    LL l=li,r=ri;
    while(abs(r-l)>2) {
      LL lthird=l+(r-l)/3,rthird=r-(r-l)/3;
      
      LL lx=min((lthird-li)*K+lh, (ri-lthird)*K+rh),
      rx=min((rthird-li)*K+lh, (ri-rthird)*K+rh);
      
      if(lx<rx) l=lthird;
      else r=rthird;
    }
    
    LL res=0;
    FOR(i,l,r+1) {
      LL h=min(((LL)i-li)*K+lh, (ri-(LL)i)*K+rh);
      res=max(res,h);
    }
    
    return res;
  }
  
  long long maxHeight(int N,
                  int K,
                  vector<int> &x,
                  vector<int> const &t) {
    this->K=K;
    vector<LL> xx,tt;
    int M=SZ(x);
    if(M==0||x[0]!=1) xx.push_back(1),tt.push_back(0);
    REP(i,M) xx.push_back(x[i]),tt.push_back(t[i]);
    if(xx.back()!=N) xx.push_back(N),tt.push_back(999999999000000000LL);
    
    //    dumpAR(xx);
    //    dumpAR(tt);
    
    P.push_back(1LL),T.push_back(0LL);
    for(int i=1; i<SZ(xx); ++i) {
      P.push_back(xx[i]);
      LL t2=min(tt[i], T.back()+(xx[i]-xx[i-1])*this->K);
      T.push_back(t2);
    }
    for(int i=SZ(xx)-2; i>=0; --i) {
      T[i]=min(T[i],T[i+1]+(P[i+1]-P[i])*this->K);
    }
    
    //    dumpAR(P);
    //    dumpAR(T);
    
    LL res=0LL;
    REP(i,SZ(P)-1) {
      int li=P[i],ri=P[i+1];
      LL lh=T[i],rh=T[i+1];
      res=max(res,top(li,ri,lh,rh));
    }
    return res;
  }
};

// CUT begin
ifstream data("BuildingTowers.sample");

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

bool do_test(int N, int K, vector<int> x, vector<int> t, long long __expected) {
    time_t startClock = clock();
    BuildingTowers *instance = new BuildingTowers();
    long long __result = instance->maxHeight(N, K, x, t);
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
        int N;
        from_stream(N);
        int K;
        from_stream(K);
        vector<int> x;
        from_stream(x);
        vector<int> t;
        from_stream(t);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, x, t, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505071558;
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
        cout << "BuildingTowers (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
