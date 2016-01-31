# Define a variable for classpath
CLASS_PATH = ../bin

# Define a virtual path for .class in the bin directory
vpath %.class $(CLASS_PATH)

all: linMain.so

# $@ matches the target, $< matches the first dependancy
libMain.so : Main.cpp Main.h Matrix.cpp Matrix.h
	g++ -fPIC -std=c++11 -I"/usr/lib/jvm/jdk1.8.0_72/include" -I"/usr/lib/jvm/jdk1.8.0_72/include/linux" -shared -o $@ $< Matrix.cpp

libBenchmark.so : Benchmark.cpp Benchmark.h Matrix.cpp Matrix.h Mat.cpp Mat.h
	g++ -O3 -fPIC -std=c++11 -I"/usr/lib/jvm/jdk1.8.0_72/include" -I"/usr/lib/jvm/jdk1.8.0_72/include/linux" -shared -o $@ $< Matrix.cpp Mat.cpp
# $* matches the target filename without the extension
	
Main.h : Main.class
	javah -classpath $(CLASS_PATH) $*
	
Benchmark.h : Benchmark.class
	javah -classpath $(CLASS_PATH) $*

clean :
	rm libMain.so libBenchmark.so