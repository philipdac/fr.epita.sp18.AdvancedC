// Insensitive case comparison for string. Meaning "a" equals "A"; both "a" and "A" are smaller than "b"
//  @param s1 the first string
//  @param s2 the second string
//  @return 1 when s1 > s2
//  @return 0 when s1 == s2
//  @return -1 when s1 < s2
int strcpm_insensitive(char *s1, char *s2)
{
    for (;;)
    {
        char c1 = *(s1++);
        char c2 = *(s2++);

        if ((c1 >= 'a') && (c1 <= 'z'))
            c1 -= 0x20;

        if ((c2 >= 'a') && (c2 <= 'z'))
            c2 -= 0x20;

        if (c1 == '\0')
            return ((c2 == '\0') ? 0 : -1);

        if (c2 == '\0')
            return 1;

        if (c1 < c2)
            return -1;

        if (c1 > c2)
            return 1;
    }
}
