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
 
 11/17/2017
 
 9:24-9:57 analysis
 9:57-10:40 implementation
 10:40-11:04 debug, submit and got TLE (337.16 pt)
 11:10 system test passed by constant time optimizatin.. (1.966 sec in worst case)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+585
   - O(M^3) time
  - http://kmjp.hatenablog.jp/entry/2013/07/24/1000
   - O(M^3) time
  - https://topcoder.g.hatena.ne.jp/firewood/20130805/1375717350
   - O(M^3) time
  - http://emkcsharp.hatenablog.com/entry/SRM585/EnclosingTriangleColorful
   - O(N*M^2) time

 Key:
  - Pre-compute so that we can compute if triangle can be formed in O(1) time for given three points
  - Points are in side of a segment => cross product as usual
 
 Summary:
  - Analysis was strightforward though, I'm not good at geometry problem 😩
  - I'm always in panic for cross product
  - My original code was very close to TLE
  - Nice to learn to reduce some constant factor by using more memory
   - space of 8*300 integer and 24*M^3 time vs space of 1200*1200 integer and 4*M^3 time
 
 O(N*M^2) solutions
  - https://community.topcoder.com/stat?c=problem_solution&rm=318154&rd=15697&pm=12694&cr=23138993
  - https://community.topcoder.com/stat?c=problem_solution&rm=318184&rd=15697&pm=12694&cr=23081838
 O(M^3) solutions
  - https://community.topcoder.com/stat?c=problem_solution&rm=318153&rd=15697&pm=12694&cr=23042478
  - https://community.topcoder.com/stat?c=problem_solution&rm=318179&rd=15697&pm=12694&cr=23008512
 
 */

class EnclosingTriangleColorful {
public:
  int M,N;
  VI X,Y;
  int det(int x1, int y1, int x2, int y2) {
    return x1*y2-x2*y1;
  }
  double xcut(int x1, int x2, int y1, int y2, int M) {
    return (1.0*x1*(M-y2)+1.0*x2*(y1-M))/(1.0*(y1-y2));
  }
  int f(int x1, int y1, int x2, int y2) {
    II p1={0,0},p2={M,0};
    
    int l=1,r=M-1;
    REP(i,N) {
      int x3=X[i],y3=Y[i];
      if(det(x3-x1,y3-y1,x2-x1,y2-y1)>0) return 0;
      if (det(p1.first-x1,p1.second-y2,x3-x1,y3-y1)>0) {
        p1={x3,y3};
      }
      if (det(x3-x2,y3-y2,p2.first-x2,p2.second-y2)>0) {
        p2={x3,y3};
      }
      
      if (y3>y2) l=min(M-1,max(l,(int)ceil(M-(double)(M-x3)*(M-y2)/(double)(y3-y2))));
      if (y3>y1) r=max(1,min(r,(int)floor((double)x3*(M-y1)/(double)(y3-y1))));
    }
    assert(p1.first!=0);
    assert(p2.first!=M);
    
    /*
    int r=M-1;
    {
      int dy=p1.second-y1;
      int dx=p1.first-x1;
      int ry=M-p1.second;
      int xc=p1.first+(int)floor(1.0*ry*dx/dy);
      r=min(M-1,xc);
    }
    
    int l=1;
    {
      int dy=p2.second-y2;
      int dx=p2.first-x2;
      int ry=M-p2.second;
      int xc=p2.first+(int)ceil(1.0*ry*dx/dy);
      l=max(1,xc);
    }*/
    
//    int r=min(M-1,(int)floor(xcut(x1,y1,pl.first,pl.second,M)));
//    int l=max(1,(int)ceil(xcut(x2,y2,pr.first,pr.second,M)));
    return max(r-l+1,0);
  }
  int getNumber(int M, vector<int> XX, vector<int> YY) {
    this->N=SZ(XX);
    this->M=M;
    this->X=XX,this->Y=YY;
    int res=0;
    REP(_,4) {
      FOR(y1,1,M) FOR(y2,1,M) {
        int x1=0,x2=M;
        res+=f(x1,y1,x2,y2);
      }
      REP(i,N) {
        int a=X[i],b=Y[i];
        X[i]=b,Y[i]=M-a;
      }
    }
    return res;
  }
};

