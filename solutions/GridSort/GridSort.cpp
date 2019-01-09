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

int vR[51];
int vC[51];

/**
 
 7/10/2017
 
 8:35-8:46 design done
 FFFFFFFFFFUUUUUCCCCKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK. matrix index computation bug AGAINNNNNNNNN
 9:18 (228 pt) passed system test
 
 - Operation order doesn't matter
 - Keep swapping row/columns to put 1,..,n*m
 
 22:35 read editorials
 - http://beet-aizu.hatenablog.com/entry/2016/11/16/002730
 - https://apps.topcoder.com/wiki/display/tc/SRM+702
  - ok, numbers in the same row/column cannot be broken
  - in row-wise, we can check if numbers are in the same expected group
  - in column-wise, we can check if numbers are in the same expected group
    - If we do swap operation from sorted matrix, it may have been easier to find this property.
 */

// O(M*N) time, O(1) space
class GridSort {
public:
  int N,M;
  string sort(int N, int M, vector<int> grid) {
    this->N=N,this->M=M;
    // horizontal check
    REP(i,N) {
      int expectedRow=(grid[i*M]-1)/M;
      REP(j,M) {
        if((grid[i*M+j]-1)/M!=expectedRow) return "Impossible";
      }
    }
    // vertical check
    REP(j,M) {
      int expectedCol=(grid[j]-1)%M;
      REP(i,N) {
        if((grid[i*M+j]-1)%M!=expectedCol) return "Impossible";
      }
    }
    
    return "Possible";
  }
};

// O(N^2*M^2)
class GridSort_org {
  public:
  int N,M;
  string sort(int N, int M, vector<int> grid) {
    this->N=N,this->M=M;
    memset(vR,0,sizeof vR);
    memset(vC,0,sizeof vC);

    for(int t=1; t<=N*M; ++t) {
      int p=-1;
      REP(i,N*M) { if(grid[i]==t) p=i; }
      assert(p!=-1);
      int r1=p/M,r2=(t-1)/M,c1=p%M,c2=(t-1)%M;

      if(r1!=r2&&(vR[r2]||vR[r1])) return "Impossible";
      swapr(grid,r1,r2);
      vR[r2]=true;
      
      if(c1!=c2&&(vC[c2]||vC[c1])) return "Impossible";
      swapc(grid,c1,c2);
      vC[c2]=true;
    }

    return "Possible";
  }
  
  void swapr(VI &grid, int r1, int r2) {
    REP(i,M) {
      swap(grid[r1*M+i],grid[r2*M+i]);
    }
  }
  void swapc(VI &grid, int c1, int c2) {
    REP(i,N) {
      swap(grid[i*M+c1],grid[i*M+c2]);
    }
  }
};

// CUT begin
ifstream data("GridSort.sample");

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

bool do_test(int n, int m, vector<int> grid, string __expected) {
    time_t startClock = clock();
    GridSort *instance = new GridSort();
    string __result = instance->sort(n, m, grid);
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
        int m;
        from_stream(m);
        vector<int> grid;
        from_stream(grid);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, grid, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499700898;
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
        cout << "GridSort (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
