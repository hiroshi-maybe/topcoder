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
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 8/27/2018
 
 21:32-23:00 submit and WA
 23:13 bug fix and got AC
 
 Editorials:
  - http://kmjp.hatenablog.jp/entry/2017/02/03/0900
  - http://hamko.hatenadiary.jp/entry/2017/02/13/175119
  - http://topcoder.g.hatena.ne.jp/firewood/20170213/1487000346
 
 Summary:
  - I was completely confused about relationship between distance and number of blocks
  - Keep invariant `.` addition == +1 distance. Otherwise messed up.
  - Be cautious lower bound of additional zigzag block
 
   ...............
   ..............*
   ...............
 
  At least distance 5 is added. If remaining <=4, keep adding empty rows.
 
 */

void test(int K, vector<string> res) {
  int tot=0;
  REP(i,SZ(res)) {
    tot+=count(res[i].begin(),res[i].end(),'.');
  }
  dump2(tot,K);
  
  if(tot-1!=K) dumpAR(res);
  assert(tot-1==K);
}

class MazeConstruct {
public:
  vector<string> construct(int k) {
    int K=k;
    vector<string> res;
    
    string s1(50,'.'),s2=string(49,'#')+".",s3="."+string(49,'#');
    if(k<=49) {
      res.push_back(string(k+1,'.'));
    } else if(k<=98) {
      res.push_back(s1);
      k-=49;
      assert(k<=49);
      while(k--) res.push_back(s2);
    } else {
      res.push_back(s1);
      k-=49;
      while(k>=102) {
        res.push_back(s2);
        res.push_back(s1);
        res.push_back(s3);
        res.push_back(s1);
        k-=102;
      }
      if(k>0) {
        k-=1;
        res.push_back(s2);
      }
      if(k>=3) {
        int w=(k-1)/2-1;
        res.push_back(string(50-w-1,'#')+string(w+1,'.'));
        res.push_back(string(50-w-1,'#')+string(1,'.')+string(w,'#'));
        res.push_back(string(50-w-1,'#')+string(w+1,'.'));
        k-=2*(w+1)+1;
      }
      while(k-->0) {
        res.push_back(s2);
      }
    }
    
    test(K,res);
    
    return res;
  }
};

class MazeConstruct_org {
  public:
  vector<string> construct(int K) {
    int KK=K;
    vector<string> res;
    
    string s1(50,'.'),s2(50,'#');
    
    string s;
    REPE(_,min(49,K)) s+='.';
    res.push_back(s);
    if(K<50) return res;
    s=s2; s[49]='.';
    res.push_back(s);
    if(K==50) return res;
    
    K-=50;
    int x=K/102,p=K%102;
    
    dump2(x,p);
    
    REP(_,x) {
      res.push_back(s1);
      string s=s2; s[0]='.';
      res.push_back(s);
      res.push_back(s1);
      s=s2; s[49]='.';
      res.push_back(s);
    }
    dump(p);
    if(p) {
      p-=1;
      if(p==0) {
        string s=s2; s[49]='.';
        res.push_back(s);
        return res;
      }
    }
    int y=p/2-1;
    dump2(y,p);
    if(y>0) {
      string t=s1;
      REP(i,50-y-1) t[i]='#';
      res.push_back(t);
      s=s2; s[50-y-1]='.';
      res.push_back(s);
      res.push_back(t);
      
      if(p%2==1) {
        s=s2; s[49]='.';
        res.push_back(s);
      }
    } else {
      dump(p);
      if(p>0)REPE(_,p) {
        s=s2; s[49]='.';
        res.push_back(s);
      }
    }
    
    test(KK,res);
    
    return res;
  }
};

// CUT begin
ifstream data("MazeConstruct.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(int k, vector<string> __expected) {
    time_t startClock = clock();
    MazeConstruct *instance = new MazeConstruct();
    vector<string> __result = instance->construct(k);
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
        int k;
        from_stream(k);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1535430694;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MazeConstruct (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
