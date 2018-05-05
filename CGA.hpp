//
//  CGA.hpp
//  test3
//
//  Created by Kora Xia on 5/3/18.
//  Copyright © 2018 Ke Xia. All rights reserved.
//

#ifndef CGA_hpp
#define CGA_hpp

#include <string>
#include <vector>
#include "CCityPoint.hpp"
#include "CIndiv.hpp"

class CGA {
private:
    std::vector<CCityPoint> citylist;
    int iteration;
    int pop_num;
    double crossover_pro;
    double mutation_pro;
    
    std::vector< std::vector<double> > Distance;
    
    std::vector<CIndiv> population;
    std::vector<CIndiv> parent;
    std::vector<CIndiv> child;
    
    int CityNumber;
    
public:
    
    CGA();
    
    CGA(int, int);

    CGA(int, int, double, double);
    
    void Start();
    
    void InitCityList(double city[], int num);

    void InitGraph(std::string filename);
    
    void Set_iteration(int m)        
    {
        iteration = m;
    }
    
    void Set_popNum(int val) {
        pop_num = val;
    }
    
    void Set_cross_mutation(int cross, int mutation) {
        crossover_pro = cross;
        mutation_pro = mutation;
    }
    
    double Output(std::vector<double> &city, int num);
    ~CGA() {};
    
private:
    void CalcDistance();
    void Init_population();
    void Select();
    void Crossover();
    void Mutation();
    void Evolution();
};

struct pri_grd {
    int index;
    double grad;
};

#endif /* CGA_hpp */
