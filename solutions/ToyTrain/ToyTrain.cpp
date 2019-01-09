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
 
 11:52-12:10 pause
 19:15-20:02 I CANNOT understand sample 7 AT ALL
 20:20 probably I understood problem. All the 'A',B' and 'S' MUST be used. Empty or plot of load is not necessarily used. Problem statement is NOT clear AT ALL 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
 20:30-20:47,21:47-23:24 Samples passed though, system test failed. Look at editorial.
 23:41 system test passed
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+559
  - http://kmjp.hatenablog.jp/entry/2012/11/11/0900
  - http://d.hatena.ne.jp/kusano_prog/20121031/1351713656
 
 Summary:
  - Problem statement was not clear for me
  - Pair
 
 */
vector< pair < int, int > >  moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
int viz[51][51];

class ToyTrain {
public:
  int R,C;
  vector<string> B;
  int getMinCost(vector<string> BB) {
    this->R=SZ(BB),this->C=SZ(BB[0]),this->B=BB;
    ZERO(viz);
    REP(i,R) {
      int ab=-1;
      REP(j,C) {
        if(B[i][j]!='A'&&B[i][j]!='B') {
          if(ab>=0) viz[i][j]=true;
          continue;
        }
        if(B[i][j]=='A'||B[i][j]=='B') {
          viz[i][j]=true;
          if(ab==-1) {
            ab=B[i][j]!='A';
          } else if(ab==(B[i][j]=='A')) {
            ab=-1;
          } else {
            return -1;
          }
        }
      }
      if(ab!=-1) return -1;
    }
    
    REP(j,C) {
      int ab=-1;
      REP(i,R) {
        if(B[i][j]!='A'&&B[i][j]!='B') {
          if(ab>=0) {
            if(viz[i][j]) return -1;
            viz[i][j]=true;
          }
          continue;
        }
        if(B[i][j]=='A'||B[i][j]=='B') {
          viz[i][j]=true;
          if(ab==-1) {
            ab=B[i][j]!='A';
          } else if(ab==(B[i][j]=='A')) {
            ab=-1;
          } else {
            return -1;
          }
        }
      }
      if(ab!=-1) return -1;
    }
    
    int lord[10]={};
    int vv=0;
    REP(i,R)REP(j,C) {
      if((B[i][j]=='A'||B[i][j]=='B'||B[i][j]=='S')&&!viz[i][j]) return -1;
      if('1'<=B[i][j]&&B[i][j]<='9'&&viz[i][j]) lord[B[i][j]-'0']=1;
      vv+=viz[i][j];
    }
    if(vv==0) return -1;
    
    int res=0;
    REP(i,10) if(lord[i])res+=i;
    
    return res;
  }
};

class ToyTrain_org {
  public:
  vector< pair < int, int > >  moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
  int viz[51][51];
  int R,C;
  vector<string> B;
  int ir,ic;
  VI nextdir(int dir2) {
    if(dir2==0) return {2,0};
    if(dir2==1) return {3,1};
    if(dir2==2) return {0,2};
    return {1,3};
  }
  int search(int i, int j, int ab, int dir) {
//    dump4(i,j,ab,dir);
    auto m=moves[dir];
    int i2=i+m.first,j2=j+m.second;
    while(0<=i2&&i2<R&&0<=j2&&j2<C) {
//      dump3(i2,j2,B[i2][j2]);
      if(B[i2][j2]=='A'&&(!viz[i2][j2]||(i2==ir&&j2==ic))) return ab?i2*C+j2:-1;
      if(B[i2][j2]=='B'&&(!viz[i2][j2]||(i2==ir&&j2==ic))) return !ab?i2*C+j2:-1;
      if(viz[i2][j2]) return -1;
      i2+=m.first,j2+=m.second;
    }
    return -1;
  }
  void visit(int r, int c, int dir, int tr, int tc) {
    auto p=moves[dir];
    while(r!=tr||c!=tc) {
      viz[r][c]=true;
      r+=p.first,c+=p.second;
    }
  }
  int dfs(int r, int c, int r2, int c2, int ab, int dir, int dir2) {
    dump4(r,c,r2,c2);
    dump3(ab,dir,dir2);
    visit(r,c,dir,r2,c2);
    if(r2==ir&&c2==ic) return true;
    
    VI nextds=nextdir(dir2);
    FORR(d,nextds) {
      int next=search(r2,c2,!ab,d);
//      dump4(d,next/C,next%C,!ab);
      if(next!=-1) return dfs(r2,c2,next/C,next%C,!ab,d,dir);
    }
    return false;
  }
  int getMinCost(vector<string> BB) {
    this->R=SZ(BB),this->C=SZ(BB[0]),this->B=BB;
    ZERO(viz);
    REP(i,R) REP(j,C) if(!viz[i][j]&&(B[i][j]=='A'||B[i][j]=='B')) {
      dump2(i,j);
      bool ok=true;
      ir=i,ic=j;
      int ab=B[i][j]!='A';
      int next=search(i,j,ab,0);
      if(next==-1) return -1;
      ok&=dfs(i,j,next/C,next%C,ab,0,3);
      
      /*
      REP(ii,R) {
        REP(jj,C) cout<<viz[ii][jj];
        cout<<endl;
      }*/
      
      if(!ok) return -1;
    }
    
    int lord[10]={};
    int vv=0;
    REP(i,R)REP(j,C) {
      if((B[i][j]=='A'||B[i][j]=='B'||B[i][j]=='S')&&!viz[i][j]) return -1;
      if('1'<=B[i][j]&&B[i][j]<='9'&&viz[i][j]) { dump3(i,j,B[i][j]); lord[B[i][j]-'0']=1; }
      vv+=viz[i][j];
    }
    if(vv==0) return -1;
    
    int res=0;
    REP(i,10) if(lord[i])res+=i;
    
    return res;
  }
};

// CUT begin
ifstream data("ToyTrain.sample");

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

bool do_test(vector<string> field, int __expected) {
    time_t startClock = clock();
    ToyTrain *instance = new ToyTrain();
    int __result = instance->getMinCost(field);
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
        vector<string> field;
        from_stream(field);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515009149;
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
        cout << "ToyTrain (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
