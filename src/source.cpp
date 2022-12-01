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
                    Operation operation;
                    operation.index1 = -1;
                    operation.index2 = -1;
                    operation.label = "null";
                    operation.op = -1;
                    level0.push_back(Node(operation, f));
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
        // break;
    }
}

float m_h(float a, float b) {
    return 2 * a * b / (a + b);
}

float m_p(float a, float b) {
    return sqrt((a * a + b * b) / 2);
}

int main() {
    //the vector where all the data will be stored
    vector<TreshHolds> treshHolds;
    //the graph containing the result
    vector<Graph> graphs;
    // initialize random seed:
    srand (time(NULL));
    //the graph containing the best result
    Graph graphs_ideal;
    float calculated_score = 0;
    
    //function that reads data form files
    readInputData(treshHolds, graphs);
    //keeping the number of images to not call the function daily
    int number_of_treshholds = treshHolds.size();
    cout << "Number of treshholds: " << number_of_treshholds << endl;

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
    */

    // ? task1: calculate the score using the ideal treshholds
    float average_ideal_score = 0;
    for (int i = 0; i < number_of_treshholds; i++) {
        float r = floor(255 * treshHolds[i].idealThreshHold);
        average_ideal_score += treshHolds[i].score[r];
    }
    cout << "Ideal score: " << average_ideal_score/number_of_treshholds << endl;

    for (int i = 0; i < N; i++) {
        //the level at which all the graphs are currently at
        int level = 0;
        //generate random operations and number of operations
        int nr_max_op = 15;
        int nr_min_op = nr_max_op/2 + 1;
        int nr_op = rand() % (nr_max_op - nr_min_op) + nr_min_op;
        while(nr_op >= 1) {
            vector<Operation> operation_indexes;
            for(int j = 0; j < nr_op; j++) {
                Operation op;
                op.op = rand() % (operations.size() - 1);
                //generate 2 indexes for the numbers for the operations
                op.index1 = rand() % (nr_max_op - 1);
                op.index2 = rand() % (nr_max_op - 1);
                op.label = operations[op.op];
                operation_indexes.push_back(op);
            }
            
            //calculate the result for each image
            for(int j = 0; j < number_of_treshholds; j++) {
                vector<Node> level_vector;
                //go through each operation
                for(int k = 0; k < operation_indexes.size(); k++) {
                    Node node;
                    //verify if m_g
                    if(operations[operation_indexes[k].op] == "m_g") {
                        node.result = sqrt(graphs[j].levels[level][operation_indexes[k].index1].result *
                                graphs[j].levels[level][operation_indexes[k].index2].result);
                        node.operation = operation_indexes[k];
                    }
                    //verify if m_a
                    if(operations[operation_indexes[k].op] == "m_a") {
                        node.result = (graphs[j].levels[level][operation_indexes[k].index1].result +
                                    graphs[j].levels[level][operation_indexes[k].index2].result) / 2;
                        node.operation = operation_indexes[k];
                    }
                    //verify if m_h
                    if(operations[operation_indexes[k].op] == "m_h") {
                        node.result = m_h(graphs[j].levels[level][operation_indexes[k].index1].result,
                                    graphs[j].levels[level][operation_indexes[k].index2].result);
                        node.operation = operation_indexes[k];
                    }
                    //verify if m_p
                    if(operations[operation_indexes[k].op] == "m_p") {
                        node.result = m_p(graphs[j].levels[level][operation_indexes[k].index1].result,
                            graphs[j].levels[level][operation_indexes[k].index2].result);
                        node.operation = operation_indexes[k];
                    }
                    //verify if min
                    if(operations[operation_indexes[k].op] == "min") {
                        node.result = min(graphs[j].levels[level][operation_indexes[k].index1].result,
                                    graphs[j].levels[level][operation_indexes[k].index2].result);
                        node.operation = operation_indexes[k];
                    }
                    //verify if max
                    if(operations[operation_indexes[k].op] == "max") {
                        node.result = max(graphs[j].levels[level][operation_indexes[k].index1].result,
                                    graphs[j].levels[level][operation_indexes[k].index2].result);
                        node.operation = operation_indexes[k];
                    }
                    level_vector.push_back(node);
                }
                graphs[j].levels.push_back(level_vector);
            }
            level++;

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

        float avg = 0;
        for (int a = 0; a < number_of_treshholds; a++) {
            float r = floor(255 * graphs[a].levels[graphs[a].levels.size() - 1][0].result);
            avg += treshHolds[a].score[r];
        }

        if (graphs_ideal.levels.size() == 0) {
            calculated_score = avg/number_of_treshholds;
            graphs_ideal = graphs[0];
        } else {
            if (avg/number_of_treshholds > calculated_score) {
                calculated_score = avg/number_of_treshholds;
                graphs_ideal = graphs[0];
            }
        }

        for(int a = 0; a < number_of_treshholds; a++) {
            for(int b = 0; b < graphs[a].levels.size(); b++) {
                if(b > 0) {
                    graphs[a].levels.erase(graphs[a].levels.begin() + b);
                    b--;
                }
            }
        }
    }

    for(int b = 0; b < graphs_ideal.levels.size(); b++) {
        for(int c = 0; c < graphs_ideal.levels[b].size(); c++) {
            cout << "{" << graphs_ideal.levels[b][c].operation.label << " " << 
             graphs_ideal.levels[b][c].operation.index1 << " <-> " <<
             graphs_ideal.levels[b][c].operation.index2 << "} ";
        }
        cout << endl;
    }
    cout << calculated_score << endl;

    return 0;
}
