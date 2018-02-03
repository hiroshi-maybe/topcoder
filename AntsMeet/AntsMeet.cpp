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
 
 2/2/2018
 
 8:47-9:07 sample 3 doesn't pass
 9:20 (0.5,y) missing meeting point
 10:00 it turns out that plugin was putting "" for only sample 3 somehow 😡
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+541
   - multiply by 2 only when comparing positions is smart
  - http://d.hatena.ne.jp/kusano_prog/20120423/1335206994
  - http://d.hatena.ne.jp/komiyam/20120424/1335261426
  - http://mayokoex.hatenablog.com/entry/2016/04/14/085747
  - http://kg86.hatenablog.com/entry/20130721/1374386182
  - http://topcoder.g.hatena.ne.jp/agw/20120424/1335245859
  - http://topcoder.g.hatena.ne.jp/kojingharang/20120426#1335404289
  - http://lepton.hatenablog.jp/entry/20120424/1335273075
  - http://naoyat.hatenablog.jp/category/TopCoder?page=1371631766
  - http://antipasgroup.lemonblog.co/entry/75/
 
 Key:
  - multiply by 2 to process meeting at intermediate position
  - coordinate "expansion" (<-> coordinate compression) is nice word
 
 Summary:
  - greed plugin bug in sample processing 😡
 
 */

// bfs, O(N^2*4000) time
class AntsMeet {
public:
  int countAnts(vector<int> X, vector<int> Y, string D) {
    unordered_map<char,II> moves={{'N',{0,1}},{'E',{1,0}},{'S',{0,-1}},{'W',{-1,0}}};
    int N=SZ(X);
    int done[51]={};
    REP(i,N) X[i]*=2,Y[i]*=2;
    
    REP(_,4005) {
      REP(i,N) X[i]+=moves[D[i]].first,Y[i]+=moves[D[i]].second;
      REP(i,N) if(!done[i]) {
        bool ok=true;
        FOR(j,i+1,N) if(!done[j]&&X[i]==X[j]&&Y[i]==Y[j]) {
          done[j]=true,ok=false;
        }
        if(!ok) done[i]=true;
      }
    }
    
    int res=0;
    REP(i,N) res+=done[i]==0;
    
    return res;
  }
};

// bfs, O(N*lg N*4000) time
class AntsMeet__ {
  public:
  int countAnts(vector<int> X, vector<int> Y, string D) {
    unordered_map<char,II> moves={{'N',{0,1}},{'E',{1,0}},{'S',{0,-1}},{'W',{-1,0}}};
    queue<tuple<int,int,int>> Q;
    int N=SZ(X);
    int done[51]={};
    map<II,VI> viz;
    REP(i,N) Q.emplace(i,2*X[i],2*Y[i]);
    
    REP(_,4005) {
      int M=SZ(Q);
      map<II,VI> viz;
      REP(_,M) {
        auto t=Q.front();
        Q.pop();
        int i,x,y;
        tie(i,x,y)=t;
        if(done[i]) continue;
        int xx=x+moves[D[i]].first,yy=y+moves[D[i]].second;
        viz[{xx,yy}].push_back(i);
        Q.emplace(i,xx,yy);
      }
      FORR(kvp,viz) if(SZ(kvp.second)>1) FORR(i,kvp.second) done[i]=1;
    }
    
    int res=SZ(Q);
    
    while(SZ(Q)) {
      auto t=Q.front();
      Q.pop();
      int i,x,y;
      tie(i,x,y)=t;
      dump3(i,x,y);
    }
    
    return res;
  }
};

// CUT begin
ifstream data("AntsMeet.sample");

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

bool do_test(vector<int> x, vector<int> y, string direction, int __expected) {
    time_t startClock = clock();
    AntsMeet *instance = new AntsMeet();
    int __result = instance->countAnts(x, y, direction);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        string direction;
        from_stream(direction);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, direction, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517590059;
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
        cout << "AntsMeet (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
