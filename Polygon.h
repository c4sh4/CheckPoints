#ifndef CHECKPOINTS_POLYGON_H
#define CHECKPOINTS_POLYGON_H

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>


struct Vec {
    double x, y;
    Vec();
    Vec(double x, double y);
    ~Vec();
};


Vec::~Vec(){}


std::ostream &operator<<(std::ostream &s, Vec &vec) {
    s << vec.x << ", " << vec.y;
    return s;
}


bool operator>(const Vec &v1, const Vec &v2) {
    if (v1.x > v2.x) {
        return true;
    } else return false;
}


class Polygon {
public:
    int n_vertex;
    std::vector<Vec> vertex;
    Polygon();
    Polygon(int n, std::vector<Vec> vertexes);
    ~Polygon();
    Vec left_vertex(Polygon &p);
    std::vector<double> polar_coord(std::vector<Vec> &p, Vec &lv);
    bool Algorithm(Polygon &p, std::vector<Vec> &dots);
    double polar_coord_for_dot(Vec &dot, Vec &lv);

    int ceilSearch(Polygon &arr, int low, int high, Vec &x, Vec &l);
};

Polygon::~Polygon() { }

Vec::Vec() : x(), y() {}


Vec::Vec(double x, double y) : x(x), y(y) {}


Polygon::Polygon() : n_vertex(), vertex() {}


Polygon::Polygon(int n, std::vector<Vec> vertexes) : n_vertex(n), vertex(std::move(vertexes)) {}


Vec Polygon::left_vertex(Polygon &p) {
    int n = p.n_vertex;
    Vec lv = p.vertex[0];
    int i_id = 0;
    for (int i = 0; i < n; ++i) {
        if (p.vertex[i].x < lv.x) {
            lv = p.vertex[i];
            i_id = i;
        } else if (p.vertex[i].x == lv.x && p.vertex[i].y < lv.y) {
            lv = p.vertex[i];
            i_id = i;
        }
    }
    rotate(p.vertex.begin(), p.vertex.begin() + i_id, p.vertex.end());
    p.vertex.erase(p.vertex.begin());
    p.n_vertex -= 1;
    return lv;
}


std::vector<double> Polygon::polar_coord(std::vector<Vec> &p, Vec &lv) {
    std::vector<double> coord(p.size()); //vector of polar coordinates of vertexes
    std::vector<Vec> a_b(p);
    for (int i = 0; i < p.size(); ++i) {
        a_b[i].x = p[i].x - lv.x;
        a_b[i].y = p[i].y - lv.y;
        coord[i] = atan2(a_b[i].y, a_b[i].x);
    }
    return coord;
}


double Polygon::polar_coord_for_dot(Vec &dot, Vec &lv) {
    double pd;
    Vec td(dot.x - lv.x, dot.y - lv.y);
    pd = atan2(td.y, td.x);
    return pd;
}



double check(Vec &a, Vec &b, Vec &c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}


bool Polygon::Algorithm(Polygon &p, std::vector<Vec> &dots) {
    Vec lv = p.left_vertex(p); // N
    for (int d = 0; d < dots.size(); ++d) {
        int pos = ceilSearch(p, 0, p.vertex.size(), dots[d], lv);
        if (pos == -1) {
            //std::cout << p.vertex[pos] <<" " <<p.vertex[pos+1] <<" " << dots[d] << std::endl;
            //std::cout << pc[pos] << " ! " << pc[pos+1] << " " << pc[d] << std::endl;
            std::cout << "(" << dots[d] <<") " << "out" << std::endl;
        } else {
            int pos_ = pos;
            pos -= 1;
            //std::cout << n_vertex << std::endl;
            //std::cout << p.vertex[n_vertex] << std::endl;
            //std::cout << "pos is: " << pos << std::endl;
            //std::cout << "pos_ is: " << pos_ << std::endl;
            //std::cout << p.vertex[pos] << " ; " << p.vertex[pos_] << std::endl;
            //std::cout << pc[pos] << " ; " << pc[pos_] << "; " << pd[d] << std::endl;
            //std::cout << pos << " " << pos_ << std::endl;
            if (pos_ < p.n_vertex) {
                //std::cout << p.vertex[pos] <<" " <<p.vertex[pos_] <<" " << dots[d] << std::endl;
                if (check(p.vertex[pos], p.vertex[pos_], dots[d]) >= 0) {
                    //std::cout << p.vertex[pos-1] <<" " <<p.vertex[pos_-1] <<" " << dots[d] << std::endl;
                    //std::cout << p.vertex[pos] <<" " <<p.vertex[pos_] <<" " << dots[d] << std::endl;
                    //std::cout << pos << " ! " <<pos_ << " " << pc[d] << std::endl;
                    //std::cout << pc[pos] << " ! " << pc[pos_] << " " << pc[d] << std::endl;
                    std::cout << "(" << dots[d] << ") " << "in" << std::endl;
                } else {
                    //std::cout << p.vertex[pos] <<" " <<p.vertex[pos_] <<" " << dots[d] << std::endl;
                    //std::cout << pc[pos] << " ! " << pc[pos_] << " " << pc[d] << std::endl;
                    std::cout << "(" << dots[d] << ") " << "out" << std::endl;
                }
        } else {
                //std::cout << "priv" << std::endl;
                if (check(p.vertex[pos], lv, dots[d]) >= 0) {
                    std::cout << "(" << dots[d] << ") " << "in" << std::endl;
                } else {
                    std::cout << "(" << dots[d] << ") " << "out" << std::endl;
                }
            }
        }
    }
}


int Polygon::ceilSearch(Polygon& arr, int low, int high, Vec& x, Vec& l) {

    //std::cout << "x " << x << std::endl;
    //std::cout << "arr[0] " << arr[low] << std::endl;
    double px = polar_coord_for_dot(x, l);
    //std::cout << px << std::endl;

    if (px < polar_coord_for_dot(arr.vertex[low], l)) {
        //std::cout << "=)" <<std::endl;
        return -1;
    }
    int mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (polar_coord_for_dot(arr.vertex[mid], l) == px)
            return mid;
        else if (px < polar_coord_for_dot(arr.vertex[mid], l)) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    //std::cout << "low is: " << low << std::endl;
    //std::cout << "mid is: " << mid << std::endl;
    //std::cout << "high is: " << high << std::endl;
    return low;
}


#endif //CHECKPOINTS_POLYGON_H
