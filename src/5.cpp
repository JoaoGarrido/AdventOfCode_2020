#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

#define PART_1_MULT 8

typedef struct {
    int row;
    int column;
    int id;
}seat;

//true if upper half, false if lower half
constexpr int split_range_in_half(int min, int max, bool uppper_half){
    return min+(max-min+uppper_half*1)/2;
}

constexpr int get_seat_id(int row, int column, int multiplier){
    return row * multiplier + column;
}

seat get_seat_info(std::string seat_text){
    seat current;
    int row_range[2] = {0,127};
    int column_range[2] = {0,7};
    for(int i = 0; i < seat_text.size(); i++){
        char c = seat_text[i];
        if(i == 6){         //row selection
            (c == 'F') ? current.row = row_range[0] : current.row = row_range[1];
        }
        else if(i == 9){    //col selection
            (c == 'L') ? current.column = column_range[0] : current.column = column_range[1];
        }
        else if(i < 6){     //row division
            (c == 'F') ? row_range[1] = split_range_in_half(row_range[0], row_range[1], false) : row_range[0] = split_range_in_half(row_range[0], row_range[1], true);  
        }
        else{               //col division
            (c == 'L') ? column_range[1] = split_range_in_half(column_range[0], column_range[1], false) : column_range[0] = split_range_in_half(column_range[0], column_range[1], true);
        }
    }
    current.id = get_seat_id(current.row, current.column, PART_1_MULT);
    return current;
}

std::vector<std::string> read_input(const char filename[126]){
    std::ifstream input(filename);
    std::string word;
    std::vector<std::string> file_data;
    while(input >> word){
        file_data.push_back(word);
    }
    return file_data;
}

int find_my_seat(std::vector<seat> seat_info){
    //Find max and min seat ids
    int min = 2048;
    int max = 0;
    for(auto el: seat_info){
        if(el.id > max) max = el.id;
        if(el.id < min) min = el.id;
    }
    //Sum all elements in seat_info
    int el_sum = std::accumulate(seat_info.begin(), seat_info.end(), 0, 
        [](int sum, const seat& curr){ return sum + curr.id;});
    //Sum all elements from min to max (incl)
    int range_sum = 0;
    for(int i = min; i <= max; i++){
        range_sum += i;
    }
    //Calculate seat missing between min and max
    return (range_sum - el_sum);
}

int main(){
    std::vector<std::string> file_data = read_input("../input/day05");
    std::vector<seat> seat_info;
    for(auto el: file_data){
        seat_info.push_back(get_seat_info(el));
    }
    int highest_seat_id = [](std::vector<seat> info){ int max = 0; for(auto el: info) if(el.id > max) max = el.id; return max;}(seat_info);
    std::cout << "Highest seat id: " << highest_seat_id << std::endl; 
    std::cout << "My seat is " << find_my_seat(seat_info) << std::endl; 
}