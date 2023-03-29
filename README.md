# EVM
Building a basic evm clone from scratch

#Instruction to simulate Execution Context
1. Clone the repo
2. Write evm supported assembly in hello.easm (Only PUSH,ADD,MUL,MSTORE8,STOP,RETURN) has been implemented
<div>
  <img src="https://i.postimg.cc/MHbVRSz2/opcode.jpg" title="Opcode" alt="Opcode" width="40" height="40"/>&nbsp;
</div>

In above example
  a) first command pushes "6" to stack
  b) second command pushes "7" to stack
  c) third command pops tos twice and performs multiplication on those and pushes the "result" back to the stack
  d) fourth command pushes "0" to stack
  e) MSTORE8 pops top of stack "0" and uses it as a memory offset to store value which is again popped from stack(ie. result)
  f) Two PUSH pushes "1" and "0" to stack
  g) RETURN pops tos (ie. "0") and uses it as offset of memory and another pop tos(ie. "1") and uses it as the length of memory to return and loads value from memory in output
  
3. Compile hello.easm with code: evm compile hello.easm
4. Copy the bytecode returned by the compilation which in this case is: 600660070260005360016000f3
5. Compile ExecutionContext.cpp and run [name].out file with bytecode as parameter. Eg: ./a.out 600660070260005360016000f3
6. Following ouput is expected: 