// O(6*N*M^2+4*M^3) time, 210(ms) in worst case
int OK[1200][1200];
class EnclosingTriangleColorful_cubem {
public:
  int M;
  // 0:l,1:t,2:r,3:b
  II cord(int i, int j) {
    int x=-1,y=-1;
    if(i==0) x=0,y=j;
    if(i==1) x=j,y=M;
    if(i==2) x=M,y=j;
    if(i==3) x=j,y=0;
    return {x,y};
  }
  int getNumber(int M, vector<int> X, vector<int> Y) {
    int N=SZ(X);
    this->M=M;
    ZERO(OK);
    REP(i1,4) FOR(j1,1,M) FOR(ii,i1+1,i1+3) FOR(j2,1,M) {
      int i2=ii%4;
      II o=cord(i1,j1), p1=cord(i2,j2);
      int x1=p1.first-o.first,y1=p1.second-o.second;
      bool ok=true;
      REP(i,N) {
        int x=X[i],y=Y[i];
        int x2=x-o.first,y2=y-o.second;
        
        if(x2*y1-x1*y2<0) {
          ok=false; break;
        }
      }
      OK[i1*M+j1][i2*M+j2]=ok;
    }
    int res=0;
    vector<tuple<int,int,int>> ts={
      make_tuple(1,2,3),
      make_tuple(0,2,3),
      make_tuple(0,1,3),
      make_tuple(0,1,2)
    };
    REP(i,4) {
      int s0,s1,s2;
      tie(s0,s1,s2)=ts[i];
      FOR(a,1,M)FOR(b,1,M) if(OK[s0*M+a][s1*M+b]) FOR(c,1,M) res+=OK[s1*M+b][s2*M+c]&&OK[s2*M+c][s0*M+a];
    }
    return res;
  }
};

struct Vector {
public:
  int x, y;
  Vector(pair<int,int> p1, pair<int,int> p2): Vector(p1.first-p2.first, p1.second-p2.second) {}
  Vector(int x, int y): x(x), y(y) {}
  
  long long distance() {
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
long long det(Vector u, Vector v) {
  return u.x*v.y - u.y*v.x;
}
long long distance(pair<int,int> p1, pair<int,int> p2) {
  int dx = p1.first-p2.first, dy = p1.second-p2.second;
  return dx*dx + dy*dy;
}

long long det(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vs = makeVectors(p1,p2,origin);
  return det(vs.first,vs.second);
}
void sortByPolarAngle(vector<pair<int, int>>& ps, pair<int, int> origin) {
  sort(ps.begin(), ps.end(), [&](const pair<int,int> a, const pair<int,int> b) {
    int d = det(a,b,origin);
    if(d!=0) return d > 0;
    return distance(a, origin) < distance(b, origin);
  });
}
// true: org->p1 is clockwise against org->p2
bool isClockwise(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vpair = makeVectors(p1,p2,origin);
  return det(vpair.first, vpair.second)>=0;
}
bool isCounterClockwise(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vpair = makeVectors(p1,p2,origin);
  return det(vpair.first, vpair.second)<0;
}
// O(4*2*M*M+4*3*2*M^3) time ≈7*10^8 time, 1.966 sec in worst case
pair<II,II> P[4][301];
II side[4][301];
class EnclosingTriangleColorful_org {
  public:
  int M;
  // 0:l,1:t,2:r,3:b
  II cord(int i, int j) {
    int x=-1,y=-1;
    if(i==0) x=0,y=j;
    if(i==1) x=j,y=M;
    if(i==2) x=M,y=j;
    if(i==3) x=j,y=0;
    return {x,y};
  }
  int getNumber(int M, vector<int> X, vector<int> Y) {
    int N=SZ(X);
    this->M=M;
    vector<II> ps;

    REP(i,N) ps.emplace_back(X[i],Y[i]);
    // 0:l,1:t,2:r,3:b
//    REP(i,4)FOR(j,1,M) P[i][j].clear();
    REP(i,4)FOR(j,1,M) {
      vector<II> pp=ps;
      II o=cord(i,j);
      
      II pmin={X[0],Y[0]},pmax={X[0],Y[0]};
      FOR(k,1,N) {
        II p={X[k],Y[k]};
        if(isClockwise(p,pmin,o)) pmin=p;
        if(isClockwise(pmax,p,o)) pmax=p;
      }
//      dump4(i,j,o.first,o.second);
//      dump4(pmin.first,pmin.second,pmax.first,pmax.second);
      P[i][j]={pmin,pmax};
      side[i][j]=o;
    }
    
    int res=0;
    int ii[3],jj[3];
    REP(x,4) {
      int s=0;
      REP(i,4) if(i!=x) ii[s++]=i;
      FOR(j1,1,M) FOR(j2,1,M) FOR(j3,1,M) {
        jj[0]=j1,jj[1]=j2,jj[2]=j3;
        bool ok=true;
        REP(a,3) {
          int a0=a,a1=(a+1)%3,a2=(a+2)%3;
          II o=side[ii[a0]][jj[a0]],
            p1=side[ii[a1]][jj[a1]],
            p2=side[ii[a2]][jj[a2]];
          II pmin=P[ii[a0]][jj[a0]].first,pmax=P[ii[a0]][jj[a0]].second;
          if(isClockwise(pmax,p1,o)&&isClockwise(p2,pmin,o)) continue;
          ok=false;
          break;
        }
        res+=ok;
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("EnclosingTriangleColorful.sample");

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

bool do_test(int m, vector<int> x, vector<int> y, int __expected) {
    time_t startClock = clock();
    EnclosingTriangleColorful *instance = new EnclosingTriangleColorful();
    int __result = instance->getNumber(m, x, y);
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
        int m;
        from_stream(m);
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
        if ( do_test(m, x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510939445;
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
        cout << "EnclosingTriangleColorful (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
