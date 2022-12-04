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

void node_print(LinkedList* Node) {//노드를 출력해주는 함수. 노드 주소를 매개변수로받아
    int i;
    for (i = 0; i < 100; i++)
    {
        if (Node->next_link[i] != NULL)//하위노드가 끝날때까지 
        {
            printf("%d.%s\n", i + 1, Node->next_link[i]->data);//순서와 내용을 출력해준다
        }
    }
}
char* pathselect(ll_h* L)//헤드주소를 매개변수로 받아
{
    char path[100] = "C:\\";
    int select;
    LinkedList* tmp = L->head;
    if (tmp == NULL) {
        return path;
    }
    while (tmp != NULL)//헤드에서부터 끝날때까지
    {
        system("cls");
        node_print(tmp);//해당노드 출력 및 원하는 노드선택
        printf("선택(0은해당경로선택):");
        scanf("%d", &select);
        while (select != 0) {//해당경로를 선택한게 아닌이상 반복
            if (select >= 1 && select <= 100) {//1~100까지 다음노드 이동하면서 해당경로를 path에 연결
                strcat(path, tmp->data);
                tmp = tmp->next_link[select - 1];
            }
            else
            {
                printf("잘못된입력값입니다.");//그외값은오류
                system("pause");
                continue;
            }
        }
    }


    


    return path;//path반환
}
void createf(ll_h* L)
{
    char path[100];
    
    
    strcpy(path, pathselect(L));//경로설정
    mkf(path, L);  //파일 생성 함수 호출
}
void created(ll_h* L)
{
    char path[100];
    char orpath[100];
    char name[100];//파일 이름 입력
    printf("폴더이름:");
    scanf("%s", name);
    strcpy(path, pathselect(L));//경로선택
    strcpy(orpath, path);//혼용을 방지하기위해 본래 path를 보존
    mkd(path, name);//디렉터리 생성 함수 호출
    printf("%s", path);//경로 출력(안내용)
    CreateNode(L, name,orpath);//노드(폴더용) 생성 함수 호출
    
}

void deleted(ll_h* L,char path[100]) {
    
    char fpath[100];
    char upath[100];
    strcpy(upath, path);
    strcpy(fpath, path);
    int i;
    LinkedList* tmp = L->head;
    if (tmp == NULL)//헤드 다음 노드가 없다면 반환
        return;

    

    char* ptr;
    ptr = strtok(path, "\\");//path 는 c:\\로 시작하기떄문에 두번 strtok를 함으로써 원하는경로부터 시작
    ptr = strtok(NULL, "\\");
    while (ptr != NULL)//널이 아닌이상 반복
    {
        for (i = 0; i < 100; i++)
        {
            if (strcmp(ptr, strtok(tmp->next_link[i]->data,"\\")) == 0)//노드의 데이터와 path에서 끊어온게일치하다면 그링크로 이동
            {

                tmp = tmp->next_link[i];
                break;
            }
        }
        ptr = strtok(NULL, "\\");//노드 이동후 다음 경로로 지칭
    }//해당하는 디렉터리로 이동후
    for (i = 0; i < 100; i++)
    {
        if (tmp->pre_link->next_link[i] == tmp) {//이전노드의 nextlink를 끊어버리고
            tmp->pre_link->next_link[i] = NULL;
            break;
        }
    }
    LinkedList* ttp = tmp;//tmp의원래위치(지우고자하는 노드위치)를 유지시켜줄 새로운 변수
    tmp = tmp->node;//노드, 폴더가아닌 파일 노드로 이동.
    LinkedList* tnp=tmp;
    
    while (tmp->next_link[0]!=NULL)//다음 노드가 끝날때까지반복
    {

        strcpy(fpath, path);//path 유지위해 fpath사용
        strcat(fpath, tmp->data);
        remove(fpath);//해당하는 파일의 경로로 파일삭제
    }
    
    for (i = 0; i < 100; i++)
    {
        if (tnp->next_link[i] != NULL)
        {
            deleted(L, strcat(upath,tnp->next_link[i]->data));//하위 디렉터리를 모두 삭제하기위한 재귀호출
        }
    }
    rmdir(path);
    free(ttp);//ttp free
}
/////////////////////
void deletef(ll_h* L) {
    char path[100];
    strcpy(path, pathselect(L));//경로선택
    int i;
    LinkedList* tmp = L->head;
    LinkedList* tnp;
    if (tmp == NULL)
        return;
    char* ptr;
    ptr = strtok(path, "\\");//위에 설명한 바와같이 경로에해당하는 자료구조의 위치로 가기위한 함수
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
    
    tmp = tmp->node;//파일 노드로 이동
    tnp = tmp;
    i = 0;
    while (tmp != NULL)
    {
        i++;
        printf("[%d]%s\n", i, tmp->data);//각 노드들의 데이터(파일명)을 전부 출력
        tmp = tmp->next_link[0];
    }
    int d;
    printf("선택할 파일: ");
    scanf("%d", &d);//파일선택
    for (i = 0; i < d; i++)
    {
        tnp = tnp->next_link[0];//선택한 파일 노드로 이동
    }
    tnp->pre_link->next_link[0] = tnp->next_link[0];//앞뒤 노드를 제거할 노드 를 뺴고 연결해주기
    tnp->next_link[0]->pre_link = tnp->pre_link;
    
    remove(strcat(path, tnp->data));//파일 삭제
}

