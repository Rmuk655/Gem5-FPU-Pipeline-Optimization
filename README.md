# Gem5 FPU Pipeline Optimization  
## Speeding Up Integer Programs with FPUs

This repository contains the **course project** for the Computer Architecture course, based on the project proposal titled **“Speeding Up Integer Programs with FPUs”**.

The project explores how **Floating Point Units (FPUs)** can be leveraged to accelerate programs that are traditionally written using **integer-only operations**, and analyzes the architectural and performance implications of such an approach.

---

## 📘 Project Overview

Modern processors contain powerful **Floating Point Units (FPUs)** designed for high-throughput numerical computation.  
This project investigates whether and how FPUs can be used to:

- Speed up integer-heavy programs
- Reduce execution time using architectural parallelism
- Explore alternative instruction usage beyond conventional integer pipelines

The work is inspired by architectural research and focuses on **performance analysis and implementation insights**.

---

## 🎯 Objectives

The primary objectives of this project are:

- Understand the role of FPUs in modern processors
- Analyze integer program behavior on conventional pipelines
- Explore the feasibility of mapping integer operations onto FPUs
- Compare performance between integer execution and FPU-assisted execution
- Study trade-offs in terms of complexity, correctness, and efficiency

---

## 🧠 Core Concepts Involved

- CPU microarchitecture
- Integer vs floating-point execution units
- Instruction-level parallelism (ILP)
- Performance optimization techniques
- Program analysis and benchmarking

---

## 🧪 Experimental Setup

The project involves:

- Implementing representative **integer programs**
- Modifying or re-implementing them to utilize **floating-point operations**
- Measuring and comparing:
  - Execution time
  - Instruction counts
  - Performance characteristics

Benchmarks and test programs are chosen to clearly demonstrate the effects of FPU usage.

---

## 📂 Repository Structure

```
.
├── CARCH_PROJECT.pdf            # Original project problem statement
├── src/                         # Source code and experiments
│   ├── integer_version/         # Baseline integer-only implementations
│   ├── fpu_version/             # FPU-assisted implementations
│   └── benchmarks/              # Test inputs and benchmark programs
├── results/                     # Performance results and analysis
├── report/                      # Final report and documentation
└── README.md                    # This file
```

*(Folder names may vary depending on implementation.)*

---

## ⚙️ Compilation & Execution

Programs are implemented in **C/C++**.

Compile using:

```bash
gcc program.c -o program
./program
```

or

```bash
g++ program.cpp -o program
./program
```

Specific build instructions (if any) are provided inside the respective folders.

---

## 📊 Evaluation & Analysis

The evaluation focuses on:

- Performance improvement gained using FPUs
- Accuracy and correctness of computation
- Overheads introduced by floating-point conversions
- Architectural insights from experimental results

Results are documented in the `results/` and `report/` directories.

---

## ⚠️ Academic Integrity

This project is part of academic coursework.

- All work is original
- External references are properly cited
- Collaboration policies follow course guidelines

---

## 📌 Acknowledgements

This project was carried out as part of the **Computer Architecture** course, inspired by academic research on processor microarchitecture and performance optimization.
