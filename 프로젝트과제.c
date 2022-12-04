#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>
typedef struct node {
    char data[100];
    struct node* node;
    struct node* pre_link;
    struct node* next_link[100];
}LinkedList;

typedef struct {
    LinkedList* head;
}ll_h;

void node_print(LinkedList* Node) {
    int i;
    for (i = 0; i < 100; i++)
    {
        if (Node->next_link[i] != NULL)
        {
            printf("%d.%s\n", i + 1, Node->next_link[i]->data);
        }
    }
}
char* pathselect(ll_h* L)
{
    char path[100] = "C:\\";
    int select;
    LinkedList* tmp = L->head;
    if (tmp == NULL) {
        return path;
    }
    while (tmp != NULL)
    {
        system("cls");
        node_print(tmp);
        printf("선택:");
        scanf("%d", &select);
        if (select == 0)
        {
            while (tmp->pre_link != L) {
                strcat(path, tmp->data);
                tmp = tmp->pre_link;
            }
            strcat(path, tmp->data);
        }
        else if (select >= 1 && select <= 100)
            tmp = tmp->next_link[select - 1];
        else
        {
            printf("잘못된입력값입니다.");
            system("pause");
            continue;
        }


    }


    return path;
}
void createf(ll_h* L)
{
    char path[100];
    char name[100];
    
    strcpy(path, pathselect(L));
    mkf(path, L);  
}
void created(ll_h* L)
{
    char path[100];
    char orpath[100];
    char name[100];
    printf("폴더이름:");
    scanf("%s", name);
    strcpy(path, pathselect(L));
    strcpy(orpath, path);
    mkd(path, name);
    printf("%s", path);
    CreateNode(L, name,orpath);
    
}

void deleted(ll_h* L) {
    char path[100];
    char fpath[100];
    strcpy(path, pathselect(L));
    strcpy(fpath, path);
    int i;

    LinkedList* tmp = L->head;
    
    if (tmp == NULL)
        return;

    

    char* ptr;
    ptr = strtok(path, "\\");
    ptr = strtok(NULL, "\\");
    while (ptr != NULL)
    {
        for (i = 0; i < 100; i++)
        {
            if (strcmp(ptr, tmp->next_link[i]->data) == 0)
            {

                tmp = tmp->next_link[i];
                break;
            }
        }
        ptr = strtok(NULL, "\\");
    }//디렉터리 이동

    for (i = 0; i < 100; i++)
    {
        if (tmp->pre_link->next_link[i] == tmp) {
            tmp->pre_link->next_link[i] = NULL;
            break;
        }
    }
    free(tmp);
    tmp = tmp->node;
    LinkedList* tnp;
    while (tmp->next_link[0]!=NULL)
    {

        strcpy(fpath, path);
        strcat(fpath, tmp->data);
        remove(fpath);
    }
    rmdir(path);//삭제되는가?
}
/////////////////////
void deletef(ll_h* L) {
    char path[100];
    strcpy(path, pathselect(L));
    int i;
    LinkedList* tmp = L->head;
    LinkedList* tnp;
    if (tmp == NULL)
        return;
    char* ptr;
    ptr = strtok(path, "\\");
    ptr = strtok(NULL, "\\");
    while (ptr != NULL)
    {
        for (i = 0; i < 100; i++)
        {
            if (strcmp(ptr, tmp->next_link[i]->data) == 0)
            {

                tmp = tmp->next_link[i];
                break;
            }
        }
        ptr = strtok(NULL, "\\");
    }//디렉터리 이동
    tmp = tmp->node;
    tnp = tmp;
    i = 0;
    while (tmp != NULL)
    {
        i++;
        printf("[%d]%s\n", i, tmp->data);
        tmp = tmp->next_link[0];
    }
    int d;
    printf("선택할 파일: ");
    scanf("%d", &d);
    for (i = 0; i < d; i++)
    {
        tnp = tnp->next_link[0];
    }
    tnp->pre_link->next_link[0] = tnp->next_link[0];
    tnp->next_link[0]->pre_link = tnp->pre_link;
    remove(strcat(path, tnp->data));
}

