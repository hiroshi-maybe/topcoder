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
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/1/2018
 
 19:37-19:43 analysis
 19:44-20:07 implement and ACC (339.39 pt)
 
 3/2/2018
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+519
  - http://d.hatena.ne.jp/kusano_prog/20110920/1316550699
   - solving shortest path by floyd-warshall
  - http://purple-jwl.hatenablog.com/entry/20121105/1352096706
  - http://topcoder.g.hatena.ne.jp/firewood/20111021/1319213138
  - http://dixq.net/forum/blog.php?u=536&b=2354&c=3&sid=03b2f6614d17ba686a710d7c52992914
  - http://peryaudo.hatenablog.com/entry/20110920/1316506652
 
 22:50-23:02 add O(V^3) solution
 
 Summary:
  - Planning was straightforward. However some implementation mistakes
   - computation was not happening in the appropriate scope
   - missed to implement permutation of order
   - it took some time to debug them 👎
 
 */

// Floyd-Warshall, O(V^3) time
class ThreeTeleports {
public:
  LL dist(LL x1, LL y1, LL x2, LL y2) {
    return abs(x1-x2)+abs(y1-y2);
  }
  int shortestDistance(int xs, int ys, int xt, int yt, vector<string> TT) {
    LL mx[8][8]={{0}};
    vector<II> P(8);
    P[0]={xs,ys},P[7]={xt,yt};
    
    REP(i,3) {
      int x1,y1,x2,y2;
      stringstream(TT[i])>>x1>>y1>>x2>>y2;
      P[2*i+1]={x1,y1},P[2*i+2]={x2,y2};
    }
    
    REP(i,8) REP(j,8) {
      if(i!=j&&i>=1&&j>=1&&(i-1)/2==(j-1)/2) mx[i][j]=10;
      else mx[i][j]=dist(P[i].first,P[i].second,P[j].first,P[j].second);
    }
    
    REP(k,8)REP(i,8)REP(j,8) {
      SMIN(mx[i][j],mx[i][k]+mx[k][j]);
    }
    
    /*
    REP(i,8) {
      REP(j,8) cout << mx[i][j]<<",";
      cout<<endl;
    }*/
    
    return mx[0][7];
  }
};

vector<string> split(const string &s, char c) {
  vector<string> res;
  
  istringstream ss(s);
  string token;
  while(getline(ss,token,c)) {
    res.push_back(token);
  }
  
  return res;
}
// O(4^V*V!) time
class ThreeTeleports_org {
  public:
  int shortestDistance(int xs, int ys, int xt, int yt, vector<string> TT) {
    vector<II> T[3];
    REP(i,3) {
      string t=TT[i];
      vector<string> ss=split(t,' ');
      
      T[i].push_back({stoi(ss[0]),stoi(ss[1])});
      T[i].push_back({stoi(ss[2]),stoi(ss[3])});
    }
    
    LL res=abs(xt-xs)+abs(yt-ys);
    REP(mask,1<<3) {
      VI T2;
      REP(i,3) if((mask>>i)&1) T2.push_back(i);
      int N=SZ(T2);
      VI perm(N);
      REP(i,N) perm[i]=i;
      do {
        VI T3(N);
        REP(i,N) T3[i]=T2[perm[i]];
        
        REP(mask2,1<<N) {
          LL x=xs,y=ys,t=0;
          REP(j,N) {
            vector<II> W=T[T3[j]];
            int on=(mask2>>j)&1;
            LL ax=W[on].first,ay=W[on].second,bx=W[1^on].first,by=W[1^on].second;
            t+=abs(ax-x)+abs(ay-y)+10;
            x=bx,y=by;
          }
          t+=abs(xt-x)+abs(yt-y);
//          if(mask==7&&mask2=)
          SMIN(res,t);
        }
        
      } while(next_permutation(perm.begin(),perm.end()));
    }
    return res;
  }
};

// CUT begin
ifstream data("ThreeTeleports.sample");

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

bool do_test(int xMe, int yMe, int xHome, int yHome, vector<string> teleports, int __expected) {
    time_t startClock = clock();
    ThreeTeleports *instance = new ThreeTeleports();
    int __result = instance->shortestDistance(xMe, yMe, xHome, yHome, teleports);
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
        int xMe;
        from_stream(xMe);
        int yMe;
        from_stream(yMe);
        int xHome;
        from_stream(xHome);
        int yHome;
        from_stream(yHome);
        vector<string> teleports;
        from_stream(teleports);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(xMe, yMe, xHome, yHome, teleports, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519961856;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ThreeTeleports (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
