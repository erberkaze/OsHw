
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

#define SIZE 5
typedef struct _thstruct{
  double x;
  double y;
} Point;

sem_t mutex; //BU NASIL OLUŞTURULACAK
int ct;
void* homework(void* arg){

    FILE *fp;
    for(; ct > 0 ; ct--){ //BU DEĞER NASIL ALINACAK numberN
		
		
		Point buffer;
		buffer.x=(double)rand()/RAND_MAX*20.0-(10.0);
    	buffer.y=(double)rand()/RAND_MAX*2.0-(-2.0);

        if(buffer.x>0 && buffer.y>0){

            sem_wait(&mutex);
            fp  = fopen ("NE.txt", "a");
            fprintf(fp,"(%lf,%lf)\n",buffer.x,buffer.y);
            fclose(fp);
            sem_post(&mutex);
        }
        else if(buffer.x<0 && buffer.y>0){

            sem_wait(&mutex);
            fp  = fopen ("NW.txt", "a");
            fprintf(fp,"(%lf,%lf)\n",buffer.x,buffer.y);
            fclose(fp);
            sem_post(&mutex);
        }
        else if(buffer.x<0 && buffer.y<0){

            sem_wait(&mutex);
            fp  = fopen ("SW.txt", "a");
            fprintf(fp,"(%lf,%lf)\n",buffer.x,buffer.y);
            fclose(fp);
            sem_post(&mutex);
        }
        else if(buffer.x>0 && buffer.y>0){

            sem_wait(&mutex);
            fp  = fopen ("SE.txt", "a");
            fprintf(fp,"(%lf,%lf)\n",buffer.x,buffer.y);
            fclose(fp);
            sem_post(&mutex);
        }
        else{

            sem_wait(&mutex);
            fp  = fopen ("XY.txt", "a");
            fprintf(fp,"(%lf,%lf)\n",buffer.x,buffer.y);
            fclose(fp);
            sem_post(&mutex);
        }
    }
    exit(0);
    return NULL;
}


int main(int argc,char *argv[]) {

    double t_x;
    double t_y;
    srand(time(NULL));

    int threadNum=atoi(argv[1]); //thread number T
    int numberN= atoi(argv[2]);  //number N
    int total_num= threadNum*numberN;
	
	ct = threadNum*numberN;
	// tik
	
    sem_init(&mutex, 0, 1);

    pthread_t thrds[threadNum];

    for (int i = 0; i < threadNum; i++){

            pthread_create(&thrds[i], NULL, homework , NULL);
    }
    for (int i = 0; i < threadNum; i++){

        pthread_join(&thrds[i], NULL);
    }
    return 0;
}
