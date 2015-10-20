//
//  Vec2.h
//  Wtf
//
//  Created by CT on 10/20/15.
//  Copyright © 2015 陈 玉涛. All rights reserved.
//

#ifndef Vec2_h
#define Vec2_h

#include <iostream>
#include <vector>

using namespace std;

class Vec2
{
private:
public:
    int x,y;
    Vec2(){};
    Vec2(int x,int y):x(x),y(y){}
    ~Vec2(){}
    void toString() const
    {
        cout<<"Point(x:"<<x<<", y:"<<y<<")"<<endl;
    }
};

using Points = std::vector<Vec2>;

#endif /* Vec2_h */
