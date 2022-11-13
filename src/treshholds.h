#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TreshHolds
{
    public:
        string filename;
        float idealThreshHold;
        vector<float> threshholds;
        vector<float> score;
};

typedef struct {
    int op;
    int index1;
    int index2;
} operation;