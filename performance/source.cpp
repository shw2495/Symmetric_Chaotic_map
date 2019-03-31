#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string> 
#include <time.h>
#include <Windows.h>

//#include "cryptopp810\aes.h"
#include "cryptopp810\cryptlib.h"
#include "cryptopp810\sha.h"
#include "cryptopp810\filters.h" 
#include "cryptopp810\hex.h"
#include "cryptopp810\aes.h"
#include "cryptopp810\modes.h"
#include "cryptopp810\eccrypto.h"
#include "cryptopp810\oids.h"
#include "cryptopp810\osrng.h"
#include "cryptopp810\eccrypto.h"
#include "cryptopp810\asn.h"
#include "cryptopp810\ecp.h"
#include "cryptopp810\ec2n.h"
#include "cryptopp810\simple.h"

#pragma warning(disable: 4996)
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#define ECC_ALGORITHM CryptoPP::ECP
#define ECC_CURVE CryptoPP::ASN1::brainpoolP160r1()
using namespace std;
using namespace CryptoPP;

#ifdef _DEBUG
#  pragma comment ( lib, "cryptlibd" )
#else
#  pragma comment ( lib, "cryptlib" )
#endif

long long bergamo(double a)
{
	long long x = pow(10, 9), old_x = a*pow(10, 9);
	long long s = 0, old_s = 1, temp;
	long long t = 1, old_t = 0;

	//printf("%lld\n", old_x);
	while (x)
	{
		long long q = old_x / x;
		temp = x;
		x = old_x - q * x;
		old_x = temp;

		temp = s;
		s = old_s - q * s;
		old_s = temp;

		temp = t;
		t = old_t - q * t;
		old_t = temp;
	}
	if(old_x != 1)
		printf("%lld\n", old_x);

	return old_s;
}

unsigned int dischev(unsigned int a, unsigned int n, unsigned int p, unsigned long long *result)
{
	unsigned long long int mat[2][2] = { 0, 1, p-1, (2 * a) % p }, temp[2][2], res[2][2] = { 1, 0, 0, 1 };
	for (n--; n; n >>= 1)
	{
		if (n % 2)
		{
			temp[0][0] = res[0][0];
			temp[0][1] = res[0][1];
			temp[1][0] = res[1][0];
			temp[1][1] = res[1][1];

			res[0][0] = (temp[0][0] * mat[0][0] + temp[0][1] * mat[1][0]) % p;
			res[0][1] = (temp[0][0] * mat[0][1] + temp[0][1] * mat[1][1]) % p;
			res[1][0] = (temp[1][0] * mat[0][0] + temp[1][1] * mat[1][0]) % p;
			res[1][1] = (temp[1][0] * mat[0][1] + temp[1][1] * mat[1][1]) % p;
		}

		temp[0][0] = mat[0][0];
		temp[0][1] = mat[0][1];
		temp[1][0] = mat[1][0];
		temp[1][1] = mat[1][1];

		mat[0][0] = (temp[0][0] * temp[0][0] + temp[0][1] * temp[1][0]) %p;
		mat[0][1] = (temp[0][0] * temp[0][1] + temp[0][1] * temp[1][1]) %p;
		mat[1][0] = (temp[1][0] * temp[0][0] + temp[1][1] * temp[1][0]) %p;
		mat[1][1] = (temp[1][0] * temp[0][1] + temp[1][1] * temp[1][1]) %p;
	}
	result[0] = (res[0][0] * 1 + res[0][1] * a) % p;
	result[1] = (res[1][0] * 1 + res[1][1] * a) % p;
	//printf("%lld %lld \n %lld %lld \n", res[0][0], res[0][1], res[1][0], res[1][1]);
	//printf("%llu %llu \n", result[0], result[1]);
	return a;
}



