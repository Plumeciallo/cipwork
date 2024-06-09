#include <stdio.h>
#include <string.h>
#include <ctype.h>

char CIP[1000];
char MES[1000];
char KEY[26]={0};    //�������ֱ�Ӽ��ܽ��ܵ��������ĺ���Կ

// �����Ӣ����ĸƵ�ʣ����ڳ����²�
const double ENG_FREQ[] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074
};   //����ΪABCDEFGHIJKLMNOPQRSTUVWXYZ

char ENG_WORD[] = {
    'e','t','a','n','o','r','i','s','h','d','l','f','c','m','u','g','y','p','w','b','v','k','j','x','q','z'
};

// �ٶ������ģ�ʵ��Ӧ����Ӧ���ļ����û������ȡ
char ciphertext[1000];//���������ַ�������
char messtext[1000];//���������ַ�������

typedef struct{
    char word_cip;
    int num_cip;
}Stacip;    //����ͳ��������ĸ������

Stacip Cipstatic[26]={{'a',0},{'b',0},{'c',0},{'d',0},{'e',0},{'f',0},{'g',0},{'h',0},{'i',0},{'j',0},{'k',0},{'l',0},{'m',0},{'n',0},{'o',0},{'p',0},
{'q',0},{'r',0},{'s',0},{'t',0},{'u',0},{'v',0},{'w',0},{'x',0},{'y',0},{'z',0}
};

typedef struct{
    char cip_word;  //������ĸ
    char cip_change;    //���Ĵ�����ĸ
    int cip_num;      //������ĸ����
}Let_conver;    //������ʼ���Ķ�Ӧ�Ĵ��������

Let_conver Subarray[26];
Let_conver Temp[1];

typedef struct{
    char pointcip;   //������ĸ
    char pointmes;   //������ĸ
}Point;

Point userpoint[26];  //����û�ָ������������ĸ��

typedef struct{
    char grammar[3];
}dictionary;

dictionary dir[27]={
    {"as"},{"at"},{"an"},{"is"},{"it"},{"in"},{"he"},{"or"},
    {"the"},{"ing"},{"ere"},{"his"},{"her"},{"ion"},{"ent"},{"ous"},{"ive"},{"and"},{"our"},{"ard"},{"all"},{"ant"},{"him"},{"not"},{"end"},{"for"},{"was"}
};      //�ֵ�(�ɸ���)

void Straightenc()
{
    int i,len,l;
    printf("�������ģ�");
    scanf("%s",MES);
    printf("���������Կ������Ϊa~z�Ķ�Ӧ��ĸ���޶�Ӧ��ĸ����0��:");
    getchar();
    scanf("%s",KEY);
    len=strlen(MES);
    for(i=0;i<len;i++)
    {
        if(MES[i]>='a'&&MES[i]<='z')
        {
            l=MES[i]-'a';
            if(KEY[l]!=0)
                CIP[i]=KEY[l];
        }
        else
            CIP[i]=MES[i];
    }
    printf("����Ϊ��%s\n",CIP);
}

void Straightdec()
{
    int i,len,l;
    printf("�������ģ�");
    scanf("%s",CIP);
    printf("���������Կ������Ϊa~z�Ķ�Ӧ��ĸ���޶�Ӧ��ĸ����0��:");
    getchar();
    scanf("%s",KEY);
    len=strlen(CIP);
    for(i=0;i<len;i++)
    {
        if(CIP[i]>='a'&&CIP[i]<='z')
        {
            l=CIP[i]-'a';
            if(KEY[l]!=0)
                MES[i]=KEY[l];
        }
        else
            MES[i]=CIP[i];
    }
    printf("����Ϊ��%s\n",MES);
}

void firstchange(Let_conver a[])
{
    int i;
    for(i=0;i<26;i++)
    {
        a[i].cip_change=ENG_WORD[i];
    }

}

void changeciphertxt(char ciphertext[],Let_conver Subarray[],int length) //�滻�����������ĺ���
{
    int i,j;
    for(i=0;i<length;i++)
        for(j=0;j<26;j++)
        {
            if(ciphertext[i]==Subarray[j].cip_word)
                {messtext[i]=Subarray[j].cip_change;break;}
        }
}

