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

/*
 
 cross product u×v
 
 u×v = det(u,v)
 = u.x * v.y - u.y * v.x
 = |u|*|v|*sin𝛩
 = area of parallelogram formed by u and v
 
 1) u×v = det(u,v) = 0
 u and v are colinear from origin
 2) u×v = det(u,v) > 0
 u is clockwise from v
 3) u×v = det(u,v) < 0
 u is counter-clockwise from v
 
 */
long long det(Vector u, Vector v) {
  return u.x*v.y - u.y*v.x;
}
/*
 
 cross product det(o->p1, o->p2)
 
 1) det(p1,p2,o) = 0
 o->p1 is colinear with o->p2
 2) det(p1,p2,o) > 0
 o->p1 is clockwise against o->p2
 3) det(p1,p2,o) < 0
 o->p1 is counter clockwise against o->p2
 
 */
long long det(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vs = makeVectors(p1,p2,origin);
  return det(vs.first,vs.second);
}

// CLRS 33.1 ON-SEGMENT(pi,pj,pk)
bool onSegment(pair<int,int> p1, pair<int,int> p2, pair<int,int> pi) {
  int xmin=min(p1.first, p2.first),
  xmax=max(p1.second, p2.second),
  ymin=min(p1.second, p2.second),
  ymax=max(p1.second,p2.second);
  return xmin<=pi.first && pi.first<=xmax && ymin<=pi.second && pi.second<=ymax;
}
// CLRS 33.1 SEGMENTS-INTERSECT(p1,p2,p3,p4)
// p1->p2 intersects p3->p4
bool intersect(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3, pair<int,int> p4) {
  long long d1 = det(p3,p4,p1),
  d2 = det(p3,p4,p2),
  d3 = det(p1,p2,p3),
  d4 = det(p1,p2,p4);
  
  if (((d1>0&&d2<0)||(d1<0&&d2>0)) && ((d3>0&&d4<0)||(d3<0&&d4>0))) return true;
  if (d1==0 && onSegment(p3,p4,p1)) return true;
  if (d2==0 && onSegment(p3,p4,p2)) return true;
  if (d3==0 && onSegment(p1,p2,p3)) return true;
  if (d4==0 && onSegment(p1,p2,p4)) return true;
  return false;
}

/*
 
 9/3/2017
 
 16:20-18:20 give up
 
 21:40-22:25 read editorials and add solution
  - https://apps.topcoder.com/wiki/display/tc/SRM+652
  - http://kmjp.hatenablog.jp/entry/2015/03/13/1000
  - http://roiti46.hatenablog.com/entry/2015/03/13/TopCoder_SRM_652_Div2_Hard%3A_NoRightTurnDiv2
 
 Find left-bottom point to start scan.
 If we take the most right outer point, then all other remaining points are in counter clock position.
 The selected new point is also the most outer point.
 We can observe that it stays at left-bottom by rotating the corrdinate.
 by keeping this invariant, we can pick all the points without intersection.
 
 key:
  - greedy selection of starting point
    - or brute-force first point and discard it if intersection is found (@kmjp's solution)
  - keep selecting a point which is clock-wise from any other remaining points
  - small technique to use swap to keep reduce search target
 
 summary:
  - idea was almost same. keep taking outest points.
  - missing analysis was starting from left bottom to avoid intersection
    - this is the same approach as seen in graham-scan algorithm which detects convex hull
  - understanding of cross product is not sufficnet
 
 22:35-25:01 add @kmjp's solution
  - fixed a bug of library (overflow of sign check in intersect())
 
 */
class NoRightTurnDiv2 {
public:
  int N;
  VI X,Y;
  vector<int> findPath(vector<int> X, vector<int> Y) {
    N=SZ(X); this->X=X; this->Y=Y;
    vector<III> ps;
    REP(i,N) ps.emplace_back(X[i],Y[i],i);
    sort(ps.begin(),ps.end(),[&](III a, III b) {
      if(get<0>(a)!=get<0>(b)) return get<0>(a)<get<0>(b);
      return get<1>(a)<get<1>(b);
    });
    
    FOR(i,1,N) {
      sort(ps.begin()+i,ps.end(),[&](III a, III b) {
        return det({get<0>(a),get<1>(a)}, {get<0>(b),get<1>(b)}, {get<0>(ps[i-1]),get<1>(ps[i-1])})>0;
      });
    }
    
    VI res;
    REP(i,N) res.push_back(get<2>(ps[i]));
    return res;
  }
};

class NoRightTurnDiv2_bruteforceStart {
public:
  int N;
  VI X,Y;
  bool validateIntersect(VI res) {
    REP(i,N-1) {
      II a={X[res[i]],Y[res[i]]}, b={X[res[i+1]],Y[res[i+1]]};
      REP(j,i-1) {
        II c={X[res[j]],Y[res[j]]}, d={X[res[j+1]],Y[res[j+1]]};
        if(intersect(a,b,c,d)) return false;
      }
    }
    return true;
  }
  
