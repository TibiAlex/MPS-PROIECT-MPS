#include <bits/stdc++.h>

using namespace std;

//calculate graph either until N or until error smaller than E
int N = 10;
float E = 0.1;

//the operations that will be used in order to obtain the result
vector<string> operations = {
    "m_a",
    "m_g",
    "m_h",
    "m_p",
    "min", 
    "max"
};