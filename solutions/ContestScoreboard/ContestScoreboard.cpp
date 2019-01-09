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
typedef tuple<int,string,int> ISI;
typedef pair<int,int> II;

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

// note that the last empty element is trimmed
vector<string> split(const string &s, char c) {
  vector<string> res;
  
  istringstream ss(s);
  string token;
  while(getline(ss,token,c)) {
    res.push_back(token);
  }
  
  return res;
}

bool comp(pair<int,string> a, pair<int,string> b) {
  if(a.first!=b.first) return a.first>b.first;
  return a.second<b.second;
}

/**
 
 8/4/2017
 
 17:28-17:45 design
 17:45-18:07 implementation and fixing bug (sort mistake, index mistake)
 18:07-18:22 (206.10 pt)

 22:46-23:26 read editorial and solutions
 - https://apps.topcoder.com/wiki/display/tc/SRM+679
  - O(M*N*L) time (=2500*100*100<3*10^7), M: total number of submissions, N: number of teams, L: length of a score string
  - simplify logic by iterating string M times
  - similar approaches
    - https://community.topcoder.com/stat?c=problem_solution&rm=327907&rd=16649&pm=14124&cr=40100022
    - https://community.topcoder.com/stat?c=problem_solution&rm=327897&rd=16649&pm=14124&cr=40005028
      - get max without sort.
 
 23:30-24:08 add editorial solution
  - two bug fixes (10 mins)
    - missed to update max score
    - score is not sorted by time 😱
 
 d=t0,t1,...,tT
 win(d) = { i: S(p,d)=max{ S(i,d)=∑{score[i][j], time[i][j]<=d}: i=0..<N } }
 
 Key:
 - pin time and iterate
  - we are interested in distinct time
  - get unique set to avoid complex processing of same time submission
 
 Summary:
  - design div2 medium problems in more details before coding
 
 */

class ContestScoreboard {
public:
  vector<int> findWinner(vector<string> SS) {
    int N=SZ(SS);
    map<string,int,greater<string>> NAME;
    set<int> T;
    vector<vector<II>> ST(N);
    REP(i,N) {
      stringstream ss(SS[i]);
      string name;
      ss >> name;
      NAME[name]=i;
      int score, time; char _;
      while(ss >> score >> _ >> time) {
        ST[i].emplace_back(time,score);
        T.emplace(time);
      }
      sort(ST[i].begin(),ST[i].end());
    }
    T.insert(0);
    
    VI res(N,0);
    FORR(d,T) {
      int maxi=-1; int maxs=0;
      FORR(kvp,NAME) {
        int i=kvp.second;
        int score=0;
        for(int j=0; j<SZ(ST[i])&&ST[i][j].first<=d; ++j) score+=ST[i][j].second;
        if(score>=maxs) maxi=i,maxs=score;
      }
      assert(0<=maxi&&maxi<N);
      res[maxi]|=1;
    }
    
    return res;
  }
};

// O(M*N*lg N) time (=2500*100*lg 100<2*10^6), M: total number of submissions, N: number of teams.
class ContestScoreboard_org {
  public:
  map<string,int> NAME;
  vector<int> findWinner(vector<string> S) {
    int N=SZ(S);
    vector<ISI> SS;
    vector<pair<int,string>> scores(N);
    REP(i,N) {
      auto ts = split(S[i],' ');
      string name=ts.front();
      NAME[name]=i;
      FOR(j,1,SZ(ts)) {
        auto us=split(ts[j],'/');
        assert(SZ(us)==2);
        int time=stoi(us[1]),score=stoi(us[0]);
        SS.emplace_back(time,name,score);
      }
      scores[i]={0,name};
    }
    sort(SS.begin(),SS.end());
    VI res(N,0);
    res[(NAME.begin())->second]=1;
    
    SS.emplace_back(2*1e9, "#", 0);
    int prev=0;
    REP(i,SZ(SS)) {
      ISI ss=SS[i];
      int time,s; string name;
      tie(time,name,s) = ss;
//      dump4(i,time,name,s);
      
      if(time!=prev) {
        sort(scores.begin(),scores.end(),&comp);
        string x=scores.front().second;
//        dump3(i-1,x,scores.front().first);
        res[NAME[x]]|=1;
      }
      
      REP(j,N) {
        if(scores[j].second==name) scores[j].first+=s;
//        dump2(scores[j].second,scores[j].first);
      }
      prev=time;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("ContestScoreboard.sample");

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

bool do_test(vector<string> scores, vector<int> __expected) {
    time_t startClock = clock();
    ContestScoreboard *instance = new ContestScoreboard();
    vector<int> __result = instance->findWinner(scores);
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
        vector<string> scores;
        from_stream(scores);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(scores, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501892913;
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
        cout << "ContestScoreboard (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
