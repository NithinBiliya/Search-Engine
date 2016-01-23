/*      Search engine
        By: Nithin Kumar B
        Date: 23/10/10
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;

int search(char[50],int);
int search_one_file(char[22],char[50]);
void substr_search(char[20][50],int,int,int[187]);

int count=0;

int main()
{
    char key_str[50],t[50];
    char sub_str[20][50];
    int flag=0,fond[187];
    cout<<"\n\n\t\tSEARCH ENGINE\n\n\tPlease enter the string to be searched: "<<endl;
    gets(key_str);
    cout<<"The search results are as follows: "<<endl<<endl;
    flag=search(key_str,flag);
    strcpy(t,key_str);
    strlwr(t);
    flag=search(t,flag);
    char t2[50];
    int c=0;
    int l=strlen(key_str);
    key_str[l]=' ';
    key_str[l+1]='\0';
    for(int i=0,j=0;key_str[i]!='\0';i++,j++)
    {
        t2[j]=key_str[i];
        if(key_str[i]==' ')
        {
            t2[j]='\0';
            strcpy(sub_str[c],t2);
            c++;
            j=-1;
        }
    }
    for(int i=0;i<187;i++)
        fond[i]=0;
    substr_search(sub_str,flag,c,fond);
    for(;c;c--)
        for(int i=0;i<187;i++)
            if(fond[i]==c)
            {
                cout<<"link"<<i+1<<".html"<<endl;
                count++;
                if(count==15)
                    break;
            }
     c=0;
     l=strlen(t);
    t[l]=' ';
    t[l+1]='\0';
    for(int i=0,j=0;t[i]!='\0';i++,j++)
    {
        t2[j]=t[i];
        if(t[i]==' ')
        {
            t2[j]='\0';
            strcpy(sub_str[c],t2);
            c++;
            j=-1;
        }
    }
    for(int i=0;i<187;i++)
        fond[i]=0;
    substr_search(sub_str,flag,c,fond);
    for(;c;c--)
        for(int i=0;i<187;i++)
            if(fond[i]==c)
            {
                cout<<"link"<<i+1<<".html"<<endl;
                count++;
                if(count==15)
                    break;
            }

    if(!count)
        cout<<key_str<<" is not found!";
    return 0;
}

int search(char key_str[50],int flag)
{
    char filename[22],temp[5];
    for(int i=1,found;i<=187&&count<15;i++)
    {
        strcpy(filename,"html\\link");
        itoa(i,temp,10);
        strcat(filename,temp);
        strcat(filename,".html");
        found=search_one_file(filename,key_str);
        if(found==1)
        {
            flag=1;
            count++;
            strcpy(filename,"link");
            itoa(i,temp,10);
            strcat(filename,temp);
            strcat(filename,".html");
            cout<<filename<<endl;
        }
    }
    return flag;
}

int search_one_file(char filename[22],char key_str[50])
{
        char s;
        fstream file;
        file.open(filename,ios::in);
        if(!file)
        {
            cout<<"File could not be opened";
            exit(0);
        }
        int found;
        for(file.read((char*)&s,sizeof(s));!file.eof();file.read((char*)&s,sizeof(s)))
        {
            if(s==key_str[0])
            {
                long double pos=file.tellg();
                int len=strlen(key_str),j;
                for(j=0,found=0;j<len||!file.eof();j++)
                {
                    if(s!=key_str[j])
                        break;
                    file.read((char*)&s,sizeof(s));
                }
                if(j==len)
                {
                    found=1;
                    break;
                }
                file.seekg(pos);
            }
        }
        file.close();
        return found;
}

void substr_search(char sub_str[20][50],int flag,int c,int fond[187])
{
    char filename[22],temp[5];
    for(int i=1,found;i<=187&&count<15;i++)
    {
        strcpy(filename,"html\\link");
        itoa(i,temp,10);
        strcat(filename,temp);
        strcat(filename,".html");
        for(int j=c-1;j>=0;j--)
        {
            found=search_one_file(filename,sub_str[j]);
            if(found)
                fond[i-1]++;
        }
    }
}
