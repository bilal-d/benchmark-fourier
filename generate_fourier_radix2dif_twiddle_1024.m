% SPDX-License-Identifier: MIT
% Copyright © 2019  Bilal Djelassi

N = 1024;         % Taille de la transformée de Fourier
k = 0:(N/2-1);    % Vecteur ligne, prenant les valeurs entières de 0 à N/2-1

% L'exponentiation complexe est réalisée élément par élément.
W = exp(-i*2*pi*k/N);

% Simple boucle pour formatter le vecteur W selon la syntaxe C++.
for n = 1:N/2
  printf("{%+.12ff, %+.12ff},\n", real(W(n)), imag(W(n)));
end
