#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

typedef struct {
    std::string byr;
    std::string iyr;
    std::string eyr;
    std::string hgt;
    std::string hcl;
    std::string ecl;
    std::string pid;
    std::string cid; 
}passport_data;

typedef struct {
    passport_data data;
    bool valid;
}passport;


bool check_valid(passport_data data){
    if(data.byr.empty() || data.iyr.empty() || data.eyr.empty() || data.hgt.empty() || data.hcl.empty() || data.ecl.empty() || data.pid.empty() ){
        return false;
    } 
    return true;
}

bool check_valid_strict(passport_data data){
    //Check if it has the necessar
    if(data.byr.empty() || data.iyr.empty() || data.eyr.empty() || data.hgt.empty() || data.hcl.empty() || data.ecl.empty() || data.pid.empty() ){
        return false;
    }
    
    //Check byr, iyr and eyr
    int byr , iyr, eyr;
    byr = std::stoi(data.byr);
    iyr = std::stoi(data.iyr);
    eyr = std::stoi(data.eyr);
    if(byr > 2002 || byr < 1920) return false;
    if(iyr > 2020 || iyr < 2010) return false;
    if(eyr > 2030 || eyr < 2020) return false;
    
    //Check height
    int hgt = std::stoi(data.hgt);
    if(data.hgt.find('c') != std::string::npos){
        if(hgt < 150 || hgt > 193) return false;
    }
    else{
        if(hgt < 59 || hgt > 76) return false;
    }
    
    //Check hair color
    if(data.hcl[0] != '#') return false;
    for(int i = 1; i < data.hcl.size(); i++){
        if(std::isalnum(data.hcl[i]) == 0 || (data.hcl[i] > 'f' && data.hcl[i] < 'z')) return false;
    }
    
    //Check eye color
    std::vector<std::string> eye_colors_list = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    for(int i = 0; i < eye_colors_list.size(); i++){
        if(std::find(std::begin(eye_colors_list), std::end(eye_colors_list), data.ecl) == std::end(eye_colors_list)) return false;
    }
    
    //Check passport id
    if(data.pid.size() != 9 || (!std::all_of(data.pid.begin(), data.pid.end(), ::isdigit)) ) return false;
    
    return true;
}

std::vector<passport> read_input(const char* filename){
    int counter = 0;
    std::vector<std::string> list_of_data = {"byr", "iyr", "eyr", "hgt", "hcl","ecl", "pid", "cid"};
    std::vector<passport> data;
    std::ifstream input(filename);
    while(!input.eof()){
        passport aux;
        //get every word sequentually to a vector
        std::string line = "GETS_IGNORED";
        std::vector<std::string> passport_words;
        while(line.size() > 3){
            std::getline(input, line);
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream converter(line);
            std::string word;
            while(converter >> word){
                passport_words.push_back(word);
            }
        }
        
        //parse line
        for(int i = 0; i < passport_words.size(); i+=2){
            int info_idx = -1;
            for(int j = 0; j < list_of_data.size(); j++){
                if(passport_words[i].find(list_of_data[j]) != std::string::npos){
                    info_idx = j;
                    break;
                }
            }
            switch (info_idx){
            case 0:
                aux.data.byr = passport_words[i+1]; 
                break;
            case 1:
                aux.data.iyr = passport_words[i+1]; 
                break;
            case 2:
                aux.data.eyr = passport_words[i+1]; 
                break;
            case 3:
                aux.data.hgt = passport_words[i+1]; 
                break;
            case 4:
                aux.data.hcl = passport_words[i+1]; 
                break;
            case 5:
                aux.data.ecl = passport_words[i+1]; 
                break;
            case 6:
                aux.data.pid = passport_words[i+1]; 
                break;
            case 7:
                aux.data.cid = passport_words[i+1]; 
                break;
            default:
                break;
            }
        }

        //insert data
        aux.valid = check_valid(aux.data);
        data.push_back(aux);
    }
    return data;
}

int count_valid(std::vector<passport> data){
    int counter = 0;
    for(auto item: data){
        if(item.valid) counter++;
    }
    return counter;
}

int main(){
    std::vector<passport> file_data = read_input("../input/day04");
    std::cout << "Valid by normal rules: " << count_valid(file_data) << std::endl;
    for(int i = 0; i < file_data.size(); i++){
        file_data[i].valid = check_valid_strict(file_data[i].data);
    }
    std::cout << "Valid by strict rules: " <<  count_valid(file_data) << std::endl; 
}