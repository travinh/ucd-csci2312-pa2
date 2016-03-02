//
// Created by Vinh Van Tran on 2/22/16.
//
/*
#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H

#include <iostream>

namespace Clustering {

    class Point {
        unsigned int __id;
        int __dim;        // number of dimensions of the point
        double *__values; // values of the point's dimensions

        static unsigned int __idGen; // id generator

    public:
        Point(int);
        Point(int, double *);

        // Big three: cpy ctor, overloaded operator=, dtor
        Point(const Point &);
        Point &operator=(const Point &);
        ~Point();

        // Accessors & mutators
        int getId() const;
        int getDims() const;
        void setValue(int, double);
        double getValue(int) const;

        // Functions
        double distanceTo(const Point &) const;

        // Overloaded operators

        // Members
        Point &operator*=(double); // p *= 6; p.operator*=(6);
        Point &operator/=(double);
        const Point operator*(double) const; // prevent (p1 * 2) = p2;
        const Point operator/(double) const; // p3 = p2 / 2;

        double &operator[](int index);

        // Friends
        friend Point &operator+=(Point &, const Point &);
        friend Point &operator-=(Point &, const Point &);
        friend const Point operator+(const Point &, const Point &);
        friend const Point operator-(const Point &, const Point &);

        friend bool operator==(const Point &, const Point &);
        friend bool operator!=(const Point &, const Point &);

        friend bool operator<(const Point &, const Point &);
        friend bool operator>(const Point &, const Point &);
        friend bool operator<=(const Point &, const Point &);
        friend bool operator>=(const Point &, const Point &);

        friend std::ostream &operator<<(std::ostream &, const Point &);
        friend std::istream &operator>>(std::istream &, Point &);
    };

}
#endif //CLUSTERING_POINT_H


*/
#include "Point.h"
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

namespace Clustering {

    unsigned int Clustering::Point::__idGen = 0;

    Point::Point(int x)       //x is dimenssion of a point
    {
        __id = __idGen++;
        __dim = x;
        __values = new double[__dim];

        for (int i = 0; i < __dim; ++i)
            __values[i] = 0;
    }

    Point::Point(int x, double *values) {
        __id = __idGen++;
        __dim = x;
        __values = new double[__dim];
        for (int i = 0; i < __dim; ++i)
            __values[i] = 0;
    }

//Copy Constructor
    Point::Point(const Point &p) {
        __id = p.getId();
        __dim = p.getDims();
        __values = new double[__dim];

        for (int i = 0; i < __dim; i++) {
            __values[i] = p.getValue(i);
        }
    }

//Overloading operator =
    Point& Point::operator=(const Point &p) {
        if (this != &p) {
            __dim = p.getDims();
            __id = p.getId();

            //delete array if it's already have
            if (__values != NULL)
                delete[] __values;

            //create new value for this point then pass value from p to this point
            __values = new double[__dim];
            for (int i = 0; i < __dim; i++) {
                __values[i] = p.getValue(i);
            }
        }
        return *this;

    }

//destrutor
    Point::~Point() {
        delete[] __values;
    }

//---------------------------------------------------------

    int Point::getId() const {
        return __id;
    }

    int Point::getDims() const {
        return __dim;
    }

    void Point::setValue(int i, double val) {
        __values[i] = val;
    }

    double Point::getValue(int i) const {
        return __values[i];
    }

//Function distance between two points
    double Point::distanceTo(const Point &p) const {
        //condition: this.dim = p.dim, if not return 0
        if (__dim != p.getDims()) {
            return 0;
        }

        double sum = 0;

        for (int i = 0; i < __dim; i++) {
            sum += pow(this->getValue(i) - p.getValue(i), 2);
        }

        return sqrt(sum);
    }

//Overloading operator
    Point &Point::operator*=(double y) {
        for (int i = 0; i < __dim; i++) {
            __values[i] *= y;
        }

        return *this;
    }

     Point& Point::operator/=(double y) {
        for (int i = 0; i < __dim; i++) {
            __values[i] /= y;
        }

        return *this;
    }


    const Point Point::operator*(double y) const {
        Point p1(*this);

        p1 *= y;

        return p1;

    }

    const Point Point::operator/(double y) const {
        Point p1(*this);

        p1 /= y;

        return p1;

    }

    double &Point::operator[](int index) {
        return __values[index];
    }

    Point &operator+=(Point &lhs, const Point &rhs) {

        if (lhs.getDims() == rhs.getDims()) {
            for (int i = 0; i < lhs.getDims(); i++)
                lhs.__values[i] += rhs.getValue(i);
        }
        return lhs;
    }

   Point &operator-=(Point &lhs, const Point &rhs) {

        if (lhs.getDims() == rhs.getDims()) {
            for (int i = 0; i < lhs.getDims(); i++)
                lhs.__values[i] -= rhs.getValue(i);
        }
        return lhs;
    }

    const Point operator+(const Point &p1, const Point &p2) {
        Point p(p1);

        p += p2;

        return p;

    }

    const Point operator-(const Point &p1, const Point &p2) {
        Point p(p1);

        p -= p2;

        return p;

    }

    bool operator==(const Point &p1, const Point &p2) {
        if (p1.getId() != p2.getId())
            return false;
        else {
            for (int i = 0; i < p1.getDims(); i++) {
                if (p1.getValue(i) != p2.getValue(i))
                    return false;
            }
            return true;
        }
    }

    bool operator!=(const Point &p1, const Point &p2) {
        return !(p1 == p2);
    }
    /*
    bool operator<(const Point &p1, const Point &p2) {
        if (p1 == p2)
            return false;
        else
            for (int i = 0; i < p1.getDims(); i++) {
                if (p1.getValue(i) - p2.getValue(i) > 0)
                    return false;

        }
        return true;
    }
    */
     bool operator<(const Point &lhs, const Point &rhs)
    {
        bool less = false;
        for (int count = 0; count < lhs.__dim; count++)
        {
            if (lhs.__values[count] < rhs.__values[count])
                return true;
            if(lhs.__values[count] > rhs.__values[count])
                return false;
        }
        return less;
    }

    bool operator>(const Point &p1, const Point &p2) {
        if (p2<p1)
            return true;
        return false;
        //return !(p1 <= p2);
    }


    bool operator<=(const Point &p1, const Point &p2) {
        bool answer;
        answer= (p1>p2);

        return !answer;
    }

    bool operator>=(const Point &p1, const Point &p2) {
        bool answer;
        answer = p1 < p2;

        return (!answer);
    }
    
    ostream &operator<<(ostream &os, const Point &p1) {
        int i;
        for (i = 0; i < p1.__dim-1; i++) {
            os << p1.__values[i] <<", ";
            //if (i != (p1.getDims() - 1))
             //  cout << ", ";
        }
            os<< p1.__values[i];
        
        return os;
    }

    istream &operator>>(istream &is, Point &p)
    {
        string str1;
        double value;
        for(int i =0; i < p.__dim; i++)
        {
            getline(is, str1, ',');
            std::stringstream inputstring(str1);
            inputstring>>value;
            p.__values[i] = value;
        }
        return is;
    }
     
   
}