#include <stdio.h>
#include <string.h>
#include <ctype.h>

char CIP[1000];
char MES[1000];
char KEY[26]={0};    //存放用于直接加密解密的明文密文和密钥

// 假设的英文字母频率，用于初步猜测
const double ENG_FREQ[] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074
};   //依次为ABCDEFGHIJKLMNOPQRSTUVWXYZ

char ENG_WORD[] = {
    'e','t','a','n','o','r','i','s','h','d','l','f','c','m','u','g','y','p','w','b','v','k','j','x','q','z'
};

// 假定的密文，实际应用中应从文件或用户输入读取
char ciphertext[1000];//创建密文字符串数组
char messtext[1000];//创建明文字符串数组

typedef struct{
    char word_cip;
    int num_cip;
}Stacip;    //创建统计密文字母及数量

Stacip Cipstatic[26]={{'a',0},{'b',0},{'c',0},{'d',0},{'e',0},{'f',0},{'g',0},{'h',0},{'i',0},{'j',0},{'k',0},{'l',0},{'m',0},{'n',0},{'o',0},{'p',0},
{'q',0},{'r',0},{'s',0},{'t',0},{'u',0},{'v',0},{'w',0},{'x',0},{'y',0},{'z',0}
};

typedef struct{
    char cip_word;  //密文字母
    char cip_change;    //密文代换字母
    int cip_num;      //密文字母数量
}Let_conver;    //创建初始密文对应的代换密码表

Let_conver Subarray[26];
Let_conver Temp[1];

typedef struct{
    char pointcip;   //密文字母
    char pointmes;   //明文字母
}Point;

Point userpoint[26];  //存放用户指定明文密文字母对

typedef struct{
    char grammar[3];
}dictionary;

dictionary dir[27]={
    {"as"},{"at"},{"an"},{"is"},{"it"},{"in"},{"he"},{"or"},
    {"the"},{"ing"},{"ere"},{"his"},{"her"},{"ion"},{"ent"},{"ous"},{"ive"},{"and"},{"our"},{"ard"},{"all"},{"ant"},{"him"},{"not"},{"end"},{"for"},{"was"}
};      //字典(可更新)

void Straightenc()
{
    int i,len,l;
    printf("输入明文：");
    scanf("%s",MES);
    printf("输入加密密钥（依次为a~z的对应字母，无对应字母则填0）:");
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
    printf("密文为：%s\n",CIP);
}

void Straightdec()
{
    int i,len,l;
    printf("输入密文：");
    scanf("%s",CIP);
    printf("输入解密密钥（依次为a~z的对应字母，无对应字母则填0）:");
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
    printf("明文为：%s\n",MES);
}

void firstchange(Let_conver a[])
{
    int i;
    for(i=0;i<26;i++)
    {
        a[i].cip_change=ENG_WORD[i];
    }

}

void changeciphertxt(char ciphertext[],Let_conver Subarray[],int length) //替换所有密文明文函数
{
    int i,j;
    for(i=0;i<length;i++)
        for(j=0;j<26;j++)
        {
            if(ciphertext[i]==Subarray[j].cip_word)
                {messtext[i]=Subarray[j].cip_change;break;}
        }
}

int pointchange(Point userpoint[])   //替换指定密文函数
{
    int i,f;
    char cip,mes;
    printf("\n--------------------------------------\n");
    printf("用户指定几个字母对？\n");
    scanf("%d",&f);
    printf("用户尝试指定对应字母(C M)：\n");
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

void pointaction (Point userpoint[],char ciphertext[],int f,int len)  //将用户指定的密文明文对换至反解明文串
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
    printf("原密文为：\n");
    printf("%s",ciphertext);
    printf("\n----------------------\n");
    printf("根据用户指定后，此时明文为：\n");
    printf("%s",messtext);
}

