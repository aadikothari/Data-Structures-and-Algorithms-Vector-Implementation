//your code here.

// Author: Aadi Kothari

#include "Hill.hpp"
/**
   * Default constructor. It should set the encryption key to {2,4,3,5} (2-by-2) and the decryption key to its inverse.
   */
Hill::Hill() {
	E = Matrix({ 2,4,3,5 }, 2, 2);
	D = inv_mod(E);
}

/**
   * Parameterized constructor.  Use the parameter to set the encryption (E) and decryption (D) keys; if parameter is invalid then set E/D to a 0-by-0 matrix.
   * @param K - a matrix representing the encryption or decryption key.
   * @param encryption - true if the key is the encryption key, false if the key is the decryption key
   */
Hill::Hill(const Matrix& K, bool encryption) {
	// checks if inverse of matrix is 0. Which means invalid parameters...
	Matrix null(std::vector<int>(), 0, 0);

	if ((inv_mod(K).equal(null))) {
		// if it is, then set both E and D to 0.
		this->E = Matrix(std::vector<int>(), 0, 0);
		this->D = Matrix(std::vector<int>(), 0, 0);
		return;
	}

	// otherwise if it works
	else {
		// if key is decryption key
		if (!encryption) {
			this->D = K;
			this->E = this->inv_mod(this->D);
		}

		// otherwise if key is encryption key
		else {
			this->E = K;
			this->D = this->inv_mod(this->E);
		}
	}
}

/**
 * Parameterized constructor.  Use the parameters to set the encryption (E) and decryption (D) keys; if a parameter is invalid or inconsistent then set E/D to a 0-by-0 matrix.
 * @param E - encryption key.
 * @param D - decryption key.
 */
Hill::Hill(const Matrix& E, const Matrix& D) {
	Matrix null(std::vector<int>(), 0, 0);

	if ((E.size(2) > 1) && (E.size(1) > 1) && (D.size(1) > 1) && (D.size(2) > 1) && (E.size(1) == E.size(2)) && (D.size(1) == D.size(2)) && (D.equal(inv_mod(E))) && (E.equal(inv_mod(D))) && (inv_mod(E).equal(D)) && (inv_mod(D).equal(E)))
	{
		this->E = E;
		this->D = D;
	}
	else {
		this->E = null;
		this->D = null;
	}
}

/**
   * Returns the current encryption key.
   * @return the encryption key (Matrix E), if no encryption key is set a 0-by-0 matrix.
   */
Matrix Hill::getE() const {
	return E;
}

/**
   * Returns the current decryption key.
   * @return the decryption key (Matrix D), if no decryption key is set a 0-by-0 matrix.
   */
Matrix Hill::getD() const {
	return D;
}

/**
 * Sets the encryption key (Matrix E) and decryption key (Matrix D); if the parameter is invalid then set E/D to a 0-by-0 matrix.
 * @param E - encryption key.
 * @return true if set is successful, false otherwise.
 */
bool Hill::setE(const Matrix& E) {
	Matrix null = Matrix(std::vector<int>(), 0, 0);
	Matrix temp_E = E;
	for (int i = 0; i < (temp_E.size(1) * temp_E.size(2)); i++)
	{
		temp_E.set(i, mod(temp_E.get(i), 29));
	}
	Matrix holder = inv_mod(temp_E);
	if ((holder.equal(null)) && (E.size(1) == E.size(2)) && (E.size(1) > 1) && (E.size(2) > 1)) {
		this->D = holder;
		this->E = temp_E;
		return true;
	}
	else
	{
		this->D = null;
		this->E = null;
		return false;
	}
	
}


/**
 * Sets the decryption key (Matrix D) and encryption key (Matrix E); if the parameter is invalid then set E/D to a 0-by-0 matrix.
 * @param D - decryption key.
 * @return true if set is successful, false otherwise.
*/
bool Hill::setD(const Matrix& D) {
	Matrix null = Matrix(std::vector<int>(), 0, 0);
	Matrix temp_D = D;
	for (int i = 0; i < (temp_D.size(1) * temp_D.size(2)); i++)
	{
		temp_D.set(i, mod(temp_D.get(i), 29));
	}
	Matrix holder = inv_mod(D);
	if ((holder.equal(null)) && (D.size(1) == D.size(2)) && (D.size(1) > 1) && (D.size(2) > 1)) {
		this->D = temp_D;
		this->E = holder;
		return true;
	}
	else
	{
		this->D = null;
		this->E = null;
		return false;
	}
}

