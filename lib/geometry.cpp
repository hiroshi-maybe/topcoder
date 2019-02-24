#include <iostream>
#include <vector>
#include <utility>
#include <cassert>
#include <cmath>

using namespace std;

const double PI = acos(-1);

struct Point {
public:
  int x, y;
  Point(): x(0), y(0) {}
  Point(int x, int y): x(x), y(y) {}
  Point(pair<int,int> p): x(p.first), y(p.second) {}
  Point(pair<int,int> p, pair<int,int> org): Point(p.first-org.first, p.second-org.second) {}
  Point(Point p, Point org): Point(p.x-org.x, p.y-org.y) {}
  
  explicit operator bool() const { return x!=0||y!=0; }
  Point operator-() const { return Point(0,0)-*this; }
  Point &operator+=(Point that) { x+=that.x,y+=that.y; return *this; }
  Point &operator-=(Point that) { x-=that.x,y-=that.y; return *this; }
  Point operator+(Point that) const { return Point(*this)+=that; }
  Point operator-(Point that) const { return Point(*this)-=that; }
  bool operator==(Point that) const { return x==that.x&&y==that.y; }
  bool operator!=(Point that) const { return !(Point(*this)==that); }
  bool operator<(Point that) const { return pair<int,int>(x,y)<pair<int,int>(that.x,that.y); }
  bool operator>(Point that) const { return pair<int,int>(x,y)>pair<int,int>(that.x,that.y); }
  bool operator<=(Point that) const { return Point(*this)==that||Point(*this)<that; }
  bool operator>=(Point that) const { return Point(*this)==that||Point(*this)>that; }
  friend std::ostream& operator<<(std::ostream& _os, const Point& _p) { return _os<<"{"<<_p.x<<','<<_p.y<<"}"; }
  // sqrt(distance()) is definition
  long long distance() {
    return x*x + y*y;
  }
};
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
long long det(Point u, Point v) {
  return (long long)u.x*v.y - (long long)u.y*v.x;
}
/*
 
 cross product det (o->p1, o->p2)
 
 1) det(o,p1,p2) = 0
  o, p1 and p2 are co-linear (o->p1 is colinear with o->p2)
 2) det(o,p1,p2) > 0
  o->p2 is counter-clockwise from o->p1
  (p1->p2->o is counter-clockwise order)
 3) det(o,p1,p2) < 0
  o->p2 is clockwise from o->p1
  (p1->p2->o is clockwise order)
 
 */
long long det(Point origin, Point p1, Point p2) {
  return det(p1-origin, p2-origin);
}
long long dot(Point u, Point v) {
  return (long long)u.x*v.x + (long long)u.y*v.y;
}
// CLRS 33.1
// true: org->p2 is clockwise from org->p1
bool isClockwise(Point origin, Point p1, Point p2) {
  return det(origin, p1, p2)<0;
}
bool isCounterClockwise(Point origin, Point p1, Point p2) {
  return det(origin, p1, p2)>0;
}
// CLRS 33.1
// org->p1 and org->p2 form same direction or opposite direction
bool isColinear(Point origin, Point p1, Point p2) {
  return det(origin, p1, p2)==0;
}
// CLRS 33.1
// true: p1->p2 is left turn for origin
bool isLeftTurn(Point origin, Point p1, Point p2) {
  return isCounterClockwise(origin,p1,p2);
}
// CLRS 33.1
// true: p1->p2 is right turn for origin
bool isRightTurn(Point origin, Point p1, Point p2) {
  return isClockwise(origin,p1,p2);
}
// 90 degree
bool isVertical(Point u, Point v) {
  return dot(u,v)==0;
}
// CLRS 33.1 ON-SEGMENT(pi,pj,pk)
bool onSegment(Point p1, Point p2, Point q) {
  int xmin=min(p1.x, p2.x),
  xmax=max(p1.x, p2.x),
  ymin=min(p1.y, p2.y),
  ymax=max(p1.y, p2.y);
  return xmin<=q.x&&q.x<=xmax&&ymin<=q.y&&q.y<=ymax;
}
// CLRS 33.1 SEGMENTS-INTERSECT(p1,p2,p3,p4)
// p1->p2 intersects p3->p4
bool intersect(Point p1, Point p2, Point p3, Point p4) {
  long long d1 = det(p1,p3,p4),
  d2 = det(p2,p3,p4),
  d3 = det(p3,p1,p2),
  d4 = det(p4,p1,p2);
  
  if (((d1>0&&d2<0)||(d1<0&&d2>0)) && ((d3>0&&d4<0)||(d3<0&&d4>0))) return true;
  if (d1==0 && onSegment(p3,p4,p1)) return true;
  if (d2==0 && onSegment(p3,p4,p2)) return true;
  if (d3==0 && onSegment(p1,p2,p3)) return true;
  if (d4==0 && onSegment(p1,p2,p4)) return true;
  return false;
}

