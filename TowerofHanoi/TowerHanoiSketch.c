#include <stdio.h>
#include <string.h>

void DrawBox(int size, int topFromBottom, int tower_number); //pos means position from the dot
void Startup();
void StartBoxCoordinate (int x, int y, int size, int* start_row, int* start_col);
void DrawBox(int size, int topFromBottom, int tower_number);
void ReplaceBox(int box_number, int requiredtower_number, int requiredtopFromBottom);
void EnBox(int size, int topFromBottom, int tower_number, int *x, int *y);
void DeBox(int *topFromBottom, int *tower_number, int x, int y);
void SaveBox(int size, int topFromBottom, int tower_number);
void FindBoxDetails (int box_number, int *size, int *topFromBottom, int *tower_number);
void DeleteBox(int box_number);
void ResetAll();
void PrintAll();

//Every space is separated by 15
char a[11][60] = {
    "               |              |              |",
    "               |              |              |",
    "               |              |              |",
    "               |              |              |",
    "               |              |              |",
    "               |              |              |",
    "               |              |              |",
    "               |              |              |",
    "               |              |              |",
    "               |              |              |",
    "            ___.______________.______________.___"
    }; //. is put on base of each tower because it is important position to know
// . is put on 15, 30 and 45 positions respectively
char b[11][60]; //For safety backup
int boxes[10]; //Maximum of 10 boxes
//box[0] is topmost box ...... box[n] is last box
//That means we should manage box box[0] to box[n] after each save according to size


int pos_dot[3][2] = {{10,15},{10,30},{10,45}}; //Position of dot


int PrintFirstEmptyTopFromBottom(int tower_number){
    int i, size, topFromBottom, tower,t;
    topFromBottom = 0;
    tower = boxes[0]%10;
    for (i=0;i<10; i++){
        if (boxes[i]!=0){
            if ((boxes[i]%10)==tower_number){
                t = (boxes[i]%100)/10;
                if (topFromBottom < t){
                    topFromBottom = t;
                }
            }
        }
    }
    //topFromBottom gives maximum point to which boxes are filled
    return (topFromBottom+1);
}
void ForTwoChips(int box_number[], int requiredtower_number){
    //requiredtower_number is destination tower and differenttower_number is tower different from origin and destination
    //boxes are in same tower and overlapping in increasing size
    int topFromBottom1, topFromBottom2, differenttower_number;
    int origintower_number = boxes[box_number[0]-1]%10;
    int cal;
    //I also supposed origintower_number and requiredtower_number to be valid
    cal = origintower_number + requiredtower_number;
    differenttower_number = (cal==3)?3:(cal==4)?2:1;
    topFromBottom1 = PrintFirstEmptyTopFromBottom(requiredtower_number);
    topFromBottom2 = PrintFirstEmptyTopFromBottom(differenttower_number);

    ReplaceBox(box_number[0],differenttower_number,topFromBottom2);
    PrintAll();

    ReplaceBox(box_number[1],requiredtower_number, topFromBottom1);
    PrintAll();

    ReplaceBox(box_number[0],requiredtower_number, (topFromBottom1+1));
    PrintAll();
}

//These are commented out because we can make recursive by analyzing these function
//void ForThreeChips (int box_number[], int requiredtower_number){
//    //box_number stores 3 : 0,1,2
//    int cal, topFromBottom, differenttower_number;
//    int origintower_number = boxes[box_number[0]-1]%10;
//    cal = origintower_number + requiredtower_number;
//    differenttower_number = (cal==3)?3:(cal==4)?2:1;
//    int mbox[2];
//    mbox[0] = box_number[0];
//    mbox[1] = box_number[1];
//    ForTwoChips(mbox, differenttower_number);
//    topFromBottom = PrintFirstEmptyTopFromBottom(requiredtower_number);
//    ReplaceBox(box_number[2],requiredtower_number,topFromBottom);
//    PrintAll();
//    ForTwoChips(mbox, requiredtower_number);
//}
//
//void ForFourChips (int box_number[], int requiredtower_number){
//    //box_number stores 4 : 0,1,2,3
//    int mbox[3];
//    mbox[0] = box_number[0];
//    mbox[1] = box_number[1];
//    mbox[2] = box_number[2];
//    int cal, topFromBottom, differenttower_number;
//    int origintower_number = boxes[box_number[0]-1]%10;
//    cal = origintower_number + requiredtower_number;
//    differenttower_number = (cal==3)?3:(cal==4)?2:1;
//    ForThreeChips(mbox,differenttower_number);
//    topFromBottom = PrintFirstEmptyTopFromBottom(requiredtower_number);
//    ReplaceBox(box_number[3],requiredtower_number,topFromBottom);
//    PrintAll();
//    ForThreeChips(mbox, requiredtower_number);
//}

void TryingToMakeAllChips (int box_number[], int n, int requiredtower_number){ //Recursive Function of type void
    //box_number stores 3 : 0,1,2
    int cal, topFromBottom, differenttower_number, i;

    int origintower_number = boxes[box_number[0]-1]%10;
    cal = origintower_number + requiredtower_number;
    differenttower_number = (cal==3)?3:(cal==4)?2:1;

    if (n==2){
        ForTwoChips(box_number, requiredtower_number);
    }
    else {
        int mbox[n-1];
        for (i=0; i<(n-1); i++){
            mbox[i] = box_number[i];
        }
        topFromBottom = PrintFirstEmptyTopFromBottom(requiredtower_number);
        TryingToMakeAllChips(mbox,(n-1),differenttower_number);
        ReplaceBox(box_number[(n-1)],requiredtower_number,topFromBottom);
        PrintAll();
        TryingToMakeAllChips(mbox,(n-1),requiredtower_number);
    }
}

