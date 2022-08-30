# We store the first, second and third inputs in separate arrays
# We also store the sum of the second and third input
{
    strings[n] = $1;
    a[n] = $2;
    b[n] = $3;
    sum[n] = $2 + $3;
    ++n;
}
END{
    # On the basis of the sum array, we sort the program with the help of bubble sort
    for(i=1; i < n; i++)
    {
        for(j=1; j <= n-i; j++)
        {
            if(sum[j+1]<sum[j])
            {
                temp = sum[j+1];
                sum[j+1] = sum[j];
                sum[j] = temp;

                temp1 = strings[j+1];
                strings[j+1] = strings[j];
                strings[j] = temp1;

                temp2 = a[j+1];
                a[j+1] = a[j];
                a[j] = temp2;

                temp3 = b[j+1];
                b[j+1] = b[j];
                b[j] = temp3;
            }
        }
    }
    # We output the result
    for (i = 1; i <= n; ++i)
    {
        print strings[i], a[i], b[i];
    }
}