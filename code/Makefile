CC=chpl
SRCS=$(wildcard *.chpl)
OUTS=$(SRCS:%.chpl=%.o)

all: $(OUTS)

%.o: %.chpl
	$(CC) -o $@ $<

clean:
	rm *.o
