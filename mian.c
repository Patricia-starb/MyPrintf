#include <stdarg.h>

#include <unistd.h>

int printChar(char c){
    return write(1, &c, 1) == 1 ? 0 : -1;
}

void printIntTen(int num){
    char buf[32];
    int i = 0;
    if(num == 0){
        if(printChar('0') == -1){
            write(1, "Error.", 6);
        };
        return;
    }
    if(num < 0){
        if(printChar('-') == -1){
            write(1, "Error.", 6);
            return;
        }
        num = -num;
    }
    while(num > 0 && i < 31){
        buf[i++] = '0' + (num % 10);
        num /= 10;
    }
    while(i > 0){
        if(printChar(buf[--i]) == -1){
            write(1, "Error.", 6);
            return;
        }
    }
}

void printStr(const char* str){
    if(str == NULL){
        write(1, "(null)", 6);
    }
    size_t len = 0;
    while(str[len] != '\0') len++;
    write(1, str, len);
}

void myPrint(const char* initial, ...){
    va_list ap;
    va_start(ap, initial);
    const char* p = initial;

    for(;*p != '\0';p++){
        if(*p == '%' && *(p+1) != '\0'){
            p++;
            if(*p == 'd'){
                int val = va_arg(ap, int);
                printIntTen(val);
            }else if(*p == 'c'){
                char valC = (char)va_arg(ap, int);
                printChar(valC);
            }else if(*p == 's'){
                char* valS = va_arg(ap, char*);
                printStr(valS);
            }else{
                printChar(*p);
            }
        }
        else {
            printChar(*p);
        }
    }
    va_end(ap);
}

int main(void){
    char input[] = "Patricia";
    myPrint("\nThis is %s printf.\n", input);

    return 0;
}