ll_h* create_h(void) {
    ll_h* L;
    L = (ll_h*)malloc(sizeof(ll_h));
    L->head = NULL;//헤드를 할당하고 그 주소를 반환한다
    return L;
}
int CreateNode(ll_h* L, char arr[], char path[])
{
    
    LinkedList* NewNode;
    NewNode = (LinkedList*)malloc(sizeof(LinkedList));//linkedlist형 할당
    LinkedList* Pre=L->head;//이전노드를 알기위한 포인터
    LinkedList* tmp=L->head;
    int i;
    char* ptr;
    ptr = strtok(path, "\\");//위에서 설명한 바와같이 자료구조에서 원하는 위치로 가기위한 과정
    ptr = strtok(NULL, "\\");
    
    while (ptr != NULL)
    {
        printf("%s", ptr);
        printf("1");
        for (i = 0; i < 100; i++)
        {
            if (strcmp(ptr, strtok(tmp->next_link[i]->data, "\\")) == 0)
            {
                Pre = tmp;//진행하면서pre는 tmp바로 직전 노드를 가르키게 된다
                tmp = tmp->next_link[i];
            }
        }

        ptr = strtok(NULL, "\\");//경로 탐색
    }
    

    

    if (NewNode == NULL)//newnode가 할당되지않았다면 오류
    {
        printf("오류발생\n");
        return 0;
    }
    if (L->head == NULL)
    {
        NewNode->pre_link = L;//헤드다음 노드가 없다면 헤드 다음에 바로연결
        L->head = NewNode;
        strcpy(NewNode->data, "C:\\");
    }
    else
    {
        tmp->next_link[i] = NewNode; //그렇지않다면 pre노드랑 연결하며 위에서 사용된 i가 바로 비어있는 공간을 의미함.
        NewNode->pre_link = tmp;
        strcpy(NewNode->data, arr);//데이터(파일이름)이식
    }
}
void delete_node(LinkedList* Node, ll_h* L)//노드삭제를위해 삭제할 노드의 위치를 받음
{
    int i;
    if (L->head == Node)//헤드 바로다음이라면
    {
        L->head = NULL;//헤드 의 링크를 NULL로바꾸고 free후종료
        free(Node);
        return;
    }
    for (i = 0; i < 100; i++)
    {
        if (Node->pre_link->next_link[i] == Node)//위 경우 외엔 node의 이전노드의 다음링크 i번째중 옳은것에대하
        {
            Node->pre_link->next_link[i]=Node->next_link[0];//NULL로 초기화.다만 디렉터리삭제에선 하위디렉터리가 삭제될것이고, 파일 노드에선 다음 노드가 0번째이기에 
            //next_link[0]대입
            break;
        }
    }

    free(Node);//노드초기화
}
///////////////
void interface()
{
    printf("====================\n1.새 관리 헤드 생성\n2.폴더생성\n3.파일생성\n4.폴더삭제\n5.파일삭제\n6.검색\n7.종료\n====================");//인터페이스 출력함수
    printf("\n>>>");
}
int mkd(char path[100], char name[100])//디렉터리 생성함수
{
    char fpath[100];
    strcpy(fpath, path);//입력받은 path에서 복사해와서
    system("cls");
    printf("--------\n폴더생성\n--------\n");
    //안내후
    strcat(name, "\\");
    strcat(fpath, name);//fpath,name,\\를 연결해준뒤
    _mkdir(fpath);//경로생성
    printf("경로: %s\n", fpath);//경로출력후 
    system("pause");//퍼즈
    
}
int mkf(char path[100],ll_h* L)
{
    char name[100];
    char upath[100];
    strcpy(upath, path);
    printf("원하는 파일 이름(확장자명 필수):");//원하는 이름 입력
    scanf("%s", name);
    strcat(upath, name);
    FILE* file;//파일을 w+형으로 열어 파일 생성
    file = fopen(upath, "w+");
    system("cls");
    if (file == NULL)//만약 파일이 열리지않았다면 오류.
    {
        printf("오류\n");
        system("pause");
        return;
    }
    printf("--------\n파일생성\n경로: %p\n--------\n", path);//생성한 경로 출력
    fclose(file);
    int i;

    LinkedList* tmp = L->head;//노드 포인터생성
    char* ptr;
    ptr = strtok(upath, "\\");//마찬가지로 원하는 노드로 가기위한 과정
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
    LinkedList* NewNode = (LinkedList*)malloc(sizeof(LinkedList));//새로운 노드 할당

    strcpy(NewNode->node->data, name);//노드데이터에 데이터 데입
    tmp = tmp->node;//파일 노드로 진입
    while (tmp != NULL)
    {
        tmp = tmp->next_link[0];//연결리스트의 끝까지이동
    }
    tmp->next_link[0] = NewNode;//마지막 노드에 이어서 newnode 연결
    system("pause");
    return;//종료
}
void search(ll_h* L)//검색을위해 헤드를 매개변수로입력
{
    char path[100];
    char word[100];
    strcpy(path, pathselect(L));//경로선택
    LinkedList* tmp;
    int i;
    char* ptr;
    ptr = strtok(path, "\\");
    ptr = strtok(NULL, "\\");//위와같이 원하는 위치로 이동하기위한 과정
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
    tmp = tmp->node;//파일 노드로 진입
    FILE* fp;
    char text[1000];
    printf("검색할 단어: ");
    scanf("%s", word);//검색할 단어 입력
    while (tmp != NULL)//노드가 끝날때까지
    {
        fp = fopen(strcat(path, tmp->data), "r+");//경로에 tmp의 데이터, 즉 파일이름을 이은걸로 파일을 열어 
        fgets(text, sizeof(text), fp);//문장을 한줄씩 입력받아
        ptr = NULL;
        ptr = strstr(text, word);//단어와비교후
        if (ptr != NULL)//일치한다면
        {
            printf("%s\n", text);//문장을 출력하고
            printf("위치: %s", strcat(path, tmp->data));//파일 위치를 출력
        }
        tmp = tmp->next_link[0];//다음노드로 이동
    }

}

int main()
{

    ll_h* L[100];//여러 헤드를 관리하기위해 배열형식으로 생성
    L[0] = create_h();//헤드생성
    char path[100];
    int i = 0;
    int d;
    int choice;
    while (1)
    {
        interface();
        scanf("%d", &choice);//사용할 함수 선택
        printf("관리할 헤드:");//관리할 헤드선택
        scanf("%d", &d);
        switch (choice)//선택한 헤드와 함수를 이용해 함수를 실행
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
            strcpy(path, pathselect(L));
            deleted(L[d],path);
            break;
        case 5:
            deletef(L[d]);
            break;
        case 6:
            search(L[d]);
        case 7://종료
            printf("종료\n");
            return;
        default://잘못된 입력일경우
            printf("잘못된 입력값입니다\n");
        }
        system("cls");//화면정리
    }
}
