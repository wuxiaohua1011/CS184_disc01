# Discussion 1: C++ review via convolution

Please clone the discussions repository and go to the *disc01* directory.

## Compiling, Makefile
You can compile the project using the command

```
   make
```
from the *disc01* directory.

Your real assignments have a much larger codebase and link against quite a few external libraries, so they use a Makefile-creation system called `cmake`. However, after running `cmake` for the first time, you will simply run `make` to rebuild your program every time you change the source code.

A Makefile simplifies your life by checking file timestamps to determine which files really need to be recompiled.

Common C++ compilers include `g++/gcc` and `clang`.

## main.cpp

Read through *main.cpp*. As you've seen if you've programmed in C, a C++ program begins by evaluating the `main()` function. `main()` recieves two arguments that are generated from your command line input:

1. `int argc` is the number of command line arguments, including the name of the program.
2. `char* argv[]` provides pointers to the `char*` strings containing each space-separated argument. `argv[0]` is a path to the executable itself.

As indicated in `main.cpp`, the usage for this program is 

```
    ./convolve img.png filter.filt
```

`main.cpp` also contains some examples of text output in  C++ (using the standard output stream) and the main body of the program:

```Image image(argv[1]);Filter filter(argv[2]);Image filtered = image * filter;filtered.write("filtered.png");
```

Here the `*` operator is overloaded to convolve an `Image` with a `Filter`. The first two lines load an aimge and filter file, respectively, and the final line writes the filtered result to a file. Your job will be implementing the member functions of `Image` and `Filter`, found in other files.

## Filter struct

The `Filter` struct is declared in *filter.h*, a C++ header file. In C++, declarations of variables, functions, structs, and classes provide enough information to perform type checking without actually defining the value of an object. Headers are `#include`-ed in any file that uses the declared objects from that header. As you may remember, the preprocessor will paste in the text of an `#include`-ed file wherever that macro is placed. Headers are never compiled alone--only when they occur at the top of some *.cpp* file. 

Also, note the `#ifndef` guard in *filter.h*: this prevents the compiler from double-pasting the header in a single file, which could cause problems with multiple definitions (if anything is not only declared but also defined within the header). It is generally good practice not to define functions fully within a header, but exceptions can be made for short, self-explanatory functions.

`Filter` is a struct, which has a different meaning in C++ compared to C. In C++, structs and classes are nearly identical. The differences have to do with public versus private: data and functions are public by default in a struct, but private by default in a class. Semantically, people interpret a struct to be more like a bundle of public data (originating from its usage in C) and a class to be more like a fully responsive, protected object. I took a bit of liberty in making `Filter` a struct, since it should maybe be a class, but it works for illustrative purposes.

The member function definitions for `Filter` reside in *filter.cpp*. The first two are *constructors*, which are only ever called upon creation of a new `Filter`. The one with no arguments is the default constructor, and I've given it a simple "identity filter" function. The second loads a filter from a file. 

### Todos for you

**You should implement the `Filter::read` function.**

Filter files are stored in the following format:

```
w h
f f ... f
f f ... f
...
f f ... f
```

where `w` is the width and `h` is the height of the filter. The width is the number of columns and the height is the number of rows. Each `f` represents one entry in the rectangular filter kernel. **NOTE**: filters are not stored "normalized", so you need to add up all the `f` values and then divide each one by the sum so that your `Filter`'s kernel adds up to one.

Look up how to use an `ifstream` to read this data.

**You should implement the `Filter::normalize` function.**

This function adds up all the numbers in the kernel and then divides each one by that sum, ensuring that the new values will add up to one.

**You should implement the `Filter::at` function.**

This is a one line function that returns a *reference* to one entry of the `Filter` kernel. Passing-by-reference does not exist in C. You can think of it as a permanently dereferenced pointer. The important part is that if you do this:

```
Filter f("some_filter.filt");
float& v = f.at(2,3);
v = .124f;
f.at(3,1) = .71f;
```
it will change the actual (2,3) and (3,1) entries in the kernel. (Now the kernel won't be normalized anymore, which is bad.)

## Image class

Now we can move on to the `Image` class. This class is fairly similar to the `Filter` except that it supports an additional convolution operator `*`.

### Todos for you

**You should implement the `Image::read` and `Image::write` functions.**

Look up how to use the lodepng `lodepng::decode` and `lodepng::encode` functions to do this.

**You should implement the `Image::at` function.**

This function returns the address of a pixel in the `data` vector of pixels. Each pixel takes up four bytes (a.k.a. `unsigned char`s or `uint8_t`s). The pixels are laid out such that the `width` pixels in the first row (with `y=0`) comes first, then the `y=1` row, and so on, until the `y=height-1` row. This means that you need to use the `y` argument to "jump" up by `y` rows, or `y * width` pixels. Then you can access the `x` pixel in that row with

```
y * width + x
```

Finally, you need to multiply all of that by 4 to get the right pointer offset from the start of the data array, since each pixel is 4 unsigned chars.

**You should implement the `Image::operator*` (convolution) function.**

This function is the most complicated. You need to:

1. Create a new image (of the same size as the current image) that can hold the output.
2. For each pixel location in the old image, compute a weighted sum of the neighboring colors, each weighted by the filter's value at that relative offset (where the center of the pixel is at the location of your current pixel in the image).
3. Assign this weighted sum to the same location in the new image.
4. Return the new image.

Now, you should be able to run the program from the command line and inspect your filtered output at *filtered.png*. You can use any PNG image with any of the *.filt* files, or even make your own filter if you want.