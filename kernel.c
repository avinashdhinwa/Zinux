void printf(const char *str)
{
    unsigned short *videoMemory = (unsigned short*)0xb80000;
    int i;

    for(i = 0; *str != '\0'; i++, str++)
        *(videoMemory + i) = (*(videoMemory + 1) & 0xFF00) |  *str;
}

void kernelMain(void *multiboot, unsigned int magicNumber)
{
    printf("Zinux");

    while(1);
}
