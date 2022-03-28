#include <stdio.h>
#define MAX 1000

FILE * fileOpen(char*, char*);
void fileRead(FILE *, int*, int cnt);
int findK(int *, int);

FILE * fileOpen(char *filename, char *mode){
    FILE *fp;

    if((fp = fopen(filename, mode)) == NULL)
        printf("File open error.\n");
        return fp;
}

//data -> array(from file)
void fileRead(FILE *fp, int* dArr, int cnt){
    for(int i=0; i<cnt; i++){
        fscanf(fp,"%d", &dArr[i]);
    }
}

int findK(int *p, int n){
    int k=1, tmp=0; //k stands for iteration "number"
    for(int i=0; i<n-1; i++){
        for(int j=0;j<n-1-i;j++){
        // When k is odd or even.
        if(k%2!=0){
                if(p[i]>p[i+1]){
                    tmp=p[i];
                    p[i]=p[i+1];
                    p[i+1]=tmp;
                    k++;
                }
        }else{
                if(p[i]>p[i+1]){
                    tmp=p[i];
                    p[i]=p[i+1];
                    p[i+1]=tmp;
                    k++;
                }
            }
        }
    }
    return k;
}

int main() {
    int dataNum,k=0;
    int arr[MAX];

    FILE *fp;
    FILE *wf;
    //absolute path:/Users/jominjae/Desktop/input2.txt"
    fp=fileOpen("/Users/jominjae/Desktop/input2.txt", "r");

    if(fp==NULL) printf("file open miss\n");

    fscanf(fp, "%d", &dataNum);
    fileRead(fp, arr, dataNum);
    k = findK(arr,dataNum);
    printf("done");

    //absolute path:/Users/jominjae/Desktop/output2.txt"
    wf = fopen("/Users/jominjae/Desktop/output2.txt", "w");
    fprintf(wf, "%d", k);
    fclose(wf);

    return 0;
}
