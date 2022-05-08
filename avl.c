#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left,* right;
    int balance_factor;
    int student_id;
    int score;
    int age;
    int height;
    
} AVL;


void fileRead(AVL*, FILE*, int, int);
FILE * fileOpen(char*, char*);

AVL* Link(int,int,int,int);
AVL* find_rotation(AVL*);
void print_balance_factors(AVL*);
void print_preorder(AVL*, FILE *);
int intlength(int);
AVL* Print_Tree_Minimum(AVL*);
int max(int, int);

//Rotations
AVL* Rotate_Right_Right(AVL*);
AVL* Rotate_Right_Left(AVL*);
AVL* Rotate_Left_Left(AVL*);
AVL* Rotate_Left_Right(AVL*);

AVL* Insert_new_node(AVL* , int,int,int,int);
AVL* Delete_node(AVL* root, int del);


int main() {
    AVL* ROOT = NULL;
    int key_standard,num_students, deleteNode;
    FILE *fp;
    FILE *wf;
    
    //absolute path: /Users/jominjae/Desktop/input.txt"
    fp=fileOpen("input2.txt", "r");
    
    if(fp==NULL) printf("file open miss\n");
    //count for the first line(selecting standard)
    // 1: student_id 2: score 3: age
    fscanf(fp, "%d", &key_standard);
    // Line 2: number of students
    fscanf(fp, "%d", &num_students);
    int data, sid, score, age;
    for(int i=0; i<num_students; i++){
        fscanf(fp,"%d %d %d\n", &sid, &score, &age);
        switch (key_standard) {
            case 1:
                data = sid;
                break;
            case 2:
                data = score;
                break;
            case 3:
                data = age;
            default:
                printf("invalid standard input error.\n");
                data = 0;
        }
        ROOT = Insert_new_node(ROOT,data,sid,score,age);
    }

    // Data to be deleted
    fscanf(fp, "%d", &deleteNode);
    fclose(fp);
    
    
    //write to a file
    //absolute path:/Users/jominjae/Desktop/output.txt"
    wf= fopen("output2.txt", "w");
    print_preorder(ROOT, wf);
    fprintf(wf, "\n");
   
    ROOT = Delete_node(ROOT, deleteNode);
    print_preorder(ROOT, wf);
    
    fclose(wf);
    
    return 0;
}

FILE * fileOpen(char *filename, char *mode){
    FILE *fp;
    
    if((fp = fopen(filename, mode)) == NULL)
        printf("File open error.\n");
    
    return fp;
}


AVL* Link(int add, int sid, int score, int age) {
    AVL *temp = (AVL*)malloc(sizeof(AVL));
    temp->data= add;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 0;
    temp->balance_factor = 0;
    temp->student_id=sid;
    temp->score=score;
    temp->age=age;
    
    return temp;
}

AVL* Delete_node(AVL* root, int del) {
    int left = 0, right = 0;
    if (root == NULL) {
        return NULL;
    }
    if (del < root->data) {
        root->left = Delete_node(root->left, del);

        if (root->right != NULL) {
            right = root->right->height + 1;
        }
        if (root->left != NULL) {
            left = root->left->height + 1;
        }
        if (root->left == NULL && root->right == NULL) {
            root->height = 0;
            root->balance_factor = 0;
        }
        else {
            if (left == right) {
                root->balance_factor = 0;
                root->height = left;
            }
            else if (left > right) {
                root->height = left;
                root->balance_factor = left - right;
            }
            else if (left < right) {
                root->height = right;
                root->balance_factor = left - right;
            }

        }

        if (root->balance_factor >= 2 || root->balance_factor <= -2) {
            root = find_rotation(root);
        }

    }
    else if (del > root->data) {
        root->right = Delete_node(root->right, del);
        if (root->right != NULL) {
            right = root->right->height + 1;
        }
        if (root->left != NULL) {
            left = root->left->height + 1;
        }
        if (root->left == NULL && root->right == NULL) {
            root->height = 0;
            root->balance_factor = 0;
        }
        else {
            if (left == right) {
                root->balance_factor = 0;
                root->height = left;
            }
            else if (left > right) {
                root->height = left;
                root->balance_factor = left - right;
            }
            else if (left < right) {
                root->height = right;
                root->balance_factor = left - right;
            }
        }

        if (root->balance_factor >= 2 || root->balance_factor <= -2) {
            root = find_rotation(root);
        }
    }
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        }

        else if (root->left == NULL) {
            AVL *temp = root;
            root = root->right;
            free(temp);
        }

        else if (root->right == NULL) {
            AVL *temp = root;
            root = root->left;
            free(temp);
        }

        else {
            AVL *temp = Print_Tree_Minimum(root->right);
            root->data= temp->data;
            root->right = Delete_node(root->right, temp->data);
        }
    }
    return root;
}

