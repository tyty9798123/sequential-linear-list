//
//  main.c
//  Resizable-Array
//
//  Created by Swift on 2020/2/5.
//  Copyright © 2020 Swift. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20

typedef int Status;
typedef int ElemType;

typedef struct{
    ElemType data[MAXSIZE];
    int length;
} SqList;

Status GetElem(SqList L, int i, ElemType *e){
    //如果 Length == 0 或是 查找的索引小於 1(因為線性表的順序儲存結構從1開始)
    //或是 查找的 index 大於 線性表的長度
    if ( L.length == 0 || i < 1 || i > L.length){
        printf("error\n");
        return ERROR;
    }
    //賦予值，因為陣列從0開始，線性表從1開始，所以-1
    *e = L.data[i-1];
    
    return OK;
}


Status ListInsert (SqList *L, int i, ElemType e){
    int k;
    //如果此陣列的長度大於MAXSIZE
    if (L->length == MAXSIZE){
        return ERROR;
    }
    //如果查找的index小於1
    //如果查找的index大於總長度+1
    //針對第二點
    //你要新增的是6, 目前長度是5
    //6 > 6 return error
    //但如果不加1的話會變6 > 5 就return error了
    //(因為還沒新增，所以預先使用+1的判斷)
    if (i < 1 || i > L->length+1){
        return ERROR;
    }
    // 如果 你要新增的index 小於等於 目前的長度 6 <= 6
    if (i <= L->length){
        // 從後面到前面 直到新增的index - 1 (因為array-1) 全部往後調 從
        // 1 2 3 4 5 6
        // 如果我要新增在3的位子
        // 4 3 5 6 就要後退
        // 變成  1 2 newInt 3 4 5 6
        for (k = L->length -1; k >= i-1 ; k--){
            L->data[k+1] = L->data[k];
        }
    }
    // 如果是 新增的index是7 那大可不用移動
    L->data[i-1] = e;
    L->length++;
    
    return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e){
    int k;
    //如果L的lenght == 0
    if (L->length == 0){
        return ERROR;
    }
    //如果 index < 1, index > L.length
    // 因為不是新增，所以不用像inset一樣把 L->length+1（那是故意預留的）
    if (i < 1 || i > L->length){
        return ERROR;
    }
    //賦予即將刪掉的值給e
    *e = L->data[i-1];
    // 如果index < 總長度 (還沒滿)
    if (i < L->length){
        //從前到後，直到i 往前調
        for (k = i; k < L->length; k++){
            L->data[k-1] = L->data[k];
        }
    }
    L->length--;
    return OK;
}

int main(){
    ElemType numbers[] = {10, 20, 30, 40};
    SqList list1;
    list1.length = 4;
    memcpy( list1.data, numbers, 20 );
    
    //新增
    ListInsert(&list1, 5, 50);
    
    //刪除
    ElemType e2 = 0;
    ListDelete(&list1, 1, &e2);
    printf("%d\n", e2);
    
    //查找
    ElemType e = 0;
    GetElem(list1, 4, &e);
    printf("%d\n", (int)e);
    
    //查找所有
    for (int i = 1; i <= list1.length; i++){
        ElemType for_e = 0;
        GetElem(list1, i, &for_e);
        printf("%d\n", for_e);
    }
    return 0;
}