  vector<int> findPath(vector<int> X, vector<int> Y) {
    N=SZ(X); this->X=X; this->Y=Y;
    
    VI xs; REP(i,N) xs.push_back(i);
    REP(i,N) {
      VI res=xs;
      swap(res[i],res[0]);
      FOR(j,1,N) {
        II o = {X[res[j-1]],Y[res[j-1]]};
        auto it = min_element(res.begin()+j, res.end(),[&](int i, int j) {
          II p1={X[i]-o.first,Y[i]-o.second}, p2={X[j]-o.first,Y[j]-o.second};
          return (p1.first*p2.second-p1.second*p2.first)>0;
        });
        int k=it-res.begin();
        swap(res[k],res[j]);
      }
      if(validateIntersect(res)) return res;
    }
    return {};
  }
};

// CLRS 33.1
// true: org->p1 is clockwise against org->p2
bool isClockwise(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vpair = makeVectors(p1,p2,origin);
  return det(vpair.first, vpair.second)>0;
}
// CLRS 33.1
// true: p1->p2 is left turn for origin
bool isLeftTurn(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  return isClockwise(p1,p2,origin);
}

VI O[51][51];
class NoRightTurnDiv2_wrong {
  public:
  int N;
  VI X,Y;
  bool ok(VI cur) {
    // left turn check
    REP(i,N-2) {
      II a={X[cur[i]],Y[cur[i]]}, b={X[cur[i+1]],Y[cur[i+1]]}, c={X[cur[i+2]],Y[cur[i+2]]};
      if(!isLeftTurn(b,c,a)) {
//        dump3(i+1,i+2,i);
        return false;
      }
    }
    
    // intersection check
    REP(i,N-1) {
      II a={X[cur[i]],Y[cur[i]]}, b={X[cur[i+1]],Y[cur[i+1]]};
      FOR(j,1,i) {
        II c={X[cur[j-1]],Y[cur[j-1]]}, d={X[cur[j]],Y[cur[j]]};
        if(intersect(a,b,c,d)) return false;
      }
    }
    
    return true;
  }
  
  bool validateIntersect(int k, VI cur) {
    int n=SZ(cur);
    REP(i,n-2) if(intersect({X[cur[i]],Y[cur[i]]},{X[cur[i+1]],Y[cur[i+1]]},{X[cur.back()],Y[cur.back()]},{X[k],Y[k]})) {
//      dumpAR(cur);
//      dump4(cur[i],cur[i+1],cur.back(),k);
      return false;
    }
    return true;
  }
  VI dfs(VI cur) {
    if(SZ(cur)==N) return cur;
//    dumpAR(cur);
    int n=SZ(cur);
    int a=cur[n-2],b=cur[n-1];
    FORR(k,O[a][b]) if (count(cur.begin(),cur.end(),k)==0&&validateIntersect(k,cur)) {
      VI c2=cur;
      c2.push_back(k);
      return dfs(c2);
//      VI xs = dfs(c2);
//      if(!xs.empty()) return xs;
    }
    return {};
  }
  
  vector<int> findPath(vector<int> X, vector<int> Y) {
    N=SZ(X); this->X=X; this->Y=Y;
    REP(i,N)REP(j,N) O[i][j].clear();
    REP(i,N) REP(j,N) if(i!=j) {
      // this isLeftTurn() call is wrong, this is checking if p[j]<-p[k] is counter clockwise or not
      // also it doesn't make sense to take polar angle against segment.
      // thus created O[i][j] table is wrong.
      REP(k,N) if(k!=i&&k!=j&&isLeftTurn({X[j],Y[j]},{X[k],Y[k]},{X[i],Y[i]})) O[i][j].push_back(k);
      sort(O[i][j].begin(),O[i][j].end(), [&](int a, int b) {
        pair<Vector, Vector> v1=makeVectors({X[a],Y[a]},{X[j],Y[j]},{X[i],Y[i]});
        pair<Vector, Vector> v2=makeVectors({X[b],Y[b]},{X[j],Y[j]},{X[i],Y[i]});
        
        // it doesn't make sense to take distance here. to check polar angle, sing of cross product suffices
        double x=(double)det(v1.first,v1.second)/(double)(v1.first.distance()*v1.second.distance());
        double y=(double)det(v2.first,v2.second)/(double)(v2.first.distance()*v2.second.distance());
        return x<y;
      });
    }
    
    REP(i,N) REP(j,N) if(i!=j) {
      VI xs=dfs({i,j});
      if(!xs.empty()) {
//        if(!ok(xs)) dumpAR(xs);
        assert(ok(xs));
        return xs;
      }
    }
    return {};
  }
};

// CUT begin
ifstream data("NoRightTurnDiv2.sample");

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

bool do_test(vector<int> x, vector<int> y, vector<int> __expected) {
    time_t startClock = clock();
    NoRightTurnDiv2 *instance = new NoRightTurnDiv2();
    vector<int> __result = instance->findPath(x, y);
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
        vector<int> __answer;
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
        int T = time(NULL) - 1504480785;
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
        cout << "NoRightTurnDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
