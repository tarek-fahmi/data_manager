#!/bin/bash

# Define function to run tests for a specific part
run_test() {
    local part="$1"
    local test_num="$2"
    local input_file="tests/inputs/p${part}_${test_num}.in"
    local output_file="tests/output.txt"
    local test_name=$(head -n 1 "$input_file")  # Read the first line as the test name

    printf "\n\tTest: $test_name ...\n"

    tail -n +2 "$input_file" | ./mtll > "$output_file"  

    diff "$output_file" "tests/outputs/p${part}_${test_num}.out" >/dev/null
    if [ $? -eq 0 ]; then
        printf "\tPassed!  :D\n"
        ((passed_tests++))
    else
        printf "\tFailed!  :(\n"
    fi
}

calculate_coverage() {
    local num_parts="$1"
    local num_tests="$2"
    local total_tests=$((num_parts * num_tests))
    local passed_tests=0

    for ((part=1; part<=num_parts; part++)); do
        printf "\nTesting Part $part:\n\n"
        for ((test=1; test<=num_tests; test++)); do
            run_test "$part" "$test"
        done
    done

    local passed_percentage=$((passed_tests * 100 / total_tests))
    printf "\n\nSummary:\n\n"
    printf "Passed Tests: %d\n" "$passed_tests"
    printf "Total Tests: %d\n" "$total_tests"
    printf "Testcase Completion: %d%%\n" "$passed_percentage"
}

calculate_coverage 3 4
