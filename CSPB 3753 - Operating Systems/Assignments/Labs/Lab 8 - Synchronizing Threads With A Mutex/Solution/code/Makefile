ALL: example api

clean:
	rm -f ./example
	rm -f ./shared_api

api: shared_api.c
	gcc -g -o shared_api shared_api.c

example: example.c 
	gcc -g -o example example.c

testAPI: api
	./shared_api test.txt results.txt > api_test.txt

testExample: example
	./example 2 > example_test.txt