#!/bin/bash

# This script runs a command and prints the elapsed time
# Usage: ./run_with_time.sh <command>

command=$@
# Run the command and capture output
output=$( (/usr/bin/time -f "Elapsed time: %e" $command) 2>&1 )
# Print the output
echo "$output"
