import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

# ============================================================
# Signal parameters
# ============================================================
f_sampling = 2000   # Sampling frequency (Hz) — ~6.7x fmax, Nyquist + oversampling margin
f_sine1 = 50         # Sine 1 frequency (Hz)
f_sine2 = 120        # Sine 2 frequency (Hz)
f_sine3 = 300        # Sine 3 frequency (Hz)
m_sine1 = 1.0        # Sine 1 amplitude
m_sine2 = 0.5        # Sine 2 amplitude
m_sine3 = 0.2        # Sine 3 amplitude
T = 1                # Duration of the observation window (seconds) — Δf = 1Hz

N = int(f_sampling * T)   # Total number of samples

# ============================================================
# Time vector
# ============================================================
# Sample instants: n/fs for n = 0, 1, ..., N-1
# (np.arange avoids the endpoint-inclusion issue of linspace)
t = np.arange(N) / f_sampling

# ============================================================
# Composite signal: 3 sinusoids + AWGN
# ============================================================
sine_1 = m_sine1 * np.sin(2 * np.pi * f_sine1 * t)   # 50 Hz component
sine_2 = m_sine2 * np.sin(2 * np.pi * f_sine2 * t)   # 120 Hz component
sine_3 = m_sine3 * np.sin(2 * np.pi * f_sine3 * t)   # 300 Hz component

noise = np.random.normal(0, 0.1, size=N)              # Additive White Gaussian Noise (AWGN)
comp_signal = sine_1 + sine_2 + sine_3 + noise         # Composite signal

# Sanity checks
print(comp_signal.shape)   # Expected: (2000,)
print(comp_signal[:5])     # First samples, should vary and be non-zero

# ============================================================
# Windowing (Hann) — reduces spectral leakage at the cost of
# a wider main lobe (~2x vs rectangular)
# ============================================================
window = np.hanning(N)
windowed_signal = window * comp_signal   # w[n] * x[n]

# ============================================================
# Spectral analysis (original signal)
# ============================================================
spectrum = np.fft.rfft(windowed_signal)              # Real FFT (signal is real-valued)
freqs = np.fft.rfftfreq(N, d=1 / f_sampling)           # Frequency axis (Hz)

magnitude = np.abs(spectrum)                           # Magnitude (combines real + imaginary parts)
magnitude_db = 20 * np.log10(magnitude + 1e-12)        # Magnitude in dB (epsilon avoids log10(0))

# ============================================================
# Bandpass filter design (Butterworth, isolating ~120 Hz)
# ============================================================
f_low = 95           # Lower cutoff frequency (Hz)
f_high = 145          # Upper cutoff frequency (Hz)
filter_order = 4       # Order 4: sufficient given sosfiltfilt doubles the effective rolloff

# scipy expects normalized frequencies (fraction of the Nyquist frequency)
nyquist = f_sampling / 2
low_norm = f_low / nyquist
high_norm = f_high / nyquist

sos = signal.butter(filter_order, [low_norm, high_norm], btype='bandpass', output='sos')

# Zero-phase filtering: two passes (forward + backward) cancel phase distortion,
# at the cost of doubling the effective filter order / rolloff steepness
filtered_signal = signal.sosfiltfilt(sos, comp_signal)

# ============================================================
# Spectral analysis (filtered signal)
# ============================================================
windowed_filtered = window * filtered_signal
spectrum_filtered = np.fft.rfft(windowed_filtered)
mag_filtered = np.abs(spectrum_filtered)
mag_filtered_db = 20 * np.log10(mag_filtered + 1e-12)

# ============================================================
# SNR / SINR calculation (ground truth — signal is synthetic,
# so the clean target tone is known exactly)
# ============================================================
s_n = m_sine2 * np.sin(2 * np.pi * f_sine2 * t)   # Clean 120 Hz target tone
Ps = np.mean(s_n ** 2)                              # Signal power

# SNR: target tone vs. AWGN only
Pe_noise_only = np.mean(noise ** 2)
SNR_pure = 10 * np.log10(Ps / Pe_noise_only)

# SINR: target tone vs. other tones + AWGN (interference + noise)
interference_plus_noise = sine_1 + sine_3 + noise
Pe_total = np.mean(interference_plus_noise ** 2)
SINR = 10 * np.log10(Ps / Pe_total)

print(f"SNR (pure, vs AWGN only): {SNR_pure:.2f} dB")
print(f"SINR (vs other tones + noise): {SINR:.2f} dB")

# ============================================================
# Plots
# ============================================================
plt.figure(figsize=(10, 5))
plt.plot(freqs, magnitude_db, label='Original Signal Spectrum')
plt.plot(freqs, mag_filtered_db, label='Filtered Signal Spectrum (~120Hz Butterworth)', color='red')
plt.legend()
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude (dB)")
plt.title("Spectrum of composite signal (Hann window)")
plt.grid(True)
plt.show()