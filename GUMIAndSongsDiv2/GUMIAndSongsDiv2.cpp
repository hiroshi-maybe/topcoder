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
 
 11/14/2017
 
 8:32-9:19 most of time to fix a bug due to wrong DP initialization (220.99pt)
 
 Editorials:
  - http://apps.topcoder.com/wiki/display/tc/SRM+588
  - http://d.hatena.ne.jp/semiexp/20130813/1376357527
    - problem writer
  - http://emkcsharp.hatenablog.com/entry/SRM588/GUMIAndSongsDiv2
  - http://kenkoooo.hatenablog.com/entry/2016/04/27/015828
 
 22:05-22:15 add greedy solution
 
 We can brute-force all the used songs (<=2^15≈3*10^4).
 Now we want to minimize time due to tones.
 
 Suppose we have three songs with tones a,b,c and a<b<c.
 We can compute cool down time in order s1={a,b,c} and s2={b,a,c}.
 
 T(s1)=b-a+c-b=c-a
 T(s2)=b-a+c-a=b+c-2a
 
 T(s1)-T(s2)=c-a-(b+c-2a)=a-b<0 => T(s1)<T(s2)
 Thus singing in ascendent order seems to be optimal.
 It's possible to prove it by induction.
 If Gumi sings songs in order of non-descendent tones `s`, sum of cool down time is max(s)-min(s).
 
 So we can compute minimum time to sing songs for each subset, in linear time O(N).
 
 Key:
  - N is small. It's easy to brute-force used songs by bitmask
  - Compute minimul tones in greedy way or dp
 
 Summary:
  - Analysis was straightforward in about 20 mins
  - It took much time to fix a bug due to ZERO(dp) 👎
   - My code was not differentiating unvisited state in dp table
   - Use `Inf` accordingly
 
 Same as my DP solution:
  - https://community.topcoder.com/stat?c=problem_solution&rm=318478&rd=15700&pm=12707&cr=23183771
 
 */
// dp, O(N^2*2^N) time, O(N*2^N) space
int dp[1<<15][15];
class GUMIAndSongsDiv2_org {
  public:
  int maxSongs(vector<int> ds, vector<int> ts, int T) {
    int N=SZ(ds);
    const int Inf=1e8+10;
    REP(mask,1<<N)REP(i,N) dp[mask][i]=Inf;
    REP(i,N) dp[1<<i][i]=ds[i];
    REP(mask,1<<N) REP(last,N) {
      REP(i,N) if(((mask>>i)&1)==0) {
        int t1=dp[mask][last];
        int mask2=mask|(1<<i);
        dp[mask2][i]=min(dp[mask2][i],t1+abs(ts[i]-ts[last])+ds[i]);
      }
    }
    
    int res=0;
    FOR(mask,1,1<<N) REP(last,N) if(dp[mask][last]<=T) {
      res=max(res,__builtin_popcount(mask));
    }
    return res;
  }
};

// greedy, O(N*2^N+N*lg N) time, O(N) space
class GUMIAndSongsDiv2 {
public:
  int maxSongs(vector<int> ds, vector<int> ts, int T) {
    int N=SZ(ds);
    int res=0;
    
    vector<II> ps;
    REP(i,N) ps.emplace_back(ts[i],ds[i]);
    sort(ps.begin(),ps.end());
    
    REP(mask, 1<<N) {
      int t=0;
      int maxt=0,mint=1e5+10;
      REP(i,N) if((mask>>i)&1) {
        t+=ps[i].second;
        maxt=max(maxt,ps[i].first);
        mint=min(mint,ps[i].first);
      }
      t+=maxt-mint;
      if(t<=T) res=max(res,__builtin_popcount(mask));
    }
    return res;
  }
};

// CUT begin
ifstream data("GUMIAndSongsDiv2.sample");

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

bool do_test(vector<int> duration, vector<int> tone, int T, int __expected) {
    time_t startClock = clock();
    GUMIAndSongsDiv2 *instance = new GUMIAndSongsDiv2();
    int __result = instance->maxSongs(duration, tone, T);
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
        vector<int> duration;
        from_stream(duration);
        vector<int> tone;
        from_stream(tone);
        int T;
        from_stream(T);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(duration, tone, T, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510677160;
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
        cout << "GUMIAndSongsDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
