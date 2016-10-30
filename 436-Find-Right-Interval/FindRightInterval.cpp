/**
 * 
 * 10/30/2016
 * 
 * 15:07 start
 * 15:17 TLE for brute force
 * 15:38 accepted
 */

#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

// vector
#define PUSH(s, e) (s).push_back(e)
#define POP(s) (s).pop_back()
#define REVERSE(c) reverse((c).begin(),(c).end())
#define SORT(c) sort((c).begin(),(c).end())
#define CONCAT(a,b) (a).insert((a).begin(), (b).begin(),(b).end())
#define ERASE(arr,i) (arr).erase((arr).begin()+i)

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
#define REPS(i,arr)  for(int i=0; i<(arr).size(); ++i)

typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;

bool comp(Interval &a, Interval &b) {
  return a.start < b.start;
}

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
  vector<int> findRightInterval(vector<Interval>& intervals) {
    int L = SZ(intervals);
    // start -> index
    MAPII indices;
    REP(i,L) indices[intervals[i].start] = i;

    sort(intervals.begin(),intervals.end(), comp);

    VI res(L, -1);
    REP(i, L) {
      int start = intervals[i].start;
      int end = intervals[i].end;
      int p = indices[start];

      res[p] = bs(end, intervals, indices);
    }

    return res;
  }

  // t -> index
  int bs(int t, vector<Interval>& intervals, MAPII &indices) {
    int s = 0;
    int e = SZ(intervals);
    int mid;

    while (s<e) {
      mid = (s+e) >> 1;
      int n = intervals[mid].start;
      if (n==t) return indices[n];
      if (t<n) {
	if (mid==0 || intervals[mid-1].start<t) return indices[n];
	e = mid;
      } else {
	s = mid + 1;
      }
    }

    return -1;
  }
};