void test_point() {
  {
    Point p;
    assert(p.x==0&&p.y==0);
  }
  {
    Point p1(0,0),p2(0,1);
    assert(!p1);
    assert(p2);
  }
  {
    Point p1(1,2),p2(3,4);
    p1+=p2;
    assert(p1.x==4&&p1.y==6);
  }
  {
    Point p1(1,2),p2(3,4);
    p1-=p2;
    assert(p1.x==-2&&p1.y==-2);
  }
  {
    Point p1(1,1),p2(1,1),p3(1,2);
    assert(p1==p2);
    assert(p1!=p3);
  }
  
  Point origin(0,0), p1(1,0), p2(0,1), p3(-1,0), p4(0,-1);
  
  assert(isVertical(Point(p1,origin),Point(p2,origin)));
  assert(isClockwise(origin, p2, p1));
  assert(isCounterClockwise(origin, p1, p2));
  assert(isColinear(origin, p1, p3));
  assert(isLeftTurn(origin, p1, p2));
  assert(isRightTurn(origin, p2, p1));
  assert(intersect(p1, p4, p2, p4));
}

/*
 
 Compute area of parallelogram formed by p1, p2 and origin
 
 A = det(o,p1,p2)
 
 0.5*area() is an area of (o,p1,p2) triangle
 
 */
long long area(Point p1, Point p2, Point origin) {
  return abs(det(origin,p1,p2));
}

// CLRS 33.3 GRAHAM-SCAN(Q)

// sort points by plar angle
// smaller scalar comes first for tie
void sortByPolarAngle(vector<Point>& ps, Point origin) {
  sort(ps.begin(), ps.end(), [&](const Point &a, const Point &b) {
    int d = det(origin,a,b);
    if(d!=0) return d > 0;
    return Point(a,origin).distance() < Point(b,origin).distance();
  });
}
vector<Point> findConvexHull(vector<Point> ps) {
  if (ps.size()<3) return {};

  // find p0 (bottom left point)
  int p0_i = 0;
  for(int i=1; i<ps.size(); ++i) {
    if (ps[i].y <= ps[p0_i].y && ps[i].x <= ps[p0_i].x) p0_i = i;
  }
  swap(ps[0], ps[p0_i]);
  Point p0=ps[0];

  // sort by polar angle
  sortByPolarAngle(ps, p0);

  // remove all but furthest point if points have same angle
  int N=1;
  for (int i=1; i<ps.size(); ++i) {
    while(i<ps.size()-1&&isColinear(p0, ps[i],ps[i+1])) ++i;
    ps[N++] = ps[i];
  }

  if (N<3) return {};

  int si=0;
  vector<Point> S(N);
  S[si++] = ps[0];
  S[si++] = ps[1];
  S[si] = ps[2];

  for(int i=3; i<N; ++i) {
    while(!isLeftTurn(S[si-1],S[si],ps[i])) --si;
    S[++si] = ps[i];
  }
  S.erase(S.begin()+si+1, S.end());
  return S;
}

