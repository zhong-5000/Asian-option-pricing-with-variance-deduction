//
//  payoff.hpp
//  Asian_opt_pricing
//
//  Created by Wuqian Zhong on 07/01/2017.
//  Copyright © 2017 Wuqian Zhong. All rights reserved.
//

#ifndef payoff_hpp
#define payoff_hpp


#include <algorithm>

// abstract base class 抽象基类(类中定义了纯虚成员函数的类)，不能实例化
class PayOff {
public:
    PayOff();   // Default (no parameter) constructor
    virtual ~PayOff() {};   // Virtual destructor
    
    // Overloaded () operator, turns the PayOff into an abstract function object (like a function)
    virtual double operator() (const double& S) const = 0;  // pure virtual function 在派生类中必须重写
};


class PayOffCall : public PayOff {
private:
    double K;   // Strike price
    
public:
    PayOffCall(const double& K_);
    virtual ~PayOffCall() {};
    
    // Virtual function is now over-ridden (not pure-virtual anymore)
    virtual double operator() (const double& S) const;  // 常量函数，防止修改对象
};


class PayOffPut : public PayOff {
private:
    double K;   // Strike price
    
public:
    PayOffPut(const double& K_);
    virtual ~PayOffPut() {};
    virtual double operator() (const double& S) const;
};

#endif /* payoff_hpp */
