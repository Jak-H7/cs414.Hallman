//File: HallmanAsg3Q1.cpp
//Author: Jackson Hallman
//Student Num: 00102945
//Email: jhallma5@my.athens.edu

#include <iostream>
#include <functional>
#include <map>         

struct FunctionSwitch {
    
    std::map<int, std::function<void()>> funcMap;

    std::map<int, std::function<void()>> getMap() const {
        return funcMap;
    }

    void setMap(const std::map<int, std::function<void()>>& newMap) {
        funcMap = newMap;
    }

    void operator()(int key) {
        
        if (funcMap.find(key) != funcMap.end()) {
            funcMap[key]();  
        }
        else {
            std::cout << "Unknown value" << std::endl;
        }
    }
};


int main() {
    FunctionSwitch mySwitch;

    
    mySwitch.setMap({
        {1, []() { std::cout << "Value is 1" << std::endl; }},
        {2, []() { std::cout << "Value is 2" << std::endl; }},
        {3, []() { std::cout << "Value is 3" << std::endl; }},
        {4, []() { std::cout << "Value is 4" << std::endl; }}
        });

   
    mySwitch(1);  
    mySwitch(4);  
    mySwitch(0);  

    return 0;
}
