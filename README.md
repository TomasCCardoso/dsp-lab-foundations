# DSP Lab Foundations

Applied Digital Signal Processing (DSP) foundations implemented from scratch using Python, NumPy, and SciPy.

This repository is part of a long-term technical development path focused on **Digital Signal Processing, RF & Telecommunications, Software Defined Radio (SDR), and embedded systems**.

The goal is not only to study DSP theory, but to progressively translate mathematical concepts into **tested, documented, and reusable engineering implementations**.

---

## Objectives

The project aims to develop a strong practical foundation in DSP through progressive implementation and experimentation.

Main objectives:

- Translate DSP theory into working software implementations
- Develop a deeper understanding of discrete-time signal processing
- Implement fundamental DSP algorithms from first principles
- Analyse signals in both time and frequency domains
- Design and evaluate digital filters
- Develop reusable signal-processing utilities
- Apply numerical methods using Python, NumPy, and SciPy
- Establish software engineering practices suitable for future engineering projects
- Build a foundation for more advanced work in SDR, RF, communications, and embedded DSP

---

## Technical Stack

### Programming

- Python
- C/C++ — planned for future low-level implementations

### Scientific Computing

- NumPy
- SciPy

### Development

- Git
- GitHub
- Linux
- VS Code

### Testing & Documentation

- pytest
- Jupyter Notebooks
- Markdown

---

## Repository Structure

```text
dsp-lab-foundations/
│
├── src/
│   └── dsp/
│       ├── ...
│       └── ...
│
├── tests/
│   ├── ...
│   └── ...
│
├── notebooks/
│   ├── ...
│   └── ...
│
├── docs/
│   ├── ...
│   └── ...
│
├── README.md
├── ROADMAP.md
└── ...


## Current Status

🚧 **Work in Progress**

The project has progressed beyond the initial tooling phase and currently includes several implemented DSP components and signal-processing experiments.

### Implemented

- **Ring Buffer**
  - Circular buffer implementation in C
  - Sample insertion and circular indexing
  - Retrieval of recent samples using modular arithmetic
  - Input validation and error handling

- **FIR Filter**
  - Finite Impulse Response filter implementation
  - Coefficient-based convolution
  - Structured for reusable DSP processing

- **IQ Signal Analysis**
  - Python tooling for reading and analysing IQ signal data
  - Signal representation and basic inspection
  - Foundation for future spectral and SDR-oriented analysis

### Current Development

The project is currently expanding from fundamental DSP data structures and algorithms towards more advanced signal-processing capabilities.

The next development stages focus on:

- Spectral analysis
- FFT implementation and analysis
- Digital filter design and evaluation
- Sampling and reconstruction
- Modulation and demodulation
- IQ signal processing
- SDR-oriented signal analysis
