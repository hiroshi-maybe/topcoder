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
 
 11/6/2018
 
 17:48-18:48 give up
 
 N%3==0 => N/A
 Otherwise I created N=1,2,4,5. I tried to construct by extending those small squares.
 However I couldn't prove that it's possible.
 
 f(N) = extend(f(N-3),3)                     if N%3==2
 f(N) = extend(f(N-3),3) or extend(f(N-2),2) if N%3==1
 
 20:34-23:20 read editorials and got AC (5WA)
 
 http://kmjp.hatenablog.jp/entry/2018/11/02/1000
 https://www.topcoder.com/blog/single-round-match-741-editorials/
 
 ```
 A good strategy for problems like this one is to reduce the bigger problems to smaller ones: find a way to take any large instance and construct a partial solution (in our case, a partial tiling) in such a way that the part that remains to be solved is another valid and solvable instance. If you can do that, you can then take an arbitrarily large instance and apply the above steps repeatedly, until you get one of finitely many constant-size instances that are too small for the rule to apply.
 ```
 
 My observation was not so bad. However it was redundant. I didn't need to mind +2 case.
 Also editorial solution is removing 3 rows or columns independently while mine is removing x rows/columns removing simultaneously.
 
 Another missing part was sufficiency of the minimal parts.
 Actually my manual paintings were covering all the necessary work.
 However I didn't figure out that it's sufficient because I didn't have clear vision to keep reducing 3 rows or columns.
 
 Summary:
  - too much implementation
 
 */

VV<int> X55={
  {0,0,0,6,7},
  {1,1,1,6,7},
  {2,3,-1,6,7},
  {2,3,4,4,4},
  {2,3,5,5,5}
};
VV<int> X44={
  {-1,-1,1,1},
  {-1,-1,2,1},
  {4,4,2,2},
  {4,3,3,3}
};
VV<int> X25={
  {-1,-1,1,1,1},
  {-1,-1,2,2,2}
};
VV<int> X25_2={
  {0,0,-1,1,1},
  {0,2,2,2,1}
};

vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
int viz[50][50];
class BoardCoveringDiv1 {
  public:
  int c=1,N;
  void paint(int x, bool hor, VV<int> &res) {
    /*
    if(hor) {dumpf("rows %d-%d\n",x,x+3);
    }else{ dumpf("cols %d-%d\n",x,x+3);}
     */
    REP(j,N) {
      FOR(i,x,x+3) {
        (hor?res[i][j]:res[j][i])=c;
      }
      ++c;
    }
  }
  void dfs(int i, int j, int c, VV<int> &res, set<II> &S) {
    if(viz[i][j]||res[i][j]!=c) return;
    viz[i][j]=true;
    S.emplace(i,j);
    FORR(m,moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii>=N||ii<0||jj>=N||jj<0) continue;
      dfs(ii,jj,c,res,S);
    }
  }
  vector<string> norm(VV<int> &res) {
    ZERO(viz);
    vector<string> ans(N,string(N,'#'));
    REP(i,N)REP(j,N) if(res[i][j]!=-1) {
      set<II> S;
      dfs(i,j,res[i][j],res,S);
      if(SZ(S)) {
        int used[10]={};
        FORR(p,S) {
          int i=p.first,j=p.second;
          FORR(m,moves) {
            int ii=i+m.first,jj=j+m.second;
            if(ii>=N||ii<0||jj>=N||jj<0) continue;
            if(isdigit(ans[ii][jj])) used[ans[ii][jj]-'0']=true;
          }
        }
        REP(c,10) if(!used[c]) {
          FORR(p,S) ans[p.first][p.second]='0'+c;
          break;
        }
      }
    }
    
    REP(i,N) cout<<ans[i]<<endl;
    return ans;
  }
  
  vector<string> make(int _N, int R, int C) {
    this->N=_N;
    /*
    FORE(a,1,47)FORE(b,1,47) if(a<=b) {
      if((a*b-1)%3==0)dump4(a,b,a*b,(a*b-1)%3==0);
    }*/
    if(N%3==0) return {};
    VV<int> res(N,VI(N,-1));
    
    if(N==1) return norm(res);
    if(N==2) {
      res=VV<int>(N,VI(N,0));
      res[R][C]=-1;
      return norm(res);
    }
    
    int t=0,b=N,l=0,r=N;
    int minl=N%3==1?4:5;
    while(b-t>minl||r-l>minl) {
      if(!(t<=R&&R<t+3)&&b-t>minl) paint(t,true,res),t+=3;
      else if(!(b-3<=R&&R<b)&&b-t>minl) paint(b-3,true,res),b-=3;
      else if(!(l<=C&&C<l+3)&&r-l>minl) paint(l,false,res),l+=3;
      else if(!(r-3<=C&&C<r)&&r-l>minl) paint(r-3,false,res),r-=3;
    }
    if(minl==5) {
      if(!(t<=R&&R<t+3)) paint(t,true,res),t+=3;
      else if(!(b-3<=R&&R<b)) paint(b-3,true,res),b-=3;
      else if(!(l<=C&&C<l+3)) paint(l,false,res),l+=3;
      else if(!(r-3<=C&&C<r)) paint(r-3,false,res),r-=3;
    }
    
    dump4(t,b,l,r);
    
    REP(i,N) {
      REP(j,N) cout<<res[i][j];
      cout<<endl;
    }
    
    assert(r-l<=minl&&b-t<=minl);
    int R2=R-t,C2=C-l,N2=b-t,M2=r-l;
    dump4(R2,C2,N2,M2);
    int fliph=false,flipv=false,flipd=false;;
    if(R2>=N2/2) R2=N2-R2-1,flipv=true;
    if(C2>=M2/2) C2=M2-C2-1,fliph=true;
//    if(R2<C2) swap(R2,C2),swap(N2,M2),flipd=true;
    if(N2==5&&M2==2) swap(R2,C2),swap(N2,M2),flipd=true;
    VV<int> res2(N2,VI(M2,-1));
    int base=1e4;
    dump4(R2,C2,N2,M2);
    if(N2==4&&M2==4) {
      assert(R2<2&&C2<2);
      REP(i,N2)REP(j,M2) {
        res2[i][j]=base+X44[i][j];
      }
      REP(i,2)REP(j,2)res2[i][j]=0;
    }
    if(N2==2&&M2==5) {
      assert(R2<2&&C2<3);
      VV<int> org=C2<2?X25:X25_2;
      REP(i,N2)REP(j,M2) {
        res2[i][j]=base+org[i][j];
      }
      if(C2<2) REP(i,2)REP(j,2) res2[i][j]=0;
    }
    if(N2==5&&M2==5) {
      assert(R2==2&&C2==2);
      REP(i,N2)REP(j,M2) {
        res2[i][j]=base+X55[i][j];
      }
    }
    res2[R2][C2]=-1;
    
    dump4("before flip",fliph,flipv,flipd);
    REP(i,N2){
      REP(j,M2) cout<<res2[i][j]<<",";
      cout<<endl;
    }
    
    if(flipd) {
      VV<int> res3(M2,VI(N2,0));
      REP(i,N2)REP(j,M2) res3[j][i]=res2[i][j];
      res2=res3;
      swap(N2,M2);
    }
    if(fliph) {
       REP(i,N2) {
        int l=0,r=M2-1;
         while(l<r) {
           swap(res2[i][l],res2[i][r]);
           ++l,--r;
         }
      }
    }
    if(flipv) {
      REP(j,M2) {
        int l=0,r=N2-1;
        while(l<r) {
          swap(res2[l][j],res2[r][j]);
          ++l,--r;
        }
      }
    }
    
    dumpf("after flip");
    REP(i,N2){
      REP(j,M2) cout<<res2[i][j]<<",";
      cout<<endl;
    }
    
    REP(i,N2)REP(j,M2)res[i+t][j+l]=res2[i][j];
    
    REP(i,N) {
      REP(j,N) cout<<res[i][j]<<",";
      cout<<endl;
    }
    
    return norm(res);
  }
};

// CUT begin
ifstream data("BoardCoveringDiv1.sample");

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

bool do_test(int N, int R, int C, vector<string> __expected) {
    time_t startClock = clock();
    BoardCoveringDiv1 *instance = new BoardCoveringDiv1();
    vector<string> __result = instance->make(N, R, C);
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
        int N;
        from_stream(N);
        int R;
        from_stream(R);
        int C;
        from_stream(C);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, R, C, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541555264;
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
        cout << "BoardCoveringDiv1 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
