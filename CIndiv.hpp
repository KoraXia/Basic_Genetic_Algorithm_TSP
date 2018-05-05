//
//  CIndiv.hpp
//  test3
//
//  Created by Kora Xia on 5/3/18.
//  Copyright © 2018 Ke Xia. All rights reserved.
//

#ifndef CIndiv_hpp
#define CIndiv_hpp

#include <vector>
#include "CCityPoint.hpp"

//individual
class CIndiv {
public:
    std::vector<int> a;
    double length;
    double fit;
    int dnaLength;
public:
    CIndiv(int dnaLength);
    
    CIndiv &operator=(const CIndiv &rhs);
    
    void Calcfit(std::vector<std::vector<double> > Distance, std::vector<CCityPoint> list); //calculate fitting rate
    void Initdiv();
    
    void pfdiv();
    
};


#endif /* CIndiv_hpp */
