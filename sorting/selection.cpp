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


int get_min(const std::vector<int>& vec, int start){
    int min=start;
    for(int i=start+1;i<vec.size();i++){
        if(vec.at(i)<vec.at(min)) min=i;
    }
    return min;
}

void selection_sort(std::vector<int>& vec){
    if(vec.size()<=1) return;
    int temp;
    for(int i=0;i<vec.size();i++){
        int min_idx=get_min(vec,i);
        if(i!=min_idx){
            temp=vec.at(i);
            vec.at(i)=vec.at(min_idx);
            vec.at(min_idx)=temp;
        }
    }
}

int main(){
    std::vector<int> v1={22,10,3,8,19,16,5,0};
    print(v1);
    selection_sort(v1);
    print(v1);

    return 0;
}