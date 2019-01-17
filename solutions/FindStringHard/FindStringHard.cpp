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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stdout, ##args); putc('\n',stdout); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cout<<*begin<<','; } cout<<endl; } }

/*
 
 1/15/2019 SRM 746
 
 9:49-10:30 give up
 
 I tried to solve by composing OEIS sequence. However I had no luck.
 https://oeis.org/search?q=1%2C2%2C4%2C6%2C9&language=english&go=Search
 
 It was nice to try to construct by "abab" pattern.
 
 1/16/2019
 
 15:30-16:20 from clues in tweets I analyzed by myself and got AC

 https://www.topcoder.com/blog/single-round-match-746-editorials/
 http://kmjp.hatenablog.jp/entry/2019/01/17/1000
 http://topcoder.g.hatena.ne.jp/Hiro180/20190116/1547631358
 https://twitter.com/satanic0258/status/1085246984368189440
 https://twitter.com/uwitenpen/status/1085247548594388992
 https://twishort.com/cUtnc
 
 Key:
  - Compose "ababa.." component (odd length) to glue by "aa" separated components without unexpected match with the glue
  - "ababaabababb" should not happen because "aa" and "bb" may cause unpexpected match
  - If 1 remains, add even component "ab" which does not cause redundant match.
 
 */
class FindStringHard {
public:
  string withAntipalindromicSubstrings(int N) {
    int NN=N;
//    dump(N);
    VI S;
    int n=0;
    while((n*n/4)<=2000) {
      if(n%2==1) S.push_back(n*n/4);
      ++n;
    }
//    REP(i,SZ(S)-1) dump2(i,abs(S[i]-S[i+1]));
    int M=SZ(S);
    
    string res;
    while(N>1) {
      REP(i,M) if(S[i]>N) {
        int l=i-1;
        assert(l>=0&&S[l]>0);
        N-=S[l];
        int p=SZ(res)?res.back()-'a':0;
        string s;
        REP(i,2*l+1) {
          int pp=p^(i%2);
          s.push_back('a'+pp);
        }
        res+=s;
//        dump3(l,S[l],N);
        break;
      }
    }
    if(N==1) res+="ab",N-=1;
    
    assert(N==0);
    assert(SZ(res)<=100);
    int cnt=0;
    REP(i,SZ(res))FORE(l,1,SZ(res)-i) {
      string x=res.substr(i,l);
      string y=x; reverse(ALL(y));
      bool ok=true;
      REP(i,l) if(x[i]==y[i]) ok=false;
      /*
      dump2(i,l);
      dump(x);
      dump(y);
      dump(ok);*/
      cnt+=ok;
    }
//    dump3(res,cnt,NN);
    assert(cnt==NN);
    
    return res;
  }
};

// 9:49-10:30 give up
//vector<int> S={0, 0, 1, 2, 4, 6, 9, 12, 16, 20, 25, 30, 36, 42, 49, 56, 64, 72, 81, 90, 100, 110, 121, 132, 144, 156, 169, 182, 196, 210, 225, 240, 256, 272, 289, 306, 324, 342, 361, 380, 400, 420, 441, 462, 484, 506, 529, 552, 576, 600, 625, 650, 676, 702, 729, 756, 784, 812,841,870,900,};
class FindStringHard_wrong {
  public:
  string withAntipalindromicSubstrings(int N) {
    VI S;
    int n=0;
    while((n*n/4)<=1000) S.push_back(n*n/4),++n;
    REP(i,SZ(S)-1) dump2(i,abs(S[i]-S[i+1]));
    int M=SZ(S);
    
    string res;
    int rem=0;
    REP(i,M) if(S[i]>N) {
      dump(i);
      assert(i>0);
      res=string(i-1,'a');
      REP(i,SZ(res)) if(i%2==1) res[i]='b';
      rem=N-(i-1);
      break;
    }
    dump(res);
    
    string s(2*rem,res.back());
    FOR(i,SZ(s)/2,SZ(s)) s[i]='a'+(1-(res.back()-'a'));
    
    dump(s);
    
    res+=s;
    assert(SZ(res)<=100);
    
    int cnt=0;
    REP(i,N)FORE(l,1,SZ(res)-i) {
      string x=res.substr(i,l);
      string y=x; reverse(ALL(y));
      bool ok=true;
      REP(i,l) if(x[i]==y[i]) ok=false;
      cnt+=ok;
    }
    dump2(cnt,N);
    assert(cnt==N);

    return res;
  }
};

// CUT begin
ifstream data("FindStringHard.sample");

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

bool do_test(int n, string __expected) {
    time_t startClock = clock();
    FindStringHard *instance = new FindStringHard();
    string __result = instance->withAntipalindromicSubstrings(n);
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
        int n;
        from_stream(n);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1547574534;
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
        cout << "FindStringHard (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
