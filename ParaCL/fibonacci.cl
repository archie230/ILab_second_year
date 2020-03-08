fibonacci = func(n) 

{
i = 0;

while(i < n) {
    i = i + 1;
    a = 0;
    b = 1;

    if (i == 1)
        return 0;

    if (i == 2)
        return 1;

    if (i > 2) {
        j = 0;
        while(j < i - 2) {
            tmp = b;
            b = a + b;
            a = tmp;
            j = j + 1;
        }
        return b;
    }
}
}
