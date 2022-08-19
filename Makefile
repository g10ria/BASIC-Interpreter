compile=gcc
buildDir=bin
headersDir=headers

deps = headers/interpreter.h cson/headers/hashmapLite.h

obj = interpreter.o scanner/scanner.o parser/evals.o parser/parser.o cson/hashmapLite.o cson/hashfunctions.o

%.o: %.c
	$(compile) -c -o $@ $<

interpreter: $(obj)
	$(compile) -o ${buildDir}/$@.bin $^ -I/$(headersDir)