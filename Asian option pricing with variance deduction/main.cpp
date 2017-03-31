//
//  main.cpp
//  Asian_opt_pricing
//
//  Created by Wuqian Zhong on 07/01/2017.
//  Copyright © 2017 Wuqian Zhong. All rights reserved.
//

#include <iostream>
#include "payoff.hpp"
#include "path_generation.hpp"
#include "Asian.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    // Create the parameter list
    unsigned num_sims = 100000;  // Number of simulated asset path
    unsigned num_intervals = 250;   // 每条路径中的模拟的股价个数
    double S = 30.0;        // Option price
    double ds = 1;          // Delta S
    double K = 29.0;        // Strike price
    double r = 0.08;        // Risk-free rate 8%
    double v = 0.3;         // Volatility of the underlying 30%
    double T = 1.00;        // One year until expiry
    vector<double> spot_prices(num_intervals, S);   // 第一个参数为vector容量，第二个参数为对spot_prices[0]赋初值
    vector<double> spot_prices_p(num_intervals, S+ds);  // 用于Finite Differencing Method
    vector<double> spot_prices_m(num_intervals, S-ds);
    
    // Create the PayOff objects
    PayOff* pay_off_call = new PayOffCall(K);
    PayOff* pay_off_call_p = new PayOffCall(K);
    PayOff* pay_off_call_m = new PayOffCall(K);

    
    // Create the AsianOption objects
    AsianOptionArithmetic asian(pay_off_call);
    AsianOptionArithmetic asian_p(pay_off_call_p);
    AsianOptionArithmetic asian_m(pay_off_call_m);
    
    // Update the spot price vector
    double payoff_sum = 0.0;
    double payoff_sum_p = 0.0;
    double payoff_sum_m = 0.0;
    for (int i=0; i<num_sims; i++) {
        calc_path_spot_prices(spot_prices, r, v, T);
        calc_path_spot_prices(spot_prices_p, r, v, T);
        calc_path_spot_prices(spot_prices_m, r, v, T);
        payoff_sum += asian.pay_off_price(spot_prices);
        payoff_sum_p += asian.pay_off_price(spot_prices_p);
        payoff_sum_m += asian.pay_off_price(spot_prices_m);
    }
    double discount_payoff_avg = (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
    double discount_payoff_avg_p = (payoff_sum_p / static_cast<double>(num_sims)) * exp(-r*T);
    double discount_payoff_avg_m = (payoff_sum_m / static_cast<double>(num_sims)) * exp(-r*T);
    
    delete pay_off_call;
    delete pay_off_call_p;
    delete pay_off_call_m;
    
    // Output the parameters and price
    cout << "Number of Paths: " << num_sims << endl;
    cout << "Number of ints:  " << num_intervals << endl;
    cout << "Underlying :     " << S << endl;
    cout << "Strike:          " << K << endl;
    cout << "Risk-Free Rate:  " << r << endl;
    cout << "Volatility:      " << v << endl;
    cout << "Maturity:        " << T << endl;
    cout << "Asian Price:     " << discount_payoff_avg << endl;
    cout << "Delta:           " << (discount_payoff_avg_p - discount_payoff_avg) / ds << endl;
    cout << "Gamma:           " << (discount_payoff_avg_p - 2 * discount_payoff_avg +
                                    discount_payoff_avg_m) / (ds*ds) << endl;
    
    
    return 0;
}