void suggestion1(char messtext[],int len)
{
    int i;
    printf("\n建议如下：\n");
    for(i=1;i<len-1;i++)
    {
        if(messtext[i-1]==' '&&messtext[i+1]==' ')
            printf("将%c(%d位)换成a或i\n",messtext[i],i+1);
    }
}

void suggestion2(char messtext[],int len)
{
    int i,k;
    printf("两字母单词有：\n");
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
    printf("\n可能为：");
    for(k=0;k<8;k++)
            {
                printf("%s  ",dir[k].grammar);
            }
            printf("\n");
}

void suggestion3(char messtext[],int len)
{
    int i,j,k;
    printf("\n建议如下：\n");
    for(i=8;i<27;i++)
        for(j=0;j<len-2;j++)
        {
            if(((messtext[j]==dir[i].grammar[0]&&messtext[j+1]==dir[i].grammar[1])||(messtext[j]==dir[i].grammar[0]&&messtext[j+2]==dir[i].grammar[2])||(messtext[j+1]==dir[i].grammar[1]&&messtext[j+2]==dir[i].grammar[2]))&&
               (messtext[j]>='a'&&messtext[j]<='z')&&(messtext[j+1]>='a'&&messtext[j+1]<='z')&&(messtext[j+2]>='a'&&messtext[j+2]<='z'))
            {
                printf("%c%c%c可能为：",messtext[j],messtext[j+1],messtext[j+2]);
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
    printf("单表代换辅助工具功能：\n**1）明文密钥加密**\n**2）密文密钥解密**\n**3）辅助破译密文**\n**0）退出程序**\n");
    printf("选择功能：");
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
    printf("初始读入的密文串为：\n");
    fgets(ciphertext,sizeof(ciphertext),stdin);
    //scanf("%s",ciphertext);
    int i,j,k,f,flag,length;
    length=strlen(ciphertext);
    //printf("%d\n",length);
    for(i=0;i<length;i++)
    {
        messtext[i]=ciphertext[i];
    }
    for(i=0;i<length;i++)    //for循环统计密文字符串各个字母数量
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
    }//统计
    for(i=0;i<25;i++)
    {
        for(j=i+1,k=i;j<26;j++)
            if(Subarray[k].cip_num<=Subarray[j].cip_num){k=j;}
        Temp[0].cip_word=Subarray[i].cip_word;Subarray[i].cip_word=Subarray[k].cip_word;Subarray[k].cip_word=Temp[0].cip_word;
        Temp[0].cip_num=Subarray[i].cip_num;Subarray[i].cip_num=Subarray[k].cip_num;Subarray[k].cip_num=Temp[0].cip_num;
    }//排序
    i=0;
    firstchange(Subarray);  //第一次尝试代换字母
    changeciphertxt(ciphertext,Subarray,length);  //第一次尝试反解密文
    printf("首次代换字母为：\n");
    while(i<26)
    {
        printf("%c",Subarray[i].cip_word);
        printf("   %c",Subarray[i].cip_change);
        printf("   %d\n",Subarray[i].cip_num);
        i++;
    }
    printf("首次尝试的明文为：\n");
    for(i=0;i<length;i++)
        printf("%c",messtext[i]);
    suggestion1(messtext,length);
    suggestion2(messtext,length);
    while(1){
    f=pointchange(userpoint);  //用户指定密文替换
    pointaction(userpoint,ciphertext,f,length);
    //suggestion2(messtext,length);
    printf("\n是否完成解密(1/0)？\n");
    scanf("%d",&flag);
    if(flag==1){
        printf("\n最终得出明文为：\n");
        printf("%s",messtext);
        printf("\n*************************\n\n");
        break;
    }
    suggestion3(messtext,length);
    }
}
else
{
    printf("输入错误！\n");
    break;
}
}
    return 0;

    // 初始化为密文，用于更新显示√

    // 打印基于英文频率的初步密钥建议√

    // 假设用户根据上下文指定了几个字母的正确密钥√

    // 根据用户指定的密钥尝试解密并打印结果√
}
