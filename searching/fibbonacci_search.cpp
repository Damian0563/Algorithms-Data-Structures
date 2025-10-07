#include <iostream>
#include <vector>

std::vector<int> get_fibb_nums(int n) {
    std::vector<int> fibbs={0,1};
    if(n<=0) return fibbs;
    while(fibbs.back()<n){
        fibbs.push_back(fibbs[fibbs.size()-1] + fibbs[fibbs.size()-2]);
    }
    return fibbs;
}

int fibbonacci_search(const std::vector<int>& vec, int subject) {
    if(vec.empty()) return -1;
    std::vector<int> fibbs=get_fibb_nums(vec.size());
    int k=fibbs.size()-1;
    int offset=-1;
    while(k>1){
        int i=std::min(offset+fibbs[k-1],static_cast<int>(vec.size())-1);
        if(vec[i]==subject){
            return i;
        }else if(vec[i]>subject){
            k-=2;
        }else{
            offset=i;
            k-=1;
        }
    }
    if(k==1 && offset+1<vec.size() && vec[offset+1]==subject){
        return offset+1;
    }
    return -1;
}

int main(){
    std::vector<int> v1={1,3,6,7,9,11,12,14,17,21};
    std::cout<<fibbonacci_search(v1,9);

    return 0;
}