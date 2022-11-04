#include <fstream>
#include <filesystem>
#include <sstream>
#include <cmath>
#include "treshholds.h"

using namespace std;

//function that reads data form files
void readInputData(vector<TreshHolds> &treshHolds) {
    for (auto& file : filesystem::directory_iterator{ "../../MPS-Global" })  //loop through the folder
    {
        string line, word;
        ifstream fs{ file.path() };
        if (fs.is_open()) {

            TreshHolds th;
            th.filename = file.path().generic_string();
            bool isIdeal = true;

            getline(fs, line);
            stringstream str1(line);
            while(getline(str1, word, ',')) {
                if (isIdeal) {
                    th.idealThreshHold = stof(word);
                    isIdeal = false;
                } else {
                    th.threshholds.push_back(stof(word));
                }
            }
            getline(fs, line);
            stringstream str2(line);
            while(getline(str2, word, ','))
                th.score.push_back(stof(word));

            treshHolds.push_back(th);
        } else
            cout<<"Could not open the file\n";
        
        //comment the line below for only the first file to be read
        // break;
    }
}

int main() {

    //the vector where all the data will be stored
    vector<TreshHolds> treshHolds;
    
    //function that reads data form files
    readInputData(treshHolds);

    // displaying all read data uncomment for debug
    // for (int i = 0; i < treshHolds.size(); i++) {
    //     cout << treshHolds[i].filename << endl;
    //     cout << treshHolds[i].idealThreshHold << endl;
    //     for (int j = 0; j < treshHolds[i].threshholds.size(); j++) {
    //         cout << treshHolds[i].threshholds[j] << " ";
    //     }
    //     cout << endl;
    //     for (int j = 0; j < treshHolds[i].score.size(); j++) {
    //         cout << treshHolds[i].score[j] << " ";
    //     }
    //     cout << endl;
    // }

    // task1: calculate the score using the ideal treshholds
    float average_ideal_score = 0;
    for (int i = 0; i < treshHolds.size(); i++) {
        float r = floor(255 * treshHolds[i].idealThreshHold);
        average_ideal_score += treshHolds[i].score[r];
    }
    cout << average_ideal_score/treshHolds.size() << endl;

    return 0;
}