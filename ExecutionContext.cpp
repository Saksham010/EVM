// Online C++ compiler to run C++ program online
#include <iostream>
#include <math.h>
#include <cstddef>
#include <vector>
#include <string>
#include<functional>
#include <unordered_map>


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
            std::cout<<"Successfully pushed: "<<item;
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
        int getTopValue(){
            return stack[tos];
        }
        void print(){
            std::cout<<"Stack: [";
            for(int i =0; i <=tos;i++){
                std::cout<<stack[i]<<",";
            }
            std::cout<<"]"<<std::endl;
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


    // Opcode to operand mapping
    std::unordered_map<int,int> _opcode_to_operand;

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
            // std::cout<<std::endl<<"PC at this time: "<<pc;
            // std::cout<<" READ BYTE: "<<std::to_integer<int>(bytes[pc]);

            int opcode_value = int(bytes[pc]);  //The type of operation
            int operand_value = int(bytes[pc+num_of_bytes]); //The operand to be operated on
            // Create a mapping
            _opcode_to_operand[opcode_value] = operand_value;

            pc = pc + num_of_bytes +1;
            return opcode_value;
        }

};
// Global Execution context
ExecutionContext ctx;

// template<typename T = std::nullptr_t>
class Instruction{
    std::function<void()> callable_func;
    public:

        int opcode;
        std::string name;
        Instruction(){
            // std::cout<<"Instruction initialized"<<std::endl;
        }

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
// std::vector<Instruction> INSTRUCTION_BY_OPCODE;
std::unordered_map<int,Instruction> INSTRUCTION_BY_OPCODE;
Instruction register_instruction(int _opcode,std::string _name, std::function<void()> execute_func){
    std::cout<<"Incomming opcode : "<<_opcode<<std::endl;
    Instruction instruction = Instruction(_opcode,_name);
    // instruction.registerExec(std::bind([](F exec_func){exec_func();},execute_func)); //Registering exec func
    instruction.registerExec(execute_func); //Registering exec func

    // //Execute some instruction
    INSTRUCTIONS.push_back(instruction);

    // Check if the opcode instruction exist in list or not
    bool exist = false;

    // if(auto:){

    // }

    // if(INSTRUCTION_BY_OPCODE.find(_opcode) != 0){
    //     exist =true;
    //     // std::cout<<"Instruction already exisits: "<<INSTRUCTION_BY_OPCODE[_opcode]<<std::endl;
    // }
    // for(int i =0; i < INSTRUCTION_BY_OPCODE.size();i++){
    //     if(_opcode == INSTRUCTION_BY_OPCODE[i].opcode){
    //         exist = true;
    //     }
    // }
    // std::cout<<std::endl<<" opcode: "<<_opcode;
    if(exist == false){
        // auto iterator = INSTRUCTION_BY_OPCODE.begin()+_opcode;
        
        // INSTRUCTION_BY_OPCODE.insert(iterator,instruction);
        INSTRUCTION_BY_OPCODE[_opcode] = instruction;
    }

    return instruction;

}

// Instruction definitions
Instruction STOP = register_instruction(0x00,"STOP",[](){
    std::cout<<"STOP called"<<std::endl;
    ctx.stop();    
});

Instruction PUSH1 = register_instruction(0x60,"PUSH1",[](){
    std::cout<<"PUSH1 called"<<std::endl;
    // Reading value to be pushed
    int _opcode = ctx.readByteCode(1);
    int _value = ctx._opcode_to_operand[_opcode];

    // Pushing value to the stack
    ctx.stack.push(_value);
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
    std::cout<<" Bytecode:  "<<opcode;
    Instruction _instruction = INSTRUCTION_BY_OPCODE[opcode];
    std::cout<<" Bytecode corresponding instruction name: "<<_instruction.name;
    
    // Instruction type check (left to implement)

    return _instruction;
}

void run(std::string code){
    // Initialize execution context
    ctx.initializeByteCode(code);
    Memory _m;
    Stack _s;
    ctx.memory = _m;
    ctx.stack = _s;
    ctx.stopped =false;
    ctx.pc = 0;

    int prev_pc;
    // Run EVM
    while(ctx.stopped!= true){
        prev_pc = ctx.pc;
        //Get the current task
        // std::cout<<std::endl<<"before decoding opcode"<<std::endl;
        Instruction task =  decode_opcode(ctx);
        // std::cout<<std::endl<<"after decoding opcode"<<std::endl;
        std::cout<<"Task name: "<<task.name;

        //Execute the current task
        // std::cout<<std::endl<<"before executing opcode"<<std::endl;
        task.execute();
        // std::cout<<std::endl<<"after executing opcode"<<std::endl;


        // Displaying evm
        std::cout<<task.name<<" @ pc = "<<prev_pc<<std::endl;
        ctx.stack.print();
        // Memory display left
    }
}

int main(int argc, char* argv[]){
    // Stack obj;
    // std::cout<<obj.getTOS()<<std::endl;

    // obj.push(2);
    // std::cout<<obj.getTOS()<<std::endl;
    // obj.push(3);
    // std::cout<<obj.getTOS()<<std::endl;

    // obj.push(4);
    //     std::cout<<obj.getTOS()<<std::endl;

    // std::cout<<obj.pop()<<std::endl;
    
    // // Initializing memory
    // Memory M;
    // // M.data();
    // M.store(0,10);
    // M.store(1,20);
    // M.store(2,30);
    
    // std::cout<<M.load(0)<<std::endl;
    // std::cout<<M.load(1)<<std::endl;
    // std::cout<<M.load(2)<<std::endl;
    // std::cout<<M.load(3)<<std::endl;


    // std::cout<<"The no of argument is: "<<argc<<std::endl;
    // for (int i = 0; i < argc; i++) {
    //     std::cout<<argv[i]<<std::endl;
    // }
    std::string compiled_opcode = argv[1];
    run(compiled_opcode);
    

    return 0;
}


// 600660070200