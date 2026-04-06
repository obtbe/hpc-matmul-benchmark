#!/bin/bash

set -e

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}HPC Matrix Multiplication Benchmark${NC}"
echo -e "${GREEN}========================================${NC}"

# Check if benchmark exists
if [ ! -f "./benchmark" ]; then
    echo -e "${RED}Error: benchmark not found. Run 'make' first.${NC}"
    exit 1
fi

# Create results directory
mkdir -p results

# Run benchmark
./benchmark

# Generate plot
echo -e "${GREEN}Generating plot...${NC}"
python3 plots/generate_plot.py

echo -e "${GREEN}Done. Results in results/${NC}"