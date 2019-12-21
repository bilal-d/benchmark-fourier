% SPDX-License-Identifier: MIT
% Copyright © 2019  Bilal Djelassi

function compare_fourier_routines
    load('x_128.mat');
    load('y_vector_128.mat');
    load('y_radix2dit_128.mat');
    load('y_radix2dif_128.mat');
    load('y_splitradix_128.mat');
    load('y_vector_128_ccomplex.mat');
    load('y_radix2dit_128_ccomplex.mat');
    load('y_radix2dif_128_ccomplex.mat');
    load('y_splitradix_128_ccomplex.mat');
    load('y_libfftw_128.mat');
    load('y_libfftw_128_aligned.mat');

    load('x_1024.mat');
    load('y_vector_1024.mat');
    load('y_radix2dit_1024.mat');
    load('y_radix2dif_1024.mat');
    load('y_splitradix_1024.mat');
    load('y_vector_1024_ccomplex.mat');
    load('y_radix2dit_1024_ccomplex.mat');
    load('y_radix2dif_1024_ccomplex.mat');
    load('y_splitradix_1024_ccomplex.mat');
    load('y_libfftw_1024.mat');
    load('y_libfftw_1024_aligned.mat');

    y_128  = fft(x_128);
    y_1024 = fft(x_1024);

    function e = relative_error(x1, x2)
        e = norm(x2 - x1) / norm(x1);
    end

    e_vector_128               = relative_error(y_128, y_vector_128);
    e_radix2dit_128            = relative_error(y_128, y_radix2dit_128);
    e_radix2dif_128            = relative_error(y_128, y_radix2dif_128);
    e_splitradix_128           = relative_error(y_128, y_splitradix_128);
    e_vector_128_ccomplex      = relative_error(y_128, y_vector_128_ccomplex);
    e_radix2dit_128_ccomplex   = relative_error(y_128, y_radix2dit_128_ccomplex);
    e_radix2dif_128_ccomplex   = relative_error(y_128, y_radix2dif_128_ccomplex);
    e_splitradix_128_ccomplex  = relative_error(y_128, y_splitradix_128_ccomplex);
    e_libfftw_128              = relative_error(y_128, y_libfftw_128);
    e_libfftw_128_aligned      = relative_error(y_128, y_libfftw_128_aligned);

    e_vector_1024              = relative_error(y_1024, y_vector_1024);
    e_radix2dit_1024           = relative_error(y_1024, y_radix2dit_1024);
    e_radix2dif_1024           = relative_error(y_1024, y_radix2dif_1024);
    e_splitradix_1024          = relative_error(y_1024, y_splitradix_1024);
    e_vector_1024_ccomplex     = relative_error(y_1024, y_vector_1024_ccomplex);
    e_radix2dit_1024_ccomplex  = relative_error(y_1024, y_radix2dit_1024_ccomplex);
    e_radix2dif_1024_ccomplex  = relative_error(y_1024, y_radix2dif_1024_ccomplex);
    e_splitradix_1024_ccomplex = relative_error(y_1024, y_splitradix_1024_ccomplex);
    e_libfftw_1024             = relative_error(y_1024, y_libfftw_1024);
    e_libfftw_1024_aligned     = relative_error(y_1024, y_libfftw_1024_aligned);

    eps_float = eps('single');

    neps_vector_128               = e_vector_128              / eps_float;
    neps_radix2dit_128            = e_radix2dit_128           / eps_float;
    neps_radix2dif_128            = e_radix2dif_128           / eps_float;
    neps_splitradix_128           = e_splitradix_128          / eps_float;
    neps_vector_128_ccomplex      = e_vector_128_ccomplex     / eps_float;
    neps_radix2dit_128_ccomplex   = e_radix2dit_128_ccomplex  / eps_float;
    neps_radix2dif_128_ccomplex   = e_radix2dif_128_ccomplex  / eps_float;
    neps_splitradix_128_ccomplex  = e_splitradix_128_ccomplex / eps_float;
    neps_libfftw_128              = e_libfftw_128             / eps_float;
    neps_libfftw_128_aligned      = e_libfftw_128_aligned     / eps_float;

    neps_vector_1024              = e_vector_1024              / eps_float;
    neps_radix2dit_1024           = e_radix2dit_1024           / eps_float;
    neps_radix2dif_1024           = e_radix2dif_1024           / eps_float;
    neps_splitradix_1024          = e_splitradix_1024          / eps_float;
    neps_vector_1024_ccomplex     = e_vector_1024_ccomplex     / eps_float;
    neps_radix2dit_1024_ccomplex  = e_radix2dit_1024_ccomplex  / eps_float;
    neps_radix2dif_1024_ccomplex  = e_radix2dif_1024_ccomplex  / eps_float;
    neps_splitradix_1024_ccomplex = e_splitradix_1024_ccomplex / eps_float;
    neps_libfftw_1024             = e_libfftw_1024             / eps_float;
    neps_libfftw_1024_aligned     = e_libfftw_1024_aligned     / eps_float;


    fprintf(1, 'relative error (computed as ||result - expected|| / ||expected||):\n');
    fprintf(1, '\n');
    fprintf(1, '                vector_128: %e (%.2f eps)\n', e_vector_128, neps_vector_128); 
    fprintf(1, '             radix2dit_128: %e (%.2f eps)\n', e_radix2dit_128, neps_radix2dit_128);
    fprintf(1, '             radix2dif_128: %e (%.2f eps)\n', e_radix2dif_128, neps_radix2dif_128);
    fprintf(1, '            splitradix_128: %e (%.2f eps)\n', e_splitradix_128, neps_splitradix_128);
    fprintf(1, '       vector_128_ccomplex: %e (%.2f eps)\n', e_vector_128_ccomplex, neps_vector_128_ccomplex); 
    fprintf(1, '    radix2dit_128_ccomplex: %e (%.2f eps)\n', e_radix2dit_128_ccomplex, neps_radix2dit_128_ccomplex);
    fprintf(1, '    radix2dif_128_ccomplex: %e (%.2f eps)\n', e_radix2dif_128_ccomplex, neps_radix2dif_128_ccomplex);
    fprintf(1, '   splitradix_128_ccomplex: %e (%.2f eps)\n', e_splitradix_128_ccomplex, neps_splitradix_128_ccomplex);
    fprintf(1, '               libfftw_128: %e (%.2f eps)\n', e_libfftw_128, neps_libfftw_128);
    fprintf(1, '       libfftw_128_aligned: %e (%.2f eps)\n', e_libfftw_128_aligned, neps_libfftw_128_aligned);
    fprintf(1, '\n');
    fprintf(1, '               vector_1024: %e (%.2f eps)\n', e_vector_1024, neps_vector_1024); 
    fprintf(1, '            radix2dit_1024: %e (%.2f eps)\n', e_radix2dit_1024, neps_radix2dit_1024);
    fprintf(1, '            radix2dif_1024: %e (%.2f eps)\n', e_radix2dif_1024, neps_radix2dif_1024);
    fprintf(1, '           splitradix_1024: %e (%.2f eps)\n', e_splitradix_1024, neps_splitradix_1024);
    fprintf(1, '      vector_1024_ccomplex: %e (%.2f eps)\n', e_vector_1024_ccomplex, neps_vector_1024_ccomplex); 
    fprintf(1, '   radix2dit_1024_ccomplex: %e (%.2f eps)\n', e_radix2dit_1024_ccomplex, neps_radix2dit_1024_ccomplex);
    fprintf(1, '   radix2dif_1024_ccomplex: %e (%.2f eps)\n', e_radix2dif_1024_ccomplex, neps_radix2dif_1024_ccomplex);
    fprintf(1, '  splitradix_1024_ccomplex: %e (%.2f eps)\n', e_splitradix_1024_ccomplex, neps_splitradix_1024_ccomplex);
    fprintf(1, '              libfftw_1024: %e (%.2f eps)\n', e_libfftw_1024, neps_libfftw_1024);
    fprintf(1, '      libfftw_1024_aligned: %e (%.2f eps)\n', e_libfftw_1024_aligned, neps_libfftw_1024_aligned);
end
