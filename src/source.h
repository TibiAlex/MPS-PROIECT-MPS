#include <bits/stdc++.h>

using namespace std;

//calculate graph either until N or until error smaller than E
int N = 10;
float E = 0.1;

//the operations that will be used in order to obtain the result
vector<string> operations = {
    "multiply", 
    "sum", 
    "diff", 
    "min", 
    "max", 
    "divide", 
    "if_min_max", 
    "if_sum_diff", 
    "if_multiply_divide"
};