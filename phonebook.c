#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

FILE * fileOpen(char*, char*);
void fileRead(FILE *, char(*)[10], int);
void init(void);
void insert(char *phoneNo);

FILE * fileOpen(char *filename, char *mode){
    FILE *fp;
    
    if((fp = fopen(filename, mode)) == NULL)
        printf("File open error.\n");
        return fp;
}

//data -> array(from file)
void fileRead(FILE *fp, char(*cp)[10], int cnt){
    for(int i=0;i<cnt;i++){
       fscanf(fp,"%c", cp[i]);
    }
}

struct node
{
    char data;
    struct node *link[10];
    int endOfNumber[10];
};

//setting the first node & flag(prefix y/n)
struct node *start = NULL, *ptr = NULL, *temp = NULL, *prev = NULL;
int flag = 0;

void init(void){
    flag = 0;
    start = ptr = temp = prev = NULL;
}

void insert(char *phoneNo){
    int i, j;

    if(start == NULL){
        start = (struct node *)malloc(sizeof(struct node));
        start->data = ' ';
        for(i = 0 ; i < 10 ; i++){
            start->link[i] = NULL;
            start->endOfNumber[i] = 0;
        }
        prev = start;
        for(i = 0 ; phoneNo[i] != '\0' ; i++){
            ptr = (struct node *)malloc(sizeof(struct node));
            ptr->data = phoneNo[i];
            for(j = 0 ; j < 10 ; j++){
                ptr->link[j] = NULL;
                ptr->endOfNumber[j] = 0;
            }
            if(phoneNo[i + 1] == '\0') ptr->endOfNumber[phoneNo[i] - '0'] = 1;
            prev->link[phoneNo[i] - '0'] = ptr;
            prev = ptr;
        }
    }
    else{
        // all the other nodes after the head node
        prev = start;
        ptr = start->link[phoneNo[0] - '0'];
        for(i = 0 ; phoneNo[i] != '\0' ; i++){
            if(ptr == NULL){
                ptr = (struct node *)malloc(sizeof(struct node));
                ptr->data = phoneNo[i];
                for(j = 0 ; j < 10 ; j++){
                    ptr->link[j] = NULL;
                    ptr->endOfNumber[j] = 0;
                }
                if(phoneNo[i + 1] == '\0') ptr->endOfNumber[phoneNo[i] - '0'] = 1;
                prev->link[phoneNo[i] - '0'] = ptr;
                prev = ptr;
                if(phoneNo[i + 1] != '\0') ptr = ptr->link[phoneNo[i + 1] - '0'];
            }
            else{
                if(ptr->endOfNumber[phoneNo[i] - '0'] == 1)
                    flag = 1;
                else{
                    if(phoneNo[i + 1] == '\0'){
                        flag = 1;
                        ptr->endOfNumber[phoneNo[i] - '0'] = 1;
                        break;
                    }
                    else
                        ptr->endOfNumber[phoneNo[i] - '0'] = 0;
                }
                if(phoneNo[i + 1] != '\0'){
                    prev = ptr;
                    ptr = ptr->link[phoneNo[i + 1] - '0'];
                }
            }
        }
    }
}

int main(void){
    FILE *fp;
    FILE *wf;
    
    int i, dNum; //number of data(first line)
    char phoneNo[10]; //phone number
    
    int result=-1;
    
    //absolute path:/Users/jominjae/Desktop/input1.txt"
    fp=fileOpen("/Users/jominjae/Desktop/input1.txt", "r");
    if(fp==NULL) printf("file open miss\n");

    fscanf(fp, "%d", &dNum);
    char phoneNum[10]; //maximum phone number is 10 letters.
    while(dNum--)
    {
        init();
        for(i = 0 ; i <= dNum ; i++)
        {
            fileRead(fp, &phoneNum, dNum);
            if(!flag)
                insert(phoneNo);
        }
        if(!flag)
            result = 1;
        else
            result = 0;
    }
    
    //absolute path:/Users/jominjae/Desktop/output1.txt"
    wf = fopen("/Users/jominjae/Desktop/output1.txt", "w");
    fprintf(wf, "%d", result);
    fclose(wf);

    return 0;
}
