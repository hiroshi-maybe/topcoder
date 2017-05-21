struct Vector {
public:
    int x, y;
    Vector(pair<int,int> p1, pair<int,int> p2): Vector(p1.first-p2.first, p1.second-p2.second) {}
    Vector(int x, int y): x(x), y(y) {}
    
    int length() {
        return x*x + y*y;
    }
};

int crossProduct(Vector u, Vector v) {
    return u.x*v.y - u.y*v.x;
}
int dotProduct(Vector u, Vector v) {
    return u.x*v.x + u.y*v.y;
}
bool is90Degree(Vector u, Vector v) {
    return dotProduct(u,v)==0;
}

pair<int,int> makePair(vector<int> v) {
    assert(v.size()==2);
    return {v[0],v[1]};
} 
