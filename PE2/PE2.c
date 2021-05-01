

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 30
#define fieldLength 200


#define diskFile "diskFile.dat"
#define courseFile "course.txt"

struct db_type
{
   char name[fieldLength];
   int age;
   char course1[fieldLength];
   char course2[fieldLength];
   char status[fieldLength];
 };

struct courseInfo
{ 
  char code [20]; // e.g., EECS2030
  char title [fieldLength];
  char  date [20];
  char time_start [20];
  char time_end [20];
  char  location [20]; 
};
 
 
struct courseInfo courseArr[SIZE]; // global variable  array of struc
     

char prompt_menu(void);
void init_list(struct db_type * pArr[]); 
void clearDB(struct db_type * pArr[]);
void init_courseArr(void);

void writeDisk(struct db_type * pArr[]); 
void emptyDisk(void); 
void loadDisk(struct db_type * pArr[]); 





int main(int argc, char *argv[])
{
    
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    init_courseArr();  // load course from diskfile
    
    char choice;
    for(; ;){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
         case 'w': writeDisk(db_pArr);  break;    
         case 'l': loadDisk(db_pArr); break;
         case 's': sort(db_pArr); break;
	   
         case 'c': clearDB(db_pArr); break;  
         case 'e': emptyDisk();break;

         case 'v': displayCourses();break;
         case 'p': swap(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
	
     }
     return 0;
}

void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  { 
     pArr[t]= NULL;
  }
}

void clearDB(struct db_type * pArr[]){
   char c3[3];
   printf("are you sure to clear db? (y) or (n)? ");
 
   fgets(c3,3,stdin);
   
   if(! strcmp(c3, "y\n"))  
      init_list(pArr);
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("Swa(p) records\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay db\t|\n");
  
    printf("|    %-20s","(L)oad disk");
    printf("%-20s","(W)rite disk");
    printf("(E)mpty disk\t|\n");
  
    printf("|    %-20s", "(V)iew courses");//|\tSwa(p) record\t(Q)uit\t\t\t\t|\n");
    printf("%-20s","(Q)uit");
    printf("*Case Insensitive*\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
   
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
	 
 }
}

/* display all or specified course */
void displayCourses(void){   
;  // the provide PE2.out uses "%s\t%-40s%-5s %s-%s   %s\n" as formatting string for printing each course info
      
      char input[50];

      printf ("course code (or 'a')?\n");
      fgets(input, 30, stdin);
      input[strlen(input) - 1] = '\0';
      // get the input from user and making sure the input has a null terminating character 

      if (input[0] == 'a' || input[0] == 'A') {
        for (int i = 0; i < 21; i++) {
          printf ("%s\t%-40s%-5s %s-%s   %s\n", courseArr[i].code, courseArr[i].title, courseArr[i].date, courseArr[i].time_start, courseArr[i].time_end, courseArr[i].location);
        // if the input is 'a' or 'A', print the all courses info the way we want it 
        }
      }
      for (int i = 0; i < 21; i++) {
        if (strcmp(input, courseArr[i].code) == 0 || strcmp(input, courseArr[i].code+4) == 0) {
        // if the comparison is equal to 0, then that means the course exists
          printf ("%s\t%-40s%-5s %s-%s   %s\n", courseArr[i].code, courseArr[i].title, courseArr[i].date, courseArr[i].time_start, courseArr[i].time_end, courseArr[i].location);
        }
        // if the input contains the course code or just the 4 digit number, print it the way we want it
      }
}


/* a helper function to check if a course exists or not*/
int checkCourse(char course1[]){
  for(int i = 0; i < 21; i++){
    if(strcmp(course1, courseArr[i].code) == 0 || strcmp(course1, courseArr[i].code+4) == 0){
    return i;  
    }
  /* loop through the array and if the comparison between the input and the array element[i] is 0, then the 
     course exists, and return the value of i */
  }
  return -1;
  // if not, then return -1 to signify the course doesn't exist within the array
}

/* a helper function to check if the times of two courses overlap each other */
int checkdaysOverlap (struct courseInfo temp1, struct courseInfo temp2) {
  for (int i = 0; i < strlen(temp1.date); i++)
    if (strchr(temp2.date, temp1.date[i]) != NULL) {
      return 1;
    // loop through the day letters to see if they're the same string, meaning same day, and return 1 to represent true
    }
  return 0;
  // if not, then they are not on the same day so return 0 as false
}

/* a helper function to convert the time to a format that can be used to compare with other times */
int timeConverter (char time[]) {
  return ((time[0] - 48) *1000) + ((time[1] - 48) * 100) + ((time[3] - 48) * 10) + ((time[4] - 48));
}

