#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

std::vector<std::vector<bool>> read_input(const char* filename){
    std::vector<std::vector<bool>> file_data;
    std::ifstream input("../input/day03");
    char aux[125];
    int l = 0;
    bool first_row = true;
    while(!input.eof()){
        input.getline(aux, 100);
        if(first_row){
            l = strlen(aux);
            first_row = false;
        }
        std::vector<bool> line;
        for(int i = 0; i < l; i++){
            if(aux[i] == '.'){
                line.push_back(false);
            }
            else{
                line.push_back(true);
            }
        }
        if(line.size() == l){
            file_data.push_back(line);
        }
    }
    return file_data;
}

int count_trees(std::vector<std::vector<bool>> file_data, int n_col, int n_right, int n_down){
    //0  1  2  3
    //0->3->6->9
    int tree_counter = 0;
    int jump = 0;
    for(int i = n_down; i < file_data.size(); i+=n_down){
        jump++;
        int current_x = (jump*n_right)%n_col;
        if(file_data[i][current_x]){
            tree_counter++;
        }
    }    
    return tree_counter;
}

int main(){

    std::vector<std::vector<bool>> file_data = read_input("../input/day03");
    
    int l = file_data[0].size();

    std::vector<int> results;
    int final_result = 1;
    results.push_back(count_trees(file_data, l, 1, 1));
    results.push_back(count_trees(file_data, l, 3, 1));
    results.push_back(count_trees(file_data, l, 5, 1));
    results.push_back(count_trees(file_data, l, 7, 1));
    results.push_back(count_trees(file_data, l, 1, 2));
    for(int i = 0; i < results.size(); i++){
        final_result *= results[i]; 
        std::cout << results[i] << std::endl;
    }
    std::cout << final_result << std::endl;    
}