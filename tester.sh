#!/bin/bash

# Colors
RED="\033[0;31m"
UNDERLINE_RED="\033[4;31m"
GREEN="\033[1;32m"
UNDERLINE_GREEN="\033[4;32m"
YELLOW="\033[1;33m"
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
    
    echo -e "${PURPLE}▶ Testing ${YELLOW}${test_name^^} ${PURPLE}commands:${RESET}"
    
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
#run_test "echo" "echo \"HelloWorld\"" "echo "       spaces!     ""
#run_test "ls" "/bin/ls" "ls -a"
#run_test "pwd" "pwd"
#run_test "cd" "cd" "cd .." "cd /" "cd ~" "cd /Users" "cd /Users/$(whoami)"
#run_test "export" "export VALID_ENV" "echo \"$VALID_ENV\"" "export _#novalid_ENV" "echo \"$_novalid_ENV\"" "echo "exit status: \$?""
#run_test "unset" "unset" "unset VALID_ENV" "echo \"$VALID_ENV\"" "unset $HOME" "echo \"$HOME\""
#run_test "exit" "exit 255"
#run_test "quotes" "echo '$HOME'" "echo \"$HOME\"" "echo '$HOME'"
#run_test "random" "randominput"

# New tests
# Echo tests
run_test "echo_extended" "echo" "echo hola" "echo \"\"" "echo \"\" hola" "echo -n hola" "echo -n -n hola" \
    "echo -n -nh -n hola" "echo -nnnnnnnnn hola" "echo $?hcudshfuewrf ew  wr 4ew\"\"\"\"" \
    "echo \"\"uhjkhnkj\"hjbmb\"'''' defdjhfkjb \"iujiouhj\"f'f'f'f'f''f'f'f'f'f'f'" \
    "echo \"\"uhjkhnkj\"hjbmb\"'''' defdjhfkjb \"iujiouhj\"f'f'a'j'o''i'w'q''q" \
    "echo \"\"aaaaaaaa\"bbbbb\"'''' ccccccccc \"dddddddd\"e'e'e" \
    "echo \"ho   $USER\"  'la   $LESS'   $USER$TERM" \
    "echo \"ho   $USER\"'la   $LESS'$USER$TERM" \
    "echo\"ho   $USER\"" \
    "echo\"ho   $USE$LESS\"" \
    "\"echo ho   $USER\"" \
    "\"echo\" \"ho   $USER\"" \
    "e\"cho\" \"ho   $USER\"" \
    "       echo \"ho   $USER\"" \
    "echo \"$HOME '$LESS' $USER\"" \
    "echo '$HOME \"$LESS\" $USER'" \
    "echo \"$HOME '$LESS \"pa $TERM\" na' $USER\"" \
    "echo '$HOME \"$LESS 'pa $TERM' na\" $USER'" \
    "echo '$'\"HOME\""

# Export tests
run_test "export_extended" "export a=b" "export b=wawa" "export b=lala" "export c=lala=kaka" "export a" \
    "export a=" "export a= b=o" "export a===" "export a3=l" "export 2a=lala" "export !a=ma" \
    "export $USER=la" "export $USER=$TERM" "export $USER=$TERM$HOME" "export $USER=$TERM$HOM" \
    "export $HOME=$USER" "export $USER$SHLVL" "export" "           export" "export \"\"" \
    "export a b=$LESS $USER $HOME=la $COLORTERM=pa c=d"

# CD tests
run_test "cd_extended" "cd /tmp" "cd /nonexistent_directory" "cd /bin/ls" "cd" "           cd" \
    "cd -" "cd ~" "unset HOME" "cd ~" "cd /tmp" "chmod 000 /tmp/test_dir" "cd /tmp/test_dir" \
    "chmod 755 /tmp/test_dir" "rm -rf /tmp/test_dir"

# Env tests
run_test "env_tests" "env" "env lalal" "env /tmp"

# PWD tests
run_test "pwd_extended" "pwd" "pwd -L" "pwd arg1 arg2"

# Unset tests
run_test "unset_extended" "unset" "unset PATH" "unset HOME USER TERM"

# Exit tests
run_test "exit_extended" "exit" "exit 0" "exit 1" "exit 42" "exit lalal"

# Pipe tests
run_test "pipe_tests" "ls | wc" "ls|wc" "cat /etc/passwd | grep root | wc -l" \
    "sort /etc/passwd | uniq | sort -r | wc" "ls || wc" "ls |   | wc" \
    "ls |   > file wc" "ls | wc |" "|" "| ls | wc"

# Redirection tests
#run_test "redirection_tests" "echo hola > file" "echo hola >> file" "wc < file" \
#    "echo hola >>>>>>> file" "echo hola <<<<<<< file" "echo hola>file" \
#    "echo hola > file > file" "echo hola > file1 > file2 > file3" \
#    "echo hola > file1 > file2 > file3 | ls" "wc < /etc/passwd" \
#    "wc < /etc/passwd > file" "cat /etc/passwd | wc" \
#    "cat << EOF\nhello\nworld\nEOF" "cat << EOF > file\nhello\nworld\nEOF" \
#    "<< EOF" "cat << hola << que << tal" "cat << EOF | ls" \
#    "echo hola | cat | cat | cat | cat | cat | cat | cat" \
#    "echo hola > file << EOF\nTesting\nEOF"

# General tests
#run_test "general_tests" "" "    " "echo \"unclosed quote" "echo $?" \
#    "unset PATH" "ls" "/bin/ls" "unset HOME" "cd" "ls -la > file" \
#    "cat < nonexistent_file" "cd nonexistent_directory" "echo $?"

echo -e "${UNDERLINE_GREEN}✓ All tests completed!${RESET}"
echo
# ...existing code...

echo -e "${UNDERLINE_GREEN}✓ All tests completed!${RESET}"
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
        echo -e "${UNDERLINE_RED}▶ Memory leaks found in $test_name test:${RESET}"
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