#include <stdio.h>
#define MAX 10000

typedef struct Coordinates
{
    int x, y;
}positions;
int dv(int, int, int, int, int, int);
int numTriangles(positions*, int);
FILE * fileOpen(char*, char*);
void fileRead(FILE *fp, positions *sArr, int cnt);


FILE * fileOpen(char *filename, char *mode){
    FILE *fp;
    
    if((fp = fopen(filename, mode)) == NULL)
        printf("File open error.\n");
        return fp;
}


void fileRead(FILE *fp, positions *sArr, int cnt){
    for(int i=0; i<cnt; i++){
        fscanf(fp,"%d", &sArr[i].x);
        fscanf(fp,"%d", &sArr[i].y);
    }
}

//determinant value of three points using matrix calculation
int dv(int x1, int y1, int x2, int y2, int x3, int y3){
    return x1*(y2-y3) - y1*(x2-x3) + 1*(x2*y3-y2*x3);
}

int numTriangles(positions *arr, int n){
    int triangles = 0;
    
    for(int i=0;i<n;i++){
        for (int j=i+1;j<n;j++){
            for (int k=j+1;k<n;k++){
                if(dv(arr[i].x, arr[i].y, arr[j].x, arr[j].y, arr[k].x, arr[k].y))
                    triangles++;
            }
        }
    }
    return triangles;
}

int main(){
    positions arr[MAX];//for searching i need to make an array.
    int n,result;
    FILE *fp;
    FILE *wf;
    //absolute path:/Users/jominjae/Desktop/input2.txt"
    fp=fileOpen("input2.txt", "r");
    
    if(fp==NULL) printf("file open miss\n");
    
    fscanf(fp, "%d", &n); //count for the first line(number of data)
    fileRead(fp, arr, n);
    result = numTriangles(arr,n);
    
    //absolute path:/Users/jominjae/Desktop/output2.txt"
    wf = fopen("output2.txt", "w");
    fprintf(wf, "%d", result);
    fclose(wf);
    
    return 0;
}
