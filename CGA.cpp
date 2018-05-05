//
//  CGA.cpp
//  test3
//
//  Created by Kora Xia on 5/3/18.
//  Copyright © 2018 Ke Xia. All rights reserved.
//

#include "CGA.hpp"
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>

CGA::CGA()
{
    iteration = 1000;
    pop_num = 50;
    crossover_pro = 0.8;
    mutation_pro = 0.1;
}

CGA::CGA(int it, int po)
{
    iteration = it;
    pop_num = po;
    crossover_pro = 0.8;
    mutation_pro = 0.1;
}

CGA::CGA(int it, int po, double cross, double mutate)
{
    iteration = it;
    pop_num = po;
    crossover_pro = cross;
    mutation_pro = mutate;
}

//genetic algorithm
void CGA::InitCityList(double city[], int num) {
    for (int i = 0; i < num; i++) {
        citylist[i].GetPoint(city, i);
        city++;
        city++;
    }
}

//init graph
void CGA::InitGraph(std::string filename) {
    std::fstream in;
    in.open(filename);
    double x_, y_;
    int num;
    
    in >> CityNumber;
    
    citylist = std::vector<CCityPoint>(CityNumber);
    
    for (int i = 0; i < CityNumber; i++) {
        in >> num >> x_ >> y_;
        citylist[i].setX(x_);
        citylist[i].setY(y_);
        citylist[i].setNo(i);
        //std::cout << x_ << " " << y_ << std::endl;
    }
    in.close();
}

//calculate distance matrix
void CGA::CalcDistance()
{
    Distance = std::vector<std::vector<double>>(CityNumber, std::vector<double>(CityNumber));
    
    for (int i = 0; i < CityNumber; i++) {
        for (int j = 0; j < CityNumber; j++) {
            Distance[i][j] = sqrt(pow((citylist[i].re_x() - citylist[j].re_x()), 2) +
                                  pow((citylist[i].re_y() - citylist[j].re_y()), 2));
        }
    }
}

//initialize population
void CGA::Init_population() {
    CIndiv tmpindiv(CityNumber);
    int tmp;
    
    population.reserve(450);
    parent.reserve(450);
    child.reserve(450);
    
    srand((unsigned) time(nullptr));
    
    for (int k = 0; k < pop_num; k++) {
        tmpindiv.Initdiv();                                   //initial individuals
        for (int i = 1; i < CityNumber; i++)                  //random generate individuals
        {
            int index;
            index = rand() % (CityNumber - i) + i;
            if (index != i) {  //change positions
                tmp = tmpindiv.a[i];
                tmpindiv.a[i] = tmpindiv.a[index];
                tmpindiv.a[index] = tmp;
            }
        }
        
        population.push_back(tmpindiv);
        population.at(k).Calcfit(Distance, citylist);
        
        //std::cout << "The initial sequence is: " << k << "  length=" << population.at(k).length << std::endl;
        //std::cout << "Initial individual is: " << k << "   ";
        //population.at(k).pfdiv();
        
    }
}


//selection
void CGA::Select() {
    
    double total_fit = 0.0;   //total fitting value
    std::vector<double> total_gr;  // possibility gradience
    
    double total_div_fit = 0.0;
    double div_fit_pro = 0.0;
    double index;
    
    parent.clear();
    total_gr.clear();
    
    
    //calculate total individual fitting value
    for (int i = 0; i < pop_num; i++)
    {
        total_fit += population.at(i).fit;
    }
    
    //calculate divide fitting rate to select better individuals
    for (int j = 0; j < pop_num; j++)
    {
        div_fit_pro = population.at(j).fit / total_fit;
        total_div_fit  += div_fit_pro;
        total_gr.push_back(total_div_fit);
        
        /**************************print individual total fitting value***********************************/

        //std::cout<<"population individual fitting rate="<<population[j].fit<<"  "<<total_div_fit<<std::endl;

        /**************************print possibility gradient*********************************************/
        //std::cout<<"possible gradient "<<total_gr.at(j)<<std::endl;
    }
    
    index = 0;
    
    for (int k = 0; k < pop_num; k++)                    //select in total pop_num individuals
    {
        index = rand() % 10000;
        index = index / 10000.0;
        
        //std::cout<<"crossover index="<<index<<std::endl;
        
        for (int t = 0; t < pop_num; t++)                //random select individual with satisfied possibility
        {
            if (total_gr.at(t) >= index) {
                parent.push_back(population.at(t));
                //std::cout<<"number: "<<t<<"  ";
                break;
            }
        }
        
        //std::cout<<parent.at(k).length<<std::endl;
        
        /*********************output selected individuals******************************/
        /*
         parent.at(k).Calcfit(Distance,citylist);
         std::cout<<"selected individual: "<<k<<std::endl;
         parent.at(k).pfdiv();
         ******************************************************************************/
    }
}

