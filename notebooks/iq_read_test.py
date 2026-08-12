import numpy as np
from scipy import signal
import matplotlib
matplotlib.use('TkAgg')   # ANTES de importar pyplot
import matplotlib.pyplot as plt

x = np.fromfile('data/fm_rds_250k_1Msamples.iq', dtype=np.complex64)
sample_rate = 250e3

# PSD via método de Welch
f, Pxx = signal.welch(x, fs=sample_rate, nperseg=1024, return_onesided=False)

# Reorganiza para a frequência 0 ficar ao centro (fftshift), já que o sinal
# é complexo e a banda ocupa tanto frequências positivas como negativas
f = np.fft.fftshift(f)
Pxx = np.fft.fftshift(Pxx)

plt.figure(figsize=(10, 5))
plt.plot(f / 1e3, 10 * np.log10(Pxx))
plt.xlabel("Frequência (kHz)")
plt.ylabel("Potência (dB/Hz)")
plt.title("PSD do sinal FM — estação a 99.5 MHz (banda base)")
plt.grid(True)
plt.savefig('docs/fm_psd.png', dpi=150)
plt.show()