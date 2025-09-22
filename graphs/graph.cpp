#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>

template <typename T>
struct Vertex{
    T data;
    std::vector<Vertex<T>*> edges;
    Vertex(const T& data):data(data){}
};

template <typename T>
class Graph{
    private:
        Vertex<T>* head;

        void recreate(Vertex<T>* node){
            if(!node) return;
            std::unordered_map<Vertex<T>*, Vertex<T>*> oldToNew;
            std::queue<Vertex<T>*> q;
            q.push(node);
            Vertex<T>* newHead=new Vertex<T>(node->data);
            oldToNew[node]=newHead;
            this->head=newHead;
            while(!q.empty()) {
                Vertex<T>* curr=q.front();
                q.pop();
                Vertex<T>* currClone=oldToNew[curr];
                for(auto& neighbor : curr->edges){
                    if(oldToNew.find(neighbor)==oldToNew.end()) {
                        oldToNew[neighbor]=new Vertex<T>(neighbor->data);
                        q.push(neighbor);
                    }
                    currClone->edges.push_back(oldToNew[neighbor]);
                }
            }
        }
        void clearRec(Vertex<T>* node,std::unordered_set<Vertex<T>*>& visited){
            if(!node || visited.count(node)) return;
            visited.insert(node);
            for(auto& itr : node->edges){
                clearRec(itr, visited);
            }
            //std::cout<<"Deleting node: "<< node->data<<"\n";
            delete node;
        }
    public:
        Graph():head(nullptr){}
        Graph(const T data){
            Vertex<T>* new_node=new Vertex<T>{data};
            this->head=new_node;
        }
        Graph(const Graph<T>& other){this->recreate(other.head);}
        Graph(Graph<T>&& other){
            this->head=other.head;
            other.head=nullptr;
        }
        Graph& operator=(const Graph<T>& other){
            if(this==&other) return *this;
            this->clear();
            this->recreate(other.head);
            return this;
        }
        friend std::ostream& operator<<(std::ostream& os,const Graph<T>& graph){
            if (!graph.head) return os;
            std::queue<Vertex<T>*> q;
            std::map<T, bool> visited;
            q.push(graph.head);
            visited[graph.head->data]=true;
            while (!q.empty()) {
                Vertex<T>* node=q.front();
                q.pop();
                os<<node->data<<": ";
                for(auto& vptr : node->edges){
                    os<<"\""<<vptr->data<<"\" ";
                    if(!visited[vptr->data]){
                        visited[vptr->data]=true;
                        q.push(vptr);
                    }
                }
                os<<"\n";
            }
            return os;
        }
        ~Graph(){this->clear();}
        void clear(){
            std::unordered_set<Vertex<T>*> visited;
            this->clearRec(this->head,visited);
            this->head=nullptr;
        }
        void insert(const T element,Vertex<T>* vertex){   
            if(!vertex) return;
            if(!this->search(element)){
                Vertex<T>* new_node=new Vertex<T>{element};
                vertex->edges.push_back(new_node);
                new_node->edges.push_back(vertex);
            }
        }
        inline Vertex<T>* get_head()const noexcept{return this->head;}
        Vertex<T>* search(T data)const noexcept{
            if(!this->head) return nullptr;
            std::queue<Vertex<T>*> q;
            std::map<T, bool> visited;
            q.push(this->head);
            visited[head->data]=true;
            while(!q.empty()){
                Vertex<T>* node=q.front();
                if(node->data==data) return node;
                for(auto&itr : node->edges){
                    if(!visited[itr->data]){
                        q.push(itr);
                        visited[itr->data]=true;
                    }
                }
                q.pop();
            }
            return nullptr;
        }
};


int main(){
    Graph<std::string> flights("Chicago");
    flights.insert("Washington",flights.get_head());
    flights.insert("New York",flights.search("Washington"));
    flights.insert("Denver",flights.search("New York"));
    flights.insert("Utah",flights.search("Chicago"));
    flights.insert("Los Angeles",flights.search("Chicago"));
    std::cout<<flights<<"\n";   


    return 0;
}