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
 
 1/30/2018
 
 9:43-10:07 pause
 10:20-10:35 pause
 18:30-18:46 give up
 18:47-19:05 read editorial
 
 2/1/2018
 
 18:20-18:50 write analysis
 
 Let's compute expected value of ws[i]. The same algorithm works for other words as well.
 
 What we want to compute is E[X], X is random variable which represents final position of ws[i].
 Definition of expectation shows
 E[X] = ∑ { x*Pr{X=x} : x=0..N-1 }
 
 However Pr{X=x} is not easy to compute because we need to try all the permutations to determine final position.
 Now we try to represent random variable `X` with sum of other random variables to leverage linearity of expectation.
 
 If ws[i] is larger than n words, position of ws[i] is `n`.
 Let's define random variable I_j below:
 
   X_j
 = I {ws[i] > ws[j]}
 = 1 if ws[i] > ws[j]
   0 if ws[i] < ws[j]
 
 I_j is a function to map original sample space into a new measure space with boolean σ-algebra
 
 X = ∑ { X_j : j !=i }
 
   E[X]
 = ∑ { E[X_j] : j !=i } // linearity of expectation
 = ∑ { Pr{ ws[i] > ws[j] } : j !=i } // CLRS 5.2 Lemma 5.1

 CLRS 5.2 Lemma 5.1:
 > Given a sample space S and an event A in the sample space S, let X_A=I{A}. Then E[X_A]=Pr{A}
 
 How to compute Pr{ ws[i] > ws[j] }?
 
 Let's compare ws[i] "ababcabc" with ws[j] "bcabaaca"
 
 ws[i]="ababcabc"
 ws[j]="bcabaaca"
        jj^^i^ji
 
 5 characters are different.
 If one of indice of those characters are selected first, order is determined.
 Pr {ws[i]>ws[j]} = 2/5
 
 So it's possible to compute E[X] in O(N).
 We need to compute it for other words as well. Total runtime is O(N^2*L) time.
 
 18:50-19:00 implement and ACC
 
 Key:
  - Computation of probability which satisfies expected random variable is
    - Use linearity of expectation
  - Represent random variable with sum of indicator random variable
    - win/lose in comparison is an event that indicator random variable shows
    - Summing up win events eventually is equal to expected random variable
  - Computation of probability of win/lose event is possible in O(L)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+542
  - http://kmjp.hatenablog.jp/entry/2014/01/04/0930
  - http://area.hateblo.jp/entry/2013/10/24/030455
 
 Summary:
  - I looked for DP solution though, no luck. Actually math solution was expected 👎
  - This is basic problem if understanding linearity of expectation and random variable
  - I spent two days to go through basics of probability space and expectation
  - Another failure is not acceptable 😡
  - Pay more attention to random variable and try to map it to sum of different ones
 
 */
class StrangeDictionary {
  public:
  vector<double> getExpectedPositions(vector<string> ws) {
    int N=SZ(ws), L=SZ(ws[0]);
    
    vector<double> res(N);
    REP(i,N) {
      REP(j,N) if(i!=j) {
        double a=0,b=0;
        REP(k,L) if(ws[i][k]!=ws[j][k]) (ws[i][k]>ws[j][k]?a:b)++;
        dump4(i,j,a,b);
        res[i]+=a/(a+b);
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("StrangeDictionary.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool double_vector_equal (const vector<double> &expected, const vector<double> &received) {
    if (expected.size() != received.size()) return false;
    int n = expected.size();
    for (int i = 0; i < n; ++i)
        if (!double_equal(expected[i], received[i])) return false;
    return true;
}

bool do_test(vector<string> words, vector<double> __expected) {
    time_t startClock = clock();
    StrangeDictionary *instance = new StrangeDictionary();
    vector<double> __result = instance->getExpectedPositions(words);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_vector_equal(__expected, __result)) {
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
        vector<double> __answer;
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
        int T = time(NULL) - 1517334184;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "StrangeDictionary (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
