#include <vector>
#include <iostream>

int binary_search(std::vector<int>& vec,const int subject){
    int right=vec.size();
    int left=0;
    int middle;
    while(left<right){
        middle=(left+right)/2;
        if(middle==subject) return middle;
        else{
            if(vec[middle]<subject) left=middle+1;
            else right=middle-1;
        }
    }
    return left;
}

int main(){
    std::vector<int> v1={2,5,9,11,14,18,21,23,26};
    std::cout<<binary_search(v1,11);
    return 0;
}