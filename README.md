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
    * Return const std::string_view from functions that use a hard-coded const char * string inside.
        * You can just return "Some String", as this will invoke an automatic conversion
          to std::string_view.  We make the final version const so that we can make it difficult
          to write into the returned view.
    * Don't automatically turn a hard-coded string into a std::string
        * This possibly creates two instances of the string in the runtime?
    * Use const std::string_view instead of std::string as input to
      constructors.  Using const std::string & is fine too if it can cut down
      on the number of conversions.
* Using std::source_location
* Allow Exception classes to only be moved and not copied
* Use the std library pointers and try to make it difficult/impossible to extract a raw pointer from inside an object and copy it.
* Singleton pattern

## Lessons Learned So Far

* Using C++ 20's source_location to automatically fill in call-site information
    * Useful for Assert(), Debug(), and exception handling.  ***We finally have a non-macro solution!***
* String Handling
    * You don't have to Use std::string_view literal on hard-coded strings ( "Hard-Coded String"sv )!
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
    * When hard-coding strings, it seems to be best to use NON-const types for the actual storage (except const char *).  You can add
      constness when you have to hand out std::string_view of that data.
      I originally stored strings as const std::string_view, but I couldn't then copy those out to an external
      data structure.
* Singleton Pattern
    * The most elegant form I have found so far is the use of a static variable inside of a block scope.
      This is guaranteed by the standard to be initialized only the first time passing through that point
      and is thread-safe.  You can see this in Console::Out()/In()/...
* std::source_location
    * Exceptions
        * Created a function (ThrowWithTarget()) that you pass an r-value exception object to and
          it will automatically fill in the function name of the call point.  No macros, thanks
          to std::source_location().
    * Debug/Trace classes
        * Use to automatically have access to the current source state at the callsite.