## Code for "A New Symmetric Chebyshev Chaotic Map and Its Secure Fast Authentication"

This repository includes the **ProVerif + AVISPA verification code** for the paper "A New Symmetric Chebyshev Chaotic Map and Its Secure Fast Authentication". We use ProVerif 2.00(proverifbsd2.00) and SPAN(Security Protocol ANimator for AVISPA) Version 1.6. In the proverif folder, we also include result folder which format is HTML. If you want to see the result, then open index.html and you can see the result in HTML file.

Moreover, we also include a **performance test** of several cryptographic primitives used in authentication schemes. The code is written by Visual Studio 2017. We use Crypto++ Library 8.1(https://www.cryptopp.com/). We compare six cryptographic functions. The list of these functions as follows:
1. symmetric Chebyshev
1. discrete Chebyshev
1. SHA-1
1. SHA-256
1. AES(encryption + decryption)
1. ECC(encryption + decryption)

We also include benchmark results of cryptographic functions in Crypto++ Library 8.1. Benchmark environment as follows:
* processor: Intel(R) Pentium(R) CPU G4600 @ 3.60GHz
* RAM: 8.00GB
* Windows 10 64bits

If you want to get a more trusted source for a benchmark of cryptographic functions, check https://www.cryptopp.com/benchmarks.html (Benchmark for Crypto++ 5.6). 