// check if point is surrounded by given points
// if p is on segment, return true
// O(N*lg N) time
bool surrounded(Point p, vector<Point>& ps) {
  sortByPolarAngle(ps, p);
  vector<int> ds;
  int N=ps.size();
  for(int i=0; i<N; ++i) {
    int d = det(p, ps[i], ps[(i+1)%N]);
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
struct Point3D {
public:
  double x, y, z;
  Point3D(vector<double> vec) {
    assert(vec.size()==3);
    this->x=vec[0],this->y=vec[1],this->z=vec[2];
  }
  Point3D(double x, double y, double z): x(x), y(y), z(z) {}
  
  Point3D rotateX(double rad) {
    double s=sin(rad),c=cos(rad);
    double xx=x;
    double yy=c*y-s*z;
    double zz=s*y+c*z;
    return Point3D(xx,yy,zz);
  }
  Point3D rotateY(double rad) {
    double s=sin(rad),c=cos(rad);
    double xx=c*x+s*z;
    double yy=y;
    double zz=-s*x+c*z;
    return Point3D(xx,yy,zz);
  }
  Point3D rotateZ(double rad) {
    double s=sin(rad),c=cos(rad);
    double xx=c*x-s*y;
    double yy=s*x+c*y;
    double zz=z;
    return Point3D(xx,yy,zz);
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
  auto v1 = Point3D(1,2,3).rotateX(M_PI/2.0);
  assert(nearlyEqual(v1.x,1)&&nearlyEqual(v1.y,-3)&&nearlyEqual(v1.z,2));
  auto v2 = Point3D(1,2,3).rotateY(M_PI/2.0);
//  printf("%f,%f,%f\n",v2.x,v2.y,v2.z);
  assert(nearlyEqual(v2.x,3)&&nearlyEqual(v2.y,2)&&nearlyEqual(v2.z,-1));
  auto v3 = Point3D(1,2,3).rotateZ(M_PI/2.0);
  assert(nearlyEqual(v3.x,-2)&&nearlyEqual(v3.y,1)&&nearlyEqual(v3.z,3));
}

int main(int argc, char const *argv[]) {
  test_point();

  // http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
  vector<Point> ps = findConvexHull({{0,3},{1,1},{2,2},{4,4},{0,0},{1,2},{3,1},{3,3}});
  vector<Point> exp = {{0,0},{3,1},{4,4},{0,3}};
  assert(ps==exp);
//  assert(ps.size()==exp.size());
//  for(int i=0; i<ps.size(); ++i) {
//    assert(ps[i].first==exp[i].first&&ps[i].second==exp[i].second);
//  }
  
  Point origin(0,0);
  
  vector<Point> surrounding = {{1,1},{-1,1},{1,-1},{-1,-1}};
  assert(surrounded(origin, surrounding));
  vector<Point> onsegment = {{1,0},{0,1},{-1,0}};
  assert(surrounded(origin, onsegment));
  vector<Point> notsurrounding = {{1,1},{2,1},{1,2},{2,2}};
  assert(!surrounded(origin, notsurrounding));
  
  assert(nearlyEqual(deg2rad(60),M_PI/3.0));
  pair<double,double> pp1=polar2cartesianSys(10,60);
  assert(nearlyEqual(pp1.first,10.0/2.0));
  assert(nearlyEqual(pp1.second,10.0*sqrt(3.0)/2.0));
  
  pair<double,double> pp2=rotate(pp1,60);
  assert(nearlyEqual(pp2.first+pp1.first,0.0));
  assert(nearlyEqual(pp2.second,pp1.second));
  assert(nearlyEqual(area({-2,0},{0,4},{3,0}),20.0));
  
  assert_vector3D();
  
  assert(insideCircle(-4,5,1,1,1,8));
  assert(!insideCircle(-4,5,1,12,1,2));
  assert(insideCircle(0,0,1,0,0,1));
}

// g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address geometry.cpp && ./a.out
