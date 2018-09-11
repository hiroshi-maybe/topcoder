#include <iostream>
#include <vector>
#include <utility>
#include <cassert>
#include <cmath>

using namespace std;

struct Vector {
public:
  int x, y;
  Vector(pair<int,int> p1, pair<int,int> p2): Vector(p1.first-p2.first, p1.second-p2.second) {}
  Vector(int x, int y): x(x), y(y) {}
    
  long long distance() {
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

/*
 
 cross product u×v
 
 u×v = det(u,v)
     = u.x * v.y - u.y * v.x
     = |u|*|v|*sin𝛩
     = area of parallelogram formed by u and v
 
 1) u×v = det(u,v) = 0
   u and v are colinear from origin
 2) u×v = det(u,v) > 0
   u is clockwise from v
 3) u×v = det(u,v) < 0
   u is counter-clockwise from v

 */
long long det(Vector u, Vector v) {
  return u.x*v.y - u.y*v.x;
}
/*
 
 cross product det(o->p1, o->p2)
 
 1) det(p1,p2,o) = 0
  o, p1 and p2 are co-linear (o->p1 is colinear with o->p2)
 2) det(p1,p2,o) > 0
  p1->p2->o is counter-clockwise order
  (o->p1 is clockwise from o->p2)
 3) det(p1,p2,o) < 0
  p1->p2->o is clockwise order
  (o->p1 is counter clockwise from o->p2)
 
 */
long long det(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vs = makeVectors(p1,p2,origin);
  return det(vs.first,vs.second);
}
long long dot(Vector u, Vector v) {
  return u.x*v.x + u.y*v.y;
}

/*
 
 Compute area of triangle formed by p1, p2 and p3
 
 A = det(p1,p2,p3) / 2
 
 */
double area(pair<double,double> p1, pair<double,double> p2, pair<double,double> p3) {
  pair<double,double> v1={ p2.first-p1.first,p2.second-p1.second };
  pair<double,double> v2={ p3.first-p1.first,p3.second-p1.second };
  
  return abs(v1.first*v2.second-v1.second*v2.first)*0.5;
}

// 90 degree
bool isVertical(Vector u, Vector v) {
  return dot(u,v)==0;
}

long long distance(pair<int,int> p1, pair<int,int> p2) {
  int dx = p1.first-p2.first, dy = p1.second-p2.second;
  return dx*dx + dy*dy;
}

// CLRS 33.1 ON-SEGMENT(pi,pj,pk)
bool onSegment(pair<int,int> p1, pair<int,int> p2, pair<int,int> pi) {
  int xmin=min(p1.first, p2.first),
      xmax=max(p1.second, p2.second),
      ymin=min(p1.second, p2.second),
      ymax=max(p1.second,p2.second);
  return xmin<=pi.first && pi.first<=xmax && ymin<=pi.second && pi.second<=ymax;
}
// CLRS 33.1 SEGMENTS-INTERSECT(p1,p2,p3,p4)
// p1->p2 intersects p3->p4
bool intersect(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3, pair<int,int> p4) {
  long long d1 = det(p3,p4,p1),
            d2 = det(p3,p4,p2),
            d3 = det(p1,p2,p3),
            d4 = det(p1,p2,p4);

  if (((d1>0&&d2<0)||(d1<0&&d2>0)) && ((d3>0&&d4<0)||(d3<0&&d4>0))) return true;
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
  return det(vpair.first, vpair.second)>0;
}
bool isCounterClockwise(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vpair = makeVectors(p1,p2,origin);
  return det(vpair.first, vpair.second)<0;
}
// CLRS 33.1
// org->p1 and org->p2 form same direction or opposite direction
bool isColinear(pair<int,int> p1, pair<int,int> p2, pair<int,int> origin) {
  auto vpair = makeVectors(p1,p2,origin);
  return det(vpair.first, vpair.second)==0;
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

// sort points by plar angle
// smaller scalar comes first for tie
void sortByPolarAngle(vector<pair<int, int>>& ps, pair<int, int> origin) {
  sort(ps.begin(), ps.end(), [&](const pair<int,int> a, const pair<int,int> b) {
    int d = det(a,b,origin);
    if(d!=0) return d > 0;
    return distance(a, origin) < distance(b, origin);
  });
}
vector<pair<int,int>> findConvexHull(vector<pair<int,int>> ps) {
  if (ps.size()<3) return {};

  // find p0 (bottom left point)
  int p0_i = 0;
  for(int i=1; i<ps.size(); ++i) {
    if (ps[i].second <= ps[p0_i].second && ps[i].first <= ps[p0_i].first) p0_i = i;
  }
  swap(ps[0], ps[p0_i]);
  pair<int, int> p0=ps[0];

  // sort by polar angle
  sortByPolarAngle(ps, p0);

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

// check if point is surrounded by given points
// if p is on segment, return true
// O(N*lg N) time
bool surrounded(pair<int,int> p, vector<pair<int, int>>& ps) {
  sortByPolarAngle(ps, p);
  vector<int> ds;
  int N=ps.size();
  for(int i=0; i<N; ++i) {
    int d = det(ps[i], ps[(i+1)%N], p);
    if(d==0) continue; // ignore colinear points or p is on segment
    d = d<0;
    if(ds.size() && ds.back()!=d) return false;
    ds.push_back(d);
  }
  return true;
}

/*
 
 Check if circle 1 is inside circle 2

 Formula:
 
 sqrt(dx*dx+dy*dy)+r1 <= R2
 
   where dx=delta x of cetner of circles, dy=delta y of center of circles
         r1=radius of circle 1, r2=radius of circle 2
 
 Used problem: https://github.com/k-ori/topcoder/blob/master/CirclesCountry/CirclesCountry.cpp#L76
 
 */
bool insideCircle(int x1, int y1, int r1, int X2, int Y2, int R2) {
  double d=hypot(abs(x1-X2),abs(y1-Y2));
  return d+r1<=R2;
}

/*
 
 Transform degree (0-360º) to radian (0-2𝛑)
 
 radian = degree * 𝛑 / 180
 
 */
double deg2rad(double deg) {
  return deg*M_PI/180.0;
}

/*
 
 Transform polar system (r,Θ) to cartesian system (x,y)
 
 (x,y) = (r * cosΘ, r * sinΘ)
 
 */
pair<double,double> polar2cartesianSys(double r, double deg) {
  double rad=deg2rad(deg);
  return { r*cos(rad), r*sin(rad) };
}

/*
 
 Rotate (x,y) by `deg` degree (not radian) in 2D
 
 (x',y') = (x*cosΘ - y*sinΘ, x*sinΘ + y*cosΘ)
 
 https://en.wikipedia.org/wiki/Rotation_matrix
 
 */
pair<double,double> rotate(pair<double,double> p, double deg) {
  double x=p.first,y=p.second;
  double rad=deg2rad(deg);
  double C = cos(rad);
  double S = sin(rad);
  return { x*C-y*S, x*S+y*C };
}

/*
 
 Data structure in 3d coordinate
 
 - Rotation in right-hand system
  - https://en.wikipedia.org/wiki/Rotation_formalisms_in_three_dimensions#Rotation_matrix_%E2%86%94_Euler_angles
  - https://en.wikipedia.org/wiki/Rotation_matrix#Basic_rotations
 - Right-hand system
  - Thumb: x-axis, Index-finger: y-axis, Middle-finger: z-axis in right hand
   - x->y is counter-clockwise from top of z-axis
  - Rotation is counter-clockwise for positive degree from top of rotation axis
 
 */
struct Vector3D {
public:
  double x, y, z;
  Vector3D(vector<double> vec) {
    assert(vec.size()==3);
    this->x=vec[0],this->y=vec[1],this->z=vec[2];
  }
  Vector3D(double x, double y, double z): x(x), y(y), z(z) {}
  
  Vector3D rotateX(double rad) {
    double s=sin(rad),c=cos(rad);
    double xx=x;
    double yy=c*y-s*z;
    double zz=s*y+c*z;
    return Vector3D(xx,yy,zz);
  }
  Vector3D rotateY(double rad) {
    double s=sin(rad),c=cos(rad);
    double xx=c*x+s*z;
    double yy=y;
    double zz=-s*x+c*z;
    return Vector3D(xx,yy,zz);
  }
  Vector3D rotateZ(double rad) {
    double s=sin(rad),c=cos(rad);
    double xx=c*x-s*y;
    double yy=s*x+c*y;
    double zz=z;
    return Vector3D(xx,yy,zz);
  }
};

// x'=x, y'=y*cos𝛩-z*sin𝛩, z'=y*sin𝛩+z*cos𝛩
vector<double> rotateX(vector<double> V, double rad) {
  double s=sin(rad),c=cos(rad);
  vector<double> res(3);
  res[0]=V[0];
  res[1]=c*V[1]-s*V[2];
  res[2]=s*V[1]+c*V[2];
  return res;
}
// x'=x*cos𝛩+z*sin𝛩, y'=y, z'=x*sin𝛩+z*cos𝛩
vector<double> rotateY(vector<double> V, double rad) {
  double s=sin(rad),c=cos(rad);
  vector<double> res(3);
  res[0]=c*V[0]+s*V[2];
  res[1]=V[1];
  res[2]=-s*V[0]+c*V[2];
  return res;
}
// x'=x*cos𝛩-y*sin𝛩, y'=x*sin𝛩+y*cos𝛩, z'=z
vector<double> rotateZ(vector<double> V, double rad) {
  double s=sin(rad),c=cos(rad);
  vector<double> res(3);
  res[0]=c*V[0]-s*V[1];
  res[1]=s*V[0]+c*V[1];
  res[2]=V[2];
  return res;
}
vector<double> rotateDegX(vector<double> V, double deg) {
  return rotateX(V,deg2rad(deg));
}
vector<double> rotateDegY(vector<double> V, double deg) {
  return rotateY(V,deg2rad(deg));
}
vector<double> rotateDegZ(vector<double> V, double deg) {
  return rotateZ(V,deg2rad(deg));
}

/************************ test ************************/

bool nearlyEqual(double x, double y) {
  const double EPS=1e-9;
  return abs(x-y)<EPS;
}

void assert_vector3D() {
  auto v1 = Vector3D(1,2,3).rotateX(M_PI/2.0);
  assert(nearlyEqual(v1.x,1)&&nearlyEqual(v1.y,-3)&&nearlyEqual(v1.z,2));
  auto v2 = Vector3D(1,2,3).rotateY(M_PI/2.0);
//  printf("%f,%f,%f\n",v2.x,v2.y,v2.z);
  assert(nearlyEqual(v2.x,3)&&nearlyEqual(v2.y,2)&&nearlyEqual(v2.z,-1));
  auto v3 = Vector3D(1,2,3).rotateZ(M_PI/2.0);
  assert(nearlyEqual(v3.x,-2)&&nearlyEqual(v3.y,1)&&nearlyEqual(v3.z,3));
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
  
  vector<pair<int,int>> surrounding = {{1,1},{-1,1},{1,-1},{-1,-1}};
  assert(surrounded(origin, surrounding));
  vector<pair<int,int>> onsegment = {{1,0},{0,1},{-1,0}};
  assert(surrounded(origin, onsegment));
  vector<pair<int,int>> notsurrounding = {{1,1},{2,1},{1,2},{2,2}};
  assert(!surrounded(origin, notsurrounding));
  
  assert(nearlyEqual(deg2rad(60),M_PI/3.0));
  pair<double,double> pp1=polar2cartesianSys(10,60);
  assert(nearlyEqual(pp1.first,10.0/2.0));
  assert(nearlyEqual(pp1.second,10.0*sqrt(3.0)/2.0));
  
  pair<double,double> pp2=rotate(pp1,60);
  assert(nearlyEqual(pp2.first+pp1.first,0.0));
  assert(nearlyEqual(pp2.second,pp1.second));
  assert(nearlyEqual(area({-2,0},{0,4},{3,0}),10.0));
  
  assert_vector3D();
  
  assert(insideCircle(-4,5,1,1,1,8));
  assert(!insideCircle(-4,5,1,12,1,2));
  assert(insideCircle(0,0,1,0,0,1));
}
