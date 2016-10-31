/**
 * 
 * 10/30/2016
 * 
 * 15:48 start
 * 16:06 start reading solutions
 * 17:14 replicated code and accepted
 */

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
#define REPS(i,arr)  for(int i=0; i<(arr).size(); ++i)

typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;

class Solution {
public:
  bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
    if (seqs.empty()) return false;
    int L = SZ(org);
    MAPII pos;
    REP(i,L) pos[org[i]] = i;

    VI prev(L,-1);
    VI next(L,L);
    FORR(seq, seqs) {
      REP(i, SZ(seq)) {
	int n = seq[i];
	if (n<1 || n>L) return false;
	int p = pos[n];
	if (i>0) {
	  prev[p] = max(prev[p], pos[seq[i-1]]);
	}
	if (i<SZ(seq)-1) {
	  next[p] = min(next[p], pos[seq[i+1]]);
	}
      }
    }

    REP(i, L) {
      if (prev[i]!=i-1) return false;
      if (next[i]!=i+1) return false;
    }
    return true;
  }
};