int pointchange(Point userpoint[])   //�滻ָ�����ĺ���
{
    int i,f;
    char cip,mes;
    printf("\n--------------------------------------\n");
    printf("�û�ָ��������ĸ�ԣ�\n");
    scanf("%d",&f);
    printf("�û�����ָ����Ӧ��ĸ(C M)��\n");
    getchar();
    for(i=0;i<f;i++)
    {
        scanf("%c %c",&cip,&mes);
        userpoint[i].pointcip=cip;
        userpoint[i].pointmes=mes;
        getchar();
    }
    return f;
}

void pointaction (Point userpoint[],char ciphertext[],int f,int len)  //���û�ָ�����������ĶԻ����������Ĵ�
{
    int i,j;
    for(i=0;i<len;i++)
    {
        for(j=0;j<f;j++)
        {
            if(ciphertext[i]==userpoint[j].pointcip){
                messtext[i]=userpoint[j].pointmes;
                break;
            }
        }
    }
    printf("\n----------------------\n");
    printf("ԭ����Ϊ��\n");
    printf("%s",ciphertext);
    printf("\n----------------------\n");
    printf("�����û�ָ���󣬴�ʱ����Ϊ��\n");
    printf("%s",messtext);
}

void suggestion1(char messtext[],int len)
{
    int i;
    printf("\n�������£�\n");
    for(i=1;i<len-1;i++)
    {
        if(messtext[i-1]==' '&&messtext[i+1]==' ')
            printf("��%c(%dλ)����a��i\n",messtext[i],i+1);
    }
}

void suggestion2(char messtext[],int len)
{
    int i,k;
    printf("����ĸ�����У�\n");
    for(i=0;i<len-3;i++){
        if(messtext[i]==' '&&(messtext[i+3]==' '||messtext[i+3]==','||messtext[i+3]=='.'||messtext[i+3]==';')){
            printf("  %c%c  ",messtext[i+1],messtext[i+2]);
            //for(k=0;k<8;k++)
            //{
                //printf("%s  ",dir[k].grammar);
            //}
            //printf("\n");
        }
    }
    printf("\n����Ϊ��");
    for(k=0;k<8;k++)
            {
                printf("%s  ",dir[k].grammar);
            }
            printf("\n");
}

void suggestion3(char messtext[],int len)
{
    int i,j,k;
    printf("\n�������£�\n");
    for(i=8;i<27;i++)
        for(j=0;j<len-2;j++)
        {
            if(((messtext[j]==dir[i].grammar[0]&&messtext[j+1]==dir[i].grammar[1])||(messtext[j]==dir[i].grammar[0]&&messtext[j+2]==dir[i].grammar[2])||(messtext[j+1]==dir[i].grammar[1]&&messtext[j+2]==dir[i].grammar[2]))&&
               (messtext[j]>='a'&&messtext[j]<='z')&&(messtext[j+1]>='a'&&messtext[j+1]<='z')&&(messtext[j+2]>='a'&&messtext[j+2]<='z'))
            {
                printf("%c%c%c����Ϊ��",messtext[j],messtext[j+1],messtext[j+2]);
                for(k=0;k<3;k++)
                    printf("%c",dir[i].grammar[k]);
                printf("      ");
            }
        }
}

