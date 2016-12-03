#include "../main.h"
#include <stdio.h>

int main (int argc, char *argv) {

	String testString = "kokot";
	String testString2 = "vysortovat";
	String testString3 = "posun";
	String testString4 = "boyle-moore";

	sort(testString);
	print(testString);

	sort(testString2);
	print(testString2);

	sort(testString3);
	print(testString3);

	sort(testString4);
	print(testString4);


}