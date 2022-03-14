#include <stdio.h>
#define MAX 10000
void descending(int *, int);
int calDis(int *, int);
void fileRead(FILE*, int*, int);
FILE * fileOpen(char*, char*);

FILE * fileOpen(char *filename, char *mode){
    FILE *fp;
    
    if((fp = fopen(filename, mode)) == NULL)
        printf("File open error.\n");
    
        return fp;
}

void fileRead(FILE *fp, int *dArr, int cnt){
    for(int i=0; i<cnt; i++){
        fscanf(fp,"%d", &dArr[i]);
    }
}

void descending(int *p, int n){
    int tmp=0;
    for(int i=0; i<n; ++i){
        for(int j=i; j<n; ++j){
            if(p[i] < p[j]){
                tmp = p[i];
                p[i]=p[j];
                p[j]=tmp;
            }
        }
    }
}

//Calculating MAX discount value
int calDis(int *arr, int n){
    int disVal=0; //TOTAL discount value
    int idx=1; //an index for counting how many products were bought to get 1 free
    for(int i=0;i<n;++i){
        if(idx%3!=0) ++idx; //should pay the product
        else{
            disVal+=arr[i]; //get 1 free
            idx=1; //reset idx
        }
    }
    return disVal;
}

int main(){
    int n, arr[MAX];
    FILE *fp;
    FILE *wf;
    //absolute path: /Users/jominjae/Desktop/input1.txt"
    fp=fileOpen("input1.txt", "r");
    
    if(fp==NULL) printf("file open miss\n");
    fscanf(fp, "%d", &n); //count for the first line(number of data)
    
    fileRead(fp,arr,n);
    descending(arr, n);
    int result = calDis(arr, n);
    
    //write to a file
    //absolute path:/Users/jominjae/Desktop/output1.txt"
    wf= fopen("output1.txt", "w");
    fprintf(wf,"%d",result);
    fclose(wf);
    
    //run this code to check answer in console; printf("%d\n", result);
}
