#!/bin/bash

# Define the number of repetitions
REPEATS=10

# Define the executables to test
executables=("time" "time_shared" "time_pipe")

# Array to store average times
average_times=()

# Function to run a program multiple times and calculate average time
run_test() {
    local prog=$1
    local total_time=0

    echo "Running $prog..."

    for i in $(seq 1 $REPEATS); do
        # Capture output using wrapper script
        output=$(./run_with_time.sh ./$prog ls)
        echo "Output for run $i:"
        echo "$output"

        # Extract the correct elapsed time
        elapsed=$(echo "$output" | grep "Elapsed time:" | head -n 1 | awk '{print $3}')
        
        if [ -z "$elapsed" ]; then
            echo "Error: Unable to find elapsed time in the output"
            exit 1
        fi

        # Convert seconds to milliseconds
        elapsed_ms=$(echo "$elapsed * 1000" | bc)
        echo "Run $i: $elapsed_ms ms"
        total_time=$(echo "$total_time + $elapsed_ms" | bc)
    done

    average_time=$(echo "scale=2; $total_time / $REPEATS" | bc)
    average_times+=("$prog: $average_time ms")
    echo
}

# Make sure the wrapper script is executable
chmod +x run_with_time.sh

# Run tests for each executable
for exe in "${executables[@]}"; do
    run_test $exe
done

# Output all the averages together at the end
echo "=================="
echo "Average Times:"
for avg in "${average_times[@]}"; do
    echo "$avg"
done
echo "=================="
