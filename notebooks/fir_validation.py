import numpy as np
from scipy import signal

# Mesmos coeficientes e sinal de entrada que usaste no main.c
coefficients = np.array([1/3, 1/3, 1/3], dtype=np.float32)
input_signal = np.array([10.0, 20.0, 30.0, 40.0, 50.0, 60.0], dtype=np.float32)

# a=[1.0] porque é um filtro FIR puro (sem realimentação/denominador)
y = signal.lfilter(coefficients, [1.0], input_signal)

for n, (x_n, y_n) in enumerate(zip(input_signal, y)):
    print(f"x[{n}] = {x_n:.2f}  ->  y[{n}] = {y_n:.4f}")