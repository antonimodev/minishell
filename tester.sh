#!/bin/bash

# Colors
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
PURPLE="\033[0;35m"
RESET="\033[0m"

# Check if we're in the right directory
if [ ! -f "Makefile" ]; then
    echo "Error: No Makefile found in current directory"
    exit 1
fi

# Check if minishell exists
if [ ! -f "./minishell" ]; then
    echo "Error: minishell executable not found"
    echo "Please run 'make run' first"
    exit 1
fi

# Create temp_logs directory if it doesn't exist
mkdir -p temp_logs

# Function to run a test and check memory leaks
run_test() {
    local test_name=$1
    shift
    
    echo -e "${PURPLE}▶ Testing ${test_name^^} commands:${RESET}"
    
    # Format the test name for the log file
    local log_file_name=$(echo "$test_name" | tr ' ' '_')
    
    # Create a temporary commands file
    local temp_file=$(mktemp)
    
    # Add all commands to the temp file
    for cmd in "$@"; do
        echo "$cmd" >> "$temp_file"
    done
    
    # Add exit command at the end
    echo "exit" >> "$temp_file"
    
    # Run minishell with the commands and save valgrind output
    cat "$temp_file" | valgrind --leak-check=full --log-file="temp_logs/${log_file_name}.log" ./minishell
    
    # Clean up
    rm "$temp_file"
    
    echo
}

# Check if we're being called with arguments - if so, just run that test
if [ $# -gt 0 ]; then
    # Determine test name from the first argument
    test_name=$(echo "$1" | sed 's/^"//' | sed 's/"$//' | tr -d '"' | tr ' ' '_')
    if [ -z "$test_name" ]; then
        test_name="unknown_test"
    fi
    
    # Create a temporary commands file
    temp_file=$(mktemp)
    
    # Add all commands to the temp file
    for cmd in "$@"; do
        echo "$cmd" >> "$temp_file"
    done
    
    # Add exit command at the end
    echo "exit" >> "$temp_file"
    
    # Run minishell with the commands and save valgrind output
    cat "$temp_file" | valgrind --leak-check=full --log-file="temp_logs/${test_name}.log" ./minishell
    
    # Clean up
    rm "$temp_file"
    
    exit 0
fi

# If no arguments, run all tests
echo -e "${YELLOW}╔════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║          TESTING MINISHELL             ║${RESET}"
echo -e "${YELLOW}╚════════════════════════════════════════╝${RESET}"

# Run all the test categories
run_test "echo" "echo \"HelloWorld\"" "echo "       spaces!     ""
run_test "ls" "/bin/ls" "ls -a"
run_test "pwd" "pwd"
run_test "cd" "cd" "cd .." "cd /" "cd ~" "cd /Users" "cd /Users/$(whoami)"
run_test "export" "export VALID_ENV" "echo \"$VALID_ENV\"" "export _novalid_ENV" "echo \"$_novalid_ENV\"" "echo "exit status: \$?""
run_test "unset" "unset" "unset VALID_ENV" "echo $VALID_ENV" "unset $HOME" "echo \"$HOME\""
run_test "exit" "exit 255"
run_test "quotes" "echo '$HOME'" "echo \"$HOME\"" "echo '$HOME'"
run_test "random" "randominput"

echo -e "${GREEN}✓ All tests completed!${RESET}"
echo
echo -e "${YELLOW}╔════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║        MEMORY LEAK ANALYSIS     🔎     ║${RESET}"
echo -e "${YELLOW}╚════════════════════════════════════════╝${RESET}"
echo -e "${PURPLE}▶ Checking for memory leaks:${RESET}"
echo

# Check for memory leaks
leaks_found=0
for log in temp_logs/*.log; do
    test_name=$(basename "$log" .log)
    definitely=$(grep "definitely lost:" "$log" | awk '{print $4}')
    indirectly=$(grep "indirectly lost:" "$log" | awk '{print $4}')
    possibly=$(grep "possibly lost:" "$log" | awk '{print $4}')
    
    if [ -z "$definitely" ] || [ -z "$indirectly" ] || [ -z "$possibly" ]; then
        echo -e "${RED}▶ Error processing valgrind output for $test_name test${RESET}"
        echo
        leaks_found=1
    elif [ "$definitely" = "0" ] && [ "$indirectly" = "0" ] && [ "$possibly" = "0" ]; then
        echo -e "${GREEN}✓ No memory leaks in $test_name test${RESET}"
        echo
    else
        echo -e "${RED}▶ Memory leaks found in $test_name test:${RESET}"
        grep -A 3 "LEAK SUMMARY:" "$log"
        echo
        leaks_found=1
    fi
done

if [ $leaks_found -eq 0 ]; then
    echo -e "${GREEN}╔════════════════════════════════════════╗${RESET}"
    echo -e "${GREEN}║     NO MEMORY LEAKS DETECTED!   🏆     ║${RESET}"
    echo -e "${GREEN}╚════════════════════════════════════════╝${RESET}"
else
    echo -e "${RED}╔════════════════════════════════════════╗${RESET}"
    echo -e "${RED}║       MEMORY LEAKS DETECTED!   📢      ║${RESET}"
    echo -e "${RED}╚════════════════════════════════════════╝${RESET}"
fi

rm -rf temp_logs