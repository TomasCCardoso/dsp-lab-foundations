# DSP Lab Foundations

A practical engineering laboratory developed by an **Electrical and Computer Engineering student** to progressively build and demonstrate skills in **Digital Signal Processing (DSP), telecommunications, RF, Software Defined Radio (SDR), and embedded systems**.

This repository documents an ongoing technical development process rather than a finished software library. Each project and implementation is used to develop engineering competencies through:

**Theory → Mathematical Model → Prediction → Implementation → Test → Experiment → Analysis → Documentation**

The objective is to progressively develop the ability to take a technical problem from fundamental theory to a validated implementation, while developing the software engineering practices required to build reliable engineering systems.

This repository is part of a broader long-term technical development path towards engineering work in **telecommunications, aerospace, RF, SDR, embedded systems, radar, and digital communications**.

---

## Objectives

The project aims to develop practical engineering competencies alongside the theoretical foundations acquired through an Electrical and Computer Engineering degree.

Main objectives:

* Translate mathematical and physical concepts into working implementations
* Develop a deeper understanding of DSP fundamentals
* Implement algorithms and data structures from first principles
* Develop reliable and reusable low-level software
* Validate implementations through systematic testing
* Learn to identify and analyse engineering trade-offs
* Develop professional software engineering practices
* Document technical decisions, experiments, results, and limitations
* Progressively connect DSP theory with real telecommunications, RF, SDR, and embedded systems

The emphasis is on **developing engineering capability**, not simply completing exercises or producing code that works once.

---

## Engineering Approach

Each component is developed progressively rather than being treated as an isolated coding exercise.

The intended workflow is:

```text
Engineering Problem
        ↓
Required Theory
        ↓
Mathematical Model
        ↓
Expected Behaviour
        ↓
Implementation
        ↓
Unit Tests
        ↓
Experimental Validation
        ↓
Documentation
        ↓
Engineering Conclusions
```

Where appropriate, implementations will be compared against established numerical references such as **NumPy** or **SciPy**.

The project prioritises understanding the underlying model and being able to justify implementation decisions over simply obtaining the correct output.

---

## Technical Stack

### Programming

* C
* Python — planned for future DSP analysis and experimentation
* C++ — planned for future low-level and embedded work

### Scientific Computing

* NumPy — planned
* SciPy — planned
* Matplotlib — planned

### Development

* Linux
* GCC
* Git
* GitHub
* VS Code

### Testing & Documentation

* Custom C test framework
* Markdown
* Technical documentation

Additional tools such as **CMake, pytest, Jupyter, GNU Radio, STM32 tooling, and FPGA development tools** will be introduced when technically justified by future projects.

---

## Repository Structure

```text
dsp-lab-foundations/
│
├── data/
│   ├── raw/
│   └── processed/
│
├── docs/
│   ├── ring-buffer.md
│   └── ...
│
├── src/
│   └── ring_buffer/
│       ├── ring_buffer.c
│       └── ring_buffer.h
│
├── tests/
│   └── test_ring_buffer.c
│
├── README.md
├── ROADMAP.md
├── requirements.txt
└── .gitignore
```

The repository structure will evolve as new DSP components, experiments, and validation workflows are introduced.

---

## Current Status

🚧 **Work in Progress**

The project is currently focused on establishing the low-level software and testing foundations required for future DSP implementations.

### Implemented

#### Ring Buffer

A circular buffer implemented in C and designed as a reusable low-level component for future DSP processing.

Current functionality includes:

* Buffer initialization
* Sample insertion
* Tracking the number of stored samples
* Circular write indexing
* Overwriting the oldest sample when the buffer is full
* Retrieval of recent samples
* Bounds checking
* Input validation
* Wraparound behaviour

The implementation is accompanied by tests covering:

* Initial state
* Empty-buffer behaviour
* Single-sample insertion
* Multiple-sample insertion
* Retrieval ordering
* Buffer capacity
* Wraparound behaviour
* Internal state (`head`, `count`, and `size`)

The Ring Buffer is currently the main validated implementation in the repository.

---

## Development Roadmap

The project will progressively cover the following areas.

### DSP Foundations

* Sampling and aliasing
* Discrete-time signals
* Convolution
* Correlation
* DFT and FFT
* FIR filters
* IIR filters
* Spectral analysis
* Power Spectral Density (PSD)
* Welch's method
* Short-Time Fourier Transform (STFT)
* Resampling
* Noise and stochastic signals

### SDR & Digital Communications

* Complex numbers and IQ representation
* Complex baseband
* Digital mixing
* Filtering
* AM/FM
* FSK
* PSK
* QPSK
* QAM
* Synchronisation
* Carrier recovery
* Timing recovery
* Channel estimation

### Embedded DSP

* C/C++
* Memory management and data structures
* Fixed-point arithmetic
* ADC/DAC concepts
* DMA
* Interrupt-driven processing
* Real-time constraints
* ARM-based DSP
* Hardware/software partitioning

### RF & Signal Processing Systems

* RF signal chains
* Mixers and frequency translation
* Oscillators
* Filters
* Amplifiers
* Noise and dynamic range
* ADC/DAC limitations
* Antennas and measurement concepts

### Radar & Advanced Applications

* Doppler processing
* Matched filtering
* Range estimation
* Range-Doppler processing
* Detection
* Tracking
* Radar signal processing
* SAR fundamentals

The roadmap is intentionally progressive. New topics will be introduced when the underlying concepts and implementation foundations are sufficiently mature.

---

## Engineering Standards

The project is developed with an emphasis on engineering quality rather than implementation speed.

Important considerations include:

* **Correctness**
* **Mathematical validity**
* **Numerical stability**
* **Computational complexity**
* **Memory usage**
* **Latency**
* **Precision**
* **Robustness**
* **Testability**
* **Maintainability**
* **Reproducibility**

A component is not considered complete simply because it compiles or produces the expected output once.

Whenever appropriate, implementations should include:

* Clearly defined requirements
* Explicit assumptions
* Mathematical models
* Unit tests
* Boundary and failure cases
* Experimental validation
* Performance considerations
* Documentation of limitations

---

## Current Focus

The immediate focus is to strengthen the project's development and validation infrastructure before moving into more complex DSP algorithms.

### Next steps

1. Formalise the Ring Buffer API and invariants
2. Expand edge-case and boundary-condition testing
3. Introduce a reproducible C build system
4. Automate test execution
5. Improve technical documentation
6. Establish a cleaner development workflow
7. Begin the next DSP component once the foundation is sufficiently validated

---

## Long-Term Goal

The long-term objective is to develop the ability to approach a real signal-processing engineering problem systematically.

For example:

```text
Signal Acquisition
        ↓
Sampling
        ↓
IQ Representation
        ↓
Filtering
        ↓
Frequency Translation
        ↓
Synchronisation
        ↓
Demodulation
        ↓
DSP
        ↓
Detection / Estimation
        ↓
Embedded Implementation
        ↓
Validation
```

The goal is to eventually be able to reason through this complete chain, make and justify engineering decisions, implement the required processing, and validate the resulting system under realistic constraints.

---

## About

This repository is developed as part of the technical development of an **Electrical and Computer Engineering student at FEUP**, with a particular interest in:

* Telecommunications
* Digital Signal Processing
* RF
* Software Defined Radio
* Embedded Systems
* Digital Communications
* Radar and SAR
* GNSS
* Satellites
* UAVs
* Aerospace and Defence

The project is intended to serve both as a learning laboratory and as a progressively developing portfolio of engineering work.

---

**Status:** Active development
**Primary focus:** DSP foundations, low-level implementation, testing, validation, and engineering methodology