/* a helper function to get the size of pArr */
int sizeHelper (struct db_type * pArr[]) {
  int i = 0;

  while(pArr[i] != NULL){
    i++;
  }
  return i;
}



/* input items into the list */
void enterNew(struct db_type * pArr[SIZE]){  
	;

  char name[200];
  printf ("name:");
  fgets(name, 30, stdin);
  name[strlen(name) - 1] = '\0';
  // get the name input from user and making sure the input has a null terminating character

  int age;
  printf ("age:");
  scanf (" %d", &age);
  getchar();
  // get the age input from user and making sure the input has a null terminating character

  char course1[200];
  printf ("course-1:");
  fgets(course1, 200, stdin);
  course1[strlen(course1) - 1] = '\0';
  // get the course1 input from user and making sure the input has a null terminating character

  struct courseInfo temp1;
  struct courseInfo temp2;
  temp1 = courseArr[checkCourse(course1)];
  /* creating 2 temp variables of type struct courseInfo, assigning course1 to temp 1, and then checking to see if 
     course1 exists within pArr */

  while (checkCourse(course1) == -1) {

      printf ("course does not exist, enter again:");

      fgets(course1, 200, stdin);
      course1[strlen(course1) - 1] = '\0';
      temp1 = courseArr[checkCourse(course1)];
  // if course does not exist, then continue to ask for input until a valid course is entered
  }

  char course2[50];
  printf ("course-2:");
  fgets(course2, 30, stdin);
  course2[strlen(course2) - 1] = '\0';
  temp2 = courseArr[checkCourse(course2)];
  /* get the course2 input from user and making sure the input has a null terminating character, and then assigning
    course2 to temp 2, and then checking to see if course2 exists within pArr */
  
  
  while (checkCourse(course2) == -1) {

      printf ("course does not exist, enter again:");

      fgets(course2, 200, stdin);
      course2[strlen(course2) - 1] = '\0';
      temp2 = courseArr[checkCourse(course2)];
  // if course does not exist, then continue to ask for input until a valid course is entered
  }

  int size = sizeHelper(pArr);
  pArr[size] = (struct db_type *) malloc (sizeof(struct db_type));
  // get the size of pArr and allocate the appropriate space

  if (checkdaysOverlap(temp1, temp2) == 0) {
  // use the helper function to check if they are on the same day
    printf ("SUCCESSFUL! No time conflict.\n");
    strcpy (pArr[size]->status, "SUCCESSFUL! No time conflict.\n");
  // if the courses are on different days, then there is no conflict. status is also assigned
  }

  else {
    if ( (timeConverter(temp1.time_start) < timeConverter(temp2.time_end) && timeConverter(temp2.time_start) < timeConverter(temp1.time_end)) == 0 ) {
    printf ("SUCCESSFUL! No time conflict.\n");
    strcpy (pArr[size]->status, "SUCCESSFUL! No time conflict.\n");
    // if there is no time overlap, then there is no conflict. status is also assigned
    }
    
    else {
      printf ("ATTENTION! Time conflict.\n");
      strcpy (pArr[size]->status, "ATTENTION! Time conflict.\n");
      // otherwise, there is a conflict between courses. status is also assigned
    }
  }
  
  strcpy (pArr[size]->name, name);
  pArr[size]->age = age;
  // assign the name and age of the person in pArr

  sprintf(pArr[size]->course1,"%s\t%-40s%-5s %s-%s   %s", temp1.code, temp1.title, temp1.date, temp1.time_start, temp1.time_end, temp1.location);
  sprintf(pArr[size]->course2,"%s\t%-40s%-5s %s-%s   %s", temp2.code, temp2.title, temp2.date, temp2.time_start, temp2.time_end, temp2.location);
  // print the courses that pertain to the person 

}

/* display records */
void displayDB(struct db_type * pArr[]){
  ;

  for (int i = 0; i < sizeHelper(pArr); i++) {
    printf ("name: %s\n", pArr[i]->name);
    printf ("age: %d\n", pArr[i]->age);
    printf ("course1: %s\n", pArr[i]->course1);
    printf ("course2: %s\n", pArr[i]->course2);
    printf ("remarks: %s\n", pArr[i]->status);
  // loop through the array pArr and print out the info for each person at index [i] 
  }
 
}


