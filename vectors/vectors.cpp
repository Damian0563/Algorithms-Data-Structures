#include <iostream>
#include <vector>

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
    ~Vector(){
      delete[] data;
    }
    void increase_capacity(){

    }
    void push_back(const T& element){
      if(this->size >= this->capacity) increase_capacity();
      this->data[size]=element;
      size++;
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
};

int main(){
  Vector<int> test(10); 
  try{
    test.push_back(9);
    test.push_back(21);
    std::cout<<test;
  }catch(const std::exception& e){
    std::cerr << "Exception: " << e.what() << "\n";
  }



  return 0;
}
