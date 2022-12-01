#include <bits/stdc++.h>
#include "treshholds.h"
#include "graph.h"
#include "source.h"

//function that reads data form files
void readInputData(vector<TreshHolds> &treshHolds, vector<Graph> &graphs) {
    for (auto& file : filesystem::directory_iterator{ "../../MPS-Global" }){
        string line, word;
        ifstream fs{ file.path() };
        if (fs.is_open()) {

            TreshHolds th;
            Graph graph;
            th.filename = file.path().generic_string();
            bool isIdeal = true;

            //reading the first line of the file
            getline(fs, line);
            stringstream str1(line);
            vector<Node> level0;
            while(getline(str1, word, ',')) {
                if (isIdeal) {
                    th.idealThreshHold = stof(word);
                    isIdeal = false;
                } else {
                    float f = stof(word);
                    th.threshholds.push_back(f);
                    level0.push_back(Node("null", f));
                }
            }
            graph.levels.push_back(level0);

            //reading the second line of the file
            getline(fs, line);
            stringstream str2(line);
            while(getline(str2, word, ','))
                th.score.push_back(stof(word));

            sort(th.threshholds.begin(),th.threshholds.end());
            treshHolds.push_back(th);
            graphs.push_back(graph);
        } else
            cout<<"Could not open the file\n";
        
        //uncomment the line below for only the first file to be read
        break;
    }
}

//function that chooses either min or max operation
float if_min_max(float n1, float n2, float ideal) {
    if(abs(min(n1, n2) - ideal) < abs(max(n1, n2) - ideal))
        return min(n1, n2);
    else
        return max(n1, n2);
}

//function that chooses either sum or diff operation
float if_sum_diff(float n1, float n2, float ideal) {
    if(abs(abs(n1 - n2) - ideal) < abs(n1 + n2 - ideal))
        if(n1 == n2)
            return n1 / 2;
        else
            return abs(n1 - n2);
    else
        return n1 + n2;
}

//function that chooses either multiply or divide operation
float if_multiply_divide(float n1, float n2, float ideal) {
    if(n2 == 0)
        return n1;
    if(n1 == 0)
        return n2;
    if(abs(n1 * n2 - ideal) < abs(n1 / n2 - ideal))
        return n1 * n2;
    else 
        return n1/n2;
}