/* remove an existing item */
void removeRecord (struct db_type * pArr[])	
{
  ;
  char name[200];
  struct db_type *temp;
  // variable for the name and pointer to a struct

  printf ("enter full name to remove:");
  fgets(name, 200, stdin);
  name[strlen(name) - 1] = '\0';
  // get input for the name from user and making sure the input has a null terminating character

  for (int i = 0; i < sizeHelper(pArr); i++) {
    if (strcmp(name, pArr[i]->name) == 0) {
      // printf ("record [%s] removed successfully.", pArr[i]->name);
      temp = pArr[i];
      printf ("record [%s] removed successfully.", pArr[i]->name);
  // loop through pArr and if the comparison between pArr[i] and name is 0, then the person exists
      
      for(int j = i; j < sizeHelper(pArr); j++) {
        pArr[j] = pArr[j+1];
      } 
      free(temp);
      // to remove, simply shift the element by one and free up the space we used before  
    }

    else {
      printf ("record not found\n");
      // otherwise, person doesn't exist within pArr and print not found 
    }
  }

}

/* swap records */
void swap(struct db_type * pArr[]){
	;
  struct db_type *temp = 0;
  // pointer to a struct variable 

  for (int i = 0; i < sizeHelper(pArr)-1; i=i+2) {
      temp = pArr[i];
      pArr[i] = pArr[i+1];
      pArr[i+1] = temp;
  /* loop through the array and take element at [i], place it at index [i+1], and place element at index [i+1]
     at index [i] (e.g, [john, bob] becomes [bob, john]) */
  }
  
} 

/* load from course.txt, store into (global) array of courses  */
void init_courseArr(void){ 
 
   FILE *fr; //file pointer
   fr = fopen (courseFile, "r");
   char arr[50];  
   int count = 0;
   while ((fgets(arr,100,fr)) != NULL)
   {  
     strncpy(courseArr[count].code,  arr, strlen(arr)-1); // remove \n  
     courseArr[count].code[strlen(arr)-1] = '\0';  //to be safe
	 
     fgets(arr,100,fr);  
     strncpy(courseArr[count].title ,  arr, strlen(arr)-1);
     courseArr[count].title[strlen(arr)-1] = '\0';  //to be safe
     
          
     fgets(arr,100,fr); 
     strncpy(courseArr[count].date,  arr, strlen(arr)-1);
     courseArr[count].date[strlen(arr)-1] = '\0';  //to be safe
	   
     // other ways, remove \n before
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_start,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_end,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].location,  arr); 
	  
     count++;
     fgets(arr,100,fr); // read the empty line
   }

   strcpy(courseArr[count].code, "EECS0000"); // a terminator token structure

   fclose(fr);
	 
 }
    
/************************ DISK IO *****************************************************************/

void writeDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;

  if ( (fp=fopen(diskFile,"ab")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  
  for (i=0; i< SIZE ; i++)
  {
     if ( pArr[i] != NULL)
     {  
       if (fwrite( pArr[i], sizeof(struct db_type), 1, fp) != 1)
       { 
          printf("file write error\n");
       }
     } 
   }
   fclose(fp);

}

void emptyDisk(void){

  FILE *fp;
  
  char c3[3];
  printf("are you sure to empty disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;
 
  //else
  if ( (fp = fopen(diskFile,"w")) == NULL)
  {
     printf("no file to open\n");
     return;
  }
  fclose(fp); // open close, will empty the file
}


void loadDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;
  char c3[3];
  printf("will overwrite current records. are you sure to load disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;

  struct db_type * tmp;  
  
  if ( (fp = fopen(diskFile,"r")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  init_list(pArr);
  for (i=0; i < SIZE ; i++)
  {    
     
     tmp =  (struct db_type *) malloc (sizeof(struct db_type));   
	   
     if (fread( tmp, sizeof(struct db_type), 1, fp) != 1)
     {
       if (feof(fp))
       { fclose(fp); 
         return;
       }
       printf("file read error\n");
     }
     else pArr[i] = tmp;
  }
}

/****bonus*************************************************************************************/

/* sort the records by ages */
void sort(struct db_type * pArr[])
{
  struct db_type *temp = 0;
  // temp variable 

  for (int i = 0; i < sizeHelper(pArr)-1; i++) {
    for (int j = i+1; j < sizeHelper(pArr); j++) {
    // double loop to compare two values beside each other in the array
      
      if (pArr[j]->age < pArr[i]->age) {
        temp = pArr[i];
        pArr[i] = pArr[j];
        pArr[j] = temp;
      /* if the age of person at index[i] is less than age of person at index[j], place person at index[j] in front of
        person at index[i] */ 
      }
    }
  }

}  

 
 
