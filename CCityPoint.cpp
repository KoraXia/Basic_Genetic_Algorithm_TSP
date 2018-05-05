//
//  CCityPoint.cpp
//  test3
//
//  Created by Kora Xia on 5/3/18.
//  Copyright © 2018 Ke Xia. All rights reserved.
//

#include "CCityPoint.hpp"


void CCityPoint::GetPoint(double *p, int k) {
    x = *p;
    p++;
    y = *p;
    no = k;
}

void CCityPoint::setX(double x) {
    CCityPoint::x = x;
}

void CCityPoint::setY(double y) {
    CCityPoint::y = y;
}

void CCityPoint::setNo(int no) {
    CCityPoint::no = no;
}
