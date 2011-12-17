basic_usage.so: basic_usage.pyx doublify.cpp doublify.h
	python setup.py build_ext --inplace

test: basic_usage.so
	python tst.py

clean:
	-rm -f basic_usage.cpp basic_usage.so *~

.PHONY: all clean test
