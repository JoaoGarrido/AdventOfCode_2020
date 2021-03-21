#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

typedef struct {
    int min;
    int max;
    char letter;
    std::string password;
}password_info;


int validate_password_rule_1(password_info data){
    size_t counter = std::count(data.password.begin(), data.password.end(), data.letter);
    if(counter >= data.min && counter <= data.max){
        return 1;
    }
    else{
        return 0;
    }
}

int validate_password_rule_2(password_info data){
    auto counter = (data.password[data.min - 1] == data.letter) + (data.password[data.max - 1] == data.letter);
    if(counter == 1){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    std::ifstream input("../input/day02");
    std::vector<password_info> file_data;
    
    password_info aux; 
    char _thrash;
    while (input >> aux.min >> _thrash >> aux.max >> aux.letter >> _thrash >> aux.password){
        file_data.push_back(aux);
    }

    auto password_counter_rule_1 = 0;
    auto password_counter_rule_2 = 0;
    for(auto i = 0; i < file_data.size(); i++){
        password_counter_rule_1 += validate_password_rule_1(file_data[i]);
        password_counter_rule_2 += validate_password_rule_2(file_data[i]);
    }
    std::cout << password_counter_rule_1 << '/' << file_data.size() << std::endl;
    std::cout << password_counter_rule_2 << '/' << file_data.size() << std::endl;
}