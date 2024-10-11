# cppdotnet

Implementation of .NET core libraries in C++

## About

This is a simple implementation of the .NET libraries in C++ and as such does not yet take into account thread safety.  It isn't currently meant to be an exact match, but instead uses C++-style idioms when I think it will help.

## Why

This is my attempt to experiment with implementing a small C++ library
using new (to me) techniques and explore various aspects of C++ 20.  This is
how I learn best!

I also plan on writing better unit tests for this so I can practice doing that and improve.

## Ideas explored so far

* Optimize string handling
    * Don't just return a const char * to hard-coded strings.  Let the
      compiler optimize that into a string_view via the std::literals.
    * Don't automatically turn a hard-coded string into a std::string
    * Use const std::string_view instead of std::string as input to
      constructors.  Using const std::string & is fine too if it can cut down
      on the number of conversions.
* Using std::source_location
* Allow Exception classes to only be moved and not copied
* Use the std library pointers and try to make it difficult/impossible to extract a raw pointer from inside an object and copy it.

## Lessons Learned So Far

* Using C++ 20's source_location to automatically fill in call-site information
    * Useful for Assert(), Debug(), and exception handling.  ***We finally have a non-macro solution!***
* String Handling
    * Use std::string_view literal on hard-coded strings ( "Hard-Coded String"sv )
    * **Return const std::string_view from functions that return a hard-coded string.**
    This isn't ideal, but I think it is better than just returning a raw
    const char *.  The underlying hard-coded string isn't going anywhere
    because it is compiled into the binary, so there should be no problem
    with returning a const std::string_view.  Returning a const object
    should help enforce not being able to modify it easily.
    * **Return std::string in cases where I actually generate a temporary
    string in a function.**
    Returning a std::string_view would be asking for trouble here.Unfortunately, this means that there is an inconsistency
    in return value types for strings as it will depend upon the implementation
    of the function as to what to return (string_view vs string).
    String-like objects can be constructed from either a string_view or string, so it should be fairly transparent.