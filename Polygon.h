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
    //~Vec();
    double polar_coord_for_dot(Vec &dot, Vec &lv);
};


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
    //~Polygon();
    Vec left_vertex(Polygon &p);
    std::vector<double> polar_coord(std::vector<Vec> &p, Vec &lv);
    int ceilSearch(std::vector<double> arr, int low, int high, double x);
    bool Algorithm(Polygon &p, std::vector<Vec> &dots);
};


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
    // delete the lv from vector:
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
        //std::cout << p[i].x << ", " << p[i].y << " polar: " << coord[i] << std::endl;
    }
    return coord;
}


double Vec::polar_coord_for_dot(Vec &dot, Vec &lv) {
    Vec pd;
    double res;
    pd.x = dot.x - lv.x;
    pd.y = dot.y - lv.y;
    res = atan2(pd.y, pd.x);
    return res;
}


int check(Vec &a, Vec &b, Vec &c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}


bool Polygon::Algorithm(Polygon &p, std::vector<Vec> &dots) {
    //std::cout << p.n_vertex << " " << p.vertex.size() << std::endl;
    Vec lv = p.left_vertex(p);
    //std::cout << p.n_vertex << " " << p.vertex.size() << std::endl;
    std::vector<double> pc = polar_coord(p.vertex, lv);
    //std::cout << pc.size() << std::endl;
    //std::cout << "dots polar vector: " << std::endl;
    std::vector<double> pd = polar_coord(dots, lv);
    for (int d = 0; d < pd.size(); ++d) {
        //std::cout << "in for " << std::endl;
        //std::cout << pd[d] << " " << dots[d] << std::endl;
        int pos = ceilSearch(pc, 0, pc.size(), pd[d]);
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
            if (pos_ != p.n_vertex) {
                //std::cout << p.vertex[pos] <<" " <<p.vertex[pos_] <<" " << dots[d] << std::endl;
                if (check(p.vertex[pos], p.vertex[pos_], dots[d]) >= 0) {
                    //std::cout << p.vertex[pos-1] <<" " <<p.vertex[pos_-1] <<" " << dots[d] << std::endl;
                    //std::cout << p.vertex[pos] <<" " <<p.vertex[pos_] <<" " << dots[d] << std::endl;
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


int Polygon::ceilSearch(std::vector<double> arr, int low, int high, double x) {

    if (x < arr[low]) {
        return -1;
    }
    int mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (arr[mid] == x)
            return mid;
        else if (x < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    /*
    std::cout << "---------" << std::endl;
    std::cout << x << std::endl;
    std::cout <<"-1 " << arr[low-1] << std::endl;
    std::cout << "0 " <<arr[low] << std::endl;
    std::cout << arr[low+1] << std::endl;
    std::cout << "+2 " << arr[low+2] << std::endl;
    std::cout << " LOW IS: " << low << " " << high << std::endl;
     */
    return low;
}


#endif //CHECKPOINTS_POLYGON_H