int main() {
    int box_number, tower_number, topFromBottom, size;
    int n, i=0;

    printf("Can you solve this?\n");
    printf("\n");

    printf("How many chips do you want?");
    scanf("%d",&n);

    int box_n[n];
    for (i=0; i<n; i++){
        DrawBox((n-i),(i+1),1);
//        DrawBox(4,2,1);
//        DrawBox(3,3,1);
//        DrawBox(2,4,1);
//        DrawBox(1,5,1);
        box_n[i] = (i+1);
    }


    PrintAll();

    printf("Taking 1,2,3 out of source tower to destination tower");
//    int box_n[5] = {1,2,3,4,5};
    int requiredtower_number = 3;
    TryingToMakeAllChips(box_n,n,requiredtower_number);


//    int n;
//    printf("Enter how many times do you want to move boxes: ");
//    scanf("%d",&n);
//    for (int i=0; i<n; i++){
//        printf("Enter box number, tower number and topFromBottom to be moved using comma: ");
//        scanf("%d,%d,%d",&box_number,&tower_number,&topFromBottom);
//        ReplaceBox(box_number,tower_number,topFromBottom);
//        PrintAll();
//    }

    return 0;
}

void Startup() {
    for (int i=0; i<11; i++){
        strcpy(b[i],a[i]);
    }

    PrintAll();
}

void StartBoxCoordinate (int x, int y, int size, int* start_row, int* start_col){ //x y are the middle point of tower
    //For exact drawing of box
    *start_row = x;
    *start_col = y - size;
}

void DrawBox(int size, int topFromBottom, int tower_number){ //Changes normal human language to coordinates
    int x,y;
    EnBox(size, topFromBottom, tower_number, &x, &y);
    int start_row, start_col; //For exact drawing of box
    StartBoxCoordinate(x,y,size,&start_row, &start_col);
    int difference = 2*size;
    int i;
    for (i = 0; i<difference; i++){
        if (i%2==0)
            a[start_row][start_col+i] = '[';
        else
            a[start_row][start_col+i] = ']';
    }
    SaveBox(size, topFromBottom, tower_number);
}
//bool CheckReplacePossible (int box_number){
    //Checks for where it is in middle or somewhere below
    //Checks for whether in destination tower, if smaller box is there
//}
void ReplaceBox(int box_number, int requiredtower_number, int requiredtopFromBottom) {
    int a, size;
    a = boxes[box_number-1];
    DeleteBox(box_number);
    size = a/100;
    DrawBox(size, requiredtopFromBottom, requiredtower_number);

}
void EnBox(int size, int topFromBottom, int tower_number, int *x, int *y){ //returns point of tower to start draw
    *x = pos_dot[tower_number-1][0] - topFromBottom;
    *y = pos_dot[tower_number-1][1];
}
void DeBox(int *topFromBottom, int *tower_number, int x, int y){ //returns size, topFromBottom, tower_number from point of tower
   int i, c=0;
   for (i=0; i<3; i++){
        if (pos_dot[i][1]==y){
            *tower_number = i+1;
            c=1;
        }
   }
   if (c!=1){
        printf("It is not the point of tower....");
        return;
   }
    *topFromBottom = pos_dot[(*tower_number-1)][0] - x;
}

void SaveBox(int size, int topFromBottom, int tower_number) {
    int box_count;
    for (int i=0; i<10; i++){
        if (boxes[i]==0){
            box_count = i+1;
            break;
        }
    }
    if (box_count>10){
        printf("Unable to save because of more boxes...\n");
    }
    boxes[box_count-1] = size*100 + topFromBottom*10 + tower_number;
    for (int i=0; i<box_count; i++){
        for (int j=0; j<box_count; j++){
            if (boxes[i]<boxes[j]){
                boxes[i] += boxes[j];
                boxes[j] = boxes[i] - boxes[j];
                boxes[i] = boxes[i] - boxes[j];
            }
        }
    }
}

void FindBoxDetails (int box_number, int *size, int *topFromBottom, int *tower_number){
    *topFromBottom = (boxes[box_number-1]%100)/10;
    *tower_number = boxes[box_number-1]%10;
    *size = boxes[box_number-1]/100;
}

void DeleteBox(int box_number){
    int size, topFromBottom, tower_number, start_row, start_col, x, y;
    FindBoxDetails(box_number, &size, &topFromBottom, &tower_number);
    EnBox(size, topFromBottom, tower_number, &x, &y);
    StartBoxCoordinate (x, y, size, &start_row, &start_col);

    int difference = 2*size;
    int i;
    for (i = 0; i<difference; i++){
        a[start_row][start_col+i] = ' ';
    }
    a[x][y] = '|';
    boxes[box_number-1] = 0;
    for (i=(box_number-1);i<9;i++){
        boxes[i] = boxes[i+1];
    }
}

void ResetAll() {
    for (int i=0; i<11; i++){
        strcpy(a[i],b[i]);
    }
}
void PrintAll() {
    printf("\n\n");
    printf("               ..........TOWER OF HANOI.........\n");
    printf("\n");
    for (int i = 0; i<11; i++){
        printf("%s\n",a[i]);
    }
    printf("\n");
    printf("           Source        Temporary       Destination\n");
    printf("\n\n\n");
}
