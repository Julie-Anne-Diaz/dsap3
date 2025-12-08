
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
// change if you choose to use a different header name
#include "CampusCompass.h"

using namespace std;

// the syntax for defining a test is below. It is important for the name to be
// unique, but you can group multiple tests with [tags]. A test can have
// [multiple][tags] using that syntax.
TEST_CASE("Example Test Name - Change me!", "[tag]") {
  // instantiate any class members that you need to test here
  int one = 1;

  // anything that evaluates to false in a REQUIRE block will result in a
  // failing test
  REQUIRE_FALSE(one == 0); // fix me!

  // all REQUIRE blocks must evaluate to true for the whole test to pass
  REQUIRE(true); // also fix me!
}

TEST_CASE("Test 2", "[tag]") {
  // you can also use "sections" to share setup code between tests, for example:
  int one = 1;

  SECTION("num is 2") {
    int num = one + 1;
    REQUIRE(num == 2);
  };

  SECTION("num is 3") {
    int num = one + 2;
    REQUIRE(num == 3);
  };

  // each section runs the setup code independently to ensure that they don't
  // affect each other
}

// You must write 5 unique, meaningful tests for credit on the testing section
// of this project!

// See the following for an example of how to easily test your output.
// Note that while this works, I recommend also creating plenty of unit tests for particular functions within your code.
// This pattern should only be used for final, end-to-end testing.

// This uses C++ "raw strings" and assumes your CampusCompass outputs a string with
//   the same thing you print.
TEST_CASE("Example CampusCompass Output Test", "[flag]") {
  // the following is a "raw string" - you can write the exact input (without
  //   any indentation!) and it should work as expected
  // this is based on the input and output of the first public test case
  string input = R"(6
insert "Student A" 10000001 1 1 COP3502
insert "Student B" 10000002 1 1 COP3502
insert "Student C" 10000003 1 2 COP3502 MAC2311
dropClass 10000001 COP3502
remove 10000001
removeClass COP3502
)";
  string expectedOutput = R"(successful
successful
successful
successful
unsuccessful
2
)";

  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }

  REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Incorrect Commands 1", "[flag]") {
  string input = R"(1
insert "A11y" 45679999 1 1 COP3530
)";
  string expectedOutput = R"(unsuccessful
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);
}
TEST_CASE("Incorrect Commands 2", "[flag]") {
  string input = R"(6
insert "Student A" 10000001 1 2 COP3502
insert "Student B" 10000002 1 1 COP3502
insert "Student C" 10000003 1 2 COP3502 MAC2311
dropClass 10000001 COP3502
remove 10000001
removeClass COP3502
)";
  string expectedOutput = R"(unsuccessful
successful
successful
unsuccessful
unsuccessful
2
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);

}
TEST_CASE("Incorrect Commands 3", "[flag]") {
  string input = R"(6
insert "Student A" 7733333 1 1 COP3502
insert "Student B" 10000002 1 1 COP3502
insert "Student C" 10000003 1 2 COP3502 MAC2311
dropClass 10000001 COP3502
remove 10000001
removeClass COP3502
)";
  string expectedOutput = R"(unsuccessful
successful
successful
unsuccessful
unsuccessful
2
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);

}
TEST_CASE("Incorrect Commands 4", "[flag]") {
  string input = R"(6
inblert "Student A" 10000001 1 1 COP3502
insert "Student B" 10000002 1 1 COP3502
insert "Student C" 10000003 1 2 COP3502 MAC2311
dropClass 10000001 COP3502
remove 10000001
removeClass COP3502
)";
  string expectedOutput = R"(unsuccessful
successful
successful
unsuccessful
unsuccessful
2
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);

}
TEST_CASE("Incorrect Commands 5", "[flag]") {
  string input = R"(6
insert "Student A" 10000001 1 1 COP3502
insert "Student B" 10000002 1 1 COP3502
insert "Student C" 10000003 1 2 COP3502 MAC2311
dropClass 10000001 COP3502 10234567
remove 10000001
removeClass COP3502
)";
  string expectedOutput = R"(successful
successful
successful
unsuccessful
successful
2
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);

}
TEST_CASE("Edge Case 1", "[flag]") {
  string input = R"(2
insert "Student A" 10000001 1 1 COP3502
remove 10000002
)";
  string expectedOutput = R"(successful
unsuccessful
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);

}
TEST_CASE("Edge Case 2", "[flag]") {
  string input = R"(6
insert "Student A" 10000001 1 1 COP3502
insert "Student B" 10000002 1 1 COP3502
insert "Student C" 10000003 1 2 COP3502 MAC2311
dropClass 10000001 COP3502 10234567
remove 10000001
removeClass COP3502
)";
  string expectedOutput = R"(successful
successful
successful
unsuccessful
successful
2
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);

}
TEST_CASE("Edge Case 3", "[flag]") {
  string input = R"(6
insert "Student A" 10000001 1 1 COP3502
insert "Student B" 10000002 1 1 COP3502
insert "Student C" 10000003 1 2 COP3502 MAC2311
dropClass 10000001 COP3502 10234567
remove 10000001
removeClass COP3509
)";
  string expectedOutput = R"(successful
