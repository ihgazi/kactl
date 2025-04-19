/**
 * Author: None
 * Date: 2024-12-24
 * License: None
 * Source: None
 * Description: Functions for modulo arithmetic.
 */
#pragma once

const ll MOD = 17; // change to something else
ll mult(ll p, ll q, ll m = MOD) {
    return (((p%m)*(q%m))%m);
}

ll binpow(ll p, ll q) {
    if (q == 0) return 1ll;
    ll temp = binpow(p, q/2);
    temp = mult(temp, temp);
    
    if (q%2) return mult(temp, p);
    return temp;
}

ll mod_inv(ll a, ll m = MOD) {
    return binpow(a, m - 2);
}