//crossover
void CGA::Crossover() {
    
    int locus, len;
    //int tmpchro1[14] = {0};
    std::vector<int> tmpchro1(CityNumber);
    //int tmpchro2[14] = {0};
    std::vector<int> tmpchro2(CityNumber);
    
    double index;
    int tmp = 0;
    
    CIndiv tmpdiv1(CityNumber), tmpdiv2(CityNumber), tmpdiv3(CityNumber), tmpdiv4(CityNumber);
    
    std::vector<CIndiv> tmpdiv;
    
    CIndiv tmpdd(CityNumber);
    
    child.clear();
    
    for (int wi = 0; wi < pop_num; wi++) {
        tmpdiv.push_back(parent.at(wi));
    }
    
    for (int qi = 0; qi < pop_num; qi++) {
        for (int qj = qi + 1; qj < pop_num; qj++) {
            
            if (tmpdiv.at(qi).fit < tmpdiv.at(qj).fit) {
                tmpdd = tmpdiv.at(qi);
                tmpdiv.at(qi) = tmpdiv.at(qj);
                tmpdiv.at(qj) = tmpdd;
            }
        }
    }
    //tmpdiedai=tmpdiv.at(0).length;
    
    for (int qjj = 0; qjj < 8; qjj++) {
        tmpdiv.at(pop_num - qjj - 1) = tmpdiv.at(qjj);
    }
    
    int ii;
    CIndiv tmpd(CityNumber);
    
    for (int w = 1; w < pop_num; w++) {
        
        ii = rand() % (pop_num - w) + w;
        if (ii != w) {
            tmpd = tmpdiv.at(w);
            tmpdiv.at(w) = tmpdiv.at(ii);
            tmpdiv.at(ii) = tmpd;
        }
    }
    
    for (int jj = 0; jj < pop_num; jj++) {
        parent.at(jj) = tmpdiv.at(jj);
    }
    
    
    for (int i = 0; i < pop_num - 1; i = i + 2) {
        tmpdiv1 = parent.at(i);
        tmpdiv2 = parent.at(i + 1);
        
        index = rand() % 10000;
        index = index / 10000.0;
        
        if (index < crossover_pro) {
            //start gene is locus
            //end gene is len+locus
            locus = rand() % (CityNumber-2) + 1;   //1-28
            len = rand() % (CityNumber - locus);   //
            
            /***************************************************/
            /*
             std::cout<<"locus="<<locus<<std::endl;
             std::cout<<"len="<<len<<std::endl;
             ***************************************************/
            
            
            for (int j = 0; j < CityNumber; j++)                    //copy dna
            {
                tmp = (locus + len + j + 1) % CityNumber;
                tmpchro1[j] = tmpdiv1.a[tmp];
                tmpchro2[j] = tmpdiv2.a[tmp];
                
            }
            
            for (int k = 0; k < len + 1; k++)                            //delete existring dna clip
            {
                for (int t = 0; t < CityNumber; t++)                            //find the target gene
                {
                    if (tmpchro1[t] == tmpdiv2.a[k + locus]) {
                        tmpdiv3.a[k + locus] = tmpchro1[t];
                        for (int r = t; r < CityNumber; r++) {
                            tmpchro1[r] = tmpchro1[r + 1];
                        }
                    }
                    if (tmpchro2[t] == tmpdiv1.a[k + locus]) {
                        tmpdiv4.a[k + locus] = tmpchro2[t];
                        for (int l = t; l < CityNumber; l++) {
                            tmpchro2[l] = tmpchro2[l + 1];
                        }
                    }
                }
            }
            
            for (int h = 0; h < CityNumber - len - 1; h++) {
                tmpdiv3.a[(h + 1 + locus + len) % CityNumber] = tmpchro1[h];
                tmpdiv4.a[(h + 1 + locus + len) % CityNumber] = tmpchro2[h];
            }
            
        } else {
            tmpdiv3 = tmpdiv1;
            tmpdiv4 = tmpdiv2;
        }
        child.push_back(tmpdiv3);
        //child.at(i).Calcfit(Distance,citylist);
        child.push_back(tmpdiv4);
        //child.at(i+1).Calcfit(Distance,citylist);
        
        /**************output crossovered individuals********************/
        /*
         std::cout<<"crossover individual no1: "<<" "<<i<<std::endl;
         
         child.at(i).pfdiv();
         std::cout<<"crossover individual no2:"<<" "<<i+1<<std::endl;
         
         child.at(i+1).pfdiv();
         ***************************************************************/
    }
}

