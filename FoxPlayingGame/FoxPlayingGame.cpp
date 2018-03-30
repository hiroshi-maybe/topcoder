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
#define dpmax(a,b) a = max(a,b)
#define dpmin(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/28/2018
 
 9:19-9:46 ACC (295.66 pt)
 
 3/29/2018
 
 Read editorials and add solution by DP.
 Also I showed that remembering only maximal and minimal is sufficient to solve by DP.
 
 Editorials:
  - http://topcoder.g.hatena.ne.jp/JAPLJ/20110331
  - http://d.hatena.ne.jp/kusano_prog/20110330/1301498390
  - http://rsujskf.blog32.fc2.com/blog-entry-1905.html
  - http://kg86.hatenablog.com/entry/20130517/1368817347
  - http://kyuridenamida.hatenablog.com/entry/2011/03/30/231757
  - http://peryaudo.hatenablog.com/entry/20110330/1301502233
  - http://techtipshoge.blogspot.com/2011/03/srm-brushup-foxplayinggame-501-div2.html
 
 In dp solution, keeping only max value does not form optimal substructure.
 We need to show that keeping only minimal and maximal is sufficient.
 I thought, I need neg min, neg max, pos min and pos max are needed though, that's not the case 😞
 Also initial value in dp needs some attention to be paid. Also memory was broken due to out of index error 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
 
 Theorem: `a` or `c` can be maximal when we have a,b,c s.t. a<b<c
 
 Lemma1: theorem holds for multiplication operation
 
 Suppose we are multiplying `p`.
 
 i) p>0
  a*p<b*p<c*p holds. Thus `c` gives maximal
 ii) p=0
  a*p=b*p=c*p=0. Thus `a` or `c` gives maximal
 iii) p<0
  c*p<b*p<a*p. Thus `a` gives maximal
 
 From i)~iii), `a` or `c` (minimal or maximal) is sufficient to compute maximal for multiplication.
 Note that above discussion is correct regardless of sign of a, b or c.
 Even if a and b are negative like a<b<0<c, result of `p` follows above discussion.
 
 For multiplication, `a` or `c` gives maximal.
 
 Lemma2: theorem holds for addition operation
 
 Suppose we are adding `p`.
 
 i) p>0
  a+p<b+p<c+p holds. Thus `c` gives maximal
 ii) p=0
  a+p<b+p<c+p. Thus `c` gives maximal
 iii) p<0
  a+p<b+p<c+p. Thus `c` gives maximal
 
 In addition, `c` always gives maximal
 
 From Lemma1 and Lemma2, minimal and maximal value is sufficient to obtain maximal value for addition and multiplication operations.
 
 Summary:
  - I tried to classify cases scoreB<-1,-1<scoreB<0,0<scoreB<1,1<scoreB first. I figured out it's too complicated 🤔
  - It's nice to figure out that classification is hard early
  - Eventually I went greedy way. After submission, I did informal proof
   - I wanted to show that multiplication does not stay between addition
   - I proved that {add,mul,add,mul} or {mul,add,mul,add} cannot be maximal
   - Thus I expected {mul}* + {add,..,.add} + {mul}* gives optimal solution
   - This is not sufficient proof though, I had a bit confidence about my solution
  - DP in editorials was completely out of my mind 😅
 
 */

double dpmin[52][52],dpmax[52][52];
class FoxPlayingGame {
public:
  double theMax(int nA, int nB, int paramA, int paramB) {
    double sA=1.0*paramA/1000.0,sB=1.0*paramB/1000.0;
    const double Inf=numeric_limits<double>::max();//50*10*pow(2,50);
    REPE(a,nA)REPE(b,nB) dpmin[a][b]=Inf,dpmax[a][b]=-Inf;
    dpmin[0][0]=0,dpmax[0][0]=0;
//    dump2(sA,sB);
    REPE(a,nA) REPE(b,nB) {
      dpmax[a+1][b]=max({dpmax[a+1][b],dpmax[a][b]+sA,dpmin[a][b]+sA});
      dpmax[a][b+1]=max({dpmax[a][b+1],dpmax[a][b]*sB,dpmin[a][b]*sB});
      dpmin[a+1][b]=min({dpmin[a+1][b],dpmax[a][b]+sA,dpmin[a][b]+sA});
      dpmin[a][b+1]=min({dpmin[a][b+1],dpmax[a][b]*sB,dpmin[a][b]*sB});
    }
    return dpmax[nA][nB];
  }
};

class FoxPlayingGame_greedy {
  public:
  double add(double sA, int n) {
    double res=0;
    REP(_,n) res+=sA;
    return res;
  }
  double mul(double sB, int n, double res) {
    REP(_,n) res*=sB;
    return res;
  }
  double theMax(int nA, int nB, int paramA, int paramB) {
    double sA=1.0*paramA/1000.0,sB=1.0*paramB/1000.0;

    double res=mul(sB,nB,0)+add(sA,nA);
    REP(n,nB) {
      double x=mul(sB,n,0)+add(sA,nA);
      x=mul(sB,nB-n,x);
      res=max(res,x);
    }
    
    return res;
    /*
    double res=0;
    
    // sA=0
    if(paramA==0) return 0;
    // sB=0
    if(paramB==0) return add(sA,nA);
    
    if(paramA<0) {
      if(paramB>0) {
        // min abs
        if(paramB>1) return add(sA,nA);
        return mul(sB,nB,add(sA,nA));
      } else {
        // paramA<0
        
        // sB<=-1
        if(paramB<=-1000) return add(sA,nA);
        
        return mul(sB,nB,add(sA,nA));
      }
    }
    // paramA>0
    
    
    return 0.0;*/
  }
};

// CUT begin
ifstream data("FoxPlayingGame.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(int nA, int nB, int paramA, int paramB, double __expected) {
    time_t startClock = clock();
    FoxPlayingGame *instance = new FoxPlayingGame();
    double __result = instance->theMax(nA, nB, paramA, paramB);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        int nA;
        from_stream(nA);
        int nB;
        from_stream(nB);
        int paramA;
        from_stream(paramA);
        int paramB;
        from_stream(paramB);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(nA, nB, paramA, paramB, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1522297177;
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
        cout << "FoxPlayingGame (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