/**
 * Encrypt the given plaintext using the previous set encryption key, an empty string if the encryption key is invalid.
 * @param P - the plaintext to encrypt
 * @return the ciphertext resulting from encrypting the plaintext using the stored encryption matrix.
 */
std::string Hill::encrypt(const std::string& P) const {
	Matrix null(std::vector<int>(), 0, 0);

	//integrate mechanism to check for invalid characters

	Matrix hidden = this->getE().mult(l2num(P, this->getE().size(1)));

	for (int i = 0; i < hidden.size(1) * hidden.size(2); i++)
	{
		hidden.set(i, mod(hidden.get(i), 29));
	}

	return n2let(hidden);


	//check if this->E is a valid matrix
	//check to make sure the string has valid characters
	//check length of the string 
	

	return "";
}

/**
 * Encrypt the given plaintext using the given encryption key, an empty string if the encryption key is invalid.
 * @param P - the plaintext to encrypt
 * @param E - the key to use to encrypt the plaintext
 * @return the ciphertext resulting from encrypting the plaintext using the given encryption matrix.
 */
std::string Hill::encrypt(const std::string& P, const Matrix& E) {
	Matrix null(std::vector<int>(), 0, 0);

	//integrate mechanism to check for invalid characters

	Matrix hidden = E.mult(l2num(P, E.size(1)));

	for (int i = 0; i < hidden.size(1) * hidden.size(2); i++)
	{
		hidden.set(i, mod(hidden.get(i), 29));
	}

	return n2let(hidden);


	//check if this->E is a valid matrix
	//check to make sure the string has valid characters
	//check length of the string 


	return "";
}

/**
 * Decrypt the given ciphertext using the previous set decryption key, an empty string if the decryption key is invalid.
 * @param C - the ciphertext to decrypt
 * @return the plaintext resulting from decrypting the ciphertext using the stored decryption matrix.
 */
std::string Hill::decrypt(const std::string& C) const{
	Matrix null(std::vector<int>(), 0, 0);

	//integrate mechanism to check for invalid characters
	Matrix hidden;
	hidden = this->getD().mult(l2num(C, this->getD().size(1)));

	for (int i = 0; i < hidden.size(1) * hidden.size(2); i++)
	{
		hidden.set(i, mod(hidden.get(i), 29));
	}

	return n2let(hidden);


	//check if this->E is a valid matrix
	//check to make sure the string has valid characters
	//check length of the string 


	return "";
}

/**
 * Decrypt the given ciphertext using the given decryption key, an empty string if the decryption key is invalid.
 * @param C - the plaintext to encrypt
 * @param D - the key to use to decrypt the ciphertext
 * @return the plaintext resulting from decrypting the ciphertext using the given decryption matrix.
 */
std::string Hill::decrypt(const std::string& C, const Matrix& D) {
	Matrix null(std::vector<int>(), 0, 0);

	//integrate mechanism to check for invalid characters

	Matrix hidden = D.mult(l2num(C, D.size(1)));

	for (int i = 0; i < hidden.size(1) * hidden.size(2); i++)
	{
		hidden.set(i, mod(hidden.get(i), 29));
	}

	return n2let(hidden);


	//check if this->E is a valid matrix
	//check to make sure the string has valid characters
	//check length of the string 


	return "";
}

/**
 * Mount a known-plaintext attack against the Hill cipher assuming an n-by-n encryption matrix.  Set E/D to the encryption/decryption key if they can be recovered.
 * @param P - the plaintexts that correspond to C
 * @param C - the ciphertexts that correspond to P
 * @return true if the encryption and decryption keys have been recovered.
 */
bool Hill::kpa(const std::vector<std::string>& P, const std::vector<std::string>& C, unsigned int n) {
	return false;
}

