#include <stdio.h>

int main(int argc, char *argv[]){
		
	int count = 0;
	FILE *fp;
	fp = fopen(argv[1], "r");
	char a;
	while((a = fgetc(fp)) != '\n'){
		printf("%c", a);
		count++;
	}

	printf("\n%d", count);
	return 0;

}
