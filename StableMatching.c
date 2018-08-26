/* Stable matching algorithm:
 * ==========================
 * 1) Initially all men M and all women W are single.
 * 2) While there is a man M who is single and hasn't proposed to every woman:
 * 3)	Choose such a man M.
 * 4)	Let W be the highest ranked woman in the preference list of M, he hasn't proposed yet.
 * 5)	If W is free then:
 * 6)		(M, W) becomes engazed.
 * 7)	Else W is currently engazed to M'.
 * 8)		If W prefers M' to M then:
 * 9)			M remains single.
 * 10)		Else W prefers M to M'. Then:
 * 11)			M becomes engazed.
 * 12)			M' becomes single.
 * 13)		Endif
 * 14)	 Endif
 * 15) Endwhile.
 * 16) Return the set of engazed pairs.
 ***********************************************************************************************/	
#include<stdio.h>

struct Male{
	int status;
	int preference[4];
	int propose_counter;
};

struct Female{
	int status;
	int preference[4];
};

// 1) We have four boys and girls. Singles, ready to mingle.
struct Male man[4];
struct Female woman[4];

// 2) All of them has a preference list about whom they desire as their partners.
int men_preference[4][4] = { {1, 3, 0, 2}, {0, 1, 2, 3}, {1, 0, 2, 3}, {0, 1, 3, 2} };
int women_preference[4][4] = { {0, 2, 1, 3}, {0, 1, 3, 2}, {1, 0, 2, 3}, {2, 0, 1, 3} };

int main(void){
	// 3) In the beginning everyone is single, so singlehool = 4. This is indicated bellow by status = -1 for everyone.
	int singlehood = 4, current, new;

	for(int i = 0; i<4; i++){
		man[i].propose_counter = 0;
		man[i].status = -1;
		woman[i].status = -1;
		// 4) No one have proposed anyone yet, so everyone's propose_counter = 0.
	}

	// Initializing everyone's preferencs.
	for(int i = 0; i< 4; i++)
		for(int j = 0; j< 4; j++){
			man[i].preference[j] = men_preference[i][j];
			woman[i].preference[j] = women_preference[i][j];
		}
	
	while(singlehood != 0)
		for(int i = 0; i<4; i++){
			/* 5) If a man is single then he goes for a girl he haven't proposed yet. First he proposes
			 * the girl he prefers most. Men's are reprasened with the count variable 'i'.
			 * 9) But after she declines/breaks up, he moves to the girl he prefers next. Each man's
			 * propose_counter keeps track to whom whe proposed to this time. */
			if(man[i].status == -1){
				int j = man[i].propose_counter; // j holds the current value of propose queue.
				man[i].propose_counter++;

				// 6) If she's single, they get engazed.
				int n = man[i].preference[j];
				if(woman[n].status == -1){
					woman[n].status = i;
					man[i].status = n;
					singlehood--;	// Once a pair is made, singlehood counter drops by one.
				}
				else{
					// 7) if she's engazed, the new suitor tries to convince the he's better than her current.
					for(int k = 0; k< 4; k++){
						if(woman[n].preference[k] == woman[n].status)
							current = k;
						if(woman[n].preference[k] == i)
							new = k;
					}					
					if(new < current){
						// 8) If the girl is convinced, she leaves her ex and pairs up with the new suitor.
						man[woman[n].status].status = -1;
						woman[n].status = i;
						man[i].status = n;
					}
				}
			}
		}
	/* 10. This pair making and breaking goes on until no one is single(singlehool = 0).
	 * 11. Finally the pairs are outputed. */
	puts("Final status:");
	for(int i = 0; i< 4; i++)
		printf("Pair[%d] - man[%d]:woman[%d]\n", i, i, man[i].status);

	puts("\nVerifying with what women says.");
	for(int i = 0; i< 4; i++)
		printf("Pair[%d] - woman[%d]:man[%d]\n", i, i, woman[i].status);

	return 0;
}
