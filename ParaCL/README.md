# ParaCL Language interpreter

## Install:

make

## Grammar:

### Variables
All variables have integer type

**Variable declaration**
 
 ```
 a = 0; // or other integer value
 a = ?; // read from standart input (stdin)
 ```

### Expressions
All C binary operator expressions works well

only +, -, ! unary operators   

### Instructions

**C like instructions**

```
while(expression) {
    // body
}

while(expression)
    // one instruction

if(expression)
    // scope or one instruction
else
    // scope or one instruction

print expression; // print expression value to stdout
```

### Functions and Scopes
The peculiarity of the ParaCL language is that everything, including the function, is an object.

The func keyword is used to introduce the function, followed by the argument names and scope

```
a = 1;
foo = func (x) {x * 42; }
b = foo (a);
print b; // on screen 42 '

// The result of the function is the last expression inside the scope.

bar = func () {
  x = 5;
  y = 10;
  x + y;
}; // semicolon here is possible but optional

t = bar (); // t == 15

// Explicit return is also possible.

buz = func (x) {
  if (x! = 5)
    return x;
  y = 10;
  x + y;
}

z = buz (6); // z == 6

// Just like a function, returning a value from any scope works.

t = {x = 5; y = 10; x + y; } // t == 15

// Functions differ from blocks in that they can be called multiple times.

// The function may have a name, if necessary (for example, for recursion) then it is written through a colon

fact = func (x): factorial {
  res = 1;
  if (x> 0)
    res = factorial (x - 1);
  res;
}

// The name of the function is always available in all scopes,

// the name of the variable in which it is written - only in the scope in which it lives
```

