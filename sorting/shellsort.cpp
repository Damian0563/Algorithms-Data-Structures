#include <iostream>
#include <vector>

void shellsort(std::vector<int>& vec){
    std::vector<int> steps={5, 3, 1};
    int n=vec.size();
    for(auto& gap : steps){
        for(int i=gap;i<n;i++) {
            int temp=vec[i];
            int j=i;
            while(j>=gap && vec[j-gap]>temp) {
                vec[j]=vec[j-gap];
                j-=gap;
            }
            vec[j]=temp;
        }
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
    std::vector<int> v1={10,23,14,11,6,32,22,0,9,8,7,5};
    print(v1);
    shellsort(v1);
    print(v1);

    return 0;
}