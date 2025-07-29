#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>

template <typename T>
class Vector{
  private:
    unsigned int capacity;
    T* data;
    unsigned int size;
  public:
    Vector(const unsigned int capacity=5){
      this->capacity=capacity;
      this->data=new T[capacity];
      this->size=0;
    }
    Vector(const Vector<T>& v){
      this->size=v.size;
      this->capacity=v.capacity;
      this->data=new T[capacity];
      for(int i=0;i<this->size;i++){
        this->data[i]=v.data[i];
      }
    }
    Vector(Vector<T>&& other) noexcept  {
      this->data=other.data;
      this->capacity=other.capacity;
      this->size=other.size;

      other.data=nullptr;
      other.capacity=0;
      other.size=0;
    }
    ~Vector(){
      delete[] data;
    }
    Vector& operator=(Vector<T>&& other) noexcept {
      if (this != &other){
          delete[] this->data;
          this->data = other.data;
          this->capacity = other.capacity;
          this->size = other.size;
          other.data = nullptr;
          other.capacity = 0;
          other.size = 0;
      }
      return *this;
    }
    Vector& operator=(const Vector<T>& v){
      if(this!=&v){
        delete[] this->data;
        this->size=v.size;
        this->capacity=v.capacity;
        this->data=new T[capacity];
        for(int i=0;i<this->size;i++){
          this->data[i]=v.data[i];
        }
      }
      return *this;
    }
    void increase_capacity(){
      T* new_data = nullptr;
      int new_capacity=2*this->capacity;
      if(new_capacity > 0){
        new_data = new T[new_capacity];
      }
      for (unsigned int i = 0; i < size; ++i) {
          new_data[i] = data[i];
      }
      delete[] this->data;
      this->data = new_data;
      this->capacity = new_capacity;
    }
    void push_back(const T& element){
      if(this->size >= this->capacity) increase_capacity();
      this->data[size]=element;
      size++;
    }
    void remove(const T& element){
      bool removed=false;
      for(int i=0;i<this->size;i++){
        if(this->data[i]==element){
          removed=true;
          for(int j=i;j<this->size-1;j++){
            this->data[j]=this->data[j+1];
          }
        }
      }
      if(removed) this->size--;
    }
    friend bool operator==(const Vector<T>& v1, const Vector<T>& v2){
      if(v1.size==v2.size){
        for(int i=0;i<v1.size;i++){
          if(v1.data[i]!=v2.data[i]) return false;
        }
        return true;
      } 
      return false;
    }
    void pop(){
      if(this->size>0) this->size--;
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v){
      if(!v.size){
        os<<"Vector empty!";
        return os;
      }
      os<<"[";
      for(int i=0;i<v.size;i++){
        if(i<v.size-1) os<<v.data[i]<<",";
        else os<<v.data[i];
      }
      os<<"]";
      return os;
    }
    T operator[](int index) const {
      if(index>=0 && index<this->size){
        return this->data[index];
      }
      throw std::out_of_range("Index out of range");
    }
};


int binary_search(const std::vector<int>& v,int element){
  int left=0;
  int right=v.size()-1;
  int middle;
  while(left<right){
    middle=(left+right)/2;
    if(v.at(middle)==element) return middle;
    else if(v.at(middle)<element){
      left=middle+1;
    }else{
      right=middle-1;     
    }
  }
  return -1;
}


bool check_prime(int number){
  if(number<2) return false;
  if(number==2) return true;
  for(int i=2;i<(number/2)+1;i++){
    if(number%i==0) return false;
  }
  return true;
}

std::vector<int> get_all_primes(const std::vector<int> v){
  std::vector<int> res={};
  for(auto& num: v){
    if(check_prime(num)) res.push_back(num); 
  }
  return res;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
  os<<"[";
  for(int i=0;i<v.size();i++){
    if(i<v.size()-1) os<<v[i]<<",";
    else os<<v[i];
  }
  os<<"]";
return os;
}

bool check_presence(const std::vector<std::vector<int>> v, const std::vector<int> pair){
  for(auto& duo : v){
    if(duo.at(0)==pair.at(0) && duo.at(1)==pair.at(1)) return true;
  }
  return false;
}

std::vector<std::vector<int>> two_sum(const std::vector<int> v,int sum){
  std::vector<std::vector<int>> res={};
  for(int i=0;i<v.size();i++){
    if(find(v.begin(),v.end(),sum-v[i])!=v.end()){
      if(v[i]>sum-v[i]){
        if(!check_presence(res,{v[i],sum-v[i]})) res.push_back({v[i],sum-v[i]});
      }else{
        if(!check_presence(res,{sum-v[i],v[i]})) res.push_back({sum-v[i],v[i]});
      }
    }
  }
  return res;
}

int main(){
  //implementation and simple tests.
  Vector<int> test(10);
  Vector<int> copy;
  try{
    test.push_back(9);
    test.push_back(21);
    test.push_back(10);
    test.push_back(4);
    test.push_back(1);
    test.push_back(909);
    test.push_back(27);
    std::cout<<test<<"\n";
    copy=test;
    test.push_back(45);
    std::cout<<copy<<"\n";
    std::cout<<test<<"\n";
    test.remove(909);
    std::cout<<test<<"\n";
    std::cout<<(test==copy)<<"\n";
    test.pop();
    std::cout<<test<<"\n";
    std::cout<<test[2]<<"\n";
  }catch(const std::exception& e){
    std::cerr << "Exception: " << e.what() << "\n";
  }
  //sample exercises using <vector>
  std::vector<int> v1={1,3,6,9,10,11,13,21,73};
  std::vector<int> v2={15,8,16,12,11,13,9,0};
  std::cout<<"Binary searching v1 for 3: "<<binary_search(v1,3)<<"\n";
  std::cout<<"Binary searching v1 for 18: "<<binary_search(v1,18)<<"\n";
  std::cout<<"All primes within v1: "<<get_all_primes(v1)<<"\n";
  std::cout<<"Two sum for v2-24: "<<"\n";
  for(std::vector<int> v: two_sum(v2,24)){
    std::cout<<"\t"<<v<<"\n";
  }

  return 0;
}
