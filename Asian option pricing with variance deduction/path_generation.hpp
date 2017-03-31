//
//  path_generation.hpp
//  Asian_opt_pricing
//
//  Created by Wuqian Zhong on 07/01/2017.
//  Copyright © 2017 Wuqian Zhong. All rights reserved.
//

#ifndef path_generation_hpp
#define path_generation_hpp

#include <vector>
#include <cmath>
#include <random>
using namespace std;

// 产生随机数
default_random_engine generator;
normal_distribution<double> distribution(0,1);

// This provides a vector containing sampled points of a GBM stock price path
void calc_path_spot_prices(vector<double>& spot_prices,  // Vector of spot prices to be filled in
                           const double& r,   // Risk free interest rate (constant)
                           const double& v,   // Volatility of underlying (constant)
                           const double& T) { // Expiry
    // Since the drift and volatility of the asset are const, we precalculate them for efficiency
    double dt = T/static_cast<double>(spot_prices.size());
    double drift = exp((r-0.5*v*v)*dt);
    double vol = sqrt(v*v*dt);
    
    for (int i=1; i<spot_prices.size(); i++) {  // spot_price[0] is already pre-filled with S elsewhere
        double gauss_bm = distribution(generator); // Generate a Gaussian random number
        spot_prices[i] = spot_prices[i-1] * drift * exp(vol*gauss_bm);
    }
    
}

#endif /* path_generation_hpp */
