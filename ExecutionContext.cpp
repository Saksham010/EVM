// Online C++ compiler to run C++ program online
#include <iostream>
#include <math.h>
#include <cstddef>
#include <vector>
#include <string>
#include<functional>

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

class ExecutionContext{
    // std::byte code;
    std::vector<std::byte> bytes;
    public:

    Stack stack;
    Memory memory;
    int pc;
    bool stopped;

    void initializeByteCode(std::string bytecode){
        int end = bytecode.length()-1;
        std::string _opcode = "0x";

        for(int i =0; i <= end;i++){
        
            _opcode = _opcode + bytecode[i];
            
            //IF odd iteration reset partial string, append to bytes array
            if(i % 2 != 0){
                std::byte oneByte = std::byte(std::stoi(_opcode,nullptr,16));
                //Appending to byte array
                bytes.push_back(oneByte); 
                //Reset parital string 
                _opcode = "0x";
            }
    
        }
        //Print vector
        for(int i =0; i < bytes.size();i++){
            std::cout<<std::to_integer<int>(bytes[i])<<" ";
        }

    }

        ExecutionContext(){
            std::cout<<"Initialized";
        }
        ExecutionContext(std::string _bytecode, Memory _memory, Stack _stack,int _pc = 0){
            initializeByteCode(_bytecode);
            stack = _stack;
            memory = _memory;
            pc = _pc;
            stopped = false;
        }

        void stop(){
            stopped = true;
        }

        int readByteCode(int num_of_bytes = 1){
            // Assuming 1 byte per a time
            int value = int(bytes[pc+num_of_bytes]); //The value read is as integer
            pc = pc + num_of_bytes;
            return value;
        }

};
// template<typename T = std::nullptr_t>
class Instruction{
    std::function<void()> callable_func;
    public:

        int opcode;
        std::string name;
        Instruction(int _opcode, std::string _name){
            opcode = _opcode;
            name = _name;
        }
        // Register execution function
        void registerExec(std::function<void()> _exec_func){
            callable_func = _exec_func;
        }
        //Execute function
        void execute(){
            callable_func();
        }

};

std::vector<Instruction> INSTRUCTIONS;
std::vector<Instruction> INSTRUCTION_BY_OPCODE;
Instruction register_instruction(int _opcode,std::string _name, std::function<void()> execute_func){
    Instruction instruction = Instruction(_opcode,_name);
    // instruction.registerExec(std::bind([](F exec_func){exec_func();},execute_func)); //Registering exec func
    instruction.registerExec(execute_func); //Registering exec func
    //Execute some instruction
    INSTRUCTIONS.push_back(instruction);

    // Check if the opcode instruction exist in list or not
    bool exist = false;
    for(int i =0; i < INSTRUCTION_BY_OPCODE.size();i++){
        if(_opcode == INSTRUCTION_BY_OPCODE[i].opcode){
            exist = true;
        }
    }
    if(exist == false){
        INSTRUCTION_BY_OPCODE[_opcode] = instruction;
    }

    return instruction;

}
// Global Execution context
ExecutionContext ctx;

// Instruction definitions
Instruction STOP = register_instruction(0x00,"STOP",[](){
    std::cout<<"STOP called"<<std::endl;
    ctx.stop();    
});

Instruction PUSH1 = register_instruction(0x60,"PUSH1",[](){
    std::cout<<"PUSH1 called"<<std::endl;
    ctx.stack.push(ctx.readByteCode(1));
});

Instruction ADD = register_instruction(0x01,"ADD",[](){
    std::cout<<"ADD called"<<std::endl;
    ctx.stack.push((ctx.stack.pop() + ctx.stack.pop()) % int(pow(2,256)));
});

Instruction MUL = register_instruction(0x02,"MULL",[](){
    std::cout<<"MUL called"<<std::endl;
    ctx.stack.push((ctx.stack.pop() * ctx.stack.pop()) % int(pow(2,256)));
});


// Decoding opcode
Instruction decode_opcode(ExecutionContext _ctx_){

    // Check if pc is off the range (left to implement)

    //Reading one opcode
    int opcode = _ctx_.readByteCode(1);
    Instruction _instruction = INSTRUCTION_BY_OPCODE[opcode];
    
    // Instruction type check (left to implement)

    return _instruction;
}

int main() {
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
