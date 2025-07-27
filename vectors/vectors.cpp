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
    Vector(const Vector<T>& v){
      this->size=v.size;
      this->capacity=v.capacity;
      this->data=new T[capacity];
      for(int i=0;i<this->size;i++){
        this->data[i]=v.data[i];
      }
    }
    ~Vector(){
      delete[] data;
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
      T* new_data = new T[this->capacity];
      bool removed = false;
      unsigned int j = 0;
      for (unsigned int i = 0; i < this->size; i++) {
        if (!removed && this->data[i] == element) {
          removed = true;
          continue;
        }
        new_data[j++] = this->data[i];
      }
      if (removed) {
        this->size--;
      }
      delete[] this->data;
      this->data = new_data;
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
    std::cout<<test;
  }catch(const std::exception& e){
    std::cerr << "Exception: " << e.what() << "\n";
  }



  return 0;
}
