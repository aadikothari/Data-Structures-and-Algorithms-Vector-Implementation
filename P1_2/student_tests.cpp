#include "catch.hpp"
#include "Hill.hpp"
#include "Matrix.hpp"
using namespace std;

TEST_CASE( "default constructor", "[Hill]" )
{
  INFO("Hint: default constructor (linear getE/D() must work)");
  Hill LS;
  Matrix E(std::vector<int>{2,4,3,5}, 2, 2);
  Matrix D(std::vector<int>{12,2,16,28}, 2, 2);

  //LS.getD().output(cout);

  REQUIRE(LS.getE().equal(E));
  REQUIRE(LS.getD().equal(D));
}

TEST_CASE("parameterized const", "[Hill]")
{
	Matrix A(std::vector<int>{3,10,28,4,7,15,6,4,10}, 3, 3);
	Matrix B(std::vector<int>{2, 14, 14, 10, 13, 25, 18, 27, 2}, 3, 3);

	Hill O(A, B);
	REQUIRE(O.getE().equal(A));
	REQUIRE(O.getD().equal(B));
}

TEST_CASE("parameterized const w/ 2 inputs", "[Hill]")
{
	Matrix A(std::vector<int>{3, 10, 28, 4, 7, 15, 6, 4, 10}, 3, 3);
	Matrix B(std::vector<int>{2, 14, 14, 10, 13, 25, 18, 27, 2}, 3, 3);

	Hill O(A, B);
	REQUIRE(O.getE().equal(A));
	REQUIRE(O.getD().equal(B));
}


TEST_CASE("encrypt", "[Hill]") {

}

TEST_CASE("encrypt 2.0", "[Hill]") {

}

TEST_CASE("decrypt", "[Hill]") {

}

TEST_CASE("decrypt 2.0", "[Hill]") {

}