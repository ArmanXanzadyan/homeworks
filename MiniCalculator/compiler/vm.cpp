#include "vm.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>


int execute(const Program& prog, const std::unordered_map<std::string, int>& vars)

{
    std::vector<int> stack;
    stack.reserve(64);

    size_t ip = 0;
    int result = 0;


    while (ip < prog.size())
    {
        const Instruction& instr = prog[ip];

        switch (instr.op)
        {
            case OpCode::PUSH: stack.push_back(instr.operand); break;

            case OpCode::LOAD:
            {
                auto it = vars.find(instr.var_name);
                if (it == vars.end()) throw std::runtime_error("Undefined variable: " + instr.var_name);
                stack.push_back(it->second);
                break;
            }

            case OpCode::ADD:
            {
                if (stack.size() < 2) throw std::runtime_error("Stack underflow on ADD");
                int b = stack.back(); stack.pop_back();
                int a = stack.back(); stack.pop_back();
                stack.push_back(a + b);
                break;
            }

            case OpCode::SUB:
            {
                if (stack.size() < 2) throw std::runtime_error("Stack underflow on SUB");
                int b = stack.back(); stack.pop_back();
                int a = stack.back(); stack.pop_back();
                stack.push_back(a - b);
                break;
            }

            case OpCode::MUL:
            {
                if (stack.size() < 2) throw std::runtime_error("Stack underflow on MUL");
                int b = stack.back(); stack.pop_back();
                int a = stack.back(); stack.pop_back();
                stack.push_back(a * b);
                break;
            }

            case OpCode::DIV:
            {
                if (stack.size() < 2) throw std::runtime_error("Stack underflow on DIV");
                int b = stack.back(); stack.pop_back();
                if (b == 0) throw std::runtime_error("Division by zero");
                int a = stack.back(); stack.pop_back();
                stack.push_back(a / b);
                break;
            }

            case OpCode::PRINT:
            {
                if (stack.empty()) throw std::runtime_error("Stack underflow on PRINT");
                result = stack.back();
                std::cout << "Value: " << result << std::endl;
                break;
            }

            case OpCode::HALT: return result;
        }

        ++ip;
    }

    return result;
}
