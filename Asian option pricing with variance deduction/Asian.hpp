//
//  Asian.hpp
//  Asian_opt_pricing
//
//  Created by Wuqian Zhong on 07/01/2017.
//  Copyright © 2017 Wuqian Zhong. All rights reserved.
//

#ifndef Asian_hpp
#define Asian_hpp

#include <vector>
#include "payoff.hpp"
using namespace std;

class AsianOption { // abstract base class
protected:
    PayOff* pay_off;    // polymorphism, pointer to PayOff abstract class, could be PayOffCall, PayOffPut
    
public:
    AsianOption(PayOff* _pay_off);
    virtual ~AsianOption() {};
    
    // Pure virtual pay-off function (will determine averaging procedure arithmetic or geometirc)
    virtual double pay_off_price(const vector<double>& spot_prices) const = 0;
};


class AsianOptionArithmetic : public AsianOption {
public:
    AsianOptionArithmetic(PayOff* _pay_off);
    virtual ~AsianOptionArithmetic() {};
    
    // Override the pure virtual function to produce arithmetic Asian Option
    virtual double pay_off_price(const vector<double>& spot_prices) const;
};


class AsianOptionGeometric : public AsianOption {
public:
    AsianOptionGeometric(PayOff* _pay_off);
    virtual ~AsianOptionGeometric() {};
    
    // Override the pure virtual function to produce geometric Asian Option
    virtual double pay_off_price(const vector<double>& spot_prices) const;
};

#endif /* Asian_hpp */
