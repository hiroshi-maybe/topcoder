#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>

using namespace std;

#define MAX_V 100
#define MAX_N 60
namespace SubsetSum {
  /*
   
   Typical subset sum dp, O(N^2*V) time, O(N*V) space
   
   dp[sum] = true/false
   
   */
  bool dp[MAX_N*MAX_V+1];
  void solve(vector<int> ns) {
    memset(dp, 0, sizeof dp);
    dp[0]=1;
    for(int n : ns) for(int sum=MAX_N*MAX_V; sum>=n; --sum) {
      dp[sum]|=dp[sum-n];
    }
  }

  /*
   
   Subset sum dp with bitset, O(N) time, O(N*V) space
   
   sumset[sum] = true/false
   
   */
  bitset<MAX_N*MAX_V+1> sumset={1};
  void solve_bitset(vector<int> ns) {
    for(int n : ns) sumset|=sumset<<n;
  }

  /*
   
   Subset sum for number of elements, O(N^2*V) time, O(N*V) space
   
   dp2[sum] = mask of possible number of elements, 0<=dp2[cnt]<=2^MAX_N
   
   Used problems:
    - https://leetcode.com/problems/split-array-with-same-average/
   
   */
  long long dp2[MAX_N*MAX_V+1];
  void countElements(vector<int> ns) {
    memset(dp2, 0, sizeof dp2);
    dp2[0]=1;
    for(int n : ns) for(int sum=MAX_N*MAX_V; sum>=0; --sum) {
      if(sum+n<=MAX_N*MAX_V) dp2[sum+n]|=dp2[sum]<<1;
    }
  }
  
  /*
   
   Subset sum for number of elements with bitset, O(N^2) time, O(N^2*V) space
   
   sumset2[cnt][sum] = true/false
   
   Used problems:
    - https://leetcode.com/problems/split-array-with-same-average/
   
   */
  bitset<MAX_N*MAX_V+1> sumset2[MAX_N+1]={1};
  void countElements_bitset(vector<int> ns) {
    memset(sumset2, 0, sizeof sumset2);
    sumset2[0]=1;
//    fill(sumset2, sumset2+MAX_N+1, 1);
//    cout<<sumset2[1]<<endl;
    for(int n : ns) for(int cnt=MAX_N; cnt>0; --cnt) {
      sumset2[cnt]|=sumset2[cnt-1]<<n;
    }
//    cout<<sumset2[1]<<endl;
  }
  
//********* test helpers *********//
  
  // O(N*2^N) time, O(N*V) space
  // brute-force all power-set to find subset sum
  vector<int> bruteforce(vector<int> ns) {
    int tot=accumulate(ns.begin(),ns.end(),0);
    int sums[MAX_N*MAX_V+1]={0};
    int N=ns.size();
    for(int mask=0; mask<(1<<N); ++mask) {
      int sum=0;
      for(int i=0; i<N; ++i) if((mask>>i)&1) {
        sum+=ns[i];
      }
      sums[sum]=true;
    }
    vector<int> res;
    for(int x=0; x<=tot; ++x) if(sums[x]) res.push_back(x);
    return res;
  }
  
  // brute-force all power-set to find subset sum with number of elements
  unordered_map<int,unordered_set<int>> bruteforce2(vector<int> ns) {
    unordered_map<int,unordered_set<int>> res;
    int N=ns.size();
    for(int mask=0; mask<(1<<N); ++mask) {
      int sum=0;
      for(int i=0; i<N; ++i) if((mask>>i)&1) {
        sum+=ns[i];
      }
      res[sum].emplace(__builtin_popcount(mask));
    }
    return res;
  }
  
  void test() {
    vector<int> ns={1,20,31,39,80};
    
    SubsetSum::solve(ns);
    SubsetSum::solve_bitset(ns);
    SubsetSum::countElements(ns);
    SubsetSum::countElements_bitset(ns);
    
    vector<int> expss = SubsetSum::bruteforce(ns);
    //  for(int x : exp) cout << x << ",";
    //  cout << endl;
    unordered_set<int> S(expss.begin(),expss.end());
    for(int sum=0; sum<=MAX_N*MAX_V; ++sum) {
      bool e=S.count(sum)>0;
      assert(e==SubsetSum::dp[sum]);
      assert(e==(SubsetSum::sumset[sum]&1));
    }
    
    auto expss2 = SubsetSum::bruteforce2(ns);
    for(int sum=0; sum<=MAX_N*MAX_V; ++sum) for(int cnt=0; cnt<=MAX_N; ++cnt) {
      bool e=expss2.count(sum)>0&&expss2[sum].count(cnt)>0;
      bool a1=(SubsetSum::dp2[sum]>>cnt)&1,a2=SubsetSum::sumset2[cnt][sum];
      assert(e==a1);
      assert(e==a2);
    }
  }
}
       
int main(int argc, char const *argv[]) {
  SubsetSum::test();
}
