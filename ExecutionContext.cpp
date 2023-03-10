// Online C++ compiler to run C++ program online
#include <iostream>
#include <math.h>
#define max_depth 1024

class Stack{
    
    int stack[max_depth];
    int tos;
    
    void constructor(){
        tos = -1;
    }
    public:
    
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
    
};

class Memory{
  int *memory;
  
  void constructor(){
      memory = (int*) calloc(1,sizeof(int));
      std::cout<<"Running: "<<sizeof(memory)<<std::endl;
  }
  public:
  
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
          if(offset > sizeof(memory)/sizeof(int)){
              memory = (int*) realloc(memory, (sizeof(memory)/sizeof(int)+1) * sizeof(int));
              if(memory == NULL){
                  std::cout<<"Cannot increase memory, Memory full"<<std::endl;
                  exit(0);
              }
          }
            
          //Saving value in the memory
          *(memory+offset) = value;
      }
      
      int load(int offset){
          if(offset < 0){
              std::cout<<"Invalid memory access. Offset: "<<offset<<std::endl;
              exit(0);
          }
          if(offset >= sizeof(memory)/sizeof(int)){
              return 0;
          }
          return *(memory+offset);
      }
      
      void data(){
          std::cout<<"Length: "<<sizeof(NULL);
        //   std::cout<<"VAKUE: "<<(*memory);
      }
  
};

int main() {
    // Write C++ code here
    Stack obj;
    obj.push(2);
    obj.push(3);
    obj.push(4);
    
    // std::cout<<obj.pop();
    
    // Initializing memory
    Memory M;
    M.data();
    // M.store(0,10);
    // M.store(1,20);
    // M.store(2,30);
    
    // std::cout<<M.load(0)<<std::endl;
    // std::cout<<M.load(1)<<std::endl;
    // std::cout<<M.load(2)<<std::endl;
    // std::cout<<M.load(3)<<std::endl;

  
    return 0;
}
