#include<stdio.h>
#include<string.h>

#define MAX_WORD 8316   //# of words in word base
#define MAX_CLUSTER 119  //Maximum # of clusters
#define MAX_WORD_LENGTH 100    //Maximum length of a word
#define MAX_REVIEW_LENGTH 10000  //Maximum length of a review
#define MAX_REVIEW 2767   //Maximum number of reviews

char* getword(char* str)
{
	char* t = str, word[MAX_WORD_LENGTH];
	int i = 0;
	while(((*t) != EOF) & ((*t) != ' ') & (i < MAX_WORD_LENGTH)){
		word[i] = *t;
		i++;
		t++;
	}
	word[i] = '\0';
	if(strlen(word) >= MAX_WORD_LENGTH){
		printf("%s Exceed the maximum length of word.\n",word);
	}
	return word; 
}

void rev2cl(char* rev,char* dict[],int loc[],int cl[])//transform a review into a vector
{
	char* t = rev,*word;
	int i = 0,j = 0,wordlen = 0,revlen = strlen(rev);
	while(j < revlen){//traversal a review

		//get the word one by one till the last
		word = getword(t);
		wordlen = strlen(word);
		//check if the word is in word base dict: if yes, add 1 to the corresponding location vector(loc+1);if not, 
		//skip
		for(i = 0; i < MAX_WORD; i++)
		{ 
			if(strcmp(dict[i],word) == 0){
				cl[loc[i]]++;
				break;
			}
		}
		t = t + wordlen + 1;
		j = j + wordlen + 1;
	}
	//finally get a MAX_CLUSTER-dimension vector
	return;
}

void main()
{
	char line[MAX_REVIEW_LENGTH];
	char *dict[MAX_WORD],word[MAX_WORD_LENGTH];
	int cl[MAX_CLUSTER]={0},loc[MAX_WORD]={0}, idx = 0, i = 0,num = 1,hot = 0;
	FILE* fp = NULL,*fp_csv_in = NULL,*fp_csv_out = NULL,*redu = NULL;

	fp = fopen("/media/sunzeyeah/Personal/SENIOR/Thesis/Data/Chinese/class_sorted_119.txt","r");
	fp_csv_in = fopen("/media/sunzeyeah/Personal/SENIOR/Thesis/Data/Chinese/Sina/sport.csv","r");
	fp_csv_out = fopen("/media/sunzeyeah/Personal/SENIOR/Thesis/Data/Chinese/Sina/TitleVectors_spo.csv","w+");
	if((fp == NULL) || (fp_csv_in == NULL) || (fp_csv_out == NULL)/* || (redu == NULL)*/){ 
		printf("cannot open file!\n");
		return;
	}
	while(EOF != fscanf(fp,"%s %d",word,&idx)){
		dict[i] = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
		strcpy(dict[i],word);
		loc[i] = idx;
		i = i + 1;
	}
	fclose(fp);

	while(fgets(line,sizeof(line),fp_csv_in)){
		for(i = 0; i < MAX_CLUSTER; i++) cl[i] = 0;
		rev2cl(line,dict,loc,cl);
		//fprintf(fp_csv_out,"%s,",line);
		//fscanf(redu,"%d",&hot);
		//printf("hot is %d\n",hot);
		//fprintf(fp_csv_out,"%d,",hot);
		for(i = 0; i < MAX_CLUSTER-1; i++)
			fprintf(fp_csv_out,"%d,",cl[i]);
		fprintf(fp_csv_out,"%d\n",cl[i]);
		printf("Progress: %.2f%%\n",100*(double)(num)/MAX_REVIEW);
		num++;
		for(i = 0;i < MAX_REVIEW_LENGTH; i++) line[i] = 0;
	}
	

	fclose(fp_csv_in);
	fclose(fp_csv_out);
	//fclose(redu);
	return;
}
