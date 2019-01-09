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
 
 2/19/2018
 
 16:19-16:40 Submit. However found a bug.
 16:42-16:51 bug fix, resubmit and ACC
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+529
   - embed ones and tens
  - https://topcoder.g.hatena.ne.jp/jackpersel/20120115/1326615296
   - embed ones and tens
  - http://purple-jwl.hatenablog.com/entry/20121018/1350548727
   - smart conversion with subtraction
  - http://kujira16.hateblo.jp/entry/20120115/1326609669
  - http://kg86.hatenablog.com/entry/20130409/1365506435
 
 Summary:
  - Just do it. This is not so interesting problem.
 
 */

string ones[10]={"","I","II","III","IV","V","VI","VII","VIII","IX"};
string tens[10]={"","X","XX","XXX","XL","L"};

class KingSort {
public:
  vector<string> getSortedList(vector<string> X) {
    vector<tuple<string,int,string>> A;
    FORR(x,X) A.push_back(parse(x));
    
    sort(A.begin(),A.end());
    vector<string> res;
    FORR(t,A) res.push_back(get<2>(t));
    return res;
  }
  
  tuple<string,int,string> parse(string S) {
    vector<string> T;
    string n,r;
    stringstream(S) >> n >> r;
    return make_tuple(n,parser(r),S);
  }
  
  int parser(string S) {
    FORE(n,1,50) if(S==tens[n/10]+ones[n%10]) return n;
    assert(false);
    return 0;
  }
};

class KingSort_org {
  public:
  vector<string> getSortedList(vector<string> X) {
    vector<tuple<string,int,string>> A;
    FORR(x,X) A.push_back(parse(x));
    
    sort(A.begin(),A.end());
    vector<string> res;
    FORR(t,A) res.push_back(get<2>(t));
    return res;
  }
  
  tuple<string,int,string> parse(string S) {
    vector<string> T;
    istringstream ss(S);
    string token;
    while(getline(ss,token,' ')) {
      T.push_back(token);
    }
    return make_tuple(T[0],dig(T[1]),S);
  }
  
  int dig(string S) {
    int a=0,i=0,N=SZ(S);
    while(i<N&&S[i]=='X') ++i;
    if(i<N&&S[i]=='L') a=i>0?40:50,++i;
    else if(i>0) a=10*i;
    
//    dump2(S,a);
    S=S.substr(i); i=0; N=SZ(S);
    while(i<N&&S[i]=='I') ++i;
    if(i>0&&i<N&&S[i]=='V') {
      a+=4;
      dump2(S,a);
      return a;
    } else if(i>0&&i<N&&S[i]=='X') {
      a+=9;
      dump2(S,a);
      return a;
    } else if(i>0) {
      a+=i;
      dump2(S,a);
      return a;
    }

    if(i<N) {
      assert(i==0&&S[i]=='V');
      ++i;
      a+=5+N-i;
    }

    dump2(S,a);
    return a;
  }
};

// CUT begin
ifstream data("KingSort.sample");

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

bool do_test(vector<string> kings, vector<string> __expected) {
    time_t startClock = clock();
    KingSort *instance = new KingSort();
    vector<string> __result = instance->getSortedList(kings);
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
        vector<string> kings;
        from_stream(kings);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(kings, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519085936;
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
        cout << "KingSort (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
