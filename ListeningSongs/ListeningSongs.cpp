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
 
 8/4/2017
 
 17:17-17:28 failed system test (218.61 pt)
 19:05 fixed a bug of missing size check :(
 
 22:18-22:25 read editorial and improved solution
 - https://apps.topcoder.com/wiki/display/tc/SRM+679
 
 Most of people design almost same algorithm.
 - https://community.topcoder.com/stat?c=problem_solution&rm=327907&rd=16649&pm=14123&cr=40100022
 - https://community.topcoder.com/stat?c=problem_solution&rm=327907&rd=16649&pm=14123&cr=40100022
 
 */
class ListeningSongs {
  public:
  int listen(vector<int> D1, vector<int> D2, int M, int T) {
    if(SZ(D1)<T||SZ(D2)<T) return -1;
    M=60*M;
    sort(D1.begin(),D1.end());
    sort(D2.begin(),D2.end());
    
    int x=accumulate(D1.begin(),D1.begin()+T,0)+accumulate(D2.begin(),D2.begin()+T,0);
    int res=2*T;
    VI R;
    FOR(i,T,SZ(D1)) R.push_back(D1[i]);
    FOR(i,T,SZ(D2)) R.push_back(D2[i]);
    sort(R.begin(),R.end());
    
    /*
    // missed to put i<SZ(R)
    int i=0;
    while(i<SZ(R)&&x+R[i]<=M) {
      x+=R[i++];
    }*/
    
    // safer than above
    REP(i,SZ(R)) {
      if(x+R[i]>M) break;
      x+=R[i];
      ++res;
    }
    
    return x>M ? -1 : res;
  }
};

// CUT begin
ifstream data("ListeningSongs.sample");

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

bool do_test(vector<int> durations1, vector<int> durations2, int minutes, int T, int __expected) {
    time_t startClock = clock();
    ListeningSongs *instance = new ListeningSongs();
    int __result = instance->listen(durations1, durations2, minutes, T);
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
        vector<int> durations1;
        from_stream(durations1);
        vector<int> durations2;
        from_stream(durations2);
        int minutes;
        from_stream(minutes);
        int T;
        from_stream(T);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(durations1, durations2, minutes, T, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501892215;
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
        cout << "ListeningSongs (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
