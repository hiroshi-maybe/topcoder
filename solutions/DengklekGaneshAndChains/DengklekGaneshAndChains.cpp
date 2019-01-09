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
 
 7/8/2017
 
 TCO 2017 Round 2B div1
 
 9:00-9:25 (187.81 pt) submitted solution which doesn't pass samples because plugin environment was broken :(
 
 7/9/2017
 
 8:55 retry
 9:06 design done (greedy)
 9:17 passed samples but failed system test (bug in complicated loop)
 9:33 passed system test
 
 read http://kmjp.hatenablog.jp/entry/2017/07/09/0900
 9:55 add simpler solution
 
 */

class DengklekGaneshAndChains {
public:
  string getBestChains(vector <string> cs, vector <int> ns) {
    int N=SZ(cs);
    FORR(s,cs) {
      string t=s+s;
      REP(j,SZ(s)) s=max(s,t.substr(j,SZ(s)));
    }
    VI visited(N,0);
    
    sort(cs.begin(),cs.end(), greater<string>());
    
    string res;
    FORR(n,ns) {
      int i=0;
      while(i<N&&visited[i]) ++i;
      assert(i!=N);
      string x=cs[i].substr(0,n);
      res += x;
      
      int k=i;
      while(i<N) {
        if(!visited[i]&&cs[i].substr(0,n)==x) k=i;
        ++i;
      }
      visited[k]=true;
    }
    
    return res;
  }
};

class DengklekGaneshAndChains_mine {
public:
  string getBestChains(vector <string> cs, vector <int> ns) {
    int N=SZ(cs);
    REP(i,N) {
      int m=SZ(cs[i]);
      string maxs=cs[i];
      REP(j,m) {
        string t=cs[i].substr(j,m-j)+cs[i].substr(0,j);
        if (t>maxs) maxs=t;
      }
      cs[i]=maxs;
    }
    VI visited(N,0);
    
    sort(cs.begin(),cs.end(), greater<string>());
    
    string res;
    FORR(n,ns) {
      int i=0;
      while(i<N&&visited[i]) ++i;
      assert(i!=N);
      string x=cs[i].substr(0,n);
      
      int k=i;
      while(i<N) {
        if(!visited[i]&&cs[i].substr(0,n)==x) k=i;
        ++i;
      }
      visited[k]=true;
      res += x;
    }
    
    return res;
  }
};

class DengklekGaneshAndChains_wrong {
public:
  string getBestChains(vector <string> _cs, vector <int> ns) {
    int N=SZ(_cs);
    vector<string> cs(N);
    REP(i,N) cs[i]=_cs[i]+_cs[i];
    VI visited(N,0);
    
    string res;
    FORR(n,ns) {
      int cur=-1; string maxs="";
      REP(i,N) {
        if(visited[i]) continue;
        string s=cs[i];
        REP(j,SZ(s)-n) {
          string t=s.substr(j,n);
          if (t>maxs) {
            cur=i;
            maxs=t;
          }
        }
      }
      
      assert(cur!=-1);
      visited[cur]=1;
      res += maxs;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("DengklekGaneshAndChains.sample");

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

bool do_test(vector<string> chains, vector<int> lengths, string __expected) {
    time_t startClock = clock();
    DengklekGaneshAndChains *instance = new DengklekGaneshAndChains();
    string __result = instance->getBestChains(chains, lengths);
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
        vector<string> chains;
        from_stream(chains);
        vector<int> lengths;
        from_stream(lengths);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(chains, lengths, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499615405;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DengklekGaneshAndChains (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
