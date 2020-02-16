#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef tuple<LL,LL,LL,LL> point;
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
#define UNIQUE(A) sort((A).begin(),(A).end()),(A).erase(std::unique((A).begin(), (A).end()), (A).end());

/**
 
 2/15/2020 SRM 778 div1
 
 9:10-10:40 time is out
 
 2/16/2020
 
 13:55-14:42 give up sweep line and max rectangle solution. sample 2 does not pass.
 
 Each segment does not have owner rectangle. So it's not equal to unique K overlapping rectangles.
 
 14:42-15:47 looked at @square1001's code and got AC
 
 https://twitter.com/hanseilimak/status/1229183158433615873
 
 */
class KRectangleIntersection {
  public:
  long long maxIntersection(vector<int> xl, vector<int> yl, vector<int> xh, vector<int> yh, int K) {
    int N=SZ(xl);
    vector<LL> Y,X;
    REP(i,N) X.push_back(xl[i]),X.push_back(xh[i]),Y.push_back(yl[i]),Y.push_back(yh[i]);
    UNIQUE(X);
    UNIQUE(Y);
    
    vector<II> xs(N),ys(N);
    REP(i,N) {
      xs[i]={lower_bound(ALL(X),xl[i])-X.begin(),lower_bound(ALL(X),xh[i])-X.begin()};
      ys[i]={lower_bound(ALL(Y),yl[i])-Y.begin(),lower_bound(ALL(Y),yh[i])-Y.begin()};
    }
    
    LL res=0;
    REP(j,SZ(X))REP(i,j) {
      dump(i,j);
      VI rs;
      REP(k,N) if(xs[k].first<=i&&xs[k].second>=j) rs.push_back(k);
      dumpc(rs);
      map<int,VI> z;
      FORR(k,rs) z[ys[k].first].push_back(ys[k].second);
      priority_queue<int> Q;
      FORR(kvp,z) {
        int l=kvp.first;
        dump(l);
        FORR(right, kvp.second) Q.emplace(-right);
        while(SZ(Q)>K) Q.pop();
        if(SZ(Q)==K) {
          int r=-Q.top();
          LL dx=X[j]-X[i],dy=Y[r]-Y[l];
          SMAX(res,dx*dy);
        }
      }
    }

    return res;
  }
};


LL largestRectangleArea(vector<pair<LL,LL>>& heights) {
  stack<int> stack;
  int L = SZ(heights);
  dumpc(heights);

  vector<LL> cum(L+1);
  REP(i,L) cum[i+1]=cum[i]+heights[i].first;
  dumpc(cum);
  
  LL ans = 0;

  REP(i, L) {
    if(stack.empty()) {
      stack.push(i);
      continue;
    }

    while (!stack.empty() && heights[stack.top()].second > heights[i].second) {
      int p = stack.top();
      stack.pop();

      int width = stack.empty() ? cum[i] : cum[i] - cum[p];
      LL area = width * heights[p].second;
      dump(i,p,width,heights[p].second,area);

      ans = max(ans, area);
    }

    // stack.top() <= heights[i]
    stack.push(i);
  }

  while (!stack.empty()) {
    int p = stack.top();
    stack.pop();

    int width = stack.empty() ? cum[L] : cum[L] - cum[stack.top()];
    LL area = width * heights[p].second;

    ans = max(ans, area);
  }

  return ans;
}



class KRectangleIntersection_wrong {
  public:
  long long maxIntersection(vector<int> xl, vector<int> yl, vector<int> xh, vector<int> yh, int K) {
    int N=SZ(xl);
    
    vector<tuple<LL,int,int>> ys,ye;
    vector<LL> Y;
    REP(i,N) ys.emplace_back(yl[i],1,i),Y.push_back(yl[i]); // start
    REP(i,N) ys.emplace_back(yh[i],-1,i),Y.push_back(yh[i]); // end
    sort(ALL(ys));
    UNIQUE(Y);
    vector<II> yrange(N);
    int M=SZ(Y);
    REP(i,N) {
      REP(j,M) if(yl[i]==Y[j]) yrange[i].first=j;
      REP(j,M) if(yh[i]==Y[j]) yrange[i].second=j;
    }
    dumpc(Y);
    
    map<LL,VI> xs,xe;
    vector<LL> X;
    REP(i,N) xs[xl[i]].emplace_back(i),X.push_back(xl[i]); // start
    REP(i,N) xe[xh[i]].emplace_back(i),X.push_back(xh[i]); // end
    UNIQUE(X);
    
    vector<set<pair<LL,int>>> z(M-1);
    LL res=0;
    FORR(x,X) {
      dump(x);
      vector<pair<LL,LL>> hs(M-1); // width,height
      REP(i,M-1) {
        dump(i);
        dumpc(z[i]);
        hs[i]={Y[i+1]-Y[i],0};
        int cnt=SZ(z[i]);
        if (cnt==0) continue;
        auto it=z[i].end(); --it;
        while(cnt>=K) {
          hs[i].second=x-it->first;
          dump(cnt,hs[i].second,x,it->first,it->second);
          --it,--cnt;
        }
      }
      dumpc(hs);
      LL a=largestRectangleArea(hs);
      dump(a);
      SMAX(res,a);
      FORR(i,xe[x]) {
        FOR(j,yrange[i].first,yrange[i].second) {
          z[j].erase({xl[i],i});
        }
      }
      FORR(i,xs[x]) {
        FOR(j,yrange[i].first,yrange[i].second) {
          z[j].emplace(x,i);
        }
      }
    }
    
    return res;
  }
};

// CUT begin
ifstream data("KRectangleIntersection.sample");

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

bool do_test(vector<int> xl, vector<int> yl, vector<int> xh, vector<int> yh, int k, long long __expected) {
    time_t startClock = clock();
    KRectangleIntersection *instance = new KRectangleIntersection();
    long long __result = instance->maxIntersection(xl, yl, xh, yh, k);
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
        vector<int> xl;
        from_stream(xl);
        vector<int> yl;
        from_stream(yl);
        vector<int> xh;
        from_stream(xh);
        vector<int> yh;
        from_stream(yh);
        int k;
        from_stream(k);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(xl, yl, xh, yh, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1581786665;
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
        cout << "KRectangleIntersection (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
