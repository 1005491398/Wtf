//
//  main.cpp
//  Wtf
//
//  Created by 陈 玉涛 on 6/26/15.
//  Copyright (c) 2015 陈 玉涛. All rights reserved.
//

#include <iostream>
#include <vector>
#include <Map>
#include <list>
#include <time.h>
#include <cstdio>
#define CCLOG(format, ...)      printf(format, ##__VA_ARGS__)

using namespace std;

const int xCount = 9;
const int yCount = 9;
void printMap(int Map[xCount][yCount]);

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

std::vector<Vec2> points;

int Map[xCount][yCount] = {
    {0,0,5,5,5,5,5,0,0},
    {4,0,5,5,6,5,6,0,3},
    {3,2,5,5,5,5,5,2,1},
    {3,2,4,5,4,5,1,2,2},
    {2,3,4,5,3,4,1,4,5},
    {3,6,4,1,4,5,6,3,6},
    {6,6,3,5,3,4,1,6,3},
    {6,0,3,2,1,6,4,0,6},
    {0,0,2,6,4,4,5,0,0},
};
int hMap[xCount][yCount];

void printMap(int Map[xCount][yCount])
{
    for (int i = 0; i < xCount; ++i)
    {
        for (int j = 0; j < yCount; ++j)
        {
            cout<<Map[i][j]<<"\t";
        }
        cout<<endl;
    }
}

template <typename T>
void printT(T t)
{
    for (auto point:t)
    {
        point.toString();
    }
}

enum Priority{
    THREE = 0x3,
    FOUR = 1<<3,
    CROSS = 1<<4,
    FIVE = 1<<5
};

struct Range{
    int a,b;
    Range(int _a, int _b):a(_a),b(_b)
    {}
    void toString()
    {
        CCLOG("Range is %d-%d\n",a,b);
    }
    inline bool rangeIn(int num)
    {
        return num>=a && num<=b;
    }
    void setRangeDisable()
    {
        a = -1;
        b = -1;
    }
};

using Nodes = std::list<Range *>;
using XYMap = std::map<int, Nodes *>;
XYMap xVec, yVec;
XYMap xx[2]{xVec, yVec};
std::vector<Vec2 *> clashs;
void threes()
{
    memset(hMap, 0, sizeof(hMap));
    for (int i = 0; i < xCount; ++i)
    {
        int startPos[] = {0,0};
        int len[] = {1,1};
        static auto cpv = [&](int value, int startPosValue, int index, int j){
            if(j<yCount && startPosValue != 0 && value == startPosValue)
            {
                ++len[index];
            }
            else
            {
                if(len[index]>=3)
                {
                    CCLOG("%dThrees!!!%d\n",i,index);
                    auto tmpMap = xx[index].find(i);
                    if (tmpMap != xx[index].end()) {
                        tmpMap->second->push_back(new Range(startPos[index],j-1));
                    }
                    else
                    {
                        auto nodes = new Nodes();
                        nodes->push_back(new Range(startPos[index],j-1));
                        xx[index][i] = nodes;
                    }
                    for (int k=startPos[index]; k<j-1; k++) {
                        if (index == 0) {
                            hMap[i][k] += 1;
                            if (hMap[i][k]>1) {
                                clashs.push_back(new Vec2(i, k));
                            }
                        }
                        else {
                            hMap[k][i] += 1;
                            if (hMap[k][i]>1) {
                                clashs.push_back(new Vec2(k, i));
                            }
                        }
                    }
                }
                len[index] = 1;
                startPos[index] = j;
            }
        };
        for (int j = 1; j < yCount+1; ++j)  //  此处多访问了 一个数组纬度
        {
            cpv(Map[i][j], Map[i][startPos[0]], 0, j);
            cpv(Map[j][i], Map[startPos[1]][i], 1, j);
        }
    }	
}

class Threes {
private:
    std::vector<Vec2> _array;
    Vec2 _center;
    Priority prrority;
public:
    Threes(){}
    ~Threes(){}
    
    void addPoint(Vec2 &point)
    {
        _array.push_back(point);
    }
    
    void setCenter(Vec2 &center)
    {
        _center = center;
    }
};
using THreesVec = std::vector<Threes *>;
void saveThress()
{
    
}

// ***@*** 七连中间未处理
bool checkSelfIsTrible( int i, Range *range )
{
    if (i - range->a >= 3) {
        range->b = i-1;
        return false;
    }
    else if (range->b - i >= 3) {
        range->a = i+1;
        return false;
    }
    return false;
}

Range* findIndex(Nodes *array, int value)
{
    if (array == nullptr) {
        return nullptr;
    }
    for (auto range:*array) {
        if (range->rangeIn(value)) {
            return range;
        }
    }
    return nullptr;
}

inline void processClash(int x, int y) {
    Range* xArray = findIndex(xx[0][x], y);
    Range* yArray = findIndex(xx[1][y], y);
    if (xArray && yArray) {
        int x1 = xArray->a, y1 = xArray->b;
        int x2 = yArray->a, y2 = yArray->b;
        xArray->setRangeDisable();
        yArray->setRangeDisable();
        for (int i=x1; i<y1; i++) {
            if (hMap[x][i] != 0) {
                processClash(x, i);
            }
            
        }
        for (int i=x2; i<y2; i++) {
            if (hMap[i][y] != 0) {
                processClash(i, y);
            }
        }
    }
    else if (xArray) {
        if (checkSelfIsTrible(x, xArray)) {
            xArray->setRangeDisable();
        }
    }
    else if (yArray) {
        if (checkSelfIsTrible(y, yArray)) {
            yArray->setRangeDisable();
        }
    }
}

void processClashs()
{
    for (auto clashP:clashs) {
        clashP->toString();
        processClash(clashP->x, clashP->y);
    }
}

void printArray()
{
    for (int i=0; i<2; i++) {
        for (auto vec:xx[i]) {
            cout<<"K is "<<vec.first<<" ";
            for (auto node:*vec.second) {
                node->toString();
            }
        }
        cout<<endl;
    }
}

void printClashs()
{
    for (auto p: clashs) {
        p->toString();
    }
}

int main(int argc, char const *argv[])
{
    clock_t start, ends;
    
    start=clock();
    threes();
    printArray();
    printClashs();
    processClashs();
    cout<<clashs.size()<<endl;
    ends=clock();
    cout << "Clock is :" << (ends-start)*1.0/1000 << endl;
    
    return 0;
}