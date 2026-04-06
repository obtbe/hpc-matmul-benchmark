CXX = g++
CXXFLAGS = -O2 -fopenmp -march=native

all: benchmark

benchmark: src/benchmark.cpp src/naive_matmul.cpp src/blocked_matmul.cpp src/openmp_matmul.cpp
	$(CXX) $(CXXFLAGS) -o benchmark $^

clean:
	rm -f benchmark results/*.csv results/*.png

# Setup virtual environment
setup-venv:
	python3 -m venv venv
	. venv/bin/activate && pip install -r requirements.txt

# Run benchmark and generate plot with venv
run: benchmark setup-venv
	./benchmark
	. venv/bin/activate && python3 plots/generate_plot.py

# Just generate plot from existing data (no re-run)
plot: setup-venv
	. venv/bin/activate && python3 plots/generate_plot.py

# Clean everything including venv
clean-all: clean
	rm -rf venv

.PHONY: all clean run setup-venv plot clean-all