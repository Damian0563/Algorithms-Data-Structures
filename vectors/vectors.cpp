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
    Vector(const Vector<T>&& other) noexcept  {
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
      if(index >= 0 && static_cast<unsigned int>(index) < this->size){
        return this->data[index];
      }
      throw std::out_of_range("Index out of range");
    }
};


unsigned int binary_search(const std::vector<int>& v,int element){
  int left=*v.begin();
  int right=*v.end();
  int middle;
  while(left<right){
    middle=(left+right)/2;
    if(v.at(middle==element)) return middle;
  }
  return -1;
}

std::vector<int> get_all_primes(){

}

std::vector<int,int> two_sum(){
  
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
    std::cout<<test;
  }catch(const std::exception& e){
    std::cerr << "Exception: " << e.what() << "\n";
  }
  //sample exercises using <vector>


  return 0;
}
