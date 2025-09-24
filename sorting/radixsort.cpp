#include <iostream>
#include <vector>
#include <algorithm>

void radixsort(std::vector<int>& vec){
    if(vec.empty()) return;
    int max_num=*max_element(vec.begin(), vec.end());
    int decimal=1;
    while(max_num/decimal>0){
        std::vector<std::vector<int>> buckets(10);
        for(auto& itr : vec){
            int digit=(itr/decimal)%10;
            buckets[digit].push_back(itr);
        }
        int idx=0;
        for(int i=0;i<10;++i) {
            for(auto& num : buckets[i]) {
                vec[idx++]=num;
            }
        }
        decimal*=10;
    }
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
    std::vector<int> v1={11,20,3,31,100,231,901,606,9};
    print(v1);
    radixsort(v1);
    print(v1);
    return 0;
}