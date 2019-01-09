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
 
 9/1/2018
 
 17:23-17:27 analysis
 18:02-18:25 pause
 
 9/2/2018
 
 15:20-15:52 AC
 
 Editorials:
  - https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm417
  - http://topcoder.g.hatena.ne.jp/n4_t/20081222/1230196118
  - https://ameblo.jp/utmath/entry-10972110454.html?frm=theme
  - http://logfiles.hatenablog.com/entry/20140902/1409655865
 
 @anta's code is very short. It's not doing unnecessary substring to make things complex.
 
 Summary:
  - What a boring implementation problem!
 
 */

class TemplateMatching {
public:
  string bestMatch(string T, string P, string S) {
    int N=SZ(T);
    int PN=SZ(P),SN=SZ(S);
    tuple<int,int,string> res=make_tuple(0,0,"~");
    REP(l,N) FORE(r,l+1,N) {
      int a=0,b=0;
      REPE(x,PN) if(x<=r-l) {
        if(P.substr(PN-x,x)==T.substr(l,x)) a=x;
      }
      REPE(x,SN) if(x<=r-l) {
        if(S.substr(0,x)==T.substr(r-x,x)) b=x;
      }
      a=-a,b=-b;
      SMIN(res,make_tuple(a+b,a,T.substr(l,r-l)));
    }
    return get<2>(res);
  }
};

class TemplateMatching_org {
  public:
  string P,S;
  
  string suf(string s, int l) {
    reverse(s.begin(),s.end());
    string t=s.substr(0,l);
    reverse(t.begin(),t.end());
    return t;
  }
  int maxmatch(string s, string t) {
    int res=0;
    int N=SZ(s),M=SZ(t);
    REPE(l,min(N,M)) {
      string tt=suf(t,l);
      if(tt==s.substr(0,l)) res=l;
    }
    return res;
  }
  
  II f(string s) {
    int a=maxmatch(s,P);
    reverse(s.begin(),s.end()),reverse(S.begin(),S.end());
    int b=maxmatch(s,S);
    reverse(S.begin(),S.end());
    return {a+b,a};
  }
  
  string bestMatch(string T, string P, string S) {
    this->P=P,this->S=S;
    int N=SZ(T);
    string res="~";
    REP(i,N) {
      string t;
      REP(l,N-i) {
        t+=T[i+l];
        
        II p1=f(t);
        II p2=f(res);
        if(p1>p2) res=t;
        else if(p1==p2&&t<res) res=t;
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("TemplateMatching.sample");

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

bool do_test(string text, string prefix, string suffix, string __expected) {
    time_t startClock = clock();
    TemplateMatching *instance = new TemplateMatching();
    string __result = instance->bestMatch(text, prefix, suffix);
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
        string text;
        from_stream(text);
        string prefix;
        from_stream(prefix);
        string suffix;
        from_stream(suffix);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(text, prefix, suffix, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1535847794;
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
        cout << "TemplateMatching (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
