#pragma once


#include <string>
#include <vector>
#include <sstream>


enum class OpCode {
    PUSH,   // Push immediate value onto stack
    LOAD,   // Load variable value onto stack
    ADD,    // Pop two, push sum
    SUB,    // Pop two, push difference
    MUL,    // Pop two, push product
    DIV,    // Pop two, push quotient
    PRINT,  // Print top of stack
    HALT    // Stop execution
};

struct Instruction {
    OpCode op;
    int operand;
    std::string var_name;

    explicit Instruction(OpCode o) : op(o), operand(0) {}
    Instruction(OpCode o, int val) : op(o), operand(val) {}
    Instruction(OpCode o, std::string name) : op(o), operand(0), var_name(std::move(name)) {}

    std::string to_string() const
    {
        switch (op)
        {
            case OpCode::PUSH: return "PUSH " + std::to_string(operand);
            case OpCode::LOAD: return "LOAD " + var_name;
            case OpCode::ADD: return "ADD";
            case OpCode::SUB: return "SUB";
            case OpCode::MUL: return "MUL";
            case OpCode::DIV: return "DIV";
            case OpCode::PRINT: return "PRINT";
            case OpCode::HALT: return "HALT";
        }
        return "???";
    }
};


using Program = std::vector<Instruction>;


inline std::string program_to_string(const Program& prog)
{
    std::ostringstream oss;

    for (size_t i = 0; i < prog.size(); ++i)
        oss << i << ": " << prog[i].to_string() << "\n";

    return oss.str();
}
