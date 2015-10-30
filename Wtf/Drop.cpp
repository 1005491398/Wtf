//
//  Drop.cpp
//  Wtf
//
//  Created by 陈 玉涛 on 10/19/15.
//  Copyright (c) 2015 陈 玉涛. All rights reserved.
//

#include "Drop.h"
const int UnReachable = -1;

Drop::Drop()
{
    memset(_map, 0, sizeof(int)*xCount*yCount);
}

void Drop::initExitList()
{
    for (int i=0; i<xCount; i++) {
        _exitPoints.push_back(Vec2(0, i));
    }
}

int Drop::getUpValue(int x, int y)
{
    if (x>0) {
        auto value = _map[x-1][y];
        if (value!=0&&value!=-1) {
            return value+1;
        }
    }
    return 1;
}

int Drop::getLeftValue(int x, int y)
{
    if (x>0&&y>0) {
        auto value = _map[x-1][y-1];
        if (value!=0&&value!=-1) {
            return value+3;
        }
    }
    return 1;
}

int Drop::getRightValue(int x, int y)
{
    if (x>0&&y<yCount-1) {
        auto value = _map[x-1][y+1];
        if (value!=0&&value!=-1) {
            return value+2;
        }
    }
    return 1;
}

void Drop::initPathValue()
{
    for (auto point: _exitPoints) {
        _map[point.x][point.y] = 1;
    }
    for (int i=0; i<xCount; i++) {
        for (int j=0; j<yCount; j++) {
            if (Map[i][j] == 0) {
                _map[i][j] = UnReachable;
            }
            else if (_map[i][j] == 0)
            {
                auto value = getUpValue(i, j);
                if (value == 1)
                {
                    value = getLeftValue(i, j);
                    if (value == 1)
                    {
                        value = getRightValue(i, j);
                    }
                }
                _map[i][j] = value;
            }
        }
    }
}

int Drop::find(int x, int y)
{
    if (x<0 || x>xCount-1 || y<0 || y>yCount-1)
        return UnReachable;
    
    return _map[x][y];
}

int Drop::findUp(int x, int y)
{
    return find(x-1,y);
}

int Drop::findLeft(int x, int y)
{
    return find(x-1,y-1);
}

int Drop::findRight(int x, int y)
{
    return find(x-1,y+1);
}

Points Drop::findOneWay(int x, int y)
{
    Points points;
    auto xx = x, yy = y;
    
    for (int i=0; i<2*xCount; i++) {
        auto value = findUp(xx, yy);
        if (value == UnReachable) {
            value = findLeft(xx, yy);
            if (value == UnReachable) {
                value = findRight(xx, yy);
                if (value == UnReachable) {
                    // 无法移动
                    break;
                }
                else {
                    points.push_back(Vec2(xx-1, yy+1));
                    points.push_back(Vec2(xx, yy));
                    xx -= 1;
                    yy += 1;
                }
            }
            else {
                points.push_back(Vec2(xx-1, yy-1));
                points.push_back(Vec2(xx, yy));
                xx -= 1;
                yy -= 1;
            }
        }
        else {
            points.push_back(Vec2(xx-1, yy));
            points.push_back(Vec2(xx, yy));
            xx -=1;
        }
        if (value == 1)
            break;
    }
    return points;
}

void Drop::doDrop()
{
    initExitList();
    initPathValue();
    printMap(_map);
    Points eliminatePoints{Vec2(9,3),Vec2(8,3),Vec2(7,3),Vec2(6,3)};
    
    for (auto p: eliminatePoints) {
        findOneWay(p.x, p.y);
    }
}