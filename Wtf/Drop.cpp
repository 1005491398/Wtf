//
//  Drop.cpp
//  Wtf
//
//  Created by 陈 玉涛 on 10/19/15.
//  Copyright (c) 2015 陈 玉涛. All rights reserved.
//

#include "Drop.h"

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
                _map[i][j] = -1;
            }
            else if (_map[i][j] == 0)
            {
                auto value = 1;
                
            }
        }
    }
}