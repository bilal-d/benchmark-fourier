🇫🇷 Ce dépôt est un simple benchmark mesurant la rapidité d'exécution
d'une [transformée de Fourier discrète][wk-fr-tfd] implémentée de diverses
façons en C++17, incluant :

- la formule naïve : $X[k] = \sum_{n=0}{N-1} x[n] \mathrm{e}^{-2i\pi kn/N}$ pour $0\le k \lt N$,
- [l’algorithme Cooley–Tukey][wk-en-ct] avec décimation en temps et décimation en fréquence,
- [l’algorithme Split-radix][wk-en-sr],
- via la [bibliothèque FFTW][hp-fftw].

Seules les transformées de taille $N=128$ et $N=1024$ sont considérées.

---

🇬🇧 This repository is a simple benchmark measuring the execution speed of
a [discrete Fourier transform][wk-en-dft], implemented in C++17, using:

- the naïve formula: $X[k] = \sum_{n=0}{N-1} x[n] \mathrm{e}^{-2i\pi kn/N}$ for $0\le k \lt N$,
- the [Cooley–Tukey algorithm][wk-en-ct], with decimation-in-time and decimation-in-frequency,
- the [Split-radix algorithm][wk-en-sr],
- the [FFTW library][hp-fftw].

Transform size is limited to the values $N=128$ and $N=1024$.

[wk-fr-tfd]: https://fr.wikipedia.org/wiki/Transformée_de_Fourier_discrète
[wk-en-dft]: https://en.wikipedia.org/wiki/Discrete_Fourier_transform
[wk-en-ct]: https://en.wikipedia.org/wiki/Cooley–Tukey_FFT_algorithm
[wk-en-sr]: https://en.wikipedia.org/wiki/Split-radix_FFT_algorithm
[hp-fftw]: https://www.fftw.org/
