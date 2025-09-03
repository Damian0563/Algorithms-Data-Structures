#include <iostream>
#include <string>
template <typename T>
class Ring{
    private:
        int m_pos;
        T* m_data;
        int m_size;
    public:
        Ring(int size){
            if(size>0){
                this->m_size=size;
                this->m_pos=0;
                this->m_data=new T[m_size];
                T default_val = T();
                for(int i=0;i<this->m_size;i++) this->m_data[i]=default_val;
            }else throw std::out_of_range("Invalid ring size initialization");
        }
        ~Ring(){
            delete[] this->m_data;
            this->m_size=0;
            this->m_pos=0;
        }
        T add(const T element){
            this->m_data[m_pos]=element;
            this->m_pos++;
            if(this->m_pos==this->m_size) this->m_pos=0;
            return this->m_data[m_pos];
        }
        friend std::ostream& operator<<(std::ostream& os,const Ring<T>& ring){
            int temp=ring.m_pos-1;
            bool flag=true;
            os<<"[";
            const T default_val=T();
            while(temp<ring.m_size){
                if(ring.m_data[temp]!=default_val){
                    os<<ring.m_data[temp];
                    if(flag){
                        os<<"   ";
                        flag=false;
                    }
                }
                temp++;
            }
            for(int i=0;i<ring.m_pos-1;i++){
                if(ring.m_data[i]!=default_val){
                    os<<"   ";
                    os<<ring.m_data[i];
                }
            }
            os<<"]";
            return os;
        }
};


int main(){
    Ring<char> ring(4);
    ring.add('A');
    std::cout<<ring<<"\n";
}