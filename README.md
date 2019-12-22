🇫🇷 Ce dépôt est un simple benchmark mesurant la rapidité d'exécution
des [transformées de Fourier discrètes][wk-fr-tfd] de taille $N=128$ et $N=1024$,
implémentées de diverses façons en C++17, incluant :

- la formule naïve : $X[k] = \displaystyle\sum_{n=0}^{N-1} x[n] \exp(-2i\pi kn/N)$ pour $0\le k \lt N$,
où les [*twiddle factors*][wk-tf] $\omega_N^m=\exp(-2i\pi m/N)$ sont précalculés avec
des scripts [Octave][hp-octave],
- [l’algorithme Cooley–Tukey][wk-en-ct] avec décimation en temps et décimation en fréquence,
- [l’algorithme Split-radix][wk-en-sr],
- via la [bibliothèque FFTW][hp-fftw].


### Comment construire sous Linux ?
Il faudra disposer d'un compilateur C++ prenant en charge le standard C++17
(GCC ou Clang sont largement suffisants), et de la bibliothèque [FFTW][hp-fftw]
en version 3.3.8.

* Avec le gestionnaire de paquets `apt` (Debian, Ubuntu, ...) :
    ```
    $ sudo apt install g++ make libfftw3-dev      # si on préfère G++
    $ sudo apt install clang make libfftw3-dev    # si on préfère Clang
    ```

* Avec le gestionnaire de paquets `dnf` (Fedora, CentOS, ...) :
    ```
    $ sudo dnf install gcc-c++ make fftw-devel    # si on préfère G++
    $ sudo dnf install clang make fftw-devel      # si on préfère Clang
    ```

* Avec le gestionnaire de paquets `pacman` (ArchLinux et dérivées) :
    ```
    $ sudo pacman -S --needed gcc make fftw       # si on préfère G++
    $ sudo pacman -S --needed clang make fftw     # si on préfère Clang
    ```

Ensuite, sur une copie clonée du dépôt :
```
$ make                      # pour construire l'exécutable ./test_fourier.prg
$ make -j$(nproc --all)     # ou si on souhaite utiliser tous les cœurs de la machine

$ ./test_fourier.prg        # pour lancer le benchmark

$ make clean                # pour nettoyer les fichiers objet
```

### Comment construire sous une autre plateforme ?
Une fois la bibliothèque FFTW installée, il suffira de compiler tous les sources
`*.cpp` pour générer un exécutable.
Le gestionnaire de bibliothèques *open source* `vcpkg` me paraît prometteur pour
simplifier la construction et l'installation de bibliothèques telles que FFTW
sur Windows.

La bibliothèque FFTW est disponible sur `vcpkg`, voir l'article: [Vcpkg: a tool to
acquire and build C++ open source libraries on Windows][msft-vcpkg].

---

🇬🇧 This repository is a simple benchmark that measures the execution speed
of [discrete Fourier transforms][wk-en-dft] of size $N=128$ and $N=1024$,
implemented in C++17, using:

- the naïve formula: $X[k] = \displaystyle\sum_{n=0}^{N-1} x[n] \exp(-2i\pi kn/N)$ for $0\le k \lt N$,
where [twiddle factors][wk-tf] $\omega_N^m=\exp(-2i\pi m/N)$ are precomputed using
[Octave][hp-octave],
- the [Cooley–Tukey algorithm][wk-en-ct], with decimation-in-time and decimation-in-frequency,
- the [Split-radix algorithm][wk-en-sr],
- the [FFTW library][hp-fftw].

### How to build on Linux?
A C++ compiler supporting C++17 is required.  The [FFTW][hp-fftw] library
v3.3.8 is also required.

* If using `apt` (on Debian, Ubuntu, ...):
    ```
    $ sudo apt install g++ make libfftw3-dev      # for G++
    $ sudo apt install clang make libfftw3-dev    # for Clang
    ```

* If using `dnf` (on Fedora, CentOS, ...):
    ```
    $ sudo dnf install gcc-c++ make fftw-devel    # for G++
    $ sudo dnf install clang make fftw-devel      # for Clang
    ```

* If using `pacman` (on ArchLinux and derivatives):
    ```
    $ sudo pacman -S --needed gcc make fftw       # for G++
    $ sudo pacman -S --needed clang make fftw     # for Clang
    ```

Then, after cloning the repository:
```
$ make                      # to build ./test_fourier.prg
$ make -j$(nproc --all)     # for a faster build using all cores

$ ./test_fourier.prg        # to run the benchmark

$ make clean                # to remove object files
```

### How to build on another platfom?
Once FFTW is installed, all `*.cpp` files can be compiled using your favorite
compiler to generate a single executable.
On Windows, `vcpkg` seems very promising for building and installing open source
libraries like FFTW.

FFTW is available through `vcpkg`, see [Vcpkg: a tool to acquire and build C++
open source libraries on Windows][msft-vcpkg].

[wk-fr-tfd]: https://fr.wikipedia.org/wiki/Transformée_de_Fourier_discrète
[wk-en-dft]: https://en.wikipedia.org/wiki/Discrete_Fourier_transform
[wk-en-ct]: https://en.wikipedia.org/wiki/Cooley–Tukey_FFT_algorithm
[wk-en-sr]: https://en.wikipedia.org/wiki/Split-radix_FFT_algorithm
[wk-tf]: https://en.wikipedia.org/wiki/Twiddle_factor
[hp-fftw]: https://www.fftw.org/
[hp-octave]: https://octave.org/
[msft-vcpkg]: https://devblogs.microsoft.com/cppblog/vcpkg-a-tool-to-acquire-and-build-c-open-source-libraries-on-windows/
