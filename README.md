<p align="center">
<img width="200" height="230" alt="image" src="https://github.com/xmm16/xmm16.github.io/blob/main/timeworm.png?raw=true" /><br>

> _A time-traveling compiler with a butterfly-effect type system that knows your code on a first-name basis?_

#### Explanation
Say we have a string that you add and remove a ton of other strings and characters to
```cpp
string example = "hello!";
example = example[0, -1]; // example = "hello"
example += ' ';
example += "world!";
```
Eventually, we may decide to ask for the length of this string
```cpp
string example = "hello!";
example = example[0, -1];
example += ' ';
example += "world!"; // example = "hello world!"
print(example.length());
```
Most languages will keep track of the length and return it, which is extremely optimized, but we've decided to do something different. 
```cpp
s̶t̶r̶i̶n̶g̶ string_with_counter example = "hello!";
example = example[0, -1]; // every operator is now overloaded to track length updates
example += ' ';
example += "world!"; // example = "hello world!"
print(example.length());
```
If you never request the length of a string (or an alias/slice of a string, since the compiler keeps track of those by referring to them as variations of a variable's "first-name"), the compiler just won't keep track of it. However, if you do, the compiler will go back (or time travel) and change the type (leading to a butterfly effect).

#### Thesis
This might seem like a silly optimization, and it kinda is, but we've mercilessly abused these fairly simple effects to build a completely memory-safe and extremely fast language, all while being fun, clean, and mostly consistent.
