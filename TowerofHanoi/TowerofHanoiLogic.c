#include <stdio.h>

void Print(char a[][3]){
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            printf("%c\t",a[j][i]);
        }
        printf("\n");
    }
}

void ForTwoChips (int box_number[2], int requiredtower_number){
    //This function is to shift 2 chips one above another to another tower in exact same way
    //only 2 array are entered
    //I suppose both boxes are in same tower now


}
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
