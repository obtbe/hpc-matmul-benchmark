#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Read data
df = pd.read_csv('results/raw_data.csv')

# Calculate speedups
df['blocked_speedup'] = df['naive_time'] / df['blocked_time']
df['openmp_speedup'] = df['naive_time'] / df['openmp_time']

# Create plot
plt.figure(figsize=(10, 6))

plt.plot(df['size'], df['openmp_speedup'], 'o-', linewidth=2, markersize=8, label='OpenMP (8 cores)')
plt.plot(df['size'], df['blocked_speedup'], 's-', linewidth=2, markersize=8, label='Blocked/Tiled (cache-optimized)')

plt.xlabel('Matrix Size (n x n)', fontsize=12)
plt.ylabel('Speedup (vs Naive O(n³))', fontsize=12)
plt.title('Matrix Multiplication Performance Comparison', fontsize=14)
plt.legend(fontsize=11)
plt.grid(True, alpha=0.3)
plt.axhline(y=1, color='gray', linestyle='--', alpha=0.5)

# Annotate best speedup
max_speedup = df['openmp_speedup'].max()
max_idx = df['openmp_speedup'].idxmax()
plt.annotate(f'Max: {max_speedup:.1f}x at n={df.loc[max_idx, "size"]}', 
             xy=(df.loc[max_idx, 'size'], max_speedup),
             xytext=(10, 10), textcoords='offset points',
             fontsize=10, bbox=dict(boxstyle='round,pad=0.3', facecolor='yellow', alpha=0.3))

plt.tight_layout()
plt.savefig('results/speedup_plot.png', dpi=150)
print("Plot saved to results/speedup_plot.png")