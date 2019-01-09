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
 
 9/11/2017
 
 15:49-17:03 pause
 17:35-17:58 figured out right use of median
 19:25-19:30 system test passed
 
 editorial:
  - http://kmjp.hatenablog.jp/entry/2015/01/21/0930
    - brute-force all cars to stay just in case
  - https://apps.topcoder.com/wiki/display/tc/SRM+645
    - brute-force all cars to stay
 
 key:
  - if we make a set of position of each car, we can move toward a car which is at mid position
 
 summary:
  - I figured out median quickly though, I was confused by length of intervals
    - somehow I was trying to use average of left outer and right outer intervals
  - I should have repeated proof
    - it's obvious that length doesn't matter. mid position of intervals matters
 
 26:01-26:07 add @kmjp's simple solution which precomputes distance of all the pairs
  - I used floyd-warshall instead
 
 */

LL dist[51][51];
class ConnectingCars {
public:
  long long minimizeCost(vector<int> ps, vector<int> ls) {
    int N=SZ(ps);
    vector<pair<LL,LL>> rs;
    REP(i,N) rs.emplace_back(ps[i],ls[i]);
    sort(rs.begin(),rs.end());
    
    const LL Inf=1e18;
    REP(i,N)REP(j,N) dist[i][j]=i==j?0:Inf;
    REP(i,N-1) dist[i][i+1]=dist[i+1][i]=abs(rs[i].first+rs[i].second-rs[i+1].first);
    REP(k,N)REP(i,N)REP(j,N) if(dist[i][k]<Inf&&dist[k][j]<Inf) dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
    
    LL res=Inf;
    REP(i,N) {
      LL d=0;
      REP(j,N) d+=dist[j][i];
      res=min(res,d);
    }
    return res;
  }
};

/*
 
 as shown below, position of median is always optimal
 
 Testcase #0 ...
 i = 0, d = 15 ✅
 i = 1, d = 15 ✅
 i = 2, d = 15 ✅
 i = 3, d = 25

 Testcase #1 ...
 i = 0, d = 144
 i = 1, d = 96 ✅
 i = 2, d = 144

 Testcase #2 ...
 i = 0, d = 69
 i = 1, d = 66 ✅
 i = 2, d = 66 ✅
 i = 3, d = 93
 i = 4, d = 126

 Testcase #3 ...
 i = 0, d = 1510930136
 i = 1, d = 1388280216
 i = 2, d = 1339532094
 i = 3, d = 1134576306
 i = 4, d = 1009957100 ✅
 i = 5, d = 1009957100 ✅
 i = 6, d = 1088888954
 i = 7, d = 1100420558
 i = 8, d = 1965006404
 i = 9, d = 2086794484
 
 */

class ConnectingCars_org {
public:
  long long minimizeCost(vector<int> ps, vector<int> ls) {
    int N=SZ(ps);
    vector<pair<LL,LL>> rs;
    REP(i,N) rs.emplace_back(ps[i],ps[i]+ls[i]);
    sort(rs.begin(),rs.end());
    
    int li=-1,ri=-1;
    LL l=-1,r=-1;
//    if(N&1) {
      l=rs[N/2].first,r=rs[N/2].second;
      li=N/2-1,ri=N/2+1;
/*
    } else {
      // this condition is not actually necessary
      // if there are even cars, there are two middle cars.
      // result is same no matter which one is picked
      l=r=(rs[N/2-1].second+rs[N/2].first)/2LL;
      li=N/2-1,ri=N/2;
    }*/
//    dump4(li,l,r,ri);
    LL res=0;
    for(int i=li; i>=0; --i) {
      LL len=rs[i].second-rs[i].first;
      res+=abs(rs[i].second-l);
      l-=len;
    }

    for(int i=ri; i<N; ++i) {
      LL len=rs[i].second-rs[i].first;
      res+=abs(rs[i].first-r);
      r+=len;
    }
    return res;
  }
};

class ConnectingCars_wrong {
  public:
  long long minimizeCost(vector<int> ps, vector<int> ls) {
    vector<pair<LL,LL>> rs;
    int N=SZ(ps);
    REP(i,N) rs.emplace_back(ps[i],ps[i]+ls[i]);
    sort(rs.begin(),rs.end());
    
    LL mid=(rs.front().second+rs.back().first)/2;
    
    LL st=lower_bound(rs.begin(),rs.end(),make_pair(mid,mid))-rs.begin();
    LL res=abs(mid-rs[st].first),l=mid,r=mid+(rs[st].second-rs[st].first);
    
    if(st>0&&rs[st-1].second-mid<(rs[st].first-mid)) {
      st=st-1;
      res=abs(mid-rs[st].second);
      l=mid-(rs[st].second-rs[st].first);
      r=mid;
    }
    
    dump4(l,r,mid,st);
    dump(res);
    
    for(int i=st-1; i>=0; --i) {
      LL len=rs[i].second-rs[i].first;
      res+=rs[i].second-l;
      l-=len;
    }
    for(int i=st+1; i<N; ++i) {
      LL len=rs[i].second-rs[i].first;
      res+=rs[i].first-r;
      r+=len;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("ConnectingCars.sample");

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

bool do_test(vector<int> positions, vector<int> lengths, long long __expected) {
    time_t startClock = clock();
    ConnectingCars *instance = new ConnectingCars();
    long long __result = instance->minimizeCost(positions, lengths);
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
        vector<int> positions;
        from_stream(positions);
        vector<int> lengths;
        from_stream(lengths);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(positions, lengths, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505083736;
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
        cout << "ConnectingCars (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
