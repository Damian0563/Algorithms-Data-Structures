#include <iostream>
#include <vector>

std::vector<int> quicksort(std::vector<int> vec) {
    if(vec.size()<=1) return vec;
    int pivotIndex=vec.size()/2;
    int pivot=vec[pivotIndex];
    std::vector<int> left;
    std::vector<int> right;
    for(int i=0;i<vec.size();i++){
        if(i==pivotIndex) continue;
        if(vec[i]<pivot) left.push_back(vec[i]);
        else right.push_back(vec[i]);
    }
    left=quicksort(left);
    right=quicksort(right);
    left.push_back(pivot);
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

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

int main(){
    std::vector<int> v1={4,5,7,3,5,7,20,1,9};
    print(v1);
    v1=quicksort(v1);
    print(v1);

    return 0;
}