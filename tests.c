#include <stdlib.h>
#include <stdio.h>
#include "ial.h"

int main(int argc, char *argv) {

	String testString = "kokot";
	String testString2 = "vysortovat";
	String testString3 = "posun";
	String testString4 = "boyle-moore";
	String printedString = "\0";

	printedString = sort(testString);
	printf(printedString);

	printedString = sort(testString2);
	printf(printedString);

	printedString = sort(testString3);
	printf(printedString);

	printedString = sort(testString4);
	printf(printedString);

	return 0;

}