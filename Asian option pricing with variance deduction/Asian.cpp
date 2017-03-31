//
//  Asian.cpp
//  Asian_opt_pricing
//
//  Created by Wuqian Zhong on 07/01/2017.
//  Copyright © 2017 Wuqian Zhong. All rights reserved.
//
#ifndef Asian_cpp
#define Asian_cpp

#include "Asian.hpp"
#include <numeric>  // Necessary for accumulate
#include <cmath>    // For log/exp functions
//#include <vector>
using namespace std;

// =====================
// AsianOption
// =====================

AsianOption::AsianOption(PayOff* _pay_off) : pay_off(_pay_off) {}


// =====================
// AsianOptionArithmetic
// =====================

AsianOptionArithmetic::AsianOptionArithmetic(PayOff* _pay_off) : AsianOption(_pay_off) {}

// Arithmetic mean pay-off price
double AsianOptionArithmetic::pay_off_price(const vector<double>& spot_prices ) const {
    unsigned num_times = spot_prices.size();
    double sum = accumulate(spot_prices.begin(), spot_prices.end(), 0);  //累加包首不包尾，初始为0
    double arith_mean = sum / static_cast<double>(num_times);
    return (*pay_off)(arith_mean);  // 取pay_off所指针指向的PayOff对象，调用其运算符()
}


// ====================
// AsianOptionGeometric
// ====================


// Geometric mean pay-off price
double AsianOptionGeometric::pay_off_price(const vector<double>& spot_prices) const {
    unsigned num_times = spot_prices.size();
    double log_sum = 0.0;
    for (int i=0; i<spot_prices.size(); i++) {
        log_sum += log(spot_prices[i]);
    }
    double geom_mean = exp(log_sum / static_cast<double>(num_times));
    return (*pay_off)(geom_mean);
}



#endif
