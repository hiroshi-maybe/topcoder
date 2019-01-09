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
 
 8/28/2018
 
 16:30-17:36 give up
 17:52 add solution
 
 Editorials:
  - https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm402
  - https://topcoder.g.hatena.ne.jp/yowa/20100802/1280696058
 
 References:
  - https://math.stackexchange.com/questions/521609/finding-expected-value-with-recursion
  - https://en.wikipedia.org/wiki/Law_of_total_expectation
  - http://math314.hateblo.jp/entry/2013/12/12/232045
  - https://mathtrain.jp/completegacha
 
 Linearity of expectation is not easy to apply in this problem because swap operation follows the same state transition multiple times.
 If we build a graph for initial state s1: [3,2,1], we have below transition graph.
 
 s1: [3,2,1], s2: [2,3,1], s3: [2,1,3], s4: [1,3,2], s5: [1,2,3], s6: [3,1,2]
 
 s1->s2 (1/3), s1->s5 (1/3), s1->s6(1/3)
 s2->s3 (1/2), s2->s4 (1/2)
 s3->s5 (1/1)
 s4->s5 (1/1)
 s6->s3 (1/2), s6->s4 (1/2)
 
 This graph forms DAG because inversion monotonically decreases.
 If we want to apply linearity of expectation, we need to compute probability that each edge is passed.
 For example, there are two routes which goes through s3->s5
  1) s1->s2->s3->s5 (1/3*1/2)
  2) s1->s6->s3->s5 (1/3*1/2)
 
 Thus Pr(x=s3,s5) = Pr(route #1) + Pr(route #2) = 1/3
 If we want to compute expectation by linearity of expectation, we can compute such probabilities for all the edges and sum them up.
 It's not straightforward to compute it due to deep dependency (conditional probability).
 Thus computing by recurrence relation is easier in this problem.
 
 Key:
  - Recurrence relation forms DAG => dp
 
 Summary:
  - This problem was not about linearity of expectation 😞
  - My understanding of linearity of expectation is not enough 😞😞
  - Nice chance to learn why recurrence relation works
   - law of total expectation ✨
   - conditional expectation ✨
  - Recurrence relation seems to be making "local" sample space to compute overall expectation
  - Use linearity of expectation when probability of indicator function can be computed easily. If it's in the deep conditional dependency, recurrence relation is easier
  - Carefully find better tool to solve problem. Don't go rush without analyzing problem
 
 */

map<VI,int> inv;
map<VI,double> memo;
class RandomSort {
  public:
  int N;
  double f(VI P) {
    if(memo.count(P)) return memo[P];
    if(inv[P]==0) return memo[P]=0.0;
    
    double p=1.0/inv[P];
    double res=0;
    REP(j,N)REP(i,j) if(P[i]>P[j]) {
      VI Y=P;
      swap(Y[i],Y[j]);
      res+=p*f(Y);
    }
    return memo[P]=res+1.0;
  }
  
  double getExpected(vector<int> P) {
    N=SZ(P);
    
    VI X(N);
    REP(i,N) X[i]=i+1;
    do {
      int x=0;
      REP(j,N)REP(i,j) if(X[i]>X[j]) ++x;
      inv[X]=x;
    } while(next_permutation(X.begin(),X.end()));
    
    return f(P);
  }
};

// CUT begin
ifstream data("RandomSort.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> permutation, double __expected) {
    time_t startClock = clock();
    RandomSort *instance = new RandomSort();
    double __result = instance->getExpected(permutation);
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
        vector<int> permutation;
        from_stream(permutation);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(permutation, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1535499019;
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
        cout << "RandomSort (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
