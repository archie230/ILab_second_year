a=?;
b=?;

while (a != 0 && b != 0)
{
    i = 0;

    if (a>b) {
       a = a % b;
       i = 1;
    }

    if (!i)
        b = b % a;
}
print a + b;