

/*****************************************************************************
 * Copyright (C) Onkar Marbhal marbhal37@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 4.4 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/



#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define RED  "\x1b[31m"
#define RESET   "\x1b[0m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGNETA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BOLD "\033[1m"

void Default_Option(char *str, char *search, FILE *fp);
void Default_Option1(char *str, char *search, char *File_name);
void Counting_Numbar_of_Mathing_String(char *str, char *search, FILE *fp);
void Printing_Output_with_Line_Numbar(char *str, char *search, FILE *fp);
void Line_Printing_After_Matching(char *str, char *search, FILE *fp, char *NUM);
void Ignore_case(char *str, char *search, FILE *fp);
int Grep_dir(char *str, char *search, char *dir_name, char *argb);
int text_or_binary(const char *File_name);
int isFile(const char *name);
void usage(void);
void help(void);

int main(int argc, char *argv[]) {

	char str1[180], search1[10], *home = ".";	
	int count1=0,count2=0,i,j,flag, count = 0, z = 0, y = 0, x, File_numbar = 2;
	int option = 6;
	FILE *fp1 = NULL;
	
	
	
	if(argc == 1){
		usage();
		return 0;
	}
	else if((argc == 2) && (strcmp(argv[1], "-h") == 0)){
		help();
		return 0;
	}
	else if(argc == 2){
		printf("mygrep:Enter the file name.\n");
		usage();
		return 0;
	}
	else if((argc == 3) && (strncmp(argv[2], "-", 1) != 0))
		option = 100;
	else if((argc >= 3) && (strncmp(argv[2], "-", 1) != 0))
		option = 6;
	else if(strcmp(argv[2], "-r") == 0)
		option = 7;
	else if(strcmp(argv[2], "-i") == 0)
		option = 5;
	else if(strcmp(argv[2], "-c") == 0)
		option = 1;
	else if(strcmp(argv[2], "-A") == 0)
		option = 3;
	else if(strcmp(argv[2], "-L") == 0)
		option = 2;
	else{
		usage();
		return -1;
	}


	strcpy(search1, argv[1]);		
	switch(option) {
			
			default:{
					if(!(fp1 = fopen(argv[2], "r"))){
						printf("mygrep : %s", argv[2]);
						perror(" ");
						return errno;
					}
					Default_Option(str1, search1, fp1);
					fclose(fp1);
				}
				break;
			case 1:{	File_numbar = 3;
					while(argv[File_numbar] != NULL){
						if(!(fp1 = fopen(argv[File_numbar], "r"))){
							printf("Can't open file %s.\n", argv[File_numbar]);
							
						}
						else{
							Counting_Numbar_of_Mathing_String(str1, search1, fp1);
							fclose(fp1);
						}
						File_numbar++;
					}
				}
				
				break;
			case 2:{	File_numbar = 3;
					while(argv[File_numbar] != NULL){
						if(!(fp1 = fopen(argv[File_numbar], "r"))){
							printf("Can't open file %s.\n", argv[File_numbar]);
							
						}
						else{
							Printing_Output_with_Line_Numbar(str1, search1, fp1);
							fclose(fp1);
						}
						File_numbar++;
					}
				}
				
				break;
			case 3:{	File_numbar = 4;
					while(argv[File_numbar] != NULL){
						if(!(fp1 = fopen(argv[File_numbar], "r"))){
							printf("Can't open file %s.\n", argv[File_numbar]);
							
						}
						else{
							Line_Printing_After_Matching(str1, search1, fp1, argv[3]);
							fclose(fp1);
						}
						File_numbar++;
					}
				}
				
				break;
			case 5:{	File_numbar = 3;
					while(argv[File_numbar] != NULL){
						if(!(fp1 = fopen(argv[File_numbar], "r"))){
							printf("Can't open file %s.\n", argv[File_numbar]);
							
						}
						else{
							Ignore_case(str1, search1, fp1);
							fclose(fp1);
						}
						File_numbar++;
					}
				}
				
				break;
			case 6:{
					while(argv[File_numbar] != NULL){
						if(!(fp1 = fopen(argv[File_numbar], "r"))){
							printf("Can't open file %s.\n", argv[File_numbar]);
							
						}
						else{
							Default_Option(str1, search1, fp1);
							fclose(fp1);
						}
						File_numbar++;
					}
				}
				break;
			case 7:
				Grep_dir(str1, search1, home, argv[3]);
	}			
	
	return 0;
}

void usage(void){
	printf("Usage: mygrep PATTERN [OPTION].... [FILE]...\n");
        printf("Try 'mygrep -h' for more information.\n");
	
}

void help(void){
	printf("\
Usage: mygrep PATTERN [OPTION]... [FILE]...\n\
Search for PATTERN in each FILE or standard input.\n\
PATTERN is, by default, a basic regular expression (BRE).\n\
Example: mygrep -i 'hello world' menu.h main.c\n\n");

	printf("\
-i, --ignore-case         ignore case distinctions\n\
	while matching the pattern ignore the difference between capital and small letters.\n\
-r, --recursive           like --directories=recurse\n\
	if combine '-r' with '*' search pattern recursivly in all files of the current directory\n\
	if only use '-r' then search in all directories.\n\
-A, --after-context=NUM   print NUM lines of trailing context\n\
-c, --count               print only a count of matching lines per FILE\n\
-L, --files-without-match  print output with line numbar\n");
										
		
}

// Search Directory recursivly
int Grep_dir(char *str, char *search, char *dir_name, char *argb){
	
	DIR *dir;
	struct dirent *dp;
	
	if(!(dir = opendir(dir_name))){
		perror("Error");
		return errno;
	}
	//printf(YELLOW BOLD "CURRENT DIR : %s"RESET, get_current_dir_name());
	if (!(dp = readdir(dir))){
		perror("Error");
        	return errno;
	}

	if(argb == NULL){

		if(chdir(dir_name)){
			perror("Error");
			return errno;
		}			
		do{
		
			if((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0)){
			
				if((dp->d_type != DT_DIR) && (dp->d_type != DT_REG)) //For files or directory, we don't have permission
					continue;
				else{  
					if(dp->d_type == DT_REG){ //*****file****
					
						if(text_or_binary(dp->d_name) == 1)
							Default_Option1(str, search, dp->d_name);
						else if(text_or_binary(dp->d_name) == 0)
							printf("Binary file %s matches\n", dp->d_name);
						else
							continue;
					
					}
					else if(dp->d_type == DT_DIR)//*********DIR**********
						Grep_dir(str, search, dp->d_name, argb);
					else
						continue;
				}
			
			}
			else
				continue;
		}while((dp = readdir(dir)));	
		chdir("..");
	}
	else if(!strcmp(argb, "*")){
		//search recursivly only in home directory.
			do{
		
				if((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0)){
			
					if((dp->d_type != DT_DIR) && (dp->d_type != DT_REG)) //For files or directory, we don't have permission
						continue;
					else{  
						if(dp->d_type == DT_REG){ //*****file************
					
							if(text_or_binary(dp->d_name) == 1)
								Default_Option1(str, search, dp->d_name);
							else if(text_or_binary(dp->d_name) == 0)
								printf("Binary file %s matches\n", dp->d_name);
							else
								continue;
					
						}
						else //********DIR**********
							continue;
					}
			
				}
				else
					continue;
			}while((dp = readdir(dir)));
			
	}
	
	closedir(dir);
	
	return 0;
}


int text_or_binary(const char *File_name){
	   
	   int x;
	   FILE *fp;
	   char ch;

	   fp = fopen(File_name, "r");

	   if( fp == NULL){
		perror("Error");
		return errno;
	}

	   while(fread(&ch, sizeof(ch), 1, fp) != 0){

	       if(isprint(ch) == 0){

		 if(isspace(ch) != 0)
		   continue ;
		 else{
		    //printf("Binary File\n");
		     fclose(fp);
		     return 0;
		 }
	       
	       }
	              
	   }
	   //printf("Text File\n");
	 
	   fclose(fp);

	   return 1;

}

void Ignore_case(char *str, char *search, FILE *fp){
	int count1=0,count2=0,i,j,flag, count = 0, z = 0, y = 0, x;
	
	while(fgets(str, 180, fp)) {
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


void Line_Printing_After_Matching(char *str, char *search, FILE *fp, char *NUM){
	int count1=0,count2=0,i,j,flag, count = 0, z = 0, y = 0, x,count_of_lines, a = 0, line_numbar = 1,b;
	long ab;
	
	count_of_lines = atoi(NUM);
	ab = ftell(fp);
	while(fgets(str, 180, fp))
		y++;
	
	long line_pointer[y + 1];
	line_pointer[0] = ab;
	y = 1;
	
	fseek(fp, line_pointer[0], SEEK_SET);
			
	while(fgets(str, 180, fp)){
		line_pointer[y] = ftell(fp);	
		y++;
	}
	
	fseek(fp, line_pointer[0], SEEK_SET);
	while(fgets(str, 180, fp)) {
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
		
					
					// Checking if matching string occure or not
					
					if(count_of_lines != 0){
						for(a = 1; a < count_of_lines + 1; a++){
							fgets(str, 180, fp);
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
							if(count != 0){
								fseek(fp, line_pointer[line_numbar], SEEK_SET);
								for(b = 0; b < (a - 1); b++){
									fgets(str, 180, fp);
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
	
	while(fgets(str, 180, fp)) {
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
	
	while(fgets(str, 180, fp)) {
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
	
	
	while(fgets(str, 180, fp)) {
				
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

void Default_Option1(char *str, char *search, char *File_name) {
	
	int count1=0,count2=0,i,j,flag, count = 0, z = 0, y = 0, x;
	FILE *fp;
	
	fp = fopen(File_name, "r");

	while(fgets(str, 180, fp)) {
				
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
					printf(MAGNETA"%s"CYAN":"RESET, File_name);
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
			
	fclose(fp);	
}

