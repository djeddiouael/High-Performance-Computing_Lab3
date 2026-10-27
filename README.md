# HPC Lab 3 – Python Profiling and OpenMP

This repository contains the practical work for **Lab 3: High Performance Computing**, Semester 2 (2025–2026), at the University of Boumerdes.

The lab focuses on performance profiling in Python and shared-memory parallel programming using OpenMP in C.

## 🎯 Learning Objectives

- Identify performance bottlenecks using Python profiling tools.
- Understand the limitations of `profile` when working with C-extension functions.
- Compile and run OpenMP programs using GCC.
- Use OpenMP directives such as `parallel`, `parallel for`, and `reduction`.
- Measure and compare serial and parallel execution times.
- Handle race conditions using `reduction` and `atomic`.
- Evaluate parallel performance using speedup.

## 🛠️ Technologies

- Python
- NumPy
- C
- OpenMP
- GCC
- Git and GitHub

## 📂 Project Structure

```text
HPC-Lab3/
├── PartA/
│   └── simulation.py       # Python profiling
├── PartB/
│   ├── hello_omp.c         # OpenMP thread identification
│   ├── vector_add.c        # Serial vs. parallel vector addition
│   └── pi_integration.c    # Numerical integration of pi
└── README.md
```

*Note: Adjust the filenames and folders to match the actual repository structure.*

## 🐍 Part A – Python Profiling

This part introduces Python performance analysis using `profile` and `cProfile`.

### Exercise 1 – Bottleneck Detection

The exercise compares two functions:

- `fast_task()` uses `numpy.sum()` to perform an array operation efficiently.
- `slow_task()` calculates the sum of squared elements using a pure Python loop.

Run the profilers:

```bash
python -m profile -s cumtime simulation.py
python -m cProfile -s cumtime simulation.py
```

The profiling results help identify the performance bottleneck and explain why optimized NumPy operations can outperform pure Python loops.

## ⚡ Part B – OpenMP Parallel Programming

This part explores shared-memory parallelism in C using OpenMP.

### Exercise 2 – Thread IDs

Create a parallel region in which each thread displays its ID and the total number of threads.

**Concepts:** `omp_get_thread_num()`, `omp_get_num_threads()`, `master`, and `barrier`.

### Exercise 3 – Vector Addition

Compute the element-wise sum of two arrays:

\[
C[i] = A[i] + B[i]
\]

Compare serial and parallel execution times using different thread counts.

**Concepts:** `parallel for`, `omp_get_wtime()`, execution time, and speedup.

### Exercise 4 – Numerical Integration of π

Approximate π using the rectangle integration method and parallelize the summation with OpenMP.

Compare the following approaches:

- `reduction(+:sum)`
- `critical` sections

**Concepts:** numerical integration, synchronization, race conditions, and parallel performance.

## 💻 Installation and Setup

### 1. Install the dependencies

Install NumPy:

```bash
pip install numpy
```

On Ubuntu or Debian, install GCC and Python:

```bash
sudo apt update
sudo apt install gcc python3 python3-pip -y
```

Verify the compiler installation:

```bash
gcc --version
```

### 2. Compile OpenMP programs

Use the `-fopenmp` flag to enable OpenMP support.

For example:

```bash
gcc -fopenmp PartB/hello_omp.c -o hello_omp
```

### 3. Run the program

Set the number of threads to four:

```bash
export OMP_NUM_THREADS=4
./hello_omp
```

On Windows, use a terminal configured for MinGW-w64. On macOS, ensure that the compiler and OpenMP runtime are properly configured.

## 📊 Performance Evaluation

The experiments compare serial and parallel execution times.

| Metric | Description |
|---|---|
| Serial Time | Execution time without parallelization |
| Parallel Time | Execution time using multiple threads |
| Speedup | Ratio of serial time to parallel time |

The speedup is calculated as:

\[
S = \frac{T_{\text{serial}}}{T_{\text{parallel}}}
\]

Parallel performance depends on the number of threads, synchronization overhead, workload size, and available CPU resources.

*Execution times and speedup values should be measured on the machine used for the experiments.*

## 📚 Key Concepts

- Python performance profiling
- Bottleneck identification
- NumPy optimization
- Shared-memory parallelism
- OpenMP directives
- Race conditions and synchronization
- Parallel speedup and scalability

## 🎓 Academic Information

- **University:** University of Boumerdes
- **Course:** High Performance Computing
- **Semester:** Semester 2 (2025–2026)
- **Lab:** Lab 3
- **Instructor:** Dr. Tayeb BENZENATI
- **Work Type:** Individual practical work

## 👤 Author

**Ouael DJEDDI**

- GitHub: [@djeddiouael](https://github.com/djeddiouael)

## 📄 License

No license has been specified. Add a `LICENSE` file if you intend to distribute this project publicly.
