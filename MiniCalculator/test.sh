#!/bin/bash

 

# Build first

cd "$(dirname "$0")"

make re 2>&1

if [ $? -ne 0 ]; then

    echo "BUILD FAILED"

    exit 1

fi

echo ""

echo "===== MiniCalc Tests ====="

echo ""

 

PASS=0

FAIL=0

 

run_test() {

    local desc="$1"

    local expected="$2"

    shift 2

    local result

    result=$(./expr "$@" 2>&1)

    local actual

    actual=$(echo "$result" | grep -oP 'Value: \K[-0-9]+')

 

    if [ "$actual" = "$expected" ]; then

        echo "[PASS] $desc => $actual"

        ((PASS++))

    else

        echo "[FAIL] $desc => expected $expected, got '$result'"

        ((FAIL++))

    fi

}

 

run_error_test() {

    local desc="$1"

    shift

    local result

    result=$(./expr "$@" 2>&1)

    local exit_code=$?

    if [ $exit_code -ne 0 ] || echo "$result" | grep -qi "error\|unexpected\|undefined\|division"; then

        echo "[PASS] $desc => error handled correctly"

        ((PASS++))

    else

        echo "[FAIL] $desc => expected error, got '$result'"

        ((FAIL++))

    fi

}

 

echo "--- Addition ---"

run_test "2+3"          5   "2+3"

run_test "0+0"          0   "0+0"

run_test "100+200"      300 "100+200"

run_test "1+2+3+4"      10  "1+2+3+4"

 

echo ""

echo "--- Subtraction ---"

run_test "10-3"         7   "10-3"

run_test "5-5"          0   "5-5"

run_test "100-30-20"    50  "100-30-20"

 

echo ""

echo "--- Multiplication ---"

run_test "3*4"          12  "3*4"

run_test "7*0"          0   "7*0"

run_test "2*3*4"        24  "2*3*4"

 

echo ""

echo "--- Division ---"

run_test "10/2"         5   "10/2"

run_test "100/10"       10  "100/10"

run_test "7/2"          3   "7/2"

 

echo ""

echo "--- Operator Precedence ---"

run_test "2+3*4"        14  "2+3*4"

run_test "10-2*3"       4   "10-2*3"

run_test "2*3+4*5"      26  "2*3+4*5"

run_test "10+20/5"      14  "10+20/5"

 

echo ""

echo "--- Parentheses ---"

run_test "(2+3)*4"      20  "(2+3)*4"

run_test "((2+3))"      5   "((2+3))"

run_test "(10-2)*(3+1)" 32  "(10-2)*(3+1)"

run_test "100/(4+1)"    20  "100/(4+1)"

 

echo ""

echo "--- Variables ---"

run_test "x+y (x=10,y=20)"         30  "x+y" "x=10" "y=20"

run_test "x*y+z (x=3,y=4,z=5)"    17  "x*y+z" "x=3" "y=4" "z=5"

run_test "a (a=42)"                 42  "a" "a=42"

run_test "(w+h)*2 (w=10,h=5)"      30  "(w+h)*2" "w=10" "h=5"

 

echo ""

echo "--- Mixed Complex ---"

run_test "1+2*3-4/2"       5   "1+2*3-4/2"

run_test "(1+2)*(3+4)"     21  "(1+2)*(3+4)"

run_test "((2+3)*4-10)/2"  5   "((2+3)*4-10)/2"

 

echo ""

echo "===== Compiler Mode Tests ====="

echo ""

 

run_compile_test() {

    local desc="$1"

    local expected="$2"

    shift 2

    local result

    result=$(./expr --compile "$@" 2>&1)

    local actual

    actual=$(echo "$result" | grep -oP 'Value: \K[-0-9]+')

 

    if [ "$actual" = "$expected" ]; then

        echo "[PASS] compile: $desc => $actual"

        ((PASS++))

    else

        echo "[FAIL] compile: $desc => expected $expected, got '$result'"

        ((FAIL++))

    fi

}

 

echo "--- Compile: Addition ---"

run_compile_test "2+3"          5   "2+3"

run_compile_test "0+0"          0   "0+0"

run_compile_test "1+2+3+4"     10  "1+2+3+4"

 

echo ""

echo "--- Compile: Subtraction ---"

run_compile_test "10-3"         7   "10-3"

run_compile_test "100-30-20"   50  "100-30-20"

 

echo ""

echo "--- Compile: Multiplication ---"

run_compile_test "3*4"         12  "3*4"

run_compile_test "2*3*4"       24  "2*3*4"

 

echo ""

echo "--- Compile: Division ---"

run_compile_test "10/2"         5   "10/2"

run_compile_test "7/2"          3   "7/2"

 

echo ""

echo "--- Compile: Precedence & Parens ---"

run_compile_test "2+3*4"       14  "2+3*4"

run_compile_test "(2+3)*4"     20  "(2+3)*4"

run_compile_test "(10-2)*(3+1)" 32  "(10-2)*(3+1)"

run_compile_test "((2+3)*4-10)/2" 5 "((2+3)*4-10)/2"

 

echo ""

echo "--- Compile: Variables ---"

run_compile_test "x+y (x=10,y=20)"     30  "x+y" "x=10" "y=20"

run_compile_test "x*y+z (x=3,y=4,z=5)" 17  "x*y+z" "x=3" "y=4" "z=5"

 

echo ""

echo "--- Assembly Output ---"

ASM_OUT=$(./expr --asm "2+3*4" 2>&1)

if echo "$ASM_OUT" | grep -q "PUSH\|ADD\|MUL"; then

    echo "[PASS] --asm flag shows assembly instructions"

    ((PASS++))

else

    echo "[FAIL] --asm flag did not show assembly"

    ((FAIL++))

fi

 

echo ""

echo "--- Error Handling ---"

run_error_test "Division by zero: 10/0"       "10/0"

run_error_test "Undefined variable: x+1"      "x+1"

run_error_test "No arguments"

 

echo ""

echo "============================="

echo "Results: $PASS passed, $FAIL failed"

echo "============================="
