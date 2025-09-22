#include <iostream>
#include <vector>

void print(const std::vector<int>& vec){
    std::cout<<"[";
    bool first=true;
    for(auto& itr: vec){
        if(!first) std::cout<<",";
        std::cout<<itr;
        first=false;
    }
    std::cout<<"]"<<std::endl;
}

std::vector<int> insertion_sort(std::vector<int>& vec){
    int i=0;
    int j,temp;
    while(i<vec.size()){
        j=i;
        while(j>0 && vec.at(j-1)>vec.at(j)){
            temp=vec.at(j-1);
            vec.at(j-1)=vec.at(j);
            vec.at(j)=temp;
            j--;
        }
        i++;
    }
    return vec;
}

std::vector<int> bubble_sort(std::vector<int>& vec){
    int temp;
    for(int i=0;i<vec.size();i++){
        for(int j=0;j<vec.size();j++){
            if(vec.at(i)<vec.at(j)){
                temp=vec.at(j);
                vec.at(j)=vec.at(i);
                vec.at(i)=temp;
            }
        }
    }
    return vec;
}

int main(){
    std::cout<<"Insertion sort: "<<"\n";
    std::vector<int> v1={2,5,1,39,4,23,0,7};
    print(v1);
    v1=insertion_sort(v1);
    print(v1);
    std::cout<<"Bubble sort: "<<"\n";
    std::vector<int> v2={9,3,0,34,22,5,6,3};
    print(v2);
    v2=bubble_sort(v2);
    print(v2);


    return 0;
}