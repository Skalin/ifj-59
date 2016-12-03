#include "../ial.h"
#include <stdio.h>

int main (int argc, char *argv) {

	String testString = "kokot";
	String testString2 = "vysortovat";
	String testString3 = "posun";
	String testString4 = "boyle-moore";

	sort(testString);
	printf(testString);

	sort(testString2);
	printf(testString2);

	sort(testString3);
	printf(testString3);

	sort(testString4);
	printf(testString4);


}