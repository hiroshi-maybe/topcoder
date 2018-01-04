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
 
 1/3/2017
 
 11:07-11:45 pause
 17:50-18:00 I finally understood the problem correctly :(
 18:01-19:07 system test passed (1WA due to minor overflow)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+559
  - http://kmjp.hatenablog.jp/entry/2012/11/07/0900
  - http://mayokoex.hatenablog.com/entry/2016/07/13/000849
   - misunderstood problem first
  - http://topcoder.g.hatena.ne.jp/firewood/20121124/1353759956
   - misunderstood problem first
  - https://chngng.blogspot.com/2015/05/srm-559-div1-easy-hyperknight.html

 Key:
  - Simulate and find distribution of possible moves in the board. We can find area with certain property.
 
 Summary:
  - I misunderstood problem as well as div2 hard. I don't like this problem writer.
 
 */
vector< pair < int, int > >  moves = { {1,1},{1,-1},{-1,1},{-1,-1} };
class HyperKnight {
  public:
  LL a,b,R,C;
  int K;
  vector<II> abs;
  // for debug
  int jump(int r, int c) {
    int res=0;
    FORR(ab, abs) FORR(m,moves) {
      int r2=r+ab.first*m.first,c2=c+ab.second*m.second;
      if(r2<0||r2>=R||c2<0||c2>=C) continue;
      ++res;
    }
    return res;
  }
  long long countCells(int _a, int _b, int _R, int _C, int K) {
    if(_a>_b) swap(_a,_b);
    this->a=_a,this->b=_b,this->R=_R,this->C=_C,this->K=K;
    this->abs={{a,b},{b,a}};
    
    if(K==0||K==1||K==5||K==7) return 0;
    LL res2=4LL*a*a;
    if(K==2) return res2;
    LL res3=8LL*a*(b-a);
    if(K==3) return res3;
    LL res6=4LL*((b-a)*(R/2-b)+(b-a)*(C/2-b));
    if(R%2==1) res6+=2LL*(b-a);
    if(C%2==1) res6+=2LL*(b-a);
    if(K==6) return res6;
    LL res8=(R-2*b)*(C-2*b);
    if(K==8) return res8;
    LL res4=R*C-res2-res3-res6-res8;
//    dump3(res2,res3,res6);
//    dump2(res8,res4);
    
    return res4;
  }
};

// CUT begin
ifstream data("HyperKnight.sample");

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

bool do_test(int a, int b, int numRows, int numColumns, int k, long long __expected) {
    time_t startClock = clock();
    HyperKnight *instance = new HyperKnight();
    long long __result = instance->countCells(a, b, numRows, numColumns, k);
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
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int numRows;
        from_stream(numRows);
        int numColumns;
        from_stream(numColumns);
        int k;
        from_stream(k);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, numRows, numColumns, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515006466;
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
        cout << "HyperKnight (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
