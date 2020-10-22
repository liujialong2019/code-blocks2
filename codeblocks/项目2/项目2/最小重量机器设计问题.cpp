#include<stdio.h>
#define MAXSIZE 150
int main()
{
    int n,m,d;
    int d_now=0;//当前总价值
    int w_now=0;//当前重量
    int w_min=100;//最小重量
    scanf("%d%d%d",&n,&m,&d);
    int w[MAXSIZE][MAXSIZE];
    int c[MAXSIZE][MAXSIZE];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&w[i][j]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&c[i][j]);
        }
    }
    int p[MAXSIZE];//存储各部件对应供应商编号
    int pmin[MAXSIZE];//存储最小重量对应供应商编号
    for(int i=1;i<=n;i++)
        p[i]=0;
    int t=1;//行
    int q=1;//列
    while(t>0)
    {
        //printf("t = %d , q = %d \n",t,q);

        if(d_now+c[t][q]>d)
        {
            if(q<m)                //下一个供应商
                q++;
            else                //上一个部件
            {
                t--;
                d_now-=c[t][p[t]];
                w_now-=w[t][p[t]];
                while(p[t]>=m)
                {
                    t--;
                    d_now-=c[t][p[t]];
                    w_now-=w[t][p[t]];
                    if(t<=0)
                        break;
                }
                q=p[t]+1;
            }
        }
        else
        {
            d_now+=c[t][q];
            w_now+=w[t][q];
            p[t]=q;
            if(t==n)//已到最后一个部件
            {
                if(w_now<w_min)
                {
                    for(int i=1;i<=n;i++)
                        pmin[i]=p[i];
                    w_min=w_now;
                }
                if(q<m)
                {
                    w_now-=w[t][q];
                    d_now-=c[t][q];
                    q++;
                }
                else
                {

                    d_now-=c[t][p[t]];
                    w_now-=w[t][p[t]];
                    t--;
                    //printf("t = %d , p[t] = %d\n",t,p[t]);
                    //printf("w_now = %d\t",w_now);
                    d_now-=c[t][p[t]];
                    w_now-=w[t][p[t]];
                    //printf("w_now = %d\n",w_now);
                    while(p[t]>=m)
                    {
                        t--;
                        d_now-=c[t][p[t]];
                        w_now-=w[t][p[t]];
                        if(t<=0)
                            break;
                    }
                    q=p[t]+1;
                }
            }
            else//未到最后一个部件
            {
                t++;
                q=1;
            }
        }

    }
    for(int i=1;i<n;i++)
    {
        printf("%d ",pmin[i]);
    }
    printf("%d\n",pmin[n]);
    printf("%d",w_min);
    return 0;
}
