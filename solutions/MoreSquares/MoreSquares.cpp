#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
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
// debug cerr
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) {  cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

struct Point {
public:
  int x, y;
  Point(): x(0), y(0) {}
  Point(int x, int y): x(x), y(y) {}
  Point(pair<int,int> p): x(p.first), y(p.second) {}
  Point(pair<int,int> p, pair<int,int> org): Point(p.first-org.first, p.second-org.second) {}
  Point(Point p, Point org): Point(p.x-org.x, p.y-org.y) {}
  
  explicit operator bool() const { return x!=0||y!=0; }
  Point operator-() const { return Point(0,0)-*this; }
  Point &operator+=(Point that) { x+=that.x,y+=that.y; return *this; }
  Point &operator-=(Point that) { x-=that.x,y-=that.y; return *this; }
  Point operator+(Point that) const { return Point(*this)+=that; }
  Point operator-(Point that) const { return Point(*this)-=that; }
  bool operator==(Point that) const { return x==that.x&&y==that.y; }
  bool operator!=(Point that) const { return !(Point(*this)==that); }
  bool operator<(Point that) const { return pair<int,int>(x,y)<pair<int,int>(that.x,that.y); }
  bool operator>(Point that) const { return pair<int,int>(x,y)>pair<int,int>(that.x,that.y); }
  bool operator<=(Point that) const { return Point(*this)==that||Point(*this)<that; }
  bool operator>=(Point that) const { return Point(*this)==that||Point(*this)>that; }
  friend std::ostream& operator<<(std::ostream& _os, const Point& _p) { return _os<<"{"<<_p.x<<','<<_p.y<<"}"; }
  // sqrt(distance()) is definition
  long long distance() {
    return x*x + y*y;
  }
  Point rotate90() {
    return Point{-y, x};
  }
};
double deg2rad(double deg) {
  return deg*M_PI/180.0;
}
pair<double,double> rotate(pair<double,double> p, double deg) {
  double x=p.first,y=p.second;
  double rad=deg2rad(deg);
  double C = cos(rad);
  double S = sin(rad);
  return { x*C-y*S, x*S+y*C };
}

/*
 
 4/19/2019
 
 16:56-17:53 AC
 
 http://kmjp.hatenablog.jp/entry/2019/04/09/0900
 https://www.topcoder.com/blog/single-round-match-754-editorials/
 
 */
long long dot(Point u, Point v) {
  return (long long)u.x*v.x + (long long)u.y*v.y;
}
bool isVertical(Point u, Point v) {
  return dot(u,v)==0;
}
class MoreSquares {
  public:
  int countLocations(int N, int SX, int SY, vector<int> Xprefix, vector<int> Yprefix) {
    int L=SZ(Xprefix);
    vector<II> X;
    REP(i,min(N,L)) {
      int x=Xprefix[i],y=Yprefix[i];
      X.emplace_back(x,y);
    }
    FOR(i,L,N) {
      int x=(X.back().first*47+42)%SX,y=(X.back().second*47+42)%SY;
      X.emplace_back(x,y);
    }
    set<II> S(ALL(X));
    vector<Point> ps;
    FORR(p,S) ps.push_back(Point(p));
    N=SZ(ps);
    set<II> res;
    REP(i,N)REP(j,N) {
      Point p1=ps[i],p2=ps[j];
      Point A=p1+(p2-p1).rotate90(),B=p2-(p1-p2).rotate90();

      assert(isVertical(A-p1,p2-p1)&&isVertical(B-p2,p1-p2));
      assert((A-p1).distance()==(p1-p2).distance()&&(B-p2).distance()==(p1-p2).distance());
      if(S.count({A.x,A.y})&&S.count({B.x,B.y})==0) {
        res.emplace(B.x,B.y);
      }
      if(S.count({B.x,B.y})&&S.count({A.x,A.y})==0) {
        res.emplace(A.x,A.y);
      }
    }
    return SZ(res);
  }
};

// CUT begin
ifstream data("MoreSquares.sample");

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

bool do_test(int N, int SX, int SY, vector<int> Xprefix, vector<int> Yprefix, int __expected) {
    time_t startClock = clock();
    MoreSquares *instance = new MoreSquares();
    int __result = instance->countLocations(N, SX, SY, Xprefix, Yprefix);
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
        int SX;
        from_stream(SX);
        int SY;
        from_stream(SY);
        vector<int> Xprefix;
        from_stream(Xprefix);
        vector<int> Yprefix;
        from_stream(Yprefix);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, SX, SY, Xprefix, Yprefix, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1555718114;
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
        cout << "MoreSquares (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
