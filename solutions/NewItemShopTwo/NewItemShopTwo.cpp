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
 
 3/7/2018
 
 9:51-10:06 analysis and pause
 10:07-11:30
 18:00-19:20 give up
 19:40 add solution
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+515
  - http://d.hatena.ne.jp/kusano_prog/20110821/1313951155
  - http://d.hatena.ne.jp/rom_k/20110821/1313944651
  - http://kmjp.hatenablog.jp/entry/2014/01/16/1000
 
 I assumed that cusotmer's probability is independent without reading the problem statement carefully.
 That's because many of problems hold this independnece property.
 However I completely missed it. It's very stupid. 😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡

 3/8/2018
 
 Read articles of probability and consolidate knowledge of conditional probability/expectation
 
 3/9/2018
 
 Analyze problem again and describe as below:
 
 There are some challenges in this problem in terms of probability
  - Use expectation to "choose" and calc expectation
  - Event of customer 1 is independent of event of customer 2. However event of combination of them is conditional
  - Per problem statement, event that customer comes is not independent each other. That forms sample space.
  - Conditional expectation needs to be calculated to choose strategy
 
 There are some solutions based on how to design sample space and random variable.
 
 Solution 1. Take pair of visited time of customers for random variable
 
 Ω = { (t1,t2) : t1∈T1, t2∈T2, T1 = time potentially customer 1 visits, T2 = same for customer 2 }
 
 E[X] = ∑ { E[X(t1,t2)=x] : (t1,t2) ∈ Ω }
 
 E[X(t1,t2)=x] = x * Pr[T1=t1,T2=t2]
 
 Since probability of customer 1 and customer 2 is mutually independent..
 Pr[T1=t1,T2=t2] = Pr[T1=t1]*Pr[T2=t2]
 
 Tricky part is computation of `x`.
 Problem statement is saying that shop makes a choice which maximizes expected value.
 Suppose either customer visited shop at t=t1'. Time that the other visits is t2'.
 (t1,t2)=(t1',t2') or (t2',t1') depending on t1' is time of customer 1 or customer 2.
 Shop chooses to sell at t=t1'.
 If value(t1') is higher than expected value at that moment, shop sells and gets value(t1').
 Otherwise shop gets value(t2').
 There are two points that we should keep in mind.
 
 1. T'=t1' is DIFFERENT random variable from T1=t1' or T2=t1'
 
 This random variable picks up an event that first customer visited the shop at t=t1'.
 Thus Pr[T'=t1'] != Pr[T1=t1'] AND Pr[T'=t1'] != Pr[T2=t1']
 User has visited shop at t=t1' for the first time for this event while it doesn't matter which customer visits first in event (t1,t2) ∈ Ω
 At t=t1', the second customer may have had chance to visit shop before t1'.
 In order for the other customer to come in t>t1', he/she should NOT visit in t<t1'.
 We should compute probability considering that second customer did not actually visit.
 
 If t1' is customer 1's time slot (t1'=t1, t2'=t2)...
 
 Pr[T'=t1'] = Pr[T1=t1'] * ∑ { 1-Pr[T2=t] : t<t1', t∈ T2 }
 
 Otherwise...
 
 Pr[T'=t1'] = Pr[T2=t1'] * ∑ { 1-Pr[T1=t] : t<t1', t∈ T1 }

 2. Expected value is CONDITIONAL
 
 Expected value is CONDITIONAL expectation because we already know that event T'=t1' has already happened.
 E[Y|T'=t1'] is the value that we want to compute.
 
 Based on above discussion...
 
   E[Y|T'=t1']
 = ∑ { E[Y=y|T'=t1'] : y = value(t), t>t1' }
 = ∑ { y * Pr[Y=y|T'=t1'] } // definition of conditional expectation
 = ∑ { y * Pr[Y=y,T'=t1']/Pr[T'=t1'] } // definition of conditional probability
 
   Pr[T'=t1']
 = Pr[T1=t1'] * ∑ { 1-Pr[T2=t] : t<t1', t∈ T2 }
   or Pr[T2=t1'] * ∑ { 1-Pr[T1=t] : t<t1', t∈ T1 }

   Pr[Y=y,T'=t1']
 = Pr[T1=t1']*Pr[T2=t2']
   or Pr[T1=t2']*Pr[T2=t1']
 
 From above formulas...
 
   Pr[Y=y,T'=t1']/Pr[T'=t1']
 = Pr[T1=t1']*Pr[T2=t2'] / Pr[T1=t1'] * ∑ { 1-Pr[T2=t] : t<t1', t∈ T2 }
 = Pr[T2=t2'] / ∑ { 1-Pr[T2=t] : t<t1', t∈ T2 }
 
 Thus we can calculate E[Y|T'=t1']
 
 If E[Y|T'=t1'] < value(t1'), x = value(t1')
 Otherwise x = value(t2')
 
 E[X(t1,t2)=x] = x * Pr[T1=t1,T2=t2], x = E[Y|T'=t1'] < value(t1') ? value(t1') : value(t2')
 
 Solution 2. Take time of first visit as primary random variable (solution by @kmjp or official editorial)
 
 Ω = { t : t = 0..23 }
 
   E[x]
 = ∑ { E[X(t)=x] : t=0..23 }
 = ∑ { x * Pr[X(t)=x] : t=0..23 }
 
 Pr[X(t)=x] = Pr[T'=t], which is computed in solution #1.
 
 Pr[T'=t] = Pr[T1=t1'] * ∑ { 1-Pr[T2=t] : t<t1', t∈T2 }
 
 Shop chooses higher expectation `x` = max(value(t), E[Y|T'=t])
 
 E[Y|T'=t] is also computed in solution #1 as well.
 
   E[Y|T'=t]
 = ∑ { E[Y=y|T'=t1'] : y = value(t), t>t1' }
 = ∑ { y * Pr[T2=t2'] / ∑ { 1-Pr[T2=t] : t<t1', t∈T2 } : y = value(t), t>t1' }
 
 Solution 3. DP
 
 There are two types of expectations
 1. expectation which contributes to the result
 2. expectation used for choice of shop
 
 Either one can be differentiated by keeping state of customer 1's visit and custome 2's visit.
 We can use dynamic programming to calculate those expectations at the same time.
 
 Summary:
  - Basic idea to take max(taken case, rejected case) is trivial
  - I misunderstood that probability of customer's appearance is independent. However that's not the case.
  - However my knowledge of conditional probability is completely messed up 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
  - I spent two days to understand what I was not understanding. It turned out that my understanding of conditional probability and conditional expectation is not sufficient.
  - I reviewed wrong points of my analysis and added solutions.
  - Keep in mind what is the event and sample space for which we want to know probability
   - Probability is determined by EVENT
   - Randome variable T' and T1,T2 seem to be same though, event of them is very different!!!!!!
 
 */
vector<string> split(const string &s, char c) {
  vector<string> res;
  
  istringstream ss(s);
  string token;
  while(getline(ss,token,c)) {
    res.push_back(token);
  }
  
  return res;
}
// Solution 3, O(N*lg N) time
double memo[51][4];
class NewItemShopTwo_dp {
public:
  vector<tuple<int,int,int,double>> xs;
  double f(int i, int mask) {
    if(i==SZ(xs)) return 0;
    double &res=memo[i][mask];
    if(res>-1) return res;
    int t,c,v; double p;
    tie(t,c,v,p)=xs[i];
    
    if((mask>>c)&1) return res=f(i+1, mask);
    
    double a=v,b=f(i+1, mask|(1<<c));
    res=p*max(a,b)+(1.0-p)*f(i+1,mask);
    return res;
  }
  double getMaximum(vector<string> C) {
    MINUS(memo);
    REP(i,2) {
      string s=C[i];
      REP(i,SZ(s)) if(s[i]==',') s[i]=' ';
      int t,v,pr;
      stringstream ss(s);
      double totp=0;
      while(ss>>t>>v>>pr) {
        double p=0.01*pr;
        // Conditional probability
        xs.emplace_back(t,i,v,p/(1.0-totp));
        totp+=p;
      }
    }
    sort(xs.begin(),xs.end());
    return f(0,0);
  }
};

// Solution #2, O(N^2) time
class NewItemShopTwo {
public:
  vector<tuple<int,int,int,double>> xs;
  double getMaximum(vector<string> C) {
    REP(i,2) {
      string S=C[i];
      REP(i,SZ(S)) if(S[i]==',') S[i]=' ';
      stringstream ss(S);
      int t,v,pr;
      while(ss>>t>>v>>pr) {
        xs.emplace_back(t,i,v,0.01*pr);
      }
    }
    sort(xs.begin(),xs.end());
    double res=0;
    int N=SZ(xs);
    
    // ∑ { 1-Pr[T2=t] : t<t1', t∈T2 }
    double basep[2]={1.0,1.0};
    REP(i,N) {
      int t,c,v; double pr;
      tie(t,c,v,pr)=xs[i];
//      dump4(t,c,v,basep[c^1]);
      basep[c]-=pr;
      double e=0;
      FOR(j,i+1,N) {
        int t2,c2,y; double pr2;
        tie(t2,c2,y,pr2)=xs[j];
        if(c2==c) continue;
        e+=y*pr2;
      }
      e=basep[c^1]==0?0:e/basep[c^1];
      double x = max(1.0*v,e);
      res+=x*pr*basep[c^1];
      //      dump4(i,e,max(e/pp,(double)v),pp*p*max(e,(double)v));
    }
    
    return res;
  }
};

// Solution #1, O(N^3) time
class NewItemShopTwo_sol1 {
public:
  vector<tuple<int,int,int,double>> xs;
  
  // calculate E[Y|T'=t1']
  double calcExp(int i) {
    // p1 = Pr[T1=t1']
    int t1,c1,v1; double p1;
    tie(t1,c1,v1,p1)=xs[i];
    double res=0;
    double basep=1.0;
    
    // Calculate probability that the other customer has not visited.
    // basep = ∑ { 1-Pr[T2=t] : t<t1', t∈ T2 }
    REP(j,i) {
      int t,c,v; double pr;
      tie(t,c,v,pr)=xs[j];
      if(c==c1) continue;
      basep-=pr;
    }
    
    // basep = Pr[T'=t1'] = Pr[T1=t1'] * ∑ { 1-Pr[T2=t] : t<t1', t∈ T2 }
    basep*=p1;
    if(basep==0) return 0;
    FOR(j,i+1,SZ(xs)) {
      int t,c,y; double pr;
      tie(t,c,y,pr)=xs[j];
      if(c==c1) continue;
      // Conditional expectation:
      // E[Y=y|T'=t1'] = y*Pr[Y=y,T'=t1']/Pr[T'=t1']
      res+=y*p1*pr/basep;
    }
    return res;
  }
  
  double getMaximum(vector<string> C) {
    double totp[2]={0.0};
    REP(i,2) {
      vector<string> ys=split(C[i],' ');
      FORR(y,ys) {
        vector<string> zs=split(y,',');
        double p=0.01*stoi(zs[2]);
        xs.emplace_back(stoi(zs[0]),i,stoi(zs[1]),p);
        totp[i]+=p;
      }
    }
    // Add events that customers have never visited
    xs.emplace_back(50,0,0,1.0-totp[0]);
    xs.emplace_back(51,1,0,1.0-totp[1]);
    
    sort(xs.begin(),xs.end());
    
    double res=0;
    int N=SZ(xs);
    
    REP(j,N) REP(i,j) {
      int t1,c1,v1,t2,c2,v2; double pr1,pr2;
      tie(t1,c1,v1,pr1)=xs[i];
      tie(t2,c2,v2,pr2)=xs[j];
      if(c1==c2) continue;
      // Pr[T1=t1,T2=t2]
      double basep=pr1*pr2;
      // E[Y|T'=t1']
      double e=calcExp(i);
      double ee=basep*(v1>e?v1:v2);
      res+=ee;
    }
    
    return res;
  }
};

// Take random variable of pair of visited time. Wrong code of solution 1.
class NewItemShopTwo_wrong1 {
public:
  vector<tuple<int,int,int,int>> xs;
  // There are two misunderstanding in this model of sample space and random variable:
  //  - Expectation should be "conditional" because we know that customer has come at `t1`
  //  - Probability that customer does not visit should be "sum" of probability instead of "product"
  double exp(int i) {
    double res=0;
    int cc=get<3>(xs[i]);
    FOR(j,i+1,SZ(xs)) {
      int t,c,v,pr;
      tie(t,c,v,pr)=xs[j];
      if(c==cc) continue;
      // probability should be summed
      res+=0.01*pr*v;
    }
    return res;
  }
  
  double getMaximum(vector<string> C) {
    REP(i,2) {
      vector<string> ys=split(C[i],' ');
      FORR(y,ys) {
        vector<string> zs=split(y,',');
        xs.emplace_back(stoi(zs[0]),i,stoi(zs[1]),stoi(zs[2]));
      }
    }
    int np1=0,np2=0;
    REP(i,SZ(xs)) {
      int c=get<1>(xs[i]),pr=get<3>(xs[i]);
      (c==0?np1:np2)+=pr;
    }
    np1=100-np1,np2=100-np2;
    
    xs.emplace_back(50,0,0,np1);
    xs.emplace_back(51,1,0,np2);
    
    dump2(np1,np2);
    
    sort(xs.begin(),xs.end());
    
    double res=0;
    int N=SZ(xs);
    
    REP(j,N) REP(i,j) {
      int t1,c1,v1,pr1,t2,c2,v2,pr2;
      tie(t1,c1,v1,pr1)=xs[i];
      tie(t2,c2,v2,pr2)=xs[j];
      if(c1==c2) continue;
      double basep=0.0001*pr1*pr2;
      dump4(i,j,t1,t2);
      dump3(pr1,pr2,basep);

      double e1=exp(i);
      dump(e1);
//      dump4(i,j,e1,v1);
      if(v1>e1) {
        res+=basep*v1;
//        dump4(i,j,basep,v1);
      } else {
        res+=basep*v2;
//        dump3(i,j,basep*v2);
      }
    }
    
    return res;
  }
};

/*
 class NewItemShopTwo_org {
 public:
 vector<tuple<int,int,int,int>> xs;
 double exp(int i) {
 double res=0;
 int cc=get<3>(xs[i]);
 FOR(j,i+1,SZ(xs)) {
 int t,c,v,pr;
 tie(t,c,v,pr)=xs[j];
 if(c==cc) continue;
 res+=0.01*pr*v;
 }
 return res;
 }
 double getMaximum(vector<string> C) {
 REP(i,2) {
 vector<string> ys=split(C[i],' ');
 FORR(y,ys) {
 vector<string> zs=split(y,',');
 xs.emplace_back(stoi(zs[0]),i,stoi(zs[1]),stoi(zs[2]));
 }
 }
 
 sort(xs.begin(),xs.end());
 double res=0;
 int N=SZ(xs);
 REP(i,N) {
 int t,c,v,pr;
 tie(t,c,v,pr)=xs[i];
 
 double p=1.0*pr/100.0;
 
 double pp=1.0;
 REP(j,i) {
 int t2,c2,v2,pr2;
 tie(t2,c2,v2,pr2)=xs[j];
 if(c2==c) continue;
 //        pp*=1.0-0.01*pr2;
 pp-=0.01*pr2;
 }
 
 double e=0;
 FOR(j,i+1,N) {
 int t2,c2,v2,pr2;
 tie(t2,c2,v2,pr2)=xs[j];
 if(c2==c) continue;
 e+=0.01*pr2*v2;
 }
 dump4(i,t,v,pp*p*max(pp?(e/pp):0,(double)v));
 res+=pp*p*max(pp?(e/pp):0,(double)v);
 //      dump4(i,e,max(e/pp,(double)v),pp*p*max(e,(double)v));
 }
 
 int np1=0,np2=0;
 REP(i,SZ(xs)) {
 int c=get<1>(xs[i]),pr=get<3>(xs[i]);
 (c==0?np1:np2)+=pr;
 }
 np1=100-np1,np2=100-np2;
 
 xs.emplace_back(50,0,0,np1);
 xs.emplace_back(51,1,0,np2);
 
 dump2(np1,np2);
 
 sort(xs.begin(),xs.end());
 
 double res=0;
 int N=SZ(xs);
 
 REP(j,N) REP(i,j) {
 int t1,c1,v1,pr1,t2,c2,v2,pr2;
 tie(t1,c1,v1,pr1)=xs[i];
 tie(t2,c2,v2,pr2)=xs[j];
 if(c1==c2) continue;
 double basep=0.0001*pr1*pr2;
 dump4(i,j,t1,t2);
 dump3(pr1,pr2,basep);
 
 double e1=exp(i);
 dump4(i,j,e1,v1);
 if(v1>e1) {
 res+=basep*v1;
 dump4(i,j,basep,v1);
 } else {
 res+=basep*v2;
 dump3(i,j,basep*v2);
 }
 }
 
 return res;
 }
 };*/

// CUT begin
ifstream data("NewItemShopTwo.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<string> customers, double __expected) {
    time_t startClock = clock();
    NewItemShopTwo *instance = new NewItemShopTwo();
    double __result = instance->getMaximum(customers);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<string> customers;
        from_stream(customers);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(customers, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1520445059;
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
        cout << "NewItemShopTwo (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
