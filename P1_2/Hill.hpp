#ifndef _HILL_HPP_
#define _HILL_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "Matrix.hpp"

/**
 * A C++ class to perform encryption/decryption and cryptanalysis using/of the Hill cipher with a 29 character alphabet.
 */
class Hill
{
public:
	/**
	 * Default constructor. It should set the encryption key to {2,4,3,5} (2-by-2) and the decryption key to its inverse.
	 */
	Hill();

	/**
	 * Parameterized constructor.  Use the parameter to set the encryption (E) and decryption (D) keys; if parameter is invalid then set E/D to a 0-by-0 matrix.
	 * @param K - a matrix representing the encryption or decryption key.
	 * @param encryption - true if the key is the encryption key, false if the key is the decryption key
	 */
Hill(const Matrix& K, bool encryption);

/**
 * Parameterized constructor.  Use the parameters to set the encryption (E) and decryption (D) keys; if a parameter is invalid or inconsistent then set E/D to a 0-by-0 matrix.
 * @param E - encryption key.
 * @param D - decryption key.
 */
Hill(const Matrix& E, const Matrix& D);

/**
 * Returns the current encryption key.
 * @return the encryption key (Matrix E), if no encryption key is set a 0-by-0 matrix.
 */
Matrix getE() const;

/**
 * Returns the current decryption key.
 * @return the decryption key (Matrix D), if no decryption key is set a 0-by-0 matrix.
 */
Matrix getD() const;

/**
 * Sets the encryption key (Matrix E) and decryption key (Matrix D); if the parameter is invalid then set E/D to a 0-by-0 matrix.
 * @param E - encryption key.
 * @return true if set is successful, false otherwise.
 */
bool setE(const Matrix& E);

/**
 * Sets the decryption key (Matrix D) and encryption key (Matrix E); if the parameter is invalid then set E/D to a 0-by-0 matrix.
 * @param D - decryption key.
 * @return true if set is successful, false otherwise.
 */
bool setD(const Matrix& D);

/**
 * Encrypt the given plaintext using the previous set encryption key, an empty string if the encryption key is invalid.
 * @param P - the plaintext to encrypt
 * @return the ciphertext resulting from encrypting the plaintext using the stored encryption matrix.
 */
std::string encrypt(const std::string& P) const;

/**
 * Encrypt the given plaintext using the given encryption key, an empty string if the encryption key is invalid.
 * @param P - the plaintext to encrypt
 * @param E - the key to use to encrypt the plaintext
 * @return the ciphertext resulting from encrypting the plaintext using the given encryption matrix.
 */
std::string encrypt(const std::string& P, const Matrix& E);

/**
 * Decrypt the given ciphertext using the previous set decryption key, an empty string if the decryption key is invalid.
 * @param C - the ciphertext to decrypt
 * @return the plaintext resulting from decrypting the ciphertext using the stored decryption matrix.
 */
std::string decrypt(const std::string& C) const;

/**
 * Decrypt the given ciphertext using the given decryption key, an empty string if the decryption key is invalid.
 * @param C - the plaintext to encrypt
 * @param D - the key to use to decrypt the ciphertext
 * @return the plaintext resulting from decrypting the ciphertext using the given decryption matrix.
 */
std::string decrypt(const std::string& C, const Matrix& D);

/**
 * Mount a known-plaintext attack against the Hill cipher assuming an n-by-n encryption matrix.  Set E/D to the encryption/decryption key if they can be recovered.
 * @param P - the plaintexts that correspond to C
 * @param C - the ciphertexts that correspond to P
 * @return true if the encryption and decryption keys have been recovered.
 */
bool kpa(const std::vector<std::string>& P, const std::vector<std::string>& C, unsigned int n);
/*
* Testing out the private method
*/
//Matrix p_l2num(std::string s, int n)
//{
//	return l2num(s, n);
//}
//
/*
* Testing out the private method
*/
std::string privateN2let(const Matrix& A)
{
	return n2let(A);
}

Matrix privateIdentityMatrix(unsigned int size) {
	return identityMatrix(size);
}

private:
	Matrix D; //current decryption key; must be consistent with E
	Matrix E; //current encryption key; must be consistent with D
	//multiplicative inverses over Z_{29}; e.g., ZI29[1] = 15 is multiplicative inverse of 2. 
	const std::vector<int> ZI29 = { 1,15,10,22,6,5,25,11,13,3,8,17,9,27,2,20,12,21,26,16,18,4,24,23,7,19,14,28 };

	//YOU ARE FREE TO IMPLEMENT THESE METHODS AND/OR ADD YOUR OWN
	/*
	* Returns the vector of number
	* convert the string of characters in s to the equivalent numerical values using our 29 character alphabet and put in matrix suitable for n-by-n encryption matrix
	* MODIFIED: changed the value to return a vector
	*/
	Matrix l2num(const std::string& s, unsigned int n) const {
		std::vector<int> result;

		// Traversing through the vector to identify characters
		for (int i = 0; i < s.length(); i++) {
			// If it is a letter (A-Z), use ASCII static casting conversion
			if (s.at(i) >= 'A' && s.at(i) <= 'Z') {
				// EXAMPLE: ASCII for A = 65. 65-65 = 0, which is what A corresponds to. This will be pushed
				result.push_back(static_cast<int>(s.at(i)) - 65);
			}

			// otherwise, if a period, manually set 26
			else if (s.at(i) == '.') {
				result.push_back(26);
			}

			// otherwise, if a question mark, manually set 27
			else if (s.at(i) == '?') {
				result.push_back(27);
			}

			// otherwise, if a space, manually set 28
			else if (s.at(i) == ' ') {
				result.push_back(28);
			}
		}
		// converting the vector to Matrix
		Matrix final(result, n, s.length() / n);
		//now, return this Matrix
		return final;
	}
	
