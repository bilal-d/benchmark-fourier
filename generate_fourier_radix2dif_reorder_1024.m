% SPDX-License-Identifier: MIT
% Copyright © 2019  Bilal Djelassi

function generate_fourier_radix2dif_reorder_1024
    N = 1024;
    R = [];
    for k = 0:N-1
        j = reorder(N, k);
        if j < k
            R = [R; j k];
        end
    end

    fprintf(1, '// length: %d\n', length(R))
    for r = R'
        fprintf(1, '{ %d, %d },\n', r(1), r(2))
    end
end

function j = reorder(n, k)
    j = undecimate(n, 1, k);
end

function j = undecimate(n, s, k)
    if n == 1
        j = k;
    elseif k < n/2
        j = undecimate(n/2, s*2, k);
    else
        j = undecimate(n/2, s*2, k - n/2) + s;
    end
end
