rec = func(x) : global {
    c = 11 + x;

    if(x == 0)
        return c + x;

    else return c + x + global(x-1);
}

print rec(3);