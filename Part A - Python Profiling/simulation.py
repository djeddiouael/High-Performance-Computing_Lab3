import numpy as np

def fast_task(data):
    return np.sum(data)  # NumPy C-extension

def slow_task(data):
    total = 0.0
    for x in data:  # Pure Python loop - BOTTLENECK
        total += x + x
    return total

# OPTIMIZED VERSION - using NumPy vectorization
def fast_task_optimized(data):
    return np.sum(data + data)  # Vectorized operation

def main():
    data = np.random.rand(1_000_000)
    
    # Original version
    print("Original version:")
    for _ in range(5):
        fast_task(data)
    
    for _ in range(5):
        slow_task(data)
    
    # Optimized version
    print("\nOptimized version:")
    for _ in range(5):
        fast_task(data)
    
    for _ in range(5):
        fast_task_optimized(data)

if __name__ == "__main__":
    main()