//
//  CCityPoint.hpp
//  test3
//
//  Created by Kora Xia on 5/3/18.
//  Copyright © 2018 Ke Xia. All rights reserved.
//

#ifndef CCityPoint_hpp
#define CCityPoint_hpp

#include <stdio.h>
//city
class CCityPoint {
private:
    double x, y;
    int no;
public:
    void GetPoint(double *, int);
    
    double re_x() {
        return x;
    }
    
    double re_y() {
        return y;
    }
    
    int re_no() {
        return no;
    }
    
    void setX(double x);
    
    void setY(double y);
    
    void setNo(int no);
    
};


#endif /* CCityPoint_hpp */
