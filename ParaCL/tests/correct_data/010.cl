global = 0;

bar = func(x) {
  y = 10;
  x + y;
};

print bar({if (global) return 1; else return 2;});