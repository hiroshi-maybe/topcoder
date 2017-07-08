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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/7/2017
 
 8:33-9:29 (201.50 pt) passed system test
 shit. completely forgot topological sort and spent a lot of time!
 
 23:36 read http://webcache.googleusercontent.com/search?q=cache:Ba7gyfNSkwgJ:kmjp.hatenablog.jp/entry/2017/01/17/0900_1+&cd=5&hl=en&ct=clnk&gl=us&client=safari
 
 23:41-23:47 add solution of floyd-warshall
 
 */

int E[26][26];
// Floyd-Warshall O(∑w[i]^2+26^3)
class AlphabetOrderDiv2 {
public:
  string isOrdered(vector<string> ws) {
    FORR(w,ws) REP(i,SZ(w)) FOR(j,i+1,SZ(w)) E[w[i]-'a'][w[j]-'a']=1;
    REP(k,26)REP(i,26)REP(j,26) E[i][j] |= E[i][k]&E[k][j];
    REP(i,26) FOR(j,i+1,26) if(E[i][j]&&E[j][i]) return "Impossible";
    return "Possible";
  }
};

int IN[26][26];
int OUT[26][26];
// Topological sort, O(∑w[i]^2+26^2+26)
class AlphabetOrderDiv2_tsort {
public:
  string isOrdered(vector<string> ws) {
    memset(IN,0,sizeof(IN));
    memset(OUT,0,sizeof(OUT));
    
    FORR(w,ws) {
      REP(i,SZ(w)) FOR(j,i+1,SZ(w)) {
        if (w[i]-'a'==w[j]-'a') continue;
        OUT[w[i]-'a'][w[j]-'a']=1;
        IN[w[j]-'a'][w[i]-'a']=1;
      }
    }
    
    queue<int> Q;
    REP(u,26) {
      bool ok=true;
      REP(v,26) if(IN[u][v]) {
        ok=false; break;
      }
      if (ok) Q.push(u);
    }
    
    while(Q.size()) {
      int u=Q.front(); Q.pop();
      
      REP(v,26) if(OUT[u][v]) {
        IN[v][u]=0;
        OUT[u][v]=0;
        
        bool ok=true;
        REP(w,26) if(IN[v][w]) {
          ok=false; break;
        }
        if (ok) Q.push(v);
      }
    }
    
    REP(u,26) REP(v,26) {
      if (IN[u][v]) return "Impossible";
    }
    
    return "Possible";
  }
};

// CUT begin
ifstream data("AlphabetOrderDiv2.sample");

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

bool do_test(vector<string> words, string __expected) {
    time_t startClock = clock();
    AlphabetOrderDiv2 *instance = new AlphabetOrderDiv2();
    string __result = instance->isOrdered(words);
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
        vector<string> words;
        from_stream(words);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(words, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499441565;
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
        cout << "AlphabetOrderDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
