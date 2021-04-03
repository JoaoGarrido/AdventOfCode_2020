#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <locale>

typedef struct {
    std::string name;
    int number;
}bag;

typedef struct {
    std::string name;
    std::vector<bag> bags;
    bool holds_shiny;
}bag_rule;

std::vector<bag_rule> read_input(const char filename[126]){
    std::vector<bag_rule> rules;
    std::ifstream input(filename);
    std::string aux;
    std::string bag_name;

    for (std::string line; std::getline(input, line); ){
        std::istringstream line_stream(line);
        
        //Read bag name
        line_stream >> bag_name;
        line_stream >> aux;
        bag_name.append(" ");
        bag_name.append(aux);
        //std::cout << bag_name << std::endl;

        //Add to end of bag_rule vector
        bag_rule i_bag_rule = {bag_name};
        i_bag_rule.holds_shiny = false;
        rules.push_back(i_bag_rule);

        //OTHER OPTION: Find element of bag_rule vector with the desired bag_name(add to the list if it doesn't exist)
        /*
        std::vector<bag_rule>::iterator add_rules_el;
        auto el = std::find_if(rules.begin(), rules.end(), [bag_name](const bag_rule& b){return b.name == bag_name;});
        if(el == rules.end()){
            bag_rule i_bag_rule = {bag_name};
            rules.push_back(i_bag_rule);
            add_rules_el = rules.end();
        }
        else{
            add_rules_el = el;
        }
        */
        
        //Read rules
        std::locale loc;
        line_stream >> aux >> aux;
        while(1){
            bag new_bag;
            line_stream >> aux;
            //std::cout << aux << ' ';
            if(aux == "no"){
                //std::cout << std::endl << std::endl;
            }
            else{
                new_bag.number = stoi(aux);
                line_stream >> bag_name;
                line_stream >> aux;
                bag_name.append(" ");
                bag_name.append(aux);
                //std::cout << bag_name << std::endl << std::endl;
                new_bag.name = bag_name;
                if(bag_name == "shiny gold") i_bag_rule.holds_shiny = true;
                rules.back().bags.push_back(new_bag);
            }
            line_stream >> aux;
            if(line_stream.eof() || aux == "other") break;
        }
        
    }

    return rules;
}

//To do:
int n_bag_color_contain_shiny_gold_bag(std::vector<bag_rule> rules){
    int diff_bag_colors = 0;
    for(auto some_bag: rules){
        for(auto bag_inside: some_bag.bags){

        }
    }
    //std::find_if(rules.begin(), rules.end(), [])
    return diff_bag_colors;
}

int main(){
    std::vector<bag_rule> file_data = read_input("../input/day07");
    std::cout << "Different bag colors that can have a shiny gold bag inside: " << n_bag_color_contain_shiny_gold_bag(file_data) << std::endl;
}