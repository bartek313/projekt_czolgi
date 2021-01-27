main:
	gcc main.c apiConnector.c mapGenerator.c jsonConverter.c algorithm.c pngGenerator.c -Wall -lcurl -lcjson -lpng16 -o tanks
test:
	gcc tests/mainTest.c tests/apiConnectorTest.c tests/mapGeneratorTest.c tests/jsonConverterTest.c tests/algorithmTest.c -Wall -lcurl -lcjson -lpng -o tanksTest
test-memory:
	valgrind ./tanks --leak-check=full
clean:
	rm -f tanks
