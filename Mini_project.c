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
#define BOLD "\033[1m"

void Default_Option(char *str, char *search, FILE *fp);
void Counting_Numbar_of_Mathing_String(char *str, char *search, FILE *fp);
void Printing_Output_with_Line_Numbar(char *str, char *search, FILE *fp);
void Line_Printing_After_Matching(char *str, char *search, FILE *fp);
void Line_Printing_Befor_Matching(char *str, char *search, FILE *fp);
void Ignore_case(char *str, char *search, FILE *fp);

int main(int argc, char *argv[]) {

	char str1[80],search1[10];	
	int count1=0,count2=0,i,j,flag, count = 0, z = 0, y = 0, x;
	int option = 5;
	FILE *fp1 = NULL;
	fp1 = fopen(argv[2], "r");
	strcpy(search1, argv[1]);		
			
			
	switch(option) {
			
			default:
				Default_Option(str1, search1, fp1);
				break;
			case 1:
				Counting_Numbar_of_Mathing_String(str1, search1, fp1);
				break;
			case 2:
				Printing_Output_with_Line_Numbar(str1, search1, fp1);
				break;
			case 3:
				Line_Printing_After_Matching(str1, search1, fp1);
				break;
			case 4:
				Line_Printing_Befor_Matching(str1, search1, fp1);
				break;
			case 5:
				Ignore_case(str1, search1, fp1);
				break;
	}			
	fclose(fp1);
	return 0;
}

void Ignore_case(char *str, char *search, FILE *fp){
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
						if ((str[j] != search[j-i]) && (str[j] != (search[j-i] + 32)) && (str[j] != (search[j-i] - 32)))
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
				
						if((str[z] != search[0]) && (str[z] != (search[0] + 32)) && (str[z] != (search[0] - 32))){
							printf("%c", str[z]);
						}
						//for highlight the matching string
						else{
							for(i = z; i < z + 1; i++)
							{
								for(j = i; j <= i + count2 - 1; j++) {
									flag=1;
									if ((str[j] != search[j-i]) && (str[j] != (search[j-i] + 32)) && (str[j] != (search[j-i] - 32)))
									{
										flag=0;
					   					break;
									}
							
								}
			
							
							}
					
							if (flag == 1){
									x = z;
									while(z != (x + count2)){
										printf(RED BOLD"%c" RESET, str[z]);
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

void Line_Printing_Befor_Matching(char *str, char *search, FILE *fp){
	//can i invert the after function. ?
	/* yes 
	how to invert
	1.invert the line pointers and so modify the array of the pointers
	2.use the same algorithem and run the function as it is
	3.insted of printing the lines store it a array.
	4.again the ouput array invert it.
	5.finally print it.
	6.thats the solution.
	OR
	1.store the pointers of each line.
	2.now pointers of the line having matching string.
	3.decide which line we have to print.
	{1.make a print function 
	  expressions
		while next is not null
		if next is frist match
			special case
		if (next[i] - previus[j] - 1) is equal or gretar than the the numbar the user entered then
			print the numbar of lines that the user had entered
			and then also print the matching line.
		else
			 next
	*/
}

void Line_Printing_After_Matching(char *str, char *search, FILE *fp){
	int count1=0,count2=0,i,j,flag, count = 0, z = 0, y = 0, x,count_of_lines, a = 0, line_numbar = 1,b;
	long ab;
	printf("Lines");
	scanf("%d", &count_of_lines);
	ab = ftell(fp);
	while(fgets(str, 80, fp))
		y++;
	
	long line_pointer[y + 1];
	line_pointer[0] = ab;
	y = 1;
	
	fseek(fp, line_pointer[0], SEEK_SET);
			
	while(fgets(str, 80, fp)){
		line_pointer[y] = ftell(fp);	
		y++;
	}
	
	fseek(fp, line_pointer[0], SEEK_SET);
	while(fgets(str, 80, fp)) {
				//printf("%d.LINE\n",line_numbar);
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
				//printf("%d.3\n""count = %d\n",line_numbar, count);
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
										printf(RED BOLD"%c" RESET, str[z]);
										z++;
									}
									z--;
							
							}
							else
								printf("%c", str[z]);
						}
						z++;
					}		
		
					
					// Checking if matching string occure or not
					
					if(count_of_lines != 0){
						for(a = 1; a < count_of_lines + 1; a++){
							fgets(str, 80, fp);
							//line_numbar++;
							//printf(CYAN"%d.line\t"RESET, line_numbar);
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
							//printf("count = %d\n", count);
							if(count != 0){
								fseek(fp, line_pointer[line_numbar], SEEK_SET);
								for(b = 0; b < (a - 1); b++){
									fgets(str, 80, fp);
									i = 0;
									while(str[i] != '\0'){
										printf("%c",str[i]);
										i++;
									}		
	
								}
								line_numbar = line_numbar + a - 1;//only setting line numbar file pointer is already set.
								printf(CYAN"\n"RESET);
								break;
							}
						}
						//printf(CYAN"CHECKING DONE\n"RESET);
						if(count == 0){
							fseek(fp, line_pointer[line_numbar], SEEK_SET);
							for(a = 0; a < count_of_lines; a++){
								fgets(str, 80, fp);
								i = 0;
								while(str[i] != '\0'){
									printf("%c",str[i]);
									i++;
								}		
							}
							line_numbar = line_numbar + count_of_lines;
							printf(CYAN"--\n"RESET);
						}
					}
				}
		
		line_numbar++;
	
	}

}

void Printing_Output_with_Line_Numbar(char *str, char *search, FILE *fp){
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
										printf(RED BOLD"%c" RESET, str[z]);
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
void Counting_Numbar_of_Mathing_String(char *str, char *search, FILE *fp){
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
						count++;//this is for numbar of matching string in a single line.
				}
			//Calculating Output
				y = y + count;//this is for counting numbar of mathing strings in all lines.
	}
		//Printing output
		printf("%d\n", y);	
			
}
void Default_Option(char *str, char *search, FILE *fp) {
	
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
										printf(RED BOLD"%c" RESET, str[z]);
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