AVL* find_rotation(AVL* cookie) {
    int left = 0, right = 0;
        while (!(cookie->balance_factor <= 1 && cookie->balance_factor >= -1)) {

            if (cookie->left != NULL) {
                left = cookie->left->height;
            }
            if (cookie->right != NULL) {
                right = cookie->right->height;
            }
            if (right > left) {
                if (cookie->right->right != NULL) {
                    cookie = Rotate_Right_Right(cookie);
                }
                else {
                    cookie = Rotate_Right_Left(cookie);
                }
            }
            else {
                if (cookie->left->left != NULL) {
                    cookie = Rotate_Left_Left(cookie);
                }
                else {
                    cookie = Rotate_Left_Right(cookie);
                }
            }
        }
        return cookie;
    }

AVL* Print_Tree_Minimum(AVL* root) {
    AVL* temp = root;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

AVL* Rotate_Right_Right(AVL* twix) {
    int left = 0, right = 0;
    AVL *temp = NULL;
    AVL* result = twix->right;
    if (twix->right->left != NULL) {
        temp = twix->right->left;
    }
    twix->right->left = twix;
    twix->right = temp;
    if (twix->left != NULL) {
        left = twix->left->height + 1;
    }
    if (temp != NULL) {
        right = temp->height + 1;
    }
    twix->height = left >= right ? left : right;
    twix->balance_factor = left - right;
    result->height = result->left->height >= result->right->height ? result->left->height + 1 : result->right->height + 1;
    result->balance_factor = result->left->height - result->right->height;
    return result;
}

AVL* Rotate_Right_Left(AVL* twix) {
    AVL* temp = twix->right;
    twix->right = temp->left;
    twix->right->right = temp;
    temp->left = NULL;
    twix->right->height = 1;
    twix->right->balance_factor = 1;
    twix->right->right->height = 0;
    twix->right->right->balance_factor = 0;
    return twix;
}

AVL* Rotate_Left_Left(AVL* twix) {
    int left = 0, right = 0;
    AVL* temp = NULL;
    AVL* result = twix->left;
    if (twix->left->right != NULL) {
        temp = twix->left->right;

    }
    twix->left->right = twix;
    twix->left = temp;
    if (twix->right != NULL) {
        right = twix->right->height + 1;
    }
    if (temp != NULL) {
        left = temp->height + 1;
    }
    twix->height = left >= right ? left : right;
    twix->balance_factor = left - right;
    result->height = result->left->height >= result->right->height ? result->left->height + 1 : result->right->height + 1;
    result->balance_factor = result->left->height - result->right->height;
    return result;
}

AVL* Rotate_Left_Right(AVL* twix) {
    AVL* temp = twix->left;
    twix->left = temp->right;
    twix->left->left = temp;
    temp->right = NULL;
    twix->left->height = 1;
    twix->left->balance_factor = 1;
    twix->left->left->height = 0;
    twix->left->left->balance_factor = 0;
    return twix;
}
int intlength(int value) {
    int len = !value;
    while (value) {
        len++;
        value /= 10;
    }
    if (value < 0) {
        len -= 1;
    }
    return len;
}

void print_balance_factors(AVL* root) {
    int number = 0;
    int i = 1;
    if (root != NULL) {
        print_balance_factors(root->left);
        number = intlength(root->data);
        if (root->balance_factor < 0) {
            i++;
        }
        for (; i < number; i++) {
            printf(" ");
        }
        printf("%d ", root->balance_factor);
        print_balance_factors(root->right);
    }

}

void print_preorder(AVL* root, FILE *wf) {
    if (root != NULL) {
        fprintf(wf, "%d ", root->student_id);
        print_preorder(root->left, wf);
        print_preorder(root->right, wf);
        }
}


AVL* Insert_new_node(AVL* nodeindi, int add, int sid, int score, int age) {
    if (nodeindi == NULL) {
        return Link(add,sid,score,age);
    }
    
    if (add < nodeindi->data) {
        nodeindi->left = Insert_new_node(nodeindi->left, add,sid,score,age);
        int left = 0, right = 0;
        if (nodeindi->left != NULL) {
            left = nodeindi->left->height + 1;
        }
        if (nodeindi->right != NULL) {
            right = nodeindi->right->height + 1;
        }
        if (left >= right) {
            nodeindi->height = left;
        }
        else {
            nodeindi->height = right;
        }
        nodeindi->balance_factor = left - right;
        if (nodeindi->balance_factor >= 2 || nodeindi->balance_factor <= -2) {
            nodeindi = find_rotation(nodeindi);
        }
    }
    else if (add > nodeindi->data) {
        nodeindi->right = Insert_new_node(nodeindi->right, add,sid,score,age);
        int left = 0, right = 0;
        if (nodeindi->left != NULL) {
            left = nodeindi->left->height + 1;
        }
        if (nodeindi->right != NULL) {
            right = nodeindi->right->height + 1;
        }
        if (left >= right) {
            nodeindi->height = left;
        }
        else {
            nodeindi->height = right;
        }
        nodeindi->balance_factor = left - right;
        if (nodeindi->balance_factor >= 2 || nodeindi->balance_factor <= -2) {
            nodeindi = find_rotation(nodeindi);
        }
    }
    return nodeindi;
}
