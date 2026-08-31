import numpy as np
import matplotlib.pyplot as plt

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

sine_1 = m_sine1*np.sin(2*np.pi*f_sine1*t); #Sine 1 wave
sine_2 = m_sine2*np.sin(2*np.pi*f_sine2*t); #Sine 2 wave
sine_3 = m_sine3*np.sin(2*np.pi*f_sine3*t); #Sine 3 wave

noise = np.random.normal(0, 0.1, size=N) # AWGN
comp_signal = sine_1 + sine_2 + sine_3 + noise #Signal with 3 sines and AWGN

print(comp_signal.shape) #Test
print(comp_signal[:5]) #Test

window = np.hanning(N) #Deffining Hanning Window
windowed_signal = window * comp_signal #Multiplying w[n] * x[n]

spectrum = np.fft.rfft(windowed_signal) #Real FFT 
freqs = np.fft.rfftfreq(N, d = 1/f_sampling)

magnitude = np.abs(spectrum) #Sinal module
magnitude_db = 20 * np.log10(magnitude + 1e-12) #Sinal magnitude translated to dB

plt.figure(figsize=(10,5))
plt.plot(freqs, magnitude_db)
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude (dB)")
plt.title("Spectrum of composite signal (Hann window)")
plt.grid(True)
plt.show()