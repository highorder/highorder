INCLUDES := -I../../include
basic_usage: basic_usage.cpp
	g++ $(INCLUDES) -o $@ $^

.PHONY: test clean
test: basic_usage
	./basic_usage

clean:
	-rm -f basic_usage
