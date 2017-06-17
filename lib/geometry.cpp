#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

struct Vector {
public:
  int x, y;
  Vector(pair<int,int> p1, pair<int,int> p2): Vector(p1.first-p2.first, p1.second-p2.second) {}
  Vector(int x, int y): x(x), y(y) {}
    
  int length() {
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

int crossProduct(Vector u, Vector v) {
  return u.x*v.y - u.y*v.x;
}
int crossProduct(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vs = makeVectors(p1,p2,origin);
  return crossProduct(vs.first,vs.second);
}
int dotProduct(Vector u, Vector v) {
  return u.x*v.x + u.y*v.y;
}

// 90 degree
bool isVertical(Vector u, Vector v) {
  return dotProduct(u,v)==0;
}

int length(pair<int,int> p1, pair<int,int> p2) {
  int dx = p1.first-p2.first, dy = p1.second-p2.second;
  return dx*dx + dy*dy;
}

// CLRS 33.1
// p1->p2 intersects p3->p4
bool onSegment(pair<int,int> p1, pair<int,int> p2, pair<int,int> pi) {
  int xmin=min(p1.first, p2.first),
      xmax=max(p1.second, p2.second),
      ymin=min(p1.second, p2.second),
      ymax=max(p1.second,p2.second);
  return xmin<=pi.first && pi.first<=xmax && ymin<=pi.second && pi.second<=ymax;
}
bool intersect(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3, pair<int,int> p4) {
  int d1 = crossProduct(p3,p4,p1),
      d2 = crossProduct(p3,p4,p2),
      d3 = crossProduct(p1,p2,p3),
      d4 = crossProduct(p1,p2,p4);

  if (d1*d2<0 && d3*d4<0) return true;
  if (d1==0 && onSegment(p3,p4,p1)) return true;
  if (d2==0 && onSegment(p3,p4,p2)) return true;
  if (d3==0 && onSegment(p1,p2,p3)) return true;
  if (d4==0 && onSegment(p1,p2,p4)) return true;
  return false;
}

// CLRS 33.1
// true: org->p1 is clockwise against org->p2
bool isClockwise(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vpair = makeVectors(p1,p2,origin);
  return crossProduct(vpair.first, vpair.second)>0;
}
bool isCounterClockwise(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vpair = makeVectors(p1,p2,origin);
  return crossProduct(vpair.first, vpair.second)<0;
}
// CLRS 33.1
// org->p1 and org->p2 form same direction or opposite direction
bool isColinear(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vpair = makeVectors(p1,p2,origin);
  return crossProduct(vpair.first, vpair.second)==0;
}
// CLRS 33.1
// true: p1->p2 is left turn for origin
bool isLeftTurn(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  return isClockwise(p1,p2,origin);
}
// CLRS 33.1
// true: p1->p2 is right turn for origin
bool isRightTurn(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  return isCounterClockwise(p1,p2,origin);
}

// CLRS 33.3 GRAHAM-SCAN(Q)
pair<int,int> p0;
bool comp(const pair<int,int> a, const pair<int,int> b) {
  int crossprod = crossProduct(a, b, p0);
  if (crossprod!=0) return crossprod > 0;
  return length(a,p0) < length(b,p0); // tie for colinear points
}
vector<pair<int,int>> findConvexHull(vector<pair<int,int>> ps) {
  if (ps.size()<3) return {};

  // find p0 (bottom left point)
  int p0_i = 0;
  for(int i=1; i<ps.size(); ++i) {
    if (ps[i].second <= ps[p0_i].second && ps[i].first <= ps[p0_i].first) p0_i = i;
  }
  swap(ps[0], ps[p0_i]);
  p0=ps[0];

  // sort by polar angle
  sort(ps.begin(), ps.end(), &comp);

  // remove all but furthest point if points have same angle
  int N=1;
  for (int i=1; i<ps.size(); ++i) {
    while(i<ps.size()-1&&isColinear(ps[i],ps[i+1],p0)) ++i;
    ps[N++] = ps[i];
  }

  if (N<3) return {};

  int si=0;
  vector<pair<int,int>> S(N);
  S[si++] = ps[0];
  S[si++] = ps[1];
  S[si] = ps[2];

  for(int i=3; i<N; ++i) {
    while(!isLeftTurn(S[si],ps[i],S[si-1])) --si;
    S[++si] = ps[i];
  }
  S.erase(S.begin()+si+1, S.end());
  return S;
}

int main(int argc, char const *argv[]) {
  pair<int,int> origin={0,0}, p1={1,0}, p2={0,1}, p3={-1,0}, p4={0,-1};

  assert(isVertical(Vector(p1, origin), Vector(p2, origin)));
  assert(isClockwise(p1, p2, origin));
  assert(isCounterClockwise(p2, p1, origin));
  assert(isColinear(p1, p3, origin));
  assert(isLeftTurn(p1, p2, origin));
  assert(isRightTurn(p2, p1, origin));
  assert(intersect(p1, p4, p2, p4));

  // http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
  vector<pair<int,int>> ps = findConvexHull({{0,3},{1,1},{2,2},{4,4},{0,0},{1,2},{3,1},{3,3}});
  vector<pair<int,int>> exp = {{0,0},{3,1},{4,4},{0,3}};
  assert(ps.size()==exp.size());
  for(int i=0; i<ps.size(); ++i) {
    assert(ps[i].first==exp[i].first&&ps[i].second==exp[i].second);
  }
}
