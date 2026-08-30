import numpy as np

# --- Signal parameters ---
f_sampling = 2000          # Sampling frequency (Hz)
f_sine1 = 50                # Sine 1 frequency (Hz)
f_sine2 = 120               # Sine 2 frequency (Hz)
f_sine3 = 300               # Sine 3 frequency (Hz)
m_sine1 = 1.0                # Sine 1 amplitude
m_sine2 = 0.5                # Sine 2 amplitude
m_sine3 = 0.2                # Sine 3 amplitude
T = 1                        # Duration of the observation window (seconds)

N = int(f_sampling * T)      # Total number of samples

# --- Time vector ---
t = np.arange(N) / f_sampling   # Sample instants: n/fs for n = 0, 1, ..., N-1