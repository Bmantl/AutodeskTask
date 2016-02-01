# Autodesk Task

A story of matrix multiplication.

## Goals:
  - Get in touch with JNI
  - Implement Matrix multiplication
  - Benchmark Java against C++

## Implementation

#### Matrix calsses
##### Java
  - Matrix.java - an implementation using a 2d double array
  - Matrix1D.java - an implementation using a 2d double array

> Both can multiply using the multiplyBy(other) function.<br/>
> There is no relation between the classes as the use a different data structure.<br/>
> There are segments of code that looks almost the same, as the logic is identical betwee the two.<br/>
> It seemed redundant to create some sort of super class (or interface) as the functions would have to be overriten  because of the different data structure.

##### C++
  - Mat.h/.cpp - an implementation using a 2d double array
  - Matrix.h/.cpp - an implementation using a 2d double array

> Both can multiply using the multiplyBy(other) function.<br/>
> Design-wise, its identical to the Java variant.

#### Program classes
  - Main.java - for running a basic multiplication with a jni call
  - Benchmark.java - for benchmarking over the 4 implementations

Usage in the usage part....

#### Why two implementations? (2D, 1D)
I started off with a simple 2d array implementation for both c++ and java, using primitive type arrays. <br/>
It appears that this kind of implementation is quite slow (especially for the c++ part :\ ). <br/>
Writing a 1D implementation of the matrix on c++ (using [i * rows + j] kind of querying) I got much (more than 100%) better results that the 2D implementation.

I did a java one as well to have a good comparison (Java does quite well).

*** All that said testing with a linux sitting on a vm.

### Compilation
#### Jni part
Located in the ```/jni``` folder there's a makefile.<br/>
It generates .h files using javah and compiles the c++ code.<br/>
make sure that the dll/so/jnilib are there.

##### Warning:
You might want to change the jdk folders in the makefile (or even the library compilation) fo compilation on other OSs.

To make all of the relevant files:
```sh
$ make all
```

#### Java part

It is already compiled and located in the ```/bin``` folder.

To compile again:
Using eclipse as a project manager or in the ```/src``` folder 
```sh
$ javac Matrix1D.java
$ javac Matrix.java
$ javac Main.java
$ javac Benchmark.java
```

### Usage
#### Main.class
```sh
$ java -Djava.library.path=../jni Main -i <input-file-location> -o <output-file-location>
```
```-i``` - an input file. There are files in the ```/Matrices``` folder.<br/>
```-o``` - ***Optional***. An output file to write the multiplication resullt. Optional, but without it it will just multiply and quit (without any output).

#### Benchmark.class
Used for benchmarking.<br/>
Outputs running times for all implementations per input.<br/>
Takes inputs from ```/Matrices``` folder.<br/>
```sh
$ java -Djava.library.path=../jni Benchmark -s <start-size> -e <start-size>
```
```-s``` - the start size for the benchmarking. Given in 1-20. i.e. 1 is for the 100.in file. 11 is for 1100.in<br/>
```-e``` - ***Optional***. The end size for the benchmarking. Given in 1-20. i.e. 1 is for the 100.in file. 11 is for 1100.in <br/>
the default will benchmark start + 5 size.

Outputs a file in ```/Matrices``` called benchmark_s_e_numOfRunsPerFile.out


### Benchmark conclusions

  - 1D implementation speed >>>> 2D implementation speed.
  - Though it should come out that c++ is faster that java, sometimes Java is faster (might need a better eval).
  - If the ```numOfRuns``` field in the ```Benchmark``` class is > 1, c++ runs worse on average. This might be due to the fact that the call to the jni suffers a huge overhead (which accumilates).
  

The results are located in the ```/Matrices``` in the benchmark...log files.

