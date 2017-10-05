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
 
 10/4/2017
 
 8:51-9:20,9:30-9:50 give up
 18:30-19:00, 23:00-24:24 read editorial and learn about Gaussian elimination in GF(2)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+621
  - http://kmjp.hatenablog.jp/entry/2014/05/21/1000
 
 Gaussian elimination:
  - https://en.wikipedia.org/wiki/Gaussian_elimination
  - CLRS 28.1 Solving systems of linear equations
 Rank:
  - https://en.wikipedia.org/wiki/Rank_(linear_algebra)
 Gaussian elimination by XOR
  - https://www.hackerearth.com/practice/notes/gaussian-elimination/
  - https://math.stackexchange.com/questions/48682/maximization-with-xor-operator
  - https://math.stackexchange.com/questions/169921/how-to-solve-system-of-linear-equations-of-xor-operation
 GF(2)
  - CLRS "D-2 Permutations defined by matrix-vector multiplication over GF(2)" Problems for Appendix D
  - https://www.cs.umd.edu/~gasarch/TOPICS/factoring/fastgauss.pdf
  - http://personals.ac.upc.edu/enricm/Pubs/pdp2015_slides.pdf
   - great overview of Gaussian elimination in GF(2) ✅

 General knowledge about GF(2)
 
   Gaussian Elimination is defined over an algebraic field
    - Infinite fields: 𝐐, 𝐑
    - Finite fields: Galoius field with 2 elements a.k.a. GF(2)
 
   In GF(2)={0,1}, algebraic operations are represented as below:
    - addition ≡ XOR ≡ subtraction (+1=-1)
    - multiplication ≡ AND
 
   Implementation remarks:
    - Gaussian elimination in infinite fields can be specialized for GF(2)
    - Gauss-Jordan Elimination can be easily merged into GE
    - Pivotting is unnecessary
     - computer arithmetic over GF(2) is always exact
   Applications
    - factoring large integer numbers, cryptography, pattern matching...
 
 Thus Gaussian elimination works in GF(2).
 Now we can just compute rank of GF(2) matrix.
 If we have linearly independent vectors X_a and X_b,
 Any X[i] can be represented as below:
 
 X[i] = (C_a & X_a) ^ (C_b & X_b), C_x ∈ {0,1}
 like... V[i] = C_a * V_a + C_b * V_b in infinite field
 
 Note that ^(XOR) and &(AND) are algebraic operation in GF(2).
 So we have same property as seen in linear algebra in infinite field.
 
 GE in GF(2) gives us linearly independent vectors.
 Expected result is number of those vectors (= rank of original matrix)
 
 We can do LU-decomposition in GF(2) by reducing MSB.
 
 24:24-24:35 add solution
 
 key:
  - solve by computing rank of vector leveraging Gaussian eliminatio in GF(2)
   - number of linearly independent row vector is the solution
 
 summary:
  - I felt like I should remove on bit though, I had no idea to connect to linear algebra 😵
 
 */

int rank_gf2(VI X) {
  int N=SZ(X);
  REP(i,N) {
    sort(X.begin()+i,X.end(),greater<int>());
    if(X[i]==0) return i;
    int msb=1;
    while((msb<<1)<=X[i]) msb<<=1;
    FOR(j,i+1,N) if(X[j]&msb) X[j]^=X[i];
  }
  return N;
}

class MixingColors {
  public:
  int minColors(vector<int> colors) {
    return rank_gf2(colors);
  }
};

// CUT begin
ifstream data("MixingColors.sample");

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

bool do_test(vector<int> colors, int __expected) {
    time_t startClock = clock();
    MixingColors *instance = new MixingColors();
    int __result = instance->minColors(colors);
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
        vector<int> colors;
        from_stream(colors);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(colors, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1507132258;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MixingColors (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
