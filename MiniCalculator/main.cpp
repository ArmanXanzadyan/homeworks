#include "tokenizer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"
#include "var_parser.hpp"
#include "compiler/compiler.hpp"
#include "compiler/vm.hpp"

#include <iostream>
#include <cstring>


static void print_usage()
{
    std::cout << "Usage: ./expr [options] \"expression\" [var=value ...]\n"
              << "Options:\n"
              << "  --eval      Evaluate with tree-walk interpreter (default)\n"
              << "  --compile   Compile to bytecode and execute on stack VM\n"
              << "  --asm       Show generated assembly instructions\n";
}

enum class Mode { EVAL, COMPILE };

int main(int argc, char** argv)
{
    if (argc < 2) { print_usage(); return 1; }

    Mode mode = Mode::EVAL;
    bool show_asm = false;
    const char* expression = nullptr;

    for (int i = 1; i < argc; ++i)
    {
        if (std::strcmp(argv[i], "--eval") == 0) mode = Mode::EVAL;
        else if (std::strcmp(argv[i], "--compile") == 0) mode = Mode::COMPILE;
        else if (std::strcmp(argv[i], "--asm") == 0) show_asm = true;
        else if (!expression) expression = argv[i];
    }

    if (!expression) { print_usage(); return 1; }

    auto tokens = tokenize(expression);
    if (tokens.empty()) return 1;

    auto tree = parse(tokens);
    if (!tree) return 1;

    auto vars = parse_all_variables(argc, argv);

    try
    {
        if (mode == Mode::COMPILE || show_asm)
        {
            auto prog = compile(tree.get());
            if (show_asm)
                std::cout << "--- Assembly ---\n" << program_to_string(prog) << "----------------\n";
            if (mode == Mode::COMPILE) execute(prog, vars);
            else std::cout << "Value: " << evaluate(tree.get(), vars) << std::endl;
        }
        else
        {
            std::cout << "Value: " << evaluate(tree.get(), vars) << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