int main() {
    int flag;
while(1)
{
    printf("��������������߹��ܣ�\n**1��������Կ����**\n**2��������Կ����**\n**3��������������**\n**0���˳�����**\n");
    printf("ѡ���ܣ�");
    scanf("%d",&flag);
if(flag==0)
    break;
else if(flag==1)
{
    Straightenc();
}
else if(flag==2)
{
    Straightdec();
}
else if(flag==3)
{
    getchar();
    printf("��ʼ��������Ĵ�Ϊ��\n");
    fgets(ciphertext,sizeof(ciphertext),stdin);
    //scanf("%s",ciphertext);
    int i,j,k,f,flag,length;
    length=strlen(ciphertext);
    //printf("%d\n",length);
    for(i=0;i<length;i++)
    {
        messtext[i]=ciphertext[i];
    }
    for(i=0;i<length;i++)    //forѭ��ͳ�������ַ���������ĸ����
    {
        switch(ciphertext[i])
        {
            case 'a':
                Cipstatic[0].num_cip++;
                //printf("%d",Cipstatic[0].num_cip);
                break;
            case 'b':
                Cipstatic[1].num_cip++;
                break;
            case 'c':
                Cipstatic[2].num_cip++;
                break;
            case 'd':
                Cipstatic[3].num_cip++;
                break;
            case 'e':
                Cipstatic[4].num_cip++;
                break;
            case 'f':
                Cipstatic[5].num_cip++;
                break;
            case 'g':
                Cipstatic[6].num_cip++;
                break;
            case 'h':
                Cipstatic[7].num_cip++;
                break;
            case 'i':
                Cipstatic[8].num_cip++;
                break;
            case 'j':
                Cipstatic[9].num_cip++;
                break;
            case 'k':
                Cipstatic[10].num_cip++;
                break;
            case 'l':
                Cipstatic[11].num_cip++;
                break;
            case 'm':
                Cipstatic[12].num_cip++;
                break;
            case 'n':
                Cipstatic[13].num_cip++;
                break;
            case 'o':
                Cipstatic[14].num_cip++;
                break;
            case 'p':
                Cipstatic[15].num_cip++;
                break;
            case 'q':
                Cipstatic[16].num_cip++;
                break;
            case 'r':
                Cipstatic[17].num_cip++;
                break;
            case 's':
                Cipstatic[18].num_cip++;
                break;
            case 't':
                Cipstatic[19].num_cip++;
                break;
            case 'u':
                Cipstatic[20].num_cip++;
                break;
            case 'v':
                Cipstatic[21].num_cip++;
                break;
            case 'w':
                Cipstatic[22].num_cip++;
                break;
            case 'x':
                Cipstatic[23].num_cip++;
                break;
            case 'y':
                Cipstatic[24].num_cip++;
                break;
            case 'z':
                Cipstatic[25].num_cip++;
                break;

        }
    }
    for(i=0;i<26;i++)
    {
        if(Cipstatic[i].num_cip==0)
            {Subarray[i].cip_word=Cipstatic[i].word_cip;continue;}
        Subarray[i].cip_word=Cipstatic[i].word_cip;
        Subarray[i].cip_num=Cipstatic[i].num_cip;
    }//ͳ��
    for(i=0;i<25;i++)
    {
        for(j=i+1,k=i;j<26;j++)
            if(Subarray[k].cip_num<=Subarray[j].cip_num){k=j;}
        Temp[0].cip_word=Subarray[i].cip_word;Subarray[i].cip_word=Subarray[k].cip_word;Subarray[k].cip_word=Temp[0].cip_word;
        Temp[0].cip_num=Subarray[i].cip_num;Subarray[i].cip_num=Subarray[k].cip_num;Subarray[k].cip_num=Temp[0].cip_num;
    }//����
    i=0;
    firstchange(Subarray);  //��һ�γ��Դ�����ĸ
    changeciphertxt(ciphertext,Subarray,length);  //��һ�γ��Է�������
    printf("�״δ�����ĸΪ��\n");
    while(i<26)
    {
        printf("%c",Subarray[i].cip_word);
        printf("   %c",Subarray[i].cip_change);
        printf("   %d\n",Subarray[i].cip_num);
        i++;
    }
    printf("�״γ��Ե�����Ϊ��\n");
    for(i=0;i<length;i++)
        printf("%c",messtext[i]);
    suggestion1(messtext,length);
    suggestion2(messtext,length);
    while(1){
    f=pointchange(userpoint);  //�û�ָ�������滻
    pointaction(userpoint,ciphertext,f,length);
    //suggestion2(messtext,length);
    printf("\n�Ƿ���ɽ���(1/0)��\n");
    scanf("%d",&flag);
    if(flag==1){
        printf("\n���յó�����Ϊ��\n");
        printf("%s",messtext);
        printf("\n*************************\n\n");
        break;
    }
    suggestion3(messtext,length);
    }
}
else
{
    printf("�������\n");
    break;
}
}
    return 0;

    // ��ʼ��Ϊ���ģ����ڸ�����ʾ��

    // ��ӡ����Ӣ��Ƶ�ʵĳ�����Կ�����

    // �����û�����������ָ���˼�����ĸ����ȷ��Կ��

    // �����û�ָ������Կ���Խ��ܲ���ӡ�����
}
