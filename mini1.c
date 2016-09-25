#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define RED  "\x1b[31m"
#define RESET   "\x1b[0m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"

void Default_Option(char str[80], char search[10], FILE *fp);
void Counting_Mathing_String(char str[80], char search[10], FILE *fp);
void Printing_Output_with_Line_Numbar(char str[80], char search[10], FILE *fp);


int main(int argc, char *argv[]) {

	char str1[80],search1[10];	
	int count1=0,count2=0,i,j,flag, count = 0, z = 0, y = 0, x;
	int option = 2;
	FILE *fp1 = NULL;
	fp1 = fopen(argv[2], "r");
	strcpy(search1, argv[1]);		
			
			
	switch(option) {
			
			default:
				Default_Option(str1, search1, fp1);
				break;
			case 1:
				Counting_Mathing_String(str1, search1, fp1);
				break;
			case 2:
				Printing_Output_with_Line_Numbar(str1, search1, fp1);
				break;
	}			
	fclose(fp1);
	return 0;
}

void Printing_Output_with_Line_Numbar(char str[80], char search[10], FILE *fp){
	int count1=0,count2=0,i,j,flag, count = 0, z = 0, y = 1, x;
	
	while(fgets(str, 80, fp)) {
				count1 = 0;
				count = 0;
				while (str[count1]!='\0')
					count1++;
		
				count2 = 0;
				while (search[count2]!='\0')
					count2++;

				for(i=0;i<=count1-count2;i++)
				{
					for(j=i;j<i+count2;j++)
					{
						flag=1;
						if (str[j]!=search[j-i])
						{
							flag=0;
					   		break;
						}
					}
					if (flag == 1)
						count++;
				}
				//Printing OUTPUT
				if(count != 0){
					z = 0;
					printf(GREEN "%d" RESET CYAN":"RESET,y);
					while(str[z] != '\0'){
				
						if(str[z] != search[0]){
							printf("%c", str[z]);
						}
						//for highlight the matching string
						else{
							for(i = z; i < z + 1; i++)
							{
								for(j = i; j <= i + count2 - 1; j++) {
									flag=1;
									if (str[j] != search[j - i])
									{
										flag=0;
					   					break;
									}
							
								}
			
							
							}
					
							if (flag == 1){
									x = z;
									while(z != (x + count2)){
										printf(RED "%c" RESET, str[z]);
										z++;
									}
									z--;
							
							}
							else
								printf("%c", str[z]);
						}
						z++;
					}		
		
				}
		y++;
	
	}
}
void Counting_Mathing_String(char str[80], char search[10], FILE *fp){
	int count1=0,count2=0,i,j,flag, count = 0, z = 0, y = 0, x;
	
	while(fgets(str, 80, fp)) {
				count1 = 0;
				count = 0;
				while (str[count1]!='\0')
					count1++;
		
				count2 = 0;
				while (search[count2]!='\0')
					count2++;

				for(i=0;i<=count1-count2;i++)
				{
					for(j=i;j<i+count2;j++)
					{
						flag=1;
						if (str[j]!=search[j-i])
						{
							flag=0;
					   		break;
						}
					}
					if (flag == 1)
						count++;
				}
			//Calculating Output
				y = y + count;
	}
		//Printing output
		printf("%d\n", y);	
			
}
void Default_Option(char str[80], char search[10], FILE *fp) {
	
	int count1=0,count2=0,i,j,flag, count = 0, z = 0, y = 0, x;
	
	while(fgets(str, 80, fp)) {
				count1 = 0;
				count = 0;
				while (str[count1]!='\0')
					count1++;
		
				count2 = 0;
				while (search[count2]!='\0')
					count2++;

				for(i=0;i<=count1-count2;i++)
				{
					for(j=i;j<i+count2;j++)
					{
						flag=1;
						if (str[j]!=search[j-i])
						{
							flag=0;
					   		break;
						}
					}
					if (flag == 1)
						count++;
				}
				//Printing OUTPUT
				if(count != 0){
					z = 0;
					while(str[z] != '\0'){
				
						if(str[z] != search[0]){
							printf("%c", str[z]);
						}
						//for highlight the matching string
						else{
							for(i = z; i < z + 1; i++)
							{
								for(j = i; j <= i + count2 - 1; j++) {
									flag=1;
									if (str[j] != search[j - i])
									{
										flag=0;
					   					break;
									}
							
								}
			
							
							}
					
							if (flag == 1){
									x = z;
									while(z != (x + count2)){
										printf(RED "%c" RESET, str[z]);
										z++;
									}
									z--;
							
							}
							else
								printf("%c", str[z]);
						}
						z++;
					}		
		
				}
		
	
	}
			
			
}
	


