#include <iostream>
#include <vector>

std::vector<int> merge(std::vector<int> v1, std::vector<int> v2){
    std::vector<int> result;
    size_t i=0,j=0;
    while(i<v1.size() && j<v2.size()){
        if(v1[i]<v2[j]){
            result.push_back(v1[i]);
            i++;
        }else{
            result.push_back(v2[j]);
            j++;
        }
    }
    while(i<v1.size()){
        result.push_back(v1[i]);
        i++;
    }
    while(j<v2.size()){
        result.push_back(v2[j]);
        j++;
    }
    return result;
}

std::vector<int> mergesort(std::vector<int> vec){
    if(vec.size()<=1) return vec;
    int middle=vec.size()/2;
    std::vector<int> v1(vec.begin(),vec.begin()+middle);
    std::vector<int> v2(vec.begin()+middle,vec.end());
    v1=mergesort(v1);
    v2=mergesort(v2);
    return merge(v1,v2);
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
    std::vector<int> v1={12,23,10,3,98,7,5,0};
    print(v1);
    v1=mergesort(v1);
    print(v1);

    return 0;
}