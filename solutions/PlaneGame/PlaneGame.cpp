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

/**
 
 8/9/2017
 
 8:32-8:53 designed
 8:53-9:44 overflow, remove intersection, no rotation case, overlap of no ration, all co-linear is in a single set, this is wrong design.
 9:45-10:03 redesigned and implemented with my own geometric library (172.28 pt), but failed system test.
 
 19:15-19:28 figured out failing case. fixed and passed system test
 
 19:28-20:17 read editorials:
  - http://kmjp.hatenablog.jp/entry/2015/12/04/0900
  - https://apps.topcoder.com/wiki/display/tc/SRM+674
 
 20:17-20:42 add solution following editorials
  - 90 degree => dot product is 0
 
 Key:
  - slope brute force. count points based on it
  - make slope and count points at the same time makes solution complex
  - one slope is determined by selecting only two points: S1
  - end-point of another 90 degree segment is determined by specifying another point
  - iterate all the points to satisfy those three points
 
 Summary:
  - intially designed wrong algorithm. should have described some examples
  - my algorithm was creating all the sets of slopes first though, it brought some corner cases
    - determine points vs determine only slopes
    - in this case, determine slopes first and count points against them.
    - then we can simply iterate all the points without considering what is already used.
 
 */

class PlaneGame {
public:
  int bestShot(vector<int> X, vector<int> Y) {
    int N=SZ(X);
    if(N<=2) return N;
    vector<II> P(N);
    REP(i,N) P[i]={X[i],Y[i]};
    
    int res=2;
    REP(i,N) REP(j,N) if(i!=j) {
      LL dx=X[i]-X[j],dy=Y[i]-Y[j];
      REP(k,N) if(i!=k&&j!=k) {
        int x=0;
        REP(l,N) {
          LL dx1=X[l]-X[i],dy1=Y[l]-Y[i];
          if(dx*dy1==dx1*dy) ++x;
          else {
            LL dx2=X[l]-X[k],dy2=Y[l]-Y[k];
            if (dx*dx2==-1*dy2*dy) ++x;
          }
        }
        res = max(res,x);
      }
    }
    
    return res;
  }
};

struct Vector {
public:
  int x, y;
  Vector(pair<int,int> p1, pair<int,int> p2): Vector(p1.first-p2.first, p1.second-p2.second) {}
  Vector(int x, int y): x(x), y(y) {}
  
  int length() {
    return x*x + y*y;
  }
};

pair<Vector, Vector> makeVectors(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  Vector v1 = Vector(p1,origin), v2 = Vector(p2,origin);
  return make_pair(v1,v2);
}
pair<int,int> makePair(vector<int> v) {
  assert(v.size()==2);
  return {v[0],v[1]};
}

int crossProduct(Vector u, Vector v) {
  return u.x*v.y - u.y*v.x;
}
int crossProduct(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vs = makeVectors(p1,p2,origin);
  return crossProduct(vs.first,vs.second);
}
int dotProduct(Vector u, Vector v) {
  return u.x*v.x + u.y*v.y;
}

int length(pair<int,int> p1, pair<int,int> p2) {
  int dx = p1.first-p2.first, dy = p1.second-p2.second;
  return dx*dx + dy*dy;
}

bool isColinear(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vpair = makeVectors(p1,p2,origin);
  return crossProduct(vpair.first, vpair.second)==0;
}

bool isVertical(Vector u, Vector v) {
  return dotProduct(u,v)==0;
}

class PlaneGame_org {
public:
  int bestShot(vector<int> X, vector<int> Y) {
    int N=SZ(X);
    if(N==1) return 1;
    vector<II> P(N);
    REP(i,N) P[i]={X[i],Y[i]};
    
    map<II, SETI> L;
    REP(i,N) REP(j,N) REP(k,N) if(i!=j&&j!=k) {
      if (isColinear(P[i],P[j],P[k])) L[{i,j}].insert(i),L[{i,j}].insert(j),L[{i,j}].insert(k);
    }
    
    int res=2;
    FORR(kvp1,L) {
      SETI X=kvp1.second;
      FORR(kvp2,L) {
        auto p1=kvp1.first, p2=kvp2.first;
        if(p1.first==p2.first&&p1.second==p2.second) continue;
        Vector v1=Vector(P[p1.first],P[p1.second]), v2=Vector(P[p2.first],P[p2.second]);
        if(!isVertical(v1, v2)) continue;
        SETI Y=kvp2.second;
        int both=0;
        FORR(n,X) if(Y.count(n)) both++;
        
        res=max(res,SZ(X)+SZ(Y)-both);
      }
      
      res=max(res,SZ(X));
      if(SZ(X)<N) res=max(res,SZ(X)+1);
    }
    
    return res;
  }
};

class PlaneGame_wrong {
  public:
  int bestShot(vector<int> X, vector<int> Y) {
    int M=SZ(X);
    if(M==1) return 1;
    map<II,SETI> P,N;
    map<int,SETI> XZ,YZ;
    
    REP(j,M)REP(i,j) {
      int dx=X[j]-X[i],dy=Y[j]-Y[i];
      
      if(dx==0) dy=X[i],dx=1e9;
      else if(dy==0) dx=Y[i],dy=1e9;
      else if(dx<0&&dy<0) dx=-dx,dy=-dy;
      else if((dx<0&&dy>0)||(dx>0&&dy<0)) dx=abs(dx),dy=-abs(dy);
//      assert(dx>=0);
      
//      dump4(i,j,dx,dy);
      
      if(dx==0||dy==0) {
        if(dy==0) YZ[dx].emplace(i),YZ[dx].emplace(j);
        else XZ[dy].emplace(i),XZ[dy].emplace(j);
      } else {
        int dx2=abs(dx),dy2=abs(dy);
        int g=__gcd(dx2,dy2);
        dx2/=g, dy2/=g;
        
        if(dy<0) N[{dx2,dy2}].emplace(i),N[{dx2,dy2}].emplace(j);
        else P[{dx2,dy2}].emplace(i),P[{dx2,dy2}].emplace(j);
      }
    }
    
    int res=2;
    for(auto kvp : P) {
      auto p = kvp.first;
      SETI S=kvp.second;
      int k=SZ(S);
      if (N.count(p)) {
        int l=SZ(N[p]);
        
        int both=0;
        FORR(n,S) if(N[p].count(n)) ++both;
        
        dumpAR(S);
        dumpAR(N[p]);
        
        dump2(p.first,p.second);
        dump4(k,l,both,k+l-both);
        
        res=max(res,k+l-both);
      }
    }
    
    for(auto kvp1 : XZ) {
      SETI S=kvp1.second;
      for(auto kvp2 : YZ) {
        SETI T=kvp2.second;
        int both=0;
        FORR(n,S) if(T.count(n)) ++both;
        res=max(res,SZ(S)+SZ(T)-both);
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("PlaneGame.sample");

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

bool do_test(vector<int> x, vector<int> y, int __expected) {
    time_t startClock = clock();
    PlaneGame *instance = new PlaneGame();
    int __result = instance->bestShot(x, y);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502292741;
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
        cout << "PlaneGame (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
