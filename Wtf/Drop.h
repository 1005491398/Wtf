//
//  Drop.h
//  Wtf
//
//  Created by 陈 玉涛 on 10/19/15.
//  Copyright (c) 2015 陈 玉涛. All rights reserved.
//

#ifndef __Wtf__Drop__
#define __Wtf__Drop__

#include <stdio.h>
#include "Vec2.h"
#include "Const.h"

class Drop {
private:
    Points _exitPoints;
    int _map[xCount][yCount];
public:
    Drop();
    ~Drop() {}
    
    void initExitList();
    void initPathValue();
    int getUpValue(int x, int y);
    int getLeftValue(int x, int y);
    int getRightValue(int x, int y);
    int find(int x, int y);
    int findUp(int x, int y);
    int findLeft(int x, int y);
    int findRight(int x, int y);
    Points findOneWay(int x, int y);
    
    void doDrop();
};

#endif /* defined(__Wtf__Drop__) */
