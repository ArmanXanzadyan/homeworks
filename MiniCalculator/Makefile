NAME = expr

CXX = c++
CXXFLAGS = -Wall -Wextra -O2 -g -std=c++17

SRC = main.cpp tokenizer.cpp parser.cpp evaluator.cpp var_parser.cpp \
      compiler/compiler.cpp compiler/vm.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(NAME)
	@echo "Running tests..."
	@bash test.sh > test_output.txt 2>&1
	@echo "Tests done. Results saved to test_output.txt"
	@cat test_output.txt

valgrind: $(NAME)
	@echo "=== Valgrind Memory Check ===" > valgrind_output.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		./$(NAME) "2+3" >> valgrind_output.txt 2>&1
	@echo "" >> valgrind_output.txt
	@echo "=== With Variables ===" >> valgrind_output.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		./$(NAME) "x+y*2" x=10 y=5 >> valgrind_output.txt 2>&1
	@echo "" >> valgrind_output.txt
	@echo "=== Complex Expression ===" >> valgrind_output.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		./$(NAME) "((2+3)*4-10)/2" >> valgrind_output.txt 2>&1
	@echo "" >> valgrind_output.txt
	@echo "=== Parentheses ===" >> valgrind_output.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		./$(NAME) "(10-2)*(3+1)" >> valgrind_output.txt 2>&1
	@echo "Valgrind done. Results saved to valgrind_output.txt"
	@cat valgrind_output.txt

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) test_output.txt valgrind_output.txt

re: fclean all

.PHONY: all clean fclean re test valgrind
