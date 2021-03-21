#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

const int TARGET = 2020;

int find_pair(std::vector<int> data, int target){
    for(auto i = 0; i < data.size(); i++){
        auto p = std::find(data.begin(), data.end(), target-data[i]);
        auto j = p - data.begin();
        if(p != data.end() && j != i){
            auto value = data[j]*data[i];
            std::cout << "Two value sum" << std::endl;
            std::cout << data[i] << '+' << data[j] << '=' << target << std::endl;
            std::cout << data[i] << '*' << data[j] << '=' << value << std::endl;
            return value;
        }
    }
    return -1;
}

int find_trio(std::vector<int> data, int target){
    for(auto i = 0; i < data.size(); i++){
        for(auto j = i + 1; j < data.size(); j++){            
            auto p = std::find(data.begin(), data.end(), target-data[i]-data[j]);
            auto k = p - data.begin();
            if(p != data.end() && k != i && k != j){
                auto value = data[j]*data[i]*data[k];
                std::cout << "Three value sum" << std::endl;
                std::cout << data[i] << '+' << data[j] << '+' << data[k] << '=' << target << std::endl;
                std::cout << data[i] << '*' << data[j] << '*' << data[k] << '=' << value << std::endl;
                return value;
            }
        }
    }
    return -1;
}

int main(){
    std::ifstream input("../input/day01"); //opens file
    std::vector<int>  data((std::istream_iterator<int>(input)), std::istream_iterator<int>()); //reads data from file
    std::sort(data.begin(), data.end()); //sorts the data. Needed?

    auto result_pair = find_pair(data, TARGET);
    auto result_trio = find_trio(data, TARGET);
    return 0;
}