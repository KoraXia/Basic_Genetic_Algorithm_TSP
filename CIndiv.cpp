//
//  CIndiv.cpp
//  test3
//
//  Created by Kora Xia on 5/3/18.
//  Copyright © 2018 Ke Xia. All rights reserved.
//

#include "CIndiv.hpp"
#include <iostream>

void CIndiv::Initdiv() {
    a = std::vector<int>(dnaLength);
    for (int i = 0; i < dnaLength; i++) {
        a[i] = i;
    }
}


void CIndiv::Calcfit(std::vector< std::vector<double> > distance, std::vector<CCityPoint> list) {
    length = 0;
    int m, n;
    for (int j = 0; j < dnaLength - 1; j++) {
        m = list[a[j]].re_no();
        n = list[a[j + 1]].re_no();
        length = length + distance[m][n];
    }
    
    m = list[a[dnaLength - 1]].re_no();
    n = list[a[0]].re_no();
    length = length + distance[m][n];
    
    fit=1.0/length;
}


void CIndiv::pfdiv() {
    for (int i = 0; i < dnaLength; i++) {
        std::cout << a[i] << "->";
    }
    std::cout << a[0];
    std::cout << std::endl << "fit=" << fit << " " << "Shortest path length=" << length;
    //std::cout << std::endl << "******************************" << std::endl;
}


CIndiv::CIndiv(int dnaLength) {
    CIndiv::dnaLength = dnaLength;
    a = std::vector<int>(dnaLength);
}

CIndiv &CIndiv::operator=(const CIndiv &rhs) {
    
    length = rhs.length;
    fit = rhs.fit;
    dnaLength = rhs.dnaLength;
    a = std::vector<int>(rhs.a);
    
    return *this;
}
