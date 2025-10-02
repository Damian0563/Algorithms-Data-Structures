#include <iostream>
#include <vector>
#include <queue>


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

void heapify(std::vector<int>& arr, int n, int i) {
    int largest=i;
    int left=2*i+1;     
    int right=2*i+2;  
    if(left<n && arr[left]>arr[largest])
        largest=left;
    if(right<n && arr[right]>arr[largest])
        largest=right;
    if(largest!=i){
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapsort(std::vector<int>& arr) {
    int n=arr.size();
    for(int i=n/2-1;i>=0;i--) heapify(arr,n,i);
    for(int i=n-1;i>0;i--){
        std::swap(arr[0],arr[i]);
        heapify(arr,i,0);         
    }
}

int main(){
    std::vector<int> v1={10,23,5,7,2,17,0,8};
    print(v1);
    heapsort(v1);
    print(v1);
    return 0;
}