int main(void)
{
	long double a1, result, a2, b2;
	unsigned long long disres[2];
	unsigned int i, j, k, n, a, p;
	LARGE_INTEGER Frequency;
	LARGE_INTEGER BeginTime;
	LARGE_INTEGER Endtime;
	long long elapsed;
	double duringtime;

	QueryPerformanceFrequency(&Frequency);


	a1 = 0.721;
	n = 154327;
	/*
	for (i = 1; i <= 20; i++)
	{
		result = cos(i*acos(a1));
		printf("%d : %lf\n", i, result);
	}
	for (i = 0; i < 100000; i++)
		result = acos(a1);

	printf("%.10f \n", acos(a1));
	printf("%.10f \n", -acos(cos(n*acos(a1))) / acos(a1));
	printf("%.10f \n", 2 * M_PI / acos(a1));
	*/
	cout << "---------------------------------------------------------" << endl;
	cout << "Chebyshev" << endl;

	QueryPerformanceCounter(&BeginTime);
	for (i = 0; i < 10000000; i++)
		result = cos(i*acos(a1));
	QueryPerformanceCounter(&Endtime);
	elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << result << endl;
	cout << "time: " << duringtime << "(ms)" << endl;
	/*
	printf("a : %.10lf\n", (acos(result) / acos(a1) - floor(acos(result) / acos(a1))));
	printf("b : %.10lf\n", (2 * M_PI / acos(a1) - floor(2 * M_PI / acos(a1))));
	printf("bergamo : %lld\n", bergamo(2 * M_PI / acos(a1) - floor(2 * M_PI / acos(a1))));
	printf("k : %lf\n", (acos(result) / acos(a1) - floor(acos(result) / acos(a1))) * bergamo(2 * M_PI / acos(a1) - floor(2 * M_PI / acos(a1))));
	*/
	QueryPerformanceCounter(&BeginTime);
	for(i=0;i<100000;i++)
	{
		a2 = (acos(result) / acos(a1) - floor(acos(result) / acos(a1)));
		b2 = (2 * M_PI / acos(a1) - floor(2 * M_PI / acos(a1)));
		result = a1 + (2 * M_PI / acos(a1)) * (a2 * bergamo(b2));
		//printf("n : %.10lf \n",  a1 + (2 * M_PI / acos(a1)) * (a2 * bergamo(b2)));
	}
	QueryPerformanceCounter(&Endtime);
	elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "time: " << duringtime << "(ms)" << endl;
	cout << result << endl;

	//discrete Chebyshev
	cout << "---------------------------------------------------------" << endl;
	cout << "Discrete Chebyshev" << endl;
	a = 35543215;
	n = 12234521;
	p = 373587883;
	QueryPerformanceCounter(&BeginTime);
	//for(k=0; k<=10000000; k++)
	//	for(j=0; j<=10000000; j++)
			for (i = 0; i <= 100000; i++)
			{
				a = dischev(a+i, n, p, disres);
//				if (i == 10000000 && j == 10000000 && k == 10000000)
//					printf("hello\n");
			}
	QueryPerformanceCounter(&Endtime);
	cout << a << endl;
	elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "time: " << duringtime << "(ms)" << endl;


	//SHA-1
	cout << "---------------------------------------------------------" << endl;
	cout << "SHA-1" << endl;
	SHA1 hash1;
	std::string msg = "Yoda said, Do or do not. There is no try.";
	std::string digest1;

	QueryPerformanceCounter(&BeginTime);
	for(i=0;i<100000;i++)
		StringSource s1(msg, true, new HashFilter(hash1, new StringSink(digest1)));
	QueryPerformanceCounter(&Endtime);
	elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "time: " << duringtime << "(ms)" << endl;
	
	std::cout << "Message: " << msg << std::endl;
	//std::cout << "Digest: " << digest1 << endl;
	std::cout << std::endl;
	
	//SHA-256
	cout << "---------------------------------------------------------" << endl;
	cout << "SHA-256" << endl;
	SHA256 hash;
	string message = "Now is the time for all good men to come to the aide...";
	string digest;
	
	QueryPerformanceCounter(&BeginTime);
	for (i = 0; i < 100000; i++)
		StringSource s(message, true, new HashFilter(hash, new StringSink(digest)));
		//StringSource s(message, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
	QueryPerformanceCounter(&Endtime);
	elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "time: " <<  duringtime << "(ms)" << endl;

	//cout << digest << endl;

	//AES
	cout << "---------------------------------------------------------" << endl;
	cout << "AES" << endl;
	//Key and IV setup
	//AES encryption uses a secret key of a variable length (128-bit, 196-bit or 256-   
	//bit). This key is secretly exchanged between two parties before communication   
	//begins. DEFAULT_KEYLENGTH= 16 bytes
	CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
	memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
	memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

	//
	// String and Sink setup
	//
	std::string plaintext = "Now is the time for all good men to come to the aide...Now is the time for all good men to come to the aide...asdfasdf";
	std::string ciphertext;
	std::string ciphertext1;
	std::string decryptedtext;

	//
	// Dump Plain Text
	//
	std::cout << "Plain Text (" << plaintext.size() << " bytes)" << std::endl;
	std::cout << plaintext;
	std::cout << std::endl << std::endl;
	CTR_Mode<AES>::Encryption encrypt((const byte*)key, AES::DEFAULT_KEYLENGTH, (const byte*)iv);
	//
	// Create Cipher Text
	//
	QueryPerformanceCounter(&BeginTime);
	for (i = 0; i < 100000; i++)
		StringSource(plaintext, true, new StreamTransformationFilter(encrypt, new StringSink(ciphertext)));
	QueryPerformanceCounter(&Endtime);
	elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "time: " << duringtime << "(ms)" << endl;

	//
	// Dump Cipher Text
	//
	StringSource(plaintext, true, new StreamTransformationFilter(encrypt, new StringSink(ciphertext1)));
	std::cout << "Cipher Text (" << ciphertext1.size() << " bytes)" << std::endl;

	std::cout << std::endl << std::endl;

	CTR_Mode<AES>::Decryption decrypt((const byte*)key, AES::DEFAULT_KEYLENGTH, (const byte*)iv);
	//
	// Decrypt
	//
	QueryPerformanceCounter(&BeginTime);
	for (i = 0; i < 100000; i++)
	{
		StringSource(ciphertext1, true, new StreamTransformationFilter(decrypt, new StringSink(decryptedtext)));
	}
	QueryPerformanceCounter(&Endtime);
	elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "time: " << duringtime << "(ms)" << endl;
	//
	// Dump Decrypted Text
	//
	std::cout << "Decrypted Text: " << std::endl;
	//std::cout << decryptedtext;
	std::cout << std::endl << std::endl;

	//ECC
	cout << "---------------------------------------------------------" << endl;
	cout << "ECC" << endl;
	CryptoPP::ECIES < ECC_ALGORITHM >::PrivateKey privateKey;
	CryptoPP::ECIES < ECC_ALGORITHM >::PublicKey publicKey;
	CryptoPP::AutoSeededRandomPool rng;

	// Key Generation
	privateKey.Initialize(rng, ECC_CURVE);
	privateKey.MakePublicKey(publicKey);

	// Key Validation
	if (false == privateKey.Validate(rng, 3))
	{
		throw runtime_error("Private key validation failed");
	}

	if (false == publicKey.Validate(rng, 3))
	{
		throw runtime_error("Public key validation failed");
	}

	// Encryptor and Decryptor
	CryptoPP::ECIES < ECC_ALGORITHM >::Encryptor Encryptor(publicKey);
	CryptoPP::ECIES < ECC_ALGORITHM >::Decryptor Decryptor(privateKey);

	// Message
	string plainText = "Yoda said, Do or do not. There is no try.";
	size_t plainTextLength = plainText.length() + 1;

	cout << "Plain text: " << plainText << endl;
	cout << "Plain text length is " << plainTextLength << " (including the trailing NULL)" << endl;

	// Size  
	size_t cipherTextLength = Encryptor.CiphertextLength(plainTextLength);

	if (0 == cipherTextLength)
	{
		throw runtime_error("cipherTextLength is not valid");
	}

	cout << "Cipher text length is ";
	cout << cipherTextLength << endl;

	// Encryption buffer
	byte * cipherText = new byte[cipherTextLength];
	if (NULL == cipherText)
	{
		throw runtime_error("Cipher text allocation failure");
	}

	memset(cipherText, 0xFB, cipherTextLength);

	// Encryption
	QueryPerformanceCounter(&BeginTime);
	for (i = 0; i < 10000; i++)
		Encryptor.Encrypt(rng, reinterpret_cast < const byte * > (plainText.data()), plainTextLength, cipherText);
	QueryPerformanceCounter(&Endtime);
	elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "time: " << duringtime << "(ms)" << endl;

	// Size
	size_t recoveredTextLength = Decryptor.MaxPlaintextLength(cipherTextLength);
	if (0 == recoveredTextLength)
	{
		throw runtime_error("recoveredTextLength is not valid");
	}

	// Decryption Buffer
	char * recoveredText = new char[recoveredTextLength];
	if (NULL == recoveredText)
	{
		throw runtime_error("recoveredText allocation failure");
	}

	memset(recoveredText, 0xFB, recoveredTextLength);

	// Decryption
	QueryPerformanceCounter(&BeginTime);
	for (i = 0; i < 10000; i++)
		Decryptor.Decrypt(rng, cipherText, cipherTextLength, reinterpret_cast < byte * >(recoveredText));
	QueryPerformanceCounter(&Endtime);
	elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "time: " << duringtime << "(ms)" << endl;

	cout << "Recovered text: " << recoveredText << endl;
	cout << "Recovered text length is " << recoveredTextLength << endl;

	// Cleanup
	if (NULL != cipherText)
	{
		delete[] cipherText;
	}

	if (NULL != recoveredText)
	{
		delete[] recoveredText;
	}

	return 0;
}