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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

/*
 
 2/1/2019
 
 17:52-18:52, 22:00-22:40 It turns out that I misunderstood problem. "Area" means # of cells. It's not rectangle formed by reachable minx,maxx,miny,maxy...
 
 2/2/2019
 
 14:00-15:25 sample #4 does not pass. Imos looks correct. However looks like I've not covered all the cases...
 15:25-18:08 read editorial and got AC
 
 http://kmjp.hatenablog.jp/entry/2019/01/27/0930
 https://www.topcoder.com/blog/single-round-match-748-editorials/
 https://twitter.com/satanic0258/status/1089230872736235520
 https://twitter.com/satanic0258/status/1089231357010563072
 https://twitter.com/_olphe/status/1089232838837190656
 
 I've guessed that 2^20 horizontal/vertical brute-force is the key.
 However I've not clearly figured out that how areas are expanded.
 It forms rectangles with monotone stairs.
 
 Key:
  1. Order of move doesn't matter (associative and commutative)
  2. Horizontal and vertical moves are independent
  3. If # of steps ranges in [l,r), reachable length increases by r-l in horizontal or vertical direction
  4. If sum of move is constant, reachable area forms monotone stairs
 
 #1 and #2 obvious
 #3 in one dimension, suppose step ranges [l,r)
 
 a) in positive direction, position ranges [a+l,a+r)
 b) in negative directin, position ranges [a-r,b-l)
 
 In either case, higher bound - lower bound = r-l
 
 #4 x+y=A, which forms monotone line in Cartesian coordinate system
 
 */

class UnreliableRover {
public:
  long long getArea(string D, vector<int> L, vector<int> R) {
    int N=SZ(D);
    LL W=1,H=1;
    vector<LL> X;
    REP(i,N) {
      if(D[i]=='?') {
        X.emplace_back(R[i]);
        continue;
      }
      LL l=L[i],r=R[i];
      if(D[i]=='N'||D[i]=='S') H+=r-l;
      if(D[i]=='E'||D[i]=='W') W+=r-l;
    }
    int M=SZ(X);
    LL tot=accumulate(ALL(X),0LL);
    LL res=H*(W+2LL*tot);
    dump(H,W,tot,res);
    vector<pair<LL,LL>> Y;
    REP(mask,1<<M) {
      LL x=0;
      REP(i,M) if((mask>>i)&1) x+=X[i];
      Y.emplace_back(x,tot-x);
    }
    sort(Y.rbegin(),Y.rend());
    dumpc(Y);
    REP(i,SZ(Y)-1) {
      LL x1,y1; tie(y1,x1)=Y[i];
      LL x2,y2; tie(y2,x2)=Y[i+1];
      LL w=W+2LL*x1,h=y1-y2;
      dump(W,x1,y1,y2,w,h);
      res+=2LL*w*h;
    }
    return res;
  }
};

//const int base=50;
int board[101][101];
class UnreliableRover_wrong {
  public:
  const LL Inf=1e15;
  long long getArea(string D, vector<int> L, vector<int> R) {
    int N=SZ(D);
    
    // x->imos[x]
    map<int, map<LL,int>> xs;
    REP(mask2,4) {
      vector<pair<LL,LL>> X;
      int xmaxim=mask2&1,ymaxim=(mask2>>1)&1;
      
      LL minx=0,maxx=0,miny=0,maxy=0;
      REP(i,N) {
        if(D[i]=='?') {
          X.emplace_back(L[i],R[i]);
          continue;
        }
        LL l=L[i],r=R[i];
        if(D[i]=='N'||D[i]=='S') {
          int a=(D[i]=='N')^ymaxim;
          if(a) swap(l,r);
          int sign=D[i]=='N'?1:-1;
          maxy=maxy+r*sign,miny=miny+l*sign;
        }
        if(D[i]=='E'||D[i]=='W') {
          int a=(D[i]=='E')^xmaxim;
          if(a) swap(l,r);
          int sign=D[i]=='E'?1:-1;
          maxx=maxx+r*sign,minx=minx+l*sign;
        }
      }
      dump(xmaxim,ymaxim,minx,maxx,miny,maxy);
      dumpc(X);
      int M=SZ(X);
      if(M==0) {
        if(minx>maxx) continue;
        if(miny>maxy) continue;
        xs[minx][miny]++,xs[minx][maxy+1]--;
        xs[maxx][miny+1]--,xs[maxx+1][maxy+1]++;
//        SMIN(a,minx),SMAX(b,maxx),SMIN(c,miny),SMAX(d,maxy);
      }
      REP(mask3,4) REP(mask,1<<M) {
        int xmaxim=mask3&1,ymaxim=(mask3>>1)&1;
        
        LL p[4]={minx,maxx,miny,maxy}; /* minx,maxx,miny,maxy */
        REP(i,M) {
          int b=0;
          if((mask>>i)&1) b=2;
          LL l,r; tie(l,r)=X[i];
          if(b==0) {
            // x
            if(xmaxim) p[1]+=r,p[0]+=l;
            else p[1]-=l,p[0]-=r;
          } else {
            // y
            if(ymaxim) p[3]+=r,p[2]+=l;
            else p[3]-=l,p[2]-=r;
          }
        }
        int a=p[0],b=p[1],c=p[2],d=p[3];
        //if(a>b||c>d) continue;
//        if(a>b) swap(a,b);
//        if(c>d) swap(c,d);
        
        dumpC(p,p+4);
        xs[a][c]++,xs[a][d+1]--;
        xs[b+1][c]--,xs[b+1][d+1]++;
        dump(mask,a,b,c,d);
        
//        FORE(x,a,b)FORE(y,c,d) board[y+base][x+base]=1;
      }
    }
    LL res=0;
    map<LL,int> imos;
    FORR(kvp,xs) {
      LL x1=kvp.first; map<LL,int> imo=kvp.second;
      auto it=xs.find(x1);
      it++;
      if(it==xs.end()) break;
      LL x2=it->first;
      FORR(kvp,imo) imos[kvp.first]+=kvp.second; // merge imos
      
      auto it2=imos.begin();
      LL sum=0,prev=it2->first; int cur=it2->second;
      dump(sum,cur)
      ++it2;
      for(; it2!=imos.end(); ++it2) {
        if(cur>0) {
          sum+=it2->first-prev;
          if(x1==1) dump(prev,it2->first,it2->first-prev,sum);
        }
        cur+=it2->second;
        prev=it2->first;
        if(x1==1)dump(it2->first,it2->second,cur,sum);
      }
      dump(x1,x2,sum,x2-x1,(x2-x1)*sum);
      res+=(x2-x1)*sum;
    }
    
    /*
    int sum=0;
    REP(i,100){
      REP(j,100) {
        cerr<<board[i][j]; sum+=board[i][j];
      }
      cerr<<endl;
    }
    dump(sum);*/
    
    return res;
  }
};

// CUT begin
ifstream data("UnreliableRover.sample");

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

bool do_test(string direction, vector<int> minSteps, vector<int> maxSteps, long long __expected) {
    time_t startClock = clock();
    UnreliableRover *instance = new UnreliableRover();
    long long __result = instance->getArea(direction, minSteps, maxSteps);
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
        string direction;
        from_stream(direction);
        vector<int> minSteps;
        from_stream(minSteps);
        vector<int> maxSteps;
        from_stream(maxSteps);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(direction, minSteps, maxSteps, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1549072285;
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
        cout << "UnreliableRover (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