int main() {
    //the vector where all the data will be stored
    vector<TreshHolds> treshHolds;
    //the graph containing the result
    vector<Graph> graphs;
    /* initialize random seed: */
    srand (time(NULL));
    
    //function that reads data form files
    readInputData(treshHolds, graphs);
    //keeping thenumber of images to not call the function daily
    int number_of_treshholds = treshHolds.size();

    // for(int i = 0 ; i < number_of_treshholds; i++) {
    //     for(int j = 0 ; j < graphs[i].levels.size(); j++) {
    //         for(int k = 0; k < graphs[i].levels[0].size(); k++) {
    //             cout << graphs[i].levels[0][k].result << " ";
    //         }
    //     }
    // }

    /*
    // ? displaying all read data uncomment for debug
    for (int i = 0; i < number_of_treshholds; i++) {
        cout << treshHolds[i].filename << endl;
        cout << treshHolds[i].idealThreshHold << endl;
        for (int j = 0; j < treshHolds[i].threshholds.size(); j++) {
            cout << treshHolds[i].threshholds[j] << " ";
        }
        cout << endl;
        for (int j = 0; j < treshHolds[i].score.size(); j++) {
            cout << treshHolds[i].score[j] << " ";
        }
        cout << endl;
    }


    /*
    // ? task1: calculate the score using the ideal treshholds
    float average_ideal_score = 0;
    for (int i = 0; i < number_of_treshholds; i++) {
        float r = floor(255 * treshHolds[i].idealThreshHold);
        average_ideal_score += treshHolds[i].score[r];
    }
    cout << average_ideal_score/number_of_treshholds << endl;
    */
    for (int i = 0; i < N; i++) {
        //the level at which all the graphs are currently at
        int level = 0;
        //generate random operations and number of operations
        int nr_max_op = 15;
        int nr_min_op = nr_max_op/2 + 1;
        int nr_op = rand() % (nr_max_op - nr_min_op) + nr_min_op;
        while(nr_op >= 1) {
            vector<operation> operation_indexes;
            for(int j = 0; j < nr_op; j++) {
                operation op;
                op.op = rand() % (operations.size() - 1);
                //generate 2 indexes for the numbers for the operations
                op.index1 = rand() % (nr_max_op - 1);
                op.index2 = rand() % (nr_max_op - 1);
                operation_indexes.push_back(op);
            }
            
            //calculate the result for each image
            for(int j = 0; j < number_of_treshholds; j++) {
                vector<Node> level_vector;
                //go through each operation
                for(int k = 0; k < operation_indexes.size(); k++) {
                    Node node;
                    //verify if multiply by 0
                    if(operations[operation_indexes[k].op] == "multiply") {
                        if (graphs[j].levels[level][operation_indexes[k].index1].result == 0)
                            node.result = graphs[j].levels[level][operation_indexes[k].index2].result;
                        else if (graphs[j].levels[level][operation_indexes[k].index2].result == 0)
                            node.result = graphs[j].levels[level][operation_indexes[k].index1].result; 
                        else
                            node.result = graphs[j].levels[level][operation_indexes[k].index1].result *
                                    graphs[j].levels[level][operation_indexes[k].index2].result; 
                        node.operation = "multiply";
                    }
                    //verify if divided by 0
                    if(operations[operation_indexes[k].op] == "divide") {
                        if (graphs[j].levels[level][operation_indexes[k].index2].result == 0) 
                            node.result = graphs[j].levels[level][operation_indexes[k].index1].result;
                        else
                            node.result = abs(graphs[j].levels[level][operation_indexes[k].index1].result /
                                        graphs[j].levels[level][operation_indexes[k].index2].result);
                        node.operation = "divide";
                    }
                    //verify if sum
                    if(operations[operation_indexes[k].op] == "sum") {
                        node.result = graphs[j].levels[level][operation_indexes[k].index1].result +
                                    graphs[j].levels[level][operation_indexes[k].index2].result;
                        node.operation = "sum";
                    }
                    //verify if diff by himself couse of 0
                    if(operations[operation_indexes[k].op] == "diff") {
                        if(operation_indexes[k].index1 == operation_indexes[k].index2)
                            node.result = graphs[j].levels[level][operation_indexes[k].index1].result/2;
                        else
                            node.result = graphs[j].levels[level][operation_indexes[k].index1].result -
                                graphs[j].levels[level][operation_indexes[k].index2].result;
                        node.operation = "diff";
                    }
                    //verify if min
                    if(operations[operation_indexes[k].op] == "min") {
                        node.result = min(graphs[j].levels[level][operation_indexes[k].index1].result,
                                    graphs[j].levels[level][operation_indexes[k].index2].result);
                        node.operation = "min";
                    }
                    //verify if max
                    if(operations[operation_indexes[k].op] == "max") {
                        node.result = max(graphs[j].levels[level][operation_indexes[k].index1].result,
                                    graphs[j].levels[level][operation_indexes[k].index2].result);
                        node.operation = "max";
                    }
                    //verify if min or max is more suitable for the situation
                    if(operations[operation_indexes[k].op] == "if_min_max") {
                        node.result = if_min_max(graphs[j].levels[level][operation_indexes[k].index1].result,
                                                graphs[j].levels[level][operation_indexes[k].index2].result,
                                                treshHolds[j].idealThreshHold);
                        node.operation = "if_min_max";
                    }
                    //verify if sum or diff is more suitable for the situation
                    if(operations[operation_indexes[k].op] == "if_sum_diff") {
                        node.result = if_sum_diff(graphs[j].levels[level][operation_indexes[k].index1].result,
                                                graphs[j].levels[level][operation_indexes[k].index2].result,
                                                treshHolds[j].idealThreshHold);
                        node.operation = "if_sum_diff";
                    }
                    //verify if multiply or divide is more suitable for the situation
                    if(operations[operation_indexes[k].op] == "if_multiply_divide") {
                        node.result = if_multiply_divide(graphs[j].levels[level][operation_indexes[k].index1].result,
                                                graphs[j].levels[level][operation_indexes[k].index2].result,
                                                treshHolds[j].idealThreshHold);
                        node.operation = "if_multiply_divide";
                    }
                    level_vector.push_back(node);
                }
                graphs[j].levels.push_back(level_vector);
                level++;
            }

            //make the next number of operations until 1
            nr_max_op = nr_op;
            if(nr_max_op <= 3) {
                nr_min_op = 0;
            } else {
                nr_min_op = nr_max_op/2 + 1;
            }
            if (nr_op == 1) break;
            nr_op = rand() % (nr_max_op - nr_min_op) + nr_min_op;
            if (nr_op == 0) nr_op = 1;
            if (nr_max_op == 0) break;
        }

        for(int a = 0; a < number_of_treshholds; a++) {
            for(int b = 0; b < graphs[a].levels.size(); b++) {
                for(int c = 0; c < graphs[a].levels[b].size(); c++) {
                    cout << graphs[a].levels[b][c].operation << " " << graphs[a].levels[b][c].result << " ";
                }
                cout << endl;
            }
            cout << endl;
        }

        // float avg = 0;
        // for (int j = 0; j < number_of_treshholds; j++) {
        //     if (graphs[j].old_level[0].result < 1) {
        //         float r = floor(255 * graphs[j].old_level[0].result);
        //         avg += treshHolds[j].score[r];
        //     }
        // }
        // cout << avg/number_of_treshholds << endl;
    }

    return 0;
}
