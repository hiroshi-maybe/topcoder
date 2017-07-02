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
using namespace std;

// type alias
typedef unsigned long UL;
typedef long long LL;

typedef vector < bool > VB;
typedef vector < int > VI;
typedef vector < string > VS;
typedef vector < vector < int > > VVI;
typedef unordered_map < int, int > MAPII;
typedef unordered_map < string, int > MAPSI;
typedef unordered_set < int > SETI;
typedef unordered_set < string > SETS;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
#define REPS(i,arr)  for(int i=0; i<(arr).size(); ++i)

// vector
#define PUSH(s, e) (s).push_back(e)
#define POP(s) (s).pop_back()
#define REVERSE(c) reverse((c).begin(),(c).end())
#define SORT(c) sort((c).begin(),(c).end())
#define CONCAT(a,b) (a).insert((a).begin(), (b).begin(),(b).end())
#define ERASE(arr,i) (arr).erase((arr).begin()+i)

// pair/tuple
typedef pair< int , int > II;
typedef vector<II> VII;
#define MP make_pair
#define _1 first
#define _2 second
typedef tuple< int , int, int > III;
#define MT make_tuple

// matrix
vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };

// priority queue
#define MAX_PQ(T) priority_queue<T>
#define MIN_PQ(T) priority_queue<T,vector<T>,greater<T>>

// binary search
#define LB(a,n,k) lower_bound(a,a+(n),(k))
#define UB(a,n,k) upper_bound(a,a+(n),(k))

// dp
#define DP(dp,i,j) int dp[i][j]
#define FILL(dp,x) memset(dp, x, sizeof(dp))
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

// 13:53-14:45 give up
// read http://kmjp.hatenablog.jp/entry/2017/06/06/0930
// 15:38 passed samples and system tests
class InPrePost {
  public:
  VII M; // {left/right, pre/in/post}
  string isPossible(vector<string> s, vector<int> a1, vector<int> a2, vector<int> a3) {
    REP(i,6) {
      if (s[i]=="pre") M.emplace_back(i%2, 0);
      if (s[i]=="in") M.emplace_back(i%2, 1);
      if (s[i]=="post") M.emplace_back(i%2, 2);
    }
    
    VVI x = {a1,a2,a3};
    if (ok(x)) return "Possible";
    else return "Impossible";
  }
  
  bool ok(VVI &trees) {
    VI pre = trees[0], in = trees[1], post = trees[2];
    int N=SZ(pre);
    if (SZ(in)!=N||SZ(post)!=N) return false;
    if (N==0) return true;
    VI pre_ = pre, in_ = in, post_ = post;
    sort(pre_.begin(),pre_.end()); sort(in_.begin(),in_.end()); sort(post_.begin(), post_.end());
    
//    dump(N);
//    dumpAR(pre); dumpAR(in); dumpAR(post);
    
    REP(i,N) {
      if (pre_[i]!=in_[i]||in_[i]!=post_[i]||post_[i]!=pre_[i]) return false;
    }
    
    int piv=-1;
    REP(i,N) {
      if (in[i]==pre[0]) {
        piv=i; break;
      }
    }
    if (piv==-1) return false;
    int ls = piv;//, rs = N-piv;
    
//    dump2(piv,ls);
    vector<VVI> next(2,VVI(3, VI()));
    
//    dump2(M[0].first,M[0].second);
    next[M[0].first][M[0].second] = VI(pre.begin()+1,pre.begin()+ls+1);
//    dumpAR(next[M[0].first][M[0].second]);
    next[M[1].first][M[1].second] = VI(pre.begin()+ls+1,pre.end());
//    dumpAR(next[M[1].first][M[1].second]);
    next[M[2].first][M[2].second] = VI(in.begin(),in.begin()+ls);
//    dumpAR(next[M[2].first][M[2].second]);
    next[M[3].first][M[3].second] = VI(in.begin()+ls+1,in.end());
//    dumpAR(next[M[3].first][M[3].second]);
    next[M[4].first][M[4].second] = VI(post.begin(),post.begin()+ls);
//    dumpAR(next[M[4].first][M[4].second]);
    next[M[5].first][M[5].second] = VI(post.begin()+ls,prev(post.end()));
//    dumpAR(next[M[5].first][M[5].second]);
    
    return ok(next[0]) && ok(next[1]);
  }
};

// CUT begin
ifstream data("InPrePost.sample");

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

bool do_test(vector<string> s, vector<int> a1, vector<int> a2, vector<int> a3, string __expected) {
    time_t startClock = clock();
    InPrePost *instance = new InPrePost();
    string __result = instance->isPossible(s, a1, a2, a3);
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
        vector<string> s;
        from_stream(s);
        vector<int> a1;
        from_stream(a1);
        vector<int> a2;
        from_stream(a2);
        vector<int> a3;
        from_stream(a3);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, a1, a2, a3, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1498942316;
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
        cout << "InPrePost (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
