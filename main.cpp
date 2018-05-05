//
//  main.cpp
//  test
//
//  Created by Kora Xia on 5/2/18.
//  Copyright © 2018 Ke Xia. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <chrono>
#include "CGA.hpp"

void foo(const std::string &filename);

int main(int argc, char* argv[]) {
    std::string filename={"datasample.txt"};
    //for(int i = 0; i < 8; i++)
    //{
        std::cout<<filename<<std::endl;
        foo(filename);
    //}
    return 0;
}

void foo(const std::string &filename) {
    std::vector<double> city;
    int num;
    
    std::fstream in(filename.c_str(),std::ios::in);
    in >> num;
    in.close();
    
    CGA a(1000, 50);
    a.InitGraph(filename);
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    a.Start();
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    double min = a.Output(city, num);
    std::cout << "length = " << min << std::endl;
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << "the running time is:" << time_span.count() << " ns" << std::endl;
    std::cout << "city:" << std::endl;
    //    for (int i = 0; i < 13; i++) {
    //        std::cout << city[i] << "->";
    //    }
    //    std::cout << city[13] << std::endl;
    
    for (double c : city)
        std::cout << c+1 << "->";
    std::cout << "\b\b" << std::endl;
    
}
