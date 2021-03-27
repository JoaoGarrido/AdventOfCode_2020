#include <iostream>
#include <fstream>
#include <vector>

typedef std::vector<std::string> group;


class GroupList{
    private:
        std::ifstream input;
        std::vector<group> data;

        enum return_codes_t {end_of_file = 0, error_reading = 1, next_group = 2};

        return_codes_t read_group();
    
    public:
        void read_input(const char filename[126]);
        void print();
        std::vector<group> get_data(){ return data;};
};

void GroupList::print(){
    std::cout << "###   Data    ###" << std::endl;
    for(auto el: data){
        for(auto answer: el){
            std::cout << answer << std::endl;
        }
        std::cout << std::endl;
    } 
}

GroupList::return_codes_t GroupList::read_group(){
    std::string aux = "TEST_STRING";
    return_codes_t return_code;
    group insert_group;
    while(1){
        std::getline(input, aux);
        if(input.eof()){
            return_code = end_of_file;
            break;
        }
        else if(aux[0] < '\n'){
            return_code = next_group;
            break;
        }
        else insert_group.push_back(aux);
    }
    data.push_back(insert_group);
    return return_code;
}

void GroupList::read_input(const char filename[126]){
    input = std::ifstream(filename);
    return_codes_t return_code;
    do{
        return_code = read_group();
    }while(next_group == return_code);
}

int count_group_rule_1(group curr_group){
    std::string list_of_char;
    for(auto person: curr_group){
        for(auto c: person){
            if(list_of_char.find(c) == std::string::npos){
                list_of_char.push_back(c);
            }
        }
    }
    return list_of_char.size();
}

int count_group_rule_2(group curr_group){
    std::string list_of_char = curr_group[0];
    int idx = 0;
    for(auto person: curr_group){
        std::string list_to_remove;
        for(auto c: list_of_char){
            if(person.find(c) == std::string::npos){
                list_to_remove.push_back(c);
            }
        }
        for(auto c: list_to_remove){
            list_of_char.erase(list_of_char.find(c), 1);
        }
    }
    return list_of_char.size();
}

int main(){
    GroupList groupList;
    groupList.read_input("../input/day06");
    int sum_count_1 = 0, sum_count_2 = 0; 
    for(auto el: groupList.get_data()){
        sum_count_1 += count_group_rule_1(el);
        sum_count_2 += count_group_rule_2(el);
    }
    std::cout << "Rule 1: " << sum_count_1 << " | Rule 2: " << sum_count_2 << std::endl;
}