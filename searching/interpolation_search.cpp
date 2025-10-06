#include <vector>
#include <iostream>

int interpolation_search(std::vector<int> vec, int subject){
    int low=0;
    int high=vec.size()-1;
    int middle;
    while(vec[low]<=subject && vec[high]>=subject && vec[low]<vec[high]){
        middle=low+((subject-vec[low])*(high-low)/(vec[high]-vec[low]));
        if(vec[middle]<subject) low=middle+1;
        else if(vec[middle]>subject) high=middle-1;
        else return middle;
    }
    if(subject==vec[low]) return low;
    else return -1;
}

int main(){
    std::vector<int> v1={1,3,5,6,8,9,13,14,19,21};
    std::cout<<interpolation_search(v1,9);
    return 0;
}