	/*
	* Converts the matrix to a string of characters using our 29 character alphabet
	* MODIFIED: returns a string object
	* uses similar logic to l2num, except reversed.
	*/
	std::string n2let(const Matrix & A) const {
		std::string result;
		// Nested loop to traverse through the matrix of numbers
		for (int i = 0; i < (A.size(1) * A.size(2)); i++) {

				// If the element is within 0 and 25
				if (A.get(i) >= 0 && A.get(i) <= 25) {
					result.push_back(static_cast<char>(A.get(i) + 65));
				}
				else if (A.get(i) == 26) {
					result.push_back('.');
				}
				else if (A.get(i) == 27) {
					result.push_back('?');
				}
				else if (A.get(i) == 28) {
					result.push_back(' ');
				}
		}
		return result;
	}

	/*
	* Calculates the invese of a matrix
	* ps ~this function killed me
	*/
	Matrix inv_mod(Matrix A) {

		//Matrix inv = A;
		int placeHolder = 0;

		// First step is to create an identity matrix
		Matrix inv = identityMatrix(A.size(1));

		// Now we continue to do the same operation on both the original and the inverse matrix
		// to obtain the answer.

		// Traversing column wise
		for (int j = 0; j < A.size(2); j++) {
			
			if (A.get(j, j) > 1)
			{
				int currentElement = A.get(j, j);
				// Using row mult and doing same operations on both inverse and original matrix
				row_mult(inv, j, 0, inv.size(2), ZI29[currentElement - 1]);
				row_mult(A, j, 0, A.size(2), ZI29[currentElement - 1]);

			}
			
			// Traversing row wise
			for (int k = 0; k < A.size(1); k++) {
				// If element isn't diagonal
				if ((j != k) && (A.get(k, j) != 0)) {
					placeHolder = A.get(k, j);
					// Using row diff to make the other element 0, and then performing the same operation on inverse matrix
					row_diff(inv, k, 0, inv.size(2), inv, j, placeHolder);
					row_diff(A, k, 0, A.size(2), A, j, placeHolder);
				}
			}
		}

		// Finally, the inverse matrix will contain the inverse matrix, while A will become identity matrix
		if (A.equal(identityMatrix(A.size(2))))
		{
			for (int i = 0; i < (inv.size(1) * inv.size(2)); i++)
			{
				inv.set(i, mod(inv.get(i), 29));
			}
			return inv;
		}

		return Matrix(std::vector<int>(), 0, 0);
	}

  /* Calculates the remainder of the operation and returns it
  * c = a mod b, where c = [0,b)
  */
	unsigned int mod(int a, int b) const{

		// We must account for the negative numbers
		if (a < 0) {
			return (b + (a % b));
		}
		// otherwise, just return the modulus
		else {
			return (a % b);
		}
  }

  //For row i of Matrix A, multiply columns j through k by c, mod 29
  //(i.e., in Matlab notation A(i,j:k) = mod(c*A(i,j:k), 29))
  //NOTE: matrix pass by reference means all operations occur in place
  void row_mult(Matrix& A, unsigned int i, unsigned int j, unsigned int k, unsigned int c) {

	  // using variable 'recursion' to avoid confusion between passed parameters and looping variable
	  for (int recursion = j; recursion < k; recursion++) {
		  // Logic is used from the given MATLAB notation, and set function from Matrix.cpp is used to set the value
		  A.set(i, recursion, this->mod((c * A.get(i, recursion)), 29));
	  }
  }
  //Multiply columns j through k of row l of Matrix B by c and subtract from columns j through k of row i of Matrix A, mod 29
  //(i.e., in Matlab notation A(i,j:k) = mod(A(i,j:K) - c*B(l,j:k), 29)
  //NOTE: matrix pass by reference means all operations occur in place
  void row_diff(Matrix& A, unsigned int i, unsigned int j, unsigned int k, Matrix& B, unsigned int l, unsigned int c) {

	  // using variable 'recursion' to avoid confusion between passed parameters and looping variable
	  for (int recursion = j; recursion < k; recursion++) {
		  // Logic is used from the given MATLAB notation, and set function from Matrix.cpp is used to set the value
		  A.set(i, recursion, this->mod((A.get(i, recursion) - (c*B.get(l,recursion))), 29));
	  }
  }

  /*
  * Function that creates Identity Matrix of size (size x size)
  */
  Matrix identityMatrix(unsigned int size) {
	  Matrix identityMatrix;//create identity matrix
	  std::vector<int> identityVector(size * size); //create empty matrix with 0 for all elements
														
	//add entries for diagonal
	  for (int i = 0; i < size * size; i += (size + 1))
		  identityVector[i] = 1;
	  identityMatrix = Matrix(identityVector, size, size);

	  return identityMatrix;
  }
};
#endif