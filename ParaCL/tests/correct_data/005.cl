input=?;
n=0;

if(input < 0)
    print -1;

if(input >= 0) {
    while(n < input) {
        n=n+1;
            a = 0;
            b = 1;

            if (n==1)
                print 0;

            if (n==2)
                print 1;

            if (n > 2)
            {
                i=0;
                while(i < n - 2)
                {
                    tmp = b;
                    b = a + b;
                    a = tmp;
                    i = i + 1;
                }
                print b;
            }
    }
}