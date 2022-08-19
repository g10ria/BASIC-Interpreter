// a variety of hash functions to choose from!

int sum(char *key, int size)
{
    int i = 0;
    int sum = 0;
    while (key[i] != '\0')
    {
        sum += key[i];
        i++;
    }
    return sum % size;
}