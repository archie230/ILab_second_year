errno = 0;

factorial = func(n) : global_factorial
{
    x = func() : minus_one {return -1;}

    if(n < 0) {
        errno = minus_one();
        return minus_one();
    }

    if(n == 0)
        return 1;
    return n * global_factorial(n-1);
};

x = ?;
x = factorial(x);
if(errno == -1)
    print -1;
else
    print x;