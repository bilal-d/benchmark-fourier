# SPDX-License-Identifier: MIT
# Copyright © 2019  Bilal Djelassi

CXX := c++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic -Wfatal-errors
OCTAVE := octave-cli

.PHONY: all
all: test_fourier.prg

test_fourier.prg: \
    test_fourier.obj \
    custom_complex.obj \
    fourier_transform_vector_128.obj \
    fourier_transform_radix2dit_128.obj \
    fourier_transform_radix2dif_128.obj \
    fourier_transform_splitradix_128.obj \
    fourier_transform_vector_1024.obj \
    fourier_transform_radix2dit_1024.obj \
    fourier_transform_radix2dif_1024.obj \
    fourier_transform_splitradix_1024.obj \
    fourier_transform_vector_128_ccomplex.obj \
    fourier_transform_radix2dit_128_ccomplex.obj \
    fourier_transform_radix2dif_128_ccomplex.obj \
    fourier_transform_splitradix_128_ccomplex.obj \
    fourier_transform_vector_1024_ccomplex.obj \
    fourier_transform_radix2dit_1024_ccomplex.obj \
    fourier_transform_radix2dif_1024_ccomplex.obj \
    fourier_transform_splitradix_1024_ccomplex.obj \
    fourier_transform_libfftw.obj
	$(info c++.link $@)
	@$(CXX) $(CXXFLAGS) -o $@ $+ -lfftw3f -lm

%.obj: %.cpp
	$(info c++.compile $<)
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: precalculated
precalculated: \
    fourier_matrix_128.inc \
    fourier_vector_128.inc \
    fourier_radix2dit_twiddle_128.inc \
    fourier_radix2dif_twiddle_128.inc \
    fourier_radix2dif_reorder_128.inc \
    fourier_splitradix_twiddle_128.inc \
    fourier_vector_1024.inc \
    fourier_radix2dit_twiddle_1024.inc \
    fourier_radix2dif_twiddle_1024.inc \
    fourier_radix2dif_reorder_1024.inc \
    fourier_splitradix_twiddle_1024.inc

%.inc: generate_%.m
	$(OCTAVE) $< >$@

.PHONY: clean
clean:
	rm -f test_fourier.prg
	rm -f test_fourier.obj
	rm -f custom_complex.obj
	rm -f fourier_transform_vector_128.obj
	rm -f fourier_transform_radix2dit_128.obj
	rm -f fourier_transform_radix2dif_128.obj
	rm -f fourier_transform_splitradix_128.obj
	rm -f fourier_transform_vector_1024.obj
	rm -f fourier_transform_radix2dit_1024.obj
	rm -f fourier_transform_radix2dif_1024.obj
	rm -f fourier_transform_splitradix_1024.obj
	rm -f fourier_transform_vector_128_ccomplex.obj
	rm -f fourier_transform_radix2dit_128_ccomplex.obj
	rm -f fourier_transform_radix2dif_128_ccomplex.obj
	rm -f fourier_transform_splitradix_128_ccomplex.obj
	rm -f fourier_transform_vector_1024_ccomplex.obj
	rm -f fourier_transform_radix2dit_1024_ccomplex.obj
	rm -f fourier_transform_radix2dif_1024_ccomplex.obj
	rm -f fourier_transform_splitradix_1024_ccomplex.obj
	rm -f fourier_transform_libfftw.obj

.PHONY: clean-results
clean-results:
	rm -f x_128.mat
	rm -f x_1024.mat
	rm -f y_vector_128.mat
	rm -f y_radix2dit_128.mat
	rm -f y_radix2dif_128.mat
	rm -f y_splitradix_128.mat
	rm -f y_vector_1024.mat
	rm -f y_radix2dit_1024.mat
	rm -f y_radix2dif_1024.mat
	rm -f y_splitradix_1024.mat
	rm -f y_vector_128_ccomplex.mat
	rm -f y_radix2dit_128_ccomplex.mat
	rm -f y_radix2dif_128_ccomplex.mat
	rm -f y_splitradix_128_ccomplex.mat
	rm -f y_vector_1024_ccomplex.mat
	rm -f y_radix2dit_1024_ccomplex.mat
	rm -f y_radix2dif_1024_ccomplex.mat
	rm -f y_splitradix_1024_ccomplex.mat
	rm -f y_libfftw_128.mat
	rm -f y_libfftw_128_aligned.mat
	rm -f y_libfftw_1024.mat
	rm -f y_libfftw_1024_aligned.mat
