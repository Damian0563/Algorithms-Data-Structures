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
        Ring(const Ring<T>& r){
            this->m_size=r.m_size;
            this->m_pos=r.m_pos;
            this->m_data=new T[r.m_size];
            for(int i=0;i<r.m_size;i++){
                this->m_data[i]=r.m_data[i];
            }
        }
        Ring(Ring<T>&& r){
            this->m_size=r.m_size;
            this->m_pos=r.m_pos;
            this->m_data=new T[r.m_size];
            for(int i=0;i<r.m_size;i++){
                this->m_data[i]=r.m_data[i];
            }
            r.m_size=0;
            r.m_pos=0;
            delete[] r.m_data;
        }
        Ring& operator=(Ring<T> r){
            if(*this==&r) return *this;
            this->m_size=r.m_size;
            this->m_pos=r.m_pos;
            this->m_data=new T[r.m_size];
            for(int i=0;i<r.m_size;i++){
                this->m_data[i]=r.m_data[i];
            }
            r.m_size=0;
            r.m_pos=0;
            delete[] r.m_data;
            return *this;
        }
        ~Ring(){
            delete[] this->m_data;
            this->m_size=0;
            this->m_pos=0;
        }
        void add(const T element){
            this->m_data[m_pos]=element;
            this->m_pos++;
            //std::cout<<element<<m_pos<<"\n";
            if(this->m_pos==this->m_size) this->m_pos=0;
        }
        bool full(){
            const T default_value=T();
            int acc_size=0;
            for(int i=0;i<this->m_size;i++){
                if(this->m_data[i]!=default_value) acc_size++;
            }
            return acc_size==this->m_size;
        }
        void remove(){
            const T default_value=T();
            if(this->full()) this->m_data[this->m_pos]=default_value;
            else{
                if(this->m_pos+1==this->m_size) this->m_data[0]=default_value;
                else this->m_data[this->m_pos+1]=default_value;
            }
        }
        T peek(){return this->m_pos+1!=this->m_size? this->m_data[this->m_pos+1]:this->m_data[0];}
        friend std::ostream& operator<<(std::ostream& os, const Ring<T>& ring) {
            os<<"[";
            for(int i=ring.m_pos;i<ring.m_size;++i){
                os<<ring.m_data[i];
                if(i!=ring.m_size-1 || ring.m_pos>0) os<<" |";
            }
            for(int i=0; i<ring.m_pos;++i){
                os<<ring.m_data[i];
                if(i!=ring.m_pos-1) os<<" |";
            }
            os<<"]";
            return os;
        }
};


int main(){
    Ring<char> ring(4);
    ring.add('A');
    ring.add('G');
    ring.add('Q');
    std::cout<<"Nearly full: "<<ring<<"\n";
    ring.add('B');
    std::cout<<"Full: "<<ring<<"\n";
    ring.add('X');
    std::cout<<"After overflowing with X: "<<ring<<"\n";
    ring.add('Y');
    std::cout<<"After yet another overflow with Y: "<<ring<<"\n";
    ring.remove();
    std::cout<<"After removal: "<<ring<<"\n";
    ring.remove();
    std::cout<<"After yet another removal: "<<ring<<"\n";
    Ring<char> copyRing(ring);
    std::cout<<"Copy constructed ring: "<<copyRing<<"\n";
    Ring<char> movRing(std::move(ring));
    std::cout<<"Ring move-constructed: "<<movRing<<" , Initial ring: "<<ring<<"\n";
    Ring<char> newRing=std::move(movRing);
    std::cout<<"Standard std::move on the previous ring: "<<newRing<<"\n";
}