//mutation
void CGA::Mutation() {
    
    double index;
    int locus;
    int len;
    // TODO
    //    int tmpchro1[14] = {0};
    //    int tmpchro2[14] = {0};
    std::vector<int> tmpchro1(CityNumber);
    std::vector<int> tmpchro2(CityNumber);
    
    CIndiv tmpdiv1(CityNumber);
    
    int r = 0;
    int h = 0;
    
    population.clear();
    
    for (int i = 0; i < pop_num; i++) {
        
        tmpdiv1 = child.at(i);
        
        for (int j = 0; j < CityNumber; j++) {
            tmpchro1[j] = tmpdiv1.a[j];
        }
        
        index = rand() % 1000;
        index = index / 1000.0;  // mutate or not
        if (index <= mutation_pro) {
            
            //define length and start point
            locus = rand() % (CityNumber-2) + 1;
            len = rand() % (CityNumber - 1 - locus);
            
            /***************************************************/
            /*
             std::cout<<"locus="<<locus<<std::endl;
             std::cout<<"len="<<len<<std::endl;
             ***************************************************/
            
            //do mutation
            r = 0;
            for (int k = locus + len; k >= locus; k--) {
                tmpchro2[r] = tmpchro1[k];
                r++;
            }
            
            /***************************************************/
            /*
             std::cout<<endl<<"dna reverse part: "<<std::endl;
             for(int b=0;b<len+1;b++)
             {
             std::cout<<tmpchro2[b]<<" ";
             }
             std::cout<<std::endl;
             ***************************************************/
            
            h = 0;
            for (int t = locus; t < locus + len + 1; t++) {
                tmpdiv1.a[t] = tmpchro2[h];
                h++;
            }
        }
        
        population.push_back(tmpdiv1);
        //        population.at(i).Calcfit(Distance,citylist);
        
        /***************************************************/
        /*
         std::cout<<"ouput mutationed individual"<<std::endl;
         population.at(i).pfdiv();
         ***************************************************/
    }
}

//calculate fitting value
void CGA::Evolution() {
    
    for (int i = 0; i < pop_num; i++) {
        population.at(i).Calcfit(Distance, citylist);
    }
}

//output the best individual in current generation
double CGA::Output(std::vector<double> &city, int num) {
    
    CIndiv bestdiv(CityNumber);
    this->Evolution();
    bestdiv = population.at(0);
    for (int i = 1; i < pop_num; i++) {
        if (population.at(i).fit > bestdiv.fit) {
            bestdiv = population.at(i);
        }
    }
    city = std::vector<double>(CityNumber);
    for (int j = 0; j < num; j++) {
        city[j] = bestdiv.a[j];
    }
    return bestdiv.length;
}

void CGA::Start() {
    
    srand((unsigned int) time(nullptr));
    CalcDistance();
    Init_population();
    for (int i = 0; i < iteration; i++) {
        Evolution();
        Select();
        Crossover();
        Mutation();
    }
}


