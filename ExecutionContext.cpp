// Online C++ compiler to run C++ program online
#include <iostream>
#include <math.h>
#define max_depth 1024

class Stack{
    
    int stack[max_depth];
    int tos;
    
     public:

        Stack(){
            tos = -1;

        }
    
        void push(int item) {
            if (item < 0 || item > (pow(2,256) -1)){
                std::cout<<"Invalid Stack Item: "<<item<<std::endl;
                exit(0);
            }
            
            if((tos + 1) + 1 > max_depth){
                std::cout<<"EVM stack is full"<<std::endl;
                exit(0);
            }
            tos++;
            stack[tos] = item;
        }
        
        int pop(){
            if(tos == -1){
                std::cout<<"EVM stack is empty"<<std::endl;
                exit(0);
            }
            int temp = stack[tos];
            tos--;
            return temp;
        }

        int getTOS(){
            return tos;
        }

    
};

class Memory{
  int *memory;
  int size;
  

  public:
        Memory(){
            memory = (int*) calloc(1,sizeof(int));
            size = 1;
            if(memory == NULL){
                std::cout<<"MEmory is null";
            }
            // std::cout<<"Running: "<<sizeof(memory)<<std::endl;
        }
  
      void store(int offset, int value){
          if(offset <0 || offset > (pow(2,256)-1)){
              std::cout<<"Invalid memory access. Offset: "<<offset<<" Value: "<<value<<std::endl;
              exit(0);
          }
          
          if(value <0 || value > (pow(2,256)-1)){
              std::cout<<"Invalid memory value. Offset: "<<offset<<" Value: "<<value<<std::endl;
              exit(0);
          }
          

          //Expand memory while necessary
          if(offset >size){
              memory = (int*) realloc(memory, (size * sizeof(int)));
              if(memory == NULL){
                  std::cout<<"Cannot increase memory, Memory full"<<std::endl;
                  exit(0);
              }
          }
            
          //Saving value in the memory
          *(memory+offset) = value;
          size++; //Increment size of dynamic memory
      }
      
      int load(int offset){
          if(offset < 0){
              std::cout<<"Invalid memory access. Offset: "<<offset<<std::endl;
              exit(0);
          }
          if(offset >= size){
              return 0;
          }
          return *(memory+offset);
      }
      
      void data(){
          std::cout<<"Length: "<<sizeof(size);
        //   std::cout<<"VAKUE: "<<(*memory);
      }
  
};

int main() {
    // std::cout<<"Hello World"<<endl;
    // Write C++ code here
    Stack obj;
    std::cout<<obj.getTOS()<<std::endl;

    obj.push(2);
    std::cout<<obj.getTOS()<<std::endl;
    obj.push(3);
    std::cout<<obj.getTOS()<<std::endl;

    obj.push(4);
        std::cout<<obj.getTOS()<<std::endl;

    std::cout<<obj.pop()<<std::endl;
    
    // Initializing memory
    Memory M;
    // M.data();
    M.store(0,10);
    M.store(1,20);
    M.store(2,30);
    
    std::cout<<M.load(0)<<std::endl;
    std::cout<<M.load(1)<<std::endl;
    std::cout<<M.load(2)<<std::endl;
    std::cout<<M.load(3)<<std::endl;


 
    return 0;
}
