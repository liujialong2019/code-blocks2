#include"stdio.h"
#include"string.h"
int main()
{
    char key[32];
    printf("ÇëÊäÈë×¢²áÂë:");
    gets(key);
    if(strcmp(key,"abc123456")==0)
        printf("×¢²á³É¹¦");
    else
        printf("×¢²áÊ§°Ü")
}
