% SPDX-License-Identifier: MIT
% Copyright © 2019  Bilal Djelassi

N = 1024;         % Taille de la transformée de Fourier
r = 0:N-1;        % Vecteur ligne, prenant les valeurs entières de 0 à N-1

% L'exponentiation complexe est réalisée élément par élément.
W = exp(-i*2*pi*r/N);

% Simple boucle pour formatter le vecteur W selon la syntaxe C++.
for n = 1:N
  printf("{%+.12ff, %+.12ff},\n", real(W(n)), imag(W(n)));
end
