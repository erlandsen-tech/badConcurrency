#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_THREADS 10

int saldo = 0;
int kunder = 0;
int antall = 100;
int totaltSalg = 0;
int pris = 180;
int randomnumber;

void * global_kjop(void *input) {

	randomnumber = rand() % 30;
	saldo = saldo + (pris * randomnumber);
	antall = antall - randomnumber;
	totaltSalg = totaltSalg + randomnumber;
	
	printf(
			"Kunde %i kjøpte %i biletter! \n"
			"Vi har solgt %i til nå \n" , 
			kunder, randomnumber, totaltSalg
			);
	
	kunder = kunder + 1;
}

int main() {
	srand(time(0)); 

	pthread_t thread_id[MAX_THREADS];
	int count = 0;
	
	while ( antall > 0 ) {
		while ( count < MAX_THREADS) {
			pthread_create(&thread_id[count], NULL, global_kjop, NULL); 
			count++;
		}
		for(int i = 0; i < count; i++)
			pthread_join(thread_id[i], NULL); 
		
		printf("Vi tjente	%i kr på bilettene!\n " 
				"og solgte %i av 100! \n",  saldo, totaltSalg);
}
return 0;
}