ll_h* create_h(void) {
    ll_h* L;
    L = (ll_h*)malloc(sizeof(ll_h));
    L->head = NULL;
    return L;
}
int CreateNode(ll_h* L, char arr[], char path[])
{
    
    LinkedList* NewNode;
    NewNode = (LinkedList*)malloc(sizeof(LinkedList));
    LinkedList* Pre=L->head;
    LinkedList* tmp=L->head;
    int i;
    char* ptr;
    ptr = strtok(path, "\\");
    ptr = strtok(NULL, "\\");
    printf("1");
    while (ptr != NULL)
    {
        printf("%s", ptr);
        printf("1");
        for (i = 0; i < 100; i++)
        {
            if (strcmp(ptr, strtok(tmp->next_link[i]->data, "\\")) == 0)
            {
                Pre = tmp;
                tmp = tmp->next_link[i];
            }
        }

        ptr = strtok(NULL, "\\");
    }

    

    if (NewNode == NULL)
    {
        printf("오류발생\n");
        return 0;
    }
    if (L->head == NULL)
    {
        NewNode->pre_link = L;
        L->head = NewNode;
        strcpy(NewNode->data, "C:\\");
    }
    else
    {
        Pre->next_link[i] = NewNode;
        NewNode->pre_link = Pre;
        strcpy(NewNode->data, arr);
    }
}
void delete_node(LinkedList* Node, ll_h* L)
{
    int i;
    if (L->head == Node)
    {
        L->head = NULL;
        free(Node);
        return;
    }
    for (i = 0; i < 100; i++)
    {
        if (Node->pre_link->next_link[i] == Node)
        {
            strcpy(Node->pre_link->next_link[i], NULL);
            break;
        }
    }

    free(Node);
}
///////////////
void interface()
{
    printf("====================\n1.새 관리 헤드 생성\n2.폴더생성\n3.파일생성\n4.폴더삭제\n5.파일삭제\n6.검색\n7.종료\n====================");
    printf("\n>>>");
}
char* list_find(int i)
{

    static char c[] = { "C:\\프로젝트\\" };//링크 리스트 주소 변수 선언
    if (i == 1)
    {
        return c;
    }

}
int mkd(char path[100], char name[100])
{
    system("cls");
    printf("--------\n폴더생성\n--------\n");
    
    strcat(name, "\\");
    strcat(path, name);
    _mkdir(path);
    printf("경로: %s\n", path);
    system("pause");
    
}
int mkf(char path[100],ll_h* L)
{
    char name[100];
    printf("원하는 파일 이름(확장자명 필수):");
    scanf("%s", name);
    strcat(path, name);
    FILE* file;
    file = fopen(path, "w+");
    system("cls");
    if (file == NULL)
    {
        printf("오류\n");
        system("pause");
        return;
    }
    printf("--------\n파일생성\n경로: %p\n--------\n", path);
    fclose(file);
    int i;

    LinkedList* tmp = L->head;
    char* ptr;
    ptr = strtok(path, "\\");
    ptr = strtok(NULL, "\\");
    while (ptr != NULL)
    {
        for (i = 0; i < 100; i++)
        {
            if (strcmp(ptr, strtok(tmp->next_link[i]->data, "\\")) == 0)
            {
                tmp = tmp->next_link[i];
            }
        }

        ptr = strtok(NULL, "\\");
    }
    LinkedList* NewNode = (LinkedList*)malloc(sizeof(LinkedList));

    strcpy(NewNode->node->data, name);
    tmp = tmp->node;
    while (tmp != NULL)
    {
        tmp = tmp->next_link[0];
    }
    tmp->next_link[0] = NewNode;
    system("pause");
    return;
}
void search(ll_h* L)
{
    char path[100];
    char word[100];
    strcpy(path, pathselect(L));
    LinkedList* tmp;
    int i;
    char* ptr;
    ptr = strtok(path, "\\");
    ptr = strtok(NULL, "\\");
    while (ptr != NULL)
    {
        for (i = 0; i < 100; i++)
        {
            if (strcmp(ptr, strtok(tmp->next_link[i]->data, "\\")) == 0)
            {
                tmp = tmp->next_link[i];
            }
        }
    }
    tmp = tmp->node;
    FILE* fp;
    char text[1000];
    printf("검색할 단어: ");
    scanf("%s", word);
    while (tmp != NULL)
    {
        fp = fopen(strcat(path, tmp->data), "r+");
        fgets(text, sizeof(text), fp);
        ptr = NULL;
        ptr = strstr(text, word);
        if (ptr != NULL)
        {
            printf("%s\n", text);
            printf("위치: %s", strcat(path, tmp->data));
        }
        tmp = tmp->next_link[0];
    }

}

int main()
{

    ll_h* L[100];
    L[0] = create_h();
    int i = 0;
    int d;
    int choice;
    while (1)
    {
        interface();
        scanf("%d", &choice);
        printf("관리할 헤드:");
        scanf("%d", &d);
        switch (choice)
        {
        case 1:
            i++;
            L[i] = create_h();
            break;
        case 2:
            created(L[d]);
            break;
        case 3:
            createf(L[d]);
            break;
        case 4:
            deleted(L[d]);
            break;
        case 5:
            deletef(L[d]);
            break;
        case 6:
            search(L[d]);
        case 7:
            printf("종료\n");
            return;
        default:
            printf("잘못된 입력값입니다\n");
        }
        system("cls");
    }
}