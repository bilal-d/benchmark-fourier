% SPDX-License-Identifier: MIT
% Copyright © 2019  Bilal Djelassi

N = 1024;         % Taille de la transformée de Fourier
k = 0:(3*N/4-1);  % Vecteur ligne, prenant les valeurs entières de 0 à 3N/4-1

% L'exponentiation complexe est réalisée élément par élément.
W = exp(-i*2*pi*k/N);

% Simple boucle pour formatter le vecteur W selon la syntaxe C++.
for n = 1:3*N/4
    fprintf(1, '{%+.12ff, %+.12ff},\n', real(W(n)), imag(W(n)));
end
