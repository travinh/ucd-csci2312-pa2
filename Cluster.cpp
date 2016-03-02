//Vinh Tran

#include <string>
#include <sstream>
#include <algorithm>
#include "Cluster.h"
#include <iostream>
#include "Point.h"

using namespace std;
using namespace Clustering;
namespace Clustering {

    LNode::LNode(const Point & newPoint, LNodePtr next_Ptr):point(newPoint)
    {
        point=newPoint;
        next=next_Ptr;
    }

    Clustering::Cluster::Cluster()
    {
        __size = 0;
        __points = NULL;
    }


    int Clustering::Cluster::getSize() const
    {
        return __size;
    }

    Clustering::Cluster::Cluster(const Cluster & clus1) :Cluster()
    {
        for (int i = 0; i < clus1.__size; i++)
            add(clus1[i]);
    }


    Cluster &Clustering::Cluster::operator=(const Cluster &clus1)
    {
        LNodePtr temp;

        if(this==&clus1)
            return *this;
        else
        {
            while (__points != nullptr) {
                temp = __points;
                __points = __points->next;
                delete temp;
                __size--;
            }

            for (int i = 0; i < clus1.__size; i++)
                add(clus1[i]);
        }

        return *this;
    }

    const Point &Cluster::operator[](unsigned int index) const
    {
        LNodePtr temp=__points;
        for(int i =0; (i < index) && (temp->next != nullptr); i++)
            temp=temp->next;
        return temp->point;
    }

    Clustering::Cluster::~Cluster()
    {
        if(__points!=nullptr)
        {
            LNodePtr p=__points;
            LNodePtr temp=nullptr;
            while (p != nullptr)
            {
                temp = p->next;
                delete p;
                p = temp;
            }
        }
    }

    void Clustering::Cluster::add(const Point &point)
    {
        LNodePtr insertPtr=new LNode(point, nullptr);
        LNodePtr curr=__points;
        LNodePtr prev=__points;

        if(__points==nullptr)
        {
            __points = insertPtr;
            __size++;
            return;
        }
        else if(__points->next==nullptr)
        {
            if(point<__points->point)
            {
                __points=insertPtr;
                insertPtr->next=prev;
                __size++;
                return;
            }
            else
            {
                __points->next=insertPtr;
                __size++;
                return;
            }
        }
        else
        {
            
            if(point < prev->point)
            {
                __points = insertPtr;
                insertPtr->next=prev;
                __size++;
                return;
            }
            curr=curr->next;
            while(curr!=nullptr)
            {
                if(point < curr->point)
                {
                    prev->next=insertPtr;
                    insertPtr->next=curr;
                    __size++;
                    return;
                }
                curr = curr->next;
                prev = prev->next;
            }
            prev->next=insertPtr;
            __size++;

        }
    }

    const Point &Clustering::Cluster::remove(const Point &p)
    {

        LNodePtr cursor=__points;
        LNodePtr temp=__points;

        if(__points==nullptr)
            return p;
        else if(__points->point == p)
        {
            
            __points=__points->next;
            delete cursor;
            __size--;
        }
        else
        {
            cursor=cursor->next;
            while (cursor!= nullptr)
            {
                if (cursor->point == p) {
                    temp->next=cursor->next;
                    delete cursor;
                    __size--;
                    break;
                }
                cursor = cursor->next;
                temp = temp->next;
            }
        }
        return p;
    }

    bool Clustering::Cluster::contains(const Point &p)
    {
        for (LNodePtr cursor = this->__points; cursor != nullptr; cursor = cursor->next)
        {
            if (cursor->point == p){
                return true;
            }
        }
        return false;
    }

    bool operator==(const Cluster &clus1, const Cluster &clus2)
    {
        LNodePtr node1= clus1.__points;
        LNodePtr node2=clus2.__points;
        bool answer=true;
        if (clus1.__size != clus2.__size)
            answer=false;
        while(node1!=nullptr && node2!=nullptr)
        {
            if(node1->point!=node2->point)
                answer=false;
            node1=node1->next;
            node2=node2->next;
        }
        return answer;
    }

    bool operator!=(const Cluster &clus1, const Cluster &clus2)
    {
        return (!(clus1==clus2));
    }

    Cluster &Clustering::Cluster::operator+=(const Point &p)
    {
        add(p);
        return *this;
    }

    Cluster &Clustering::Cluster::operator-=(const Point &p)
    {
        remove(p);
        return *this;
    }

    const Cluster operator+(const Cluster & clus1, const Point &p)
    {
        Cluster clus2(clus1);
        clus2+= p;

        return clus2;
    }

    const Cluster operator-(const Cluster & clus1, const Point &p)
    {
        Cluster clus2(clus1);
        clus2-= p;
        return clus2;
    }

    Cluster &Clustering::Cluster::operator+=(const Cluster & clus1)
    {

        for (int i = 0; i < clus1.__size; i++)
        {
            if (!contains(clus1[i]))
                add(clus1[i]);
        }

        return *this;
    }

    Cluster &Clustering::Cluster::operator-=(const Cluster &clus1)
    {
        for (int i = 0; i < clus1.__size; i++)
            if (contains(clus1[i]))
                remove(clus1[i]);
        return *this;
    }
    const Cluster operator+(const Cluster &clus1, const Cluster &clus2)
    {
        Cluster temp(clus1);
        temp+=clus2;
        return temp;
    }
    const Cluster operator-(const Cluster &clus1, const Cluster &clus2)
    {
        Cluster temp(clus1);
        temp-=clus2;
        return temp;
    }
   
 
    //fstream for cluster


    ostream &operator<<(ostream &os, const Cluster &clus1) {
        
        for (int i = 0; i < clus1.getSize(); ++i) {
            os << clus1.__points->point  << endl;
            
        }
        
        return os;
    }
    istream &operator>>(istream &in, Cluster &cluster) {
        while (!in.eof()) {
            Point p(1);
            
            string str;
            getline(in, str);
            
            if (str.length() > 0) {
                stringstream ss(str);
                
                ss >> p;
                
                cluster.add(p);
            }
        }
        
        
        return in;
    }


}
