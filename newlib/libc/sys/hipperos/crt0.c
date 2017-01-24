extern int main();

void _start()
{
    const int exitCode = main();
    exit(exitCode);
}
