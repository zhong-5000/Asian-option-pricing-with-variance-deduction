//
//  payoff.cpp
//  Asian_opt_pricing
//
//  Created by Wuqian Zhong on 07/01/2017.
//  Copyright © 2017 Wuqian Zhong. All rights reserved.
//

#ifndef payoff_cpp
#define payoff_cpp

#include "payoff.hpp"

PayOff::PayOff() {}


// ==========
// PayOffCall
// ==========


// Constructor with single strike parameter
PayOffCall::PayOffCall(const double& _K) { K = _K; }

// Over-ridden operator() method, which turns PayOffCall into a function object
double PayOffCall::operator() (const double &S) const {
    return std::max(S-K, 0.0);  // Standard European call pay-off
}


// ==========
// PayOffPut
// ==========


PayOffPut::PayOffPut(const double& _K) { K = _K; }

double PayOffPut::operator() (const double &S) const {
    return std::max(K-S, 0.0);  // Standard European put pay-off
}
#endif
