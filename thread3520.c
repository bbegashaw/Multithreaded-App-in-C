#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#define _GNU_SOURCE
#include <sys/syscall.h>
#include <sys/types.h>
#include <wait.h>

//shared data
int numOfStudents;
double grades[30][12];
double maxGrade;


void *readDatat();
void printArray();
void *collectResultAndDisplay(void *param);
void *computeAssignmentMark();
void *computeProjectMark();
void *computeMidtermMark();
void *computeFinalMark();
void *computeCourseMark();
void *computeMaxGrade();


int main(int argc, char *argv[]){

    // //thread to read data
    pthread_t datareadid;
    pthread_create(&datareadid,NULL,readDatat,NULL);
    pthread_join(datareadid, NULL);

    // //thread to calculate assignment mark
    pthread_t computeAssignmentID;
    pthread_create(&computeAssignmentID,NULL,computeAssignmentMark,NULL);

    //thread to calculate project mark
    pthread_t computeProjectID;
    pthread_create(&computeProjectID, NULL, computeProjectMark, NULL);

    //thread to calculate midterm mark
    pthread_t computeMidtermID;
    pthread_create(&computeMidtermID, NULL, computeMidtermMark, NULL);

    //thread to calculate final mark
    pthread_t computeFinalID;
    pthread_create(&computeFinalID, NULL, computeFinalMark, NULL);

    


    //join threads
    pthread_join(computeAssignmentID, NULL);
    pthread_join(computeProjectID, NULL);
    pthread_join(computeMidtermID, NULL);
    pthread_join(computeFinalID, NULL);
    

    //thread to calculate course mark for each student
    pthread_t computeCourseMarkID;
    pthread_create(&computeCourseMarkID, NULL, computeCourseMark, NULL);
    pthread_join(computeCourseMarkID, NULL);

    

    //threa to calculate max grade 
    pthread_t computeMaxGradeID;
    pthread_create(&computeMaxGradeID, NULL, computeMaxGrade, NULL);
    pthread_join(computeMaxGradeID, NULL);


    return 0;
}


void *readDatat(){
    printf("Hello. Enter the number of students.\n");
    scanf("%d", &numOfStudents);
    
    
    for(int i =0 ;i < numOfStudents; i++){
        grades[i][0] = i+1;
        for(int j = 0; j < 7; j++){
            if(j < 3){
                printf("Enter mark for assigment %d for student %d: ", j+1,i+1);
                scanf("%lf", &(grades[i][j+1]));
            }else if(j == 4){
                printf("Enter mark for project 1 for student %d: ", i+1);
                scanf("%lf", &(grades[i][j]));
            }else if(j==5){
                printf("Enter mark for midterm 1 for student %d: ", i+1);
                scanf("%lf", &(grades[i][j]));
            }else if(j==6){
                printf("Enter mark for final 1 for student %d: ", i+1);
                scanf("%lf", &(grades[i][j]));
            }
        }
    }
}

void *computeAssignmentMark(){
    for(int i = 0; i < numOfStudents; i++){
        double mark = 0;
        
        
        grades[i][7] = (((grades[i][1] + grades[i][2] + grades[i][3]) / 3) * 0.15);
        
    }
}

void* computeProjectMark(){
    for(int i = 0; i < numOfStudents; i++){
        grades[i][8] = (grades[i][4]) * 0.15;  
    }
}

void *computeMidtermMark(){
    for(int i = 0; i < numOfStudents; i++){
        grades[i][9] = (grades[i][5]) * 0.30; 
    }
}

void *computeFinalMark(){
    for(int i = 0; i < numOfStudents; i++){
        grades[i][10] = (grades[i][6]) * 0.40;
    }

}

void *computeCourseMark(){
    for(int i = 0; i < numOfStudents; i++){
        grades[i][11] = grades[i][7] + grades[i][8] + grades[i][9] + grades[i][10];  
    }
}

void *computeMaxGrade(){
    //calculate max grade by comparing with each student
    maxGrade = 0;
    int studentNum;
    for(int i = 0; i < numOfStudents; i++){
        if(maxGrade < grades[i][11]){
            maxGrade = grades[i][11];
            studentNum = i;
        }
    }

    printf("----------------------------------------------------");
    printf("\nTHE HIGHEST MARK IS: %.2lf from Student %d\n", maxGrade, (int)grades[studentNum][0]);
}