successful
successful
unsuccessful
successful
0
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);

}

TEST_CASE("Drop Class Remove Class Replace Class", "[flag]") {
  string input = R"(6
insert "Student A" 10000001 1 1 COP3502
insert "Student B" 10000002 1 1 COP3502
insert "Student C" 10000003 1 2 COP3502 MAC2311
dropClass 10000001 COP3502
removeClass MAC2311
replaceClass 10000002 COP3502 MAC2311
)";
  string expectedOutput = R"(successful
successful
successful
successful
1
successful
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);

}

TEST_CASE("printShortestEdges", "[flag]") {
  string input = R"(6
insert "Student A" 10000001 9 1 MAC2311
printShortestEdges 10000001
toggleEdgesClosure 4 18 15 18 17 18 25 18 34
printShortestEdges 10000001
)";
  string expectedOutput = R"(successful
Name: Student A
MAC2311 | Total Time: 17
successful
Name: Student A
MAC2311 | Total Time: -1
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);

}
TEST_CASE("unique IDs, 8 digit IDs, no special characters in name, valid ClassCode, checking non existent edge (0/5)", "[flag]") {
  string input = R"(11
insert "John Doe" 11111111 1 1 COP3530
insert "Jane Doe" 11111111 1 1 COP3530
insert "John Doe" 22222222 1 1 COP3530
insert "@lbert" 33333333 1 1 COP3530
insert "Albert" 4 1 1 COP3530
insert "Albert" 00000004 1 1 COP3530
insert "John Doe" 55555555 1 1 cop3530
insert "John Doe" 55555555 1 1 C@P3530
insert "John Doe" 55555555 1 1 3530COP
insert "John Doe" 55555555 1 1 COP3530
checkEdgeStatus 12 17
)";
  string expectedOutput = R"(successful
unsuccessful
successful
unsuccessful
unsuccessful
successful
unsuccessful
unsuccessful
unsuccessful
successful
DNE
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);
}
TEST_CASE("Checking printShortestEdges after dropping/replacing classes (0/5)", "[flag]") {
  string input = R"(12
insert "Student A" 11111111 12 3 CDA3101 MAC2313 COP3502
insert "Student B" 22222222 10 2 COP3502 MAC2311
printShortestEdges 11111111
dropClass 11111111 MAC2313
printShortestEdges 11111111
replaceClass 11111111 CDA3101 MAC2311
printShortestEdges 11111111
removeClass COP3502
printShortestEdges 11111111
printShortestEdges 22222222
dropClass 11111111 COP3502
replaceClass 11111111 COP3502 IDS2935
)";
  string expectedOutput = R"(successful
successful
Name: Student A
CDA3101 | Total Time: 3
COP3502 | Total Time: 5
MAC2313 | Total Time: 10
successful
Name: Student A
CDA3101 | Total Time: 3
COP3502 | Total Time: 5
successful
Name: Student A
COP3502 | Total Time: 5
MAC2311 | Total Time: 8
2
Name: Student A
MAC2311 | Total Time: 8
Name: Student B
MAC2311 | Total Time: 9
unsuccessful
unsuccessful
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("verifySchedule with edge cases and toggled edges (0/5)", "[flag]") {
  string input = R"(13
insert "John" 11111111 20 4 EEL3701 EEL4744 EEL3111 CEN4907
verifySchedule 11111111
insert "Jane" 22222222 30 2 MAC2313 MAP2302
verifySchedule 22222222
insert "Albert" 33333333 1 2 COP3503 CNT4007
verifySchedule 33333333
toggleEdgesClosure 1 6 43
verifySchedule 33333333
toggleEdgesClosure 1 6 43
verifySchedule 33333333
insert "Aman" 44444444 1 1 COP4600
verifySchedule 44444444
verifySchedule 99999999
)";
  string expectedOutput = R"(successful
Schedule Check for John:
EEL3701 - EEL4744 "Can make it!"
EEL4744 - EEL3111 "Can make it!"
EEL3111 - CEN4907 "Can make it!"
successful
Schedule Check for Jane:
MAC2313 - MAP2302 "Can make it!"
successful
Schedule Check for Albert:
COP3503 - CNT4007 "Can make it!"
successful
Schedule Check for Albert:
COP3503 - CNT4007 "Cannot make it!"
successful
Schedule Check for Albert:
COP3503 - CNT4007 "Can make it!"
successful
unsuccessful
unsuccessful
)";
  std::stringstream iss(input);
  string actualOutput;
  std::string line;
  CampusCompass c;
  c.ParseCSV("../data/edges.csv", "../data/classes.csv");
  std::getline(iss, line);
  while (std::getline(iss, line)) {
    actualOutput += c.ParseCommand(line)+'\n';
  }
  REQUIRE(actualOutput == expectedOutput);
}