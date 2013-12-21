/*  Copyright 2012-2013 Qi Group
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>

int sgn(int a,int b)
{
	int c=(a>b)? (a-b):(b-a);
	return c;
}

int m,n,cities,player=0,population,buildings,money,turn=0,r,print;
char data[128][12],doing[100],map[250][750][3],playdata[10][500][7],count[128][10],killr[128][21][21],updata[128][128];

void main()
{
	void begin();
	void makedata();
	void printmap();
	void stop();
	void move(char *p);
	void kill(char *p);
	void make(char *p);
	void up(char *p);
	void open(char *p);
	void change(int);
	printf("map m*n m= n=");
	scanf("%d%d",&m,&n);
    printf("cities=");
	scanf("%d",&cities);
	printf("population=");
	scanf("%d",&population);
    printf("buildings=");
	scanf("%d",&buildings);
	printf("money=");
	scanf("%d",&money);
	printf("from 'C' to buildings=");
	scanf("%d",&r);
	if(m>250||m<0) m=250;
	if(n>250||n<0) n=250;
	if(cities>10||cities<0) cities=10;
	if(population>250||population<0) population=250;
	if(money>250||money<0) money=250;
	if((r>250)||(r<0)) r=0;
	begin();
	makedata();
	printmap();
	int b=0,i;
	for(;b==0;)
	{
		if(turn==1) change(player);
		turn=0;
		print=0;
		printf("player%ddo:\n",player);
		for(i=0;i<100;i++)
		doing[i]='\0';
		gets(doing);
		if((doing[0]=='m')&&(doing[1]=='o')&&(doing[2]=='v')&&(doing[3]=='e')) move(doing);
		else if((doing[0]=='m')&&(doing[1]=='a')&&(doing[2]=='k')&&(doing[3]=='e')) make(doing);
		else if((doing[0]=='k')&&(doing[1]=='i')&&(doing[2]=='l')&&(doing[3]=='l')) kill(doing);
		else if((doing[0]=='o')&&(doing[1]=='p')&&(doing[2]=='e')&&(doing[3]=='n')) open(doing);
		else if((doing[0]=='u')&&(doing[1]=='p')) up(doing);
		else if((doing[0]=='s')&&(doing[1]=='t')&&(doing[2]=='o')&&(doing[3]=='p')) stop();
		else if((doing[0]=='s')&&(doing[1]=='h')&&(doing[2]=='u')&&(doing[3]=='t')) 
		{
			b=1;
			print=1;
		}
		else 
		{
			printf("WRONG!000\n");
			print=1;
		}
		if(print==0) printmap();
	}
}

void begin()
{
	int i,j,k;
	for(i=0;i<cities;i++)
	{
		for(j=0;j<buildings+population;j++)
		{
			for(k=0;k<7;k++)
			playdata[i][j][k]=0;
		}
	}
	for(i=0;i<m;i++)
	{
		for(j=0;j<3*n;j++)
		{
			for(k=0;k<3;k++)
			map[i][j][k]=' ';
		}
	}
	for(i=2;i<128;i++)
	{
		for(j=0;j<cities;j++)
		count[i][j]=0;
	}
	for(k=0;k<cities;k++)
	{
		count[0][k]=money;
	    count[1][k]=1;
	}
}

void printmap()
{
	int i,j,k;
	printf("map|");
	for(i=0;i<n;i++)
	printf("%-3.2d|",i);
	printf("\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<3;k++)
		    {
			    if((j==0)&&(k==0)) printf("%3.2d|",i);
			    if(map[i][3*j+k][2]!=' ') printf("%c",map[i][3*j+k][2]);
			    else if(map[i][3*j+k][1]!=' ') printf("%c",map[i][3*j+k][1]);
			    else printf("%c",map[i][3*j+k][0]);
			    if(k==2) printf("|");
		    }
		    if(j==n-1) printf("\n");
		}
	}
	printf("\n\nplaydata:\nplayer\tname\tlife\tmove\tkill\taddress\n");
	for(i=0;i<cities;i++)
	{
		for(j=0;j<buildings+population;j++)
		{
			if(playdata[i][j][4]!=0)
			printf("%d\t%d%c%d\t%d\t%d\t%d\t%d,%d\n",i,i,playdata[i][j][4],playdata[i][j][5],playdata[i][j][0],playdata[i][j][1],playdata[i][j][6],playdata[i][j][2],playdata[i][j][3]);
		}
	}
	printf("\n\ndata:\nname\ttype\tlevel\tlife\tmove\tkillp\tkillt\tkillr\tm*n\tprice\tadd/\n");
	for(i=0;i<128;i++)
	{
		if(data[i][0]!=0)
		printf("%c\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d*%d\t%d\t%d\n",i,data[i][10],data[i][11],data[i][1],data[i][2],data[i][3]-48,data[i][7],data[i][6],data[i][4],data[i][5],data[i][8],data[i][9]);
	}
	printf("\n\nupdata:\n");
	for(i=0;i<128;i++)
	{
		for(j=0;j<128;j++)
		if(updata[i][j]!=-1) printf("%c to %c\t%d\n",i,j,updata[i][j]);
	}
	printf("\n\nmoney:\n");
	for(i=0;i<cities;i++)
	printf("%d\t%d\n",i,count[0][i]);
}

void change(int a)
{
	int b=a;
	do a=(a+1)%cities;
	while((count[1][a]==0)&&(a!=b));
	if(a==b) printf("WRONG!001\n");
	player=a;
}

void stop()
{
	turn=1;
	int a=count[0][player]+5*count['D'][player]-3*count['X'][player]+2*count['C'][player];
	if(a>250) count[0][player]=250;
	else if(a<0) count[0][player]=0;
	else count[0][player]=a;
	for(a=0;(a<population+buildings)&&(playdata[player][a][4]!=0);a++)
	{
		playdata[player][a][1]=data[playdata[player][a][4]][2];
		playdata[player][a][6]=data[playdata[player][a][4]][7];
	}
}

void make(char *st)
{
	char *p=st;
	int a,b,c,d,e=0,f=0,g=0,i=0,j=0,x=0,y=0,s;
	for(a=0;(*(p+a)!='(')&&(*(p+a)!='\0');a++);
	for(b=0;(*(p+b)!=',')&&(*(p+b)!='\0');b++);
    for(c=0;(*(p+c)!=')')&&(*(p+c)!='\0');c++);
    if((b-a>0)&&(c-b>0)&&(b-a<5)&&(c-b<5))
    {
		for(a++;a<b;a++)
		{
			if((*(p+a)>=48)&&(*(p+a)<=57)) x=10*x+*(p+a)-48;
			else e=1;
		}
        for(b++;b<c;b++)
		{
			if((*(p+b)>=48)&&(*(p+b)<=57)) y=10*y+*(p+b)-48;
			else e=1;
		}
	}
	else e=1;
	if((*(p+5)>='A')&&(*(p+5)<='Z')) s=1;
	else s=2;
	for(a='A';a<'Z';a++)
	i+=count[a][player];
	if((i>=buildings)&&(s==1)) f=1;
	for(a='a';a<'z';a++)
	j+=count[a][player];
	if((j>=population)&&(s==2)) f=1;
	for(a=0;a<data[*(p+5)][4];a++)
	{
		for(b=0;b<data[*(p+5)][5];b++)
		if((x+a>=m)||(y+b>=n)||(map[x+a][3*y+3*b][2]!=' ')||(((map[x+a][3*y+3*b][1]!=' ')&&(map[x+a][3*y+3*b][1]!=player+48))||((map[x+a][3*y+3*b][1]==player+48)&&((s==1)||((s==2)&&(map[x+a][3*y+3*b+1][1]!='X')))))) g=1;
	}
	if((((count['C'][player]==1)&&(*(p+5)!='C'))||((count['C'][player]==0)&&(*(p+5)=='C')))&&(data[*(p+5)][0]==1)&&(count[*(p+5)][player]<=9)&&((sgn(2*x+data[*(p+5)][4],playdata[player][0][2]*2+data['C'][4])+sgn(2*y+data[*(p+5)][5],playdata[player][0][3]*2+data['C'][5])<=2*r)||(*(p+5)=='C')||(s==2))&&(count[0][player]>=data[*(p+5)][8]+count[*(p+5)][player]*data[*(p+5)][9])&&(e==0)&&(f==0)&&(g==0))
	{
		for(a=0;playdata[player][a][4]!=0;a++);
		for(b=0,c=0;(b<10)&&(c==1);b++)
		{
			for(d=0;d<population+buildings;d++)
			{
				if((playdata[player][d][4]==*(p+5))&&(playdata[player][d][5]==b)) c=1;
			}
		}
		count[0][player]-=data[*(p+5)][8]+count[*(p+5)][player]*data[*(p+5)][9];
		playdata[player][a][0]=data[*(p+5)][1];
		playdata[player][a][2]=x;
		playdata[player][a][3]=y;
		playdata[player][a][4]=*(p+5);
		playdata[player][a][5]=b;
		count[*(p+5)][player]++;
		for(b=0;b<data[*(p+5)][4];b++)
		{
			for(c=0;c<data[*(p+5)][5];c++)
			{
				map[x+b][3*y+3*c][s]=player+48;
				map[x+b][3*y+3*c+1][s]=*(p+5);
				map[x+b][3*y+3*c+2][s]=playdata[player][a][5]+48;
			}
		}
	}
	else 
	{
		printf("WRONG!002 e=%d f=%d g=%d %c s=%d\n",e,f,g,*(p+5),s);
		print=1;
	}
}

void kill(char *st)
{
	char *p=st;
	int a,b,c,d,e,i,j,x,y,s;
	if((data[*(p+5)][0]==1)&&(*(p+6)-48<count[*(p+5)][player])&&(*(p+6)>=48))
	{
		for(a=0;(playdata[player][a][4]!=*(p+5))||(playdata[player][a][5]!=*(p+6)-48);a++);
		for(b=0;(b<100)&&(*(p+b)!='(');b++);
		c=0;
		d=0;
		for(b++;(b<100)&&(*(p+b)!=')');b++)
		{
			switch(*(p+b))
			{
				case 'r':d++;break;
				case 'l':d--;break;
				case 'd':c++;break;
				case 'u':c--;break;
			    default:printf("WRONG!003\n");
			}
		}
		x=playdata[player][a][2];
		y=playdata[player][a][3];
		if((((killr[*(p+5)][c+10][d+10]==1)&&(c<=10)&&(c>=-10)&&(d<=10)&&(d>=-10))||((sgn(2*c,data[*(p+5)][4]-1)+sgn(2*d,data[*(p+5)][5]-1)<=2*data[*(p+5)][6])&&(killr[*(p+5)][c+10][d+10]!=-1)))&&(playdata[player][a][6]>=1)&&((map[x+c][3*y+3*d][1]!=' ')||(map[x+c][3*y+3*d][2]!=' '))&&(x+c<m)&&(y+d<n))
		{
			x+=c;
			y+=d;
			if(map[x][3*y][1]!=' ') s=1;
			else s=2;
			c=map[x][3*y][s]-48;
			d=map[x][3*y+1][s];
			e=map[x][3*y+2][s]-48;
			for(b=0;(playdata[c][b][4]!=d)||(playdata[c][b][5]!=e);b++);
			playdata[player][a][6]--;
			if(playdata[c][b][0]-data[*(p+5)][3]+48<=0)
			{
				for(i=0;i<data[d][4];i++)
				{
					for(j=0;j<data[d][5];j++)
					{
						map[playdata[c][b][2]+i][3*playdata[c][b][3]+3*j][s]=' ';
						map[playdata[c][b][2]+i][3*playdata[c][b][3]+3*j+1][s]=' ';
						map[playdata[c][b][2]+i][3*playdata[c][b][3]+3*j+2][s]=' ';
					}
				}
				if(d=='C') count[1][c]=0;
				count[d][c]--;
				for(i=0;i<7;i++)
				playdata[c][b][i]=0;
			}
			else if(playdata[c][b][0]-data[*(p+5)][3]+48>data[d][1])
			playdata[c][b][0]=data[d][1];
			else playdata[c][b][0]-=data[*(p+5)][3]-48;
		}
		else 
		{
			printf("WRONG!004\n");
		    print=1;
		}
	}
	else 
	{
		printf("WRONG!005\n");
		print=1;
	}
}

void move(char *st)
{
	char *p=st;
	int a,b,c,d,e,i,j,x,y;
	if((data[*(p+5)][0]==1)&&(*(p+6)-48<count[*(p+5)][player])&&(*(p+6)>=48)&&(*(p+5)<='z')&&(*(p+5)>='a'))
	{
		for(a=0;(playdata[player][a][4]!=*(p+5))||(playdata[player][a][5]!=*(p+6)-48);a++);
		for(b=0;(b<100)&&(*(p+b)!='(');b++);
		for(b++;(b<100)&&(*(p+b)!=')');b++)
		{
			c=0;
			d=0;
			e=0;
			x=playdata[player][a][2];
			y=playdata[player][a][3];
			switch(*(p+b))
			{
				case 'r':d++;break;
				case 'l':d--;break;
				case 'd':c++;break;
				case 'u':c--;break;
			    default:printf("WRONG!006\n");
			}
			for(i=0;i<data[*(p+5)][4];i++)
			{
				for(j=0;j<data[*(p+5)][5];j++)
				if((((map[x+c+i][3*y+3*d+3*j][2]!=player+48)||(map[x+c+i][3*y+3*d+3*j+1][2]!=*(p+5))||(map[x+c+i][3*y+3*d+3*j+2][2]!=*(p+6)))&&(map[x+c+i][3*y+3*d+3*j][2]!=' '))||((map[x+c+i][3*y+3*d+3*j][1]!=' ')&&(map[x+c+i][3*y+3*d+3*j][1]!=player+48))) e=1;
			}
			if((playdata[player][a][1]>0)&&(e==0)&&(x+c+data[*(p+5)][4]-1<m)&&(y+d+data[*(p+5)][5]-1<n))
			{
				playdata[player][a][1]--;
				for(i=0;i<data[*(p+5)][4];i++)
				{
					for(j=0;j<data[*(p+5)][5];j++)
					{
						map[x+i][3*y+3*j][2]=' ';
						map[x+i][3*y+3*j+1][2]=' ';
						map[x+i][3*y+3*j+2][2]=' ';
					}
				}
				playdata[player][a][2]+=c;
				playdata[player][a][3]+=d;
				for(i=0;i<data[*(p+5)][4];i++)
				{
					for(j=0;j<data[*(p+5)][5];j++)
					{
						map[x+c+i][3*y+3*d+3*j][2]=player+48;
						map[x+c+i][3*y+3*d+3*j+1][2]=*(p+5);
						map[x+c+i][3*y+3*d+3*j+2][2]=*(p+6);
					}
				}
			}
		    else printf("WRONG!007 e=%d\n",e);
		}
	}
	else 
	{
		printf("WRONG!008\n");
		print=1;
	}
}

void up(char *st)
{
	char *p=st;
	int a,b,c,d=0,s,t;
	if((*(p+4)<count[*(p+3)][player]+48)&&(*(p+4)>=48)&&(data[*(p+6)][0]==1))
	{
		if((*(p+6)>='A')&&(*(p+6)<='Z')) s=1;
		else s=2;
		if((*(p+3)>='A')&&(*(p+3)<='Z')) t=1;
		else t=2;
		for(a=0;(playdata[player][a][4]!=*(p+3))||(playdata[player][a][5]!=*(p+4)-48);a++);
	    for(b=0;b<data[*(p+3)][4];b++)
	    {
			for(c=0;c<data[player][5];c++)
			if((map[playdata[player][a][2]+b][3*playdata[player][a][3]+3*c][s]!=' ')||(map[playdata[player][a][2]+b][3*playdata[player][a][3]+3*c+1][1]!=player+48)||(map[playdata[player][a][2]+b][3*playdata[player][a][3]+3*c+1][2]!=player+48)) d=1;
		}
	    if((updata[*(p+3)][*(p+6)]!=-1)&&(d==0)&&(count[0][player]-updata[*(p+3)][*(p+6)]>=0))
	    {
			for(b=0,c=0;(b<10)&&(c==1);b++)
		    {
			    for(d=0;d<population+buildings;d++)
				if((playdata[player][d][4]==*(p+6))&&(playdata[player][d][5]==b)) c=1;
		    }
			if(playdata[player][a][0]>data[*(p+6)][1]) playdata[player][a][0]=data[*(p+6)][1];
			if(playdata[player][a][1]>data[*(p+6)][2]) playdata[player][a][1]=data[*(p+6)][2];
			playdata[player][a][4]=*(p+6);
			playdata[player][a][5]=b;
			if(playdata[player][a][6]>data[*(p+6)][7]) playdata[player][a][6]=data[*(p+6)][7];
			count[*(p+3)][player]--;
			count[*(p+6)][player]++;
			count[0][player]-=updata[*(p+3)][*(p+6)];
			for(b=0;b<data[*(p+3)][4];b++)
			{
				for(c=0;c<data[*(p+3)][5];c++)
				{
					map[playdata[player][a][2]+b][3*playdata[player][a][3]+3*c][t]=' ';
					map[playdata[player][a][2]+b][3*playdata[player][a][3]+3*c+1][t]=' ';
					map[playdata[player][a][2]+b][3*playdata[player][a][3]+3*c+2][t]=' ';
				}
			}
			for(b=0;b<data[*(p+6)][4];b++)
			{
				for(c=0;c<data[*(p+6)][5];c++)
				{
					map[playdata[player][a][2]+b][3*playdata[player][a][3]+3*c][s]=player+48;
					map[playdata[player][a][2]+b][3*playdata[player][a][3]+3*c+1][s]=playdata[player][a][4];
					map[playdata[player][a][2]+b][3*playdata[player][a][3]+3*c+2][s]=playdata[player][a][5]+48;
				}
			}
		}
		else 
	    {
		    printf("WRONG!009\n");
		    print=1;
	    }
	}
	else 
	{
		printf("WRONG!010\n");
		print=1;
	}
}

void open(char *st)
{
	int i,j;
	char *p=st;
	print=1;
	if(data[*(p+5)][0]==1)
	{
	    for(i=0;i<21;i++)
	    {
		    for(j=0;j<21;j++)
		    {
			    if((i>=10)&&(i<10+data[*(p+5)][4])&&(j>=10)&&(j<10+data[*(p+5)][5])) printf("%c",*(p+5));
			    else if((killr[*(p+5)][i][j]==1)||((sgn(2*(i-10),data[*(p+5)][4]-1)+sgn(2*(j-10),data[*(p+5)][5]-1)<=2*data[*(p+5)][6])&&(killr[*(p+5)][i][j]!=-1))) printf("@");
			    else printf(" ");
		    }
		    printf("\n");
	    }
    }
    else
    {
		printf("WRONG!011\n");
		print=1;
	}
}

void makedata()
{
	int i,j,k;
	for(i=0;i<128;i++)
	data[i][0]=0;
	for(i=0;i<128;i++)
	{
		for(j=0;j<11;j++)
		{
			for(k=0;k<11;k++)
			killr[i][j][k]=0;
		}
	}
	for(i=0;i<128;i++)
	{
		for(j=0;j<128;j++)
		updata[i][j]=255;
	}
	
	data['a'][0]=1;
	data['a'][1]=3;
	data['a'][2]=5;
	data['a'][3]=50;
	data['a'][4]=1;
	data['a'][5]=1;
	data['a'][6]=1;
	data['a'][7]=1;
	data['a'][8]=2;
	data['a'][9]=0;
	killr['a'][9][9]=1;
	killr['a'][9][11]=1;
	killr['a'][11][9]=1;
	killr['a'][11][11]=1;
	data['b'][0]=1;
	data['b'][1]=3;
	data['b'][2]=7;
	data['b'][3]=50;
	data['b'][4]=1;
	data['b'][5]=1;
	data['b'][6]=1;
	data['b'][7]=1;
	data['b'][8]=4;
	data['b'][9]=0;
	killr['b'][9][9]=1;
	killr['b'][9][11]=1;
	killr['b'][11][9]=1;
	killr['b'][11][11]=1;
	data['c'][0]=1;
	data['c'][1]=5;
	data['c'][2]=5;
	data['c'][3]=51;
	data['c'][4]=1;
	data['c'][5]=1;
	data['c'][6]=1;
	data['c'][7]=1;
	data['c'][8]=8;
	data['c'][9]=0;
	killr['c'][9][9]=1;
	killr['c'][9][11]=1;
	killr['c'][11][9]=1;
	killr['c'][11][11]=1;
	data['d'][0]=1;
	data['d'][1]=3;
	data['d'][2]=5;
	data['d'][3]=47;
	data['d'][4]=1;
	data['d'][5]=1;
	data['d'][6]=1;
	data['d'][7]=1;
	data['d'][8]=4;
	data['d'][9]=0;
	killr['d'][9][9]=1;
	killr['d'][9][11]=1;
	killr['d'][11][9]=1;
	killr['d'][11][11]=1;
	data['h'][0]=1;
	data['h'][1]=2;
	data['h'][2]=5;
	data['h'][3]=50;
	data['h'][4]=1;
	data['h'][5]=1;
	data['h'][6]=3;
	data['h'][7]=1;
	data['h'][8]=2;
	data['h'][9]=0;
	data['i'][0]=1;
	data['i'][1]=3;
	data['i'][2]=5;
	data['i'][3]=51;
	data['i'][4]=1;
	data['i'][5]=1;
	data['i'][6]=3;
	data['i'][7]=1;
	data['i'][8]=6;
	data['i'][9]=0;
	killr['i'][10][6]=1;
	killr['i'][10][5]=1;
	killr['i'][10][15]=1;
	killr['i'][10][14]=1;
	killr['i'][6][10]=1;
	killr['i'][5][10]=1;
	killr['i'][15][10]=1;
	killr['i'][14][10]=1;
	data['j'][0]=1;
	data['j'][1]=2;
	data['j'][2]=5;
	data['j'][3]=50;
	data['j'][4]=1;
	data['j'][5]=1;
	data['j'][6]=3;
	data['j'][7]=2;
	data['j'][8]=8;
	data['j'][9]=0;
	data['o'][0]=1;
	data['o'][1]=4;
	data['o'][2]=10;
	data['o'][3]=49;
	data['o'][4]=1;
	data['o'][5]=1;
	data['o'][6]=1;
	data['o'][7]=1;
	data['o'][8]=3;
	data['o'][9]=0;
	data['p'][0]=1;
	data['p'][1]=4;
	data['p'][2]=12;
	data['p'][3]=50;
	data['p'][4]=1;
	data['p'][5]=1;
	data['p'][6]=1;
	data['p'][7]=1;
	data['p'][8]=8;
	data['p'][9]=0;
	killr['p'][9][9]=1;
	killr['p'][11][9]=1;
	killr['p'][9][11]=1;
	killr['p'][11][11]=1;
	data['q'][0]=1;
	data['q'][1]=3;
	data['q'][2]=12;
	data['q'][3]=49;
	data['q'][4]=1;
	data['q'][5]=1;
	data['q'][6]=1;
	data['q'][7]=1;
	data['q'][8]=5;
	data['q'][9]=0;
	killr['q'][9][9]=1;
	killr['q'][11][9]=1;
	killr['q'][9][11]=1;
	killr['q'][11][11]=1;
	data['r'][0]=1;
	data['r'][1]=5;
	data['r'][2]=8;
	data['r'][3]=50;
	data['r'][4]=1;
	data['r'][5]=1;
	data['r'][6]=1;
	data['r'][7]=1;
	data['r'][8]=7;
	data['r'][9]=0;
	data['s'][0]=1;
	data['s'][1]=4;
	data['s'][2]=10;
	data['s'][3]=47;
	data['s'][4]=1;
	data['s'][5]=1;
	data['s'][6]=1;
	data['s'][7]=1;
	data['s'][8]=6;
	data['s'][9]=0;
	killr['s'][9][9]=1;
	killr['s'][11][9]=1;
	killr['s'][9][11]=1;
	killr['s'][11][11]=1;
	data['u'][0]=1;
	data['u'][1]=3;
	data['u'][2]=3;
	data['u'][3]=51;
	data['u'][4]=1;
	data['u'][5]=1;
	data['u'][6]=2;
	data['u'][7]=1;
	data['u'][8]=12;
	data['u'][9]=0;
	data['v'][0]=1;
	data['v'][1]=3;
	data['v'][2]=4;
	data['v'][3]=51;
	data['v'][4]=1;
	data['v'][5]=1;
	data['v'][6]=3;
	data['v'][7]=1;
	data['v'][8]=15;
	data['v'][9]=0;
	killr['v'][10][6]=1;
	killr['v'][10][5]=1;
	killr['v'][10][15]=1;
	killr['v'][10][14]=1;
	killr['v'][6][10]=1;
	killr['v'][5][10]=1;
	killr['v'][15][10]=1;
	killr['v'][14][10]=1;
	data['w'][0]=1;
	data['w'][1]=3;
	data['w'][2]=3;
	data['w'][3]=52;
	data['w'][4]=1;
	data['w'][5]=1;
	data['w'][6]=3;
	data['w'][7]=1;
	data['w'][8]=13;
	data['w'][9]=0;
	data['x'][0]=1;
	data['x'][1]=3;
	data['x'][2]=3;
	data['x'][3]=46;
	data['x'][4]=1;
	data['x'][5]=1;
	data['x'][6]=2;
	data['x'][7]=1;
	data['x'][8]=10;
	data['x'][9]=0;
	data['C'][0]=1;
	data['C'][1]=50;
	data['C'][2]=0;
	data['C'][3]=50;
	data['C'][4]=3;
	data['C'][5]=3;
	data['C'][6]=3;
	data['C'][7]=2;
	data['C'][8]=0;
	data['C'][9]=0;
	killr['C'][11][8]=-1;
	killr['C'][14][11]=-1;
	killr['C'][11][14]=-1;
	killr['C'][8][11]=-1;
	killr['C'][9][9]=1;
	killr['C'][9][13]=1;
	killr['C'][13][9]=1;
	killr['C'][13][13]=1;
	data['D'][0]=1;
	data['D'][1]=20;
	data['D'][2]=0;
	data['D'][3]=48;
	data['D'][4]=3;
	data['D'][5]=3;
	data['D'][6]=0;
	data['D'][7]=0;
	data['D'][8]=15;
	data['D'][9]=10;
	data['X'][0]=1;
	data['X'][1]=30;
	data['X'][2]=0;
	data['X'][3]=50;
	data['X'][4]=3;
	data['X'][5]=3;
	data['X'][6]=4;
	data['X'][7]=1;
	data['X'][8]=15;
	data['X'][9]=0;
	data['E'][0]=1;
	data['E'][1]=30;
	data['E'][2]=0;
	data['E'][3]=49;
	data['E'][4]=3;
	data['E'][5]=3;
	data['E'][6]=4;
	data['E'][7]=1;
	data['E'][8]=20;
	data['E'][9]=0;
	data['F'][0]=1;
	data['F'][1]=30;
	data['F'][2]=0;
	data['F'][3]=50;
	data['F'][4]=3;
	data['F'][5]=3;
	data['F'][6]=6;
	data['F'][7]=1;
	data['F'][8]=30;
	data['F'][9]=0;
	data['L'][0]=1;
	data['L'][1]=30;
	data['L'][2]=0;
	data['L'][3]=48;
	data['L'][4]=2;
	data['L'][5]=2;
	data['L'][6]=0;
	data['L'][7]=0;
	data['L'][8]=10;
	data['L'][9]=0;
	data['M'][0]=1;
	data['M'][1]=40;
	data['M'][2]=0;
	data['M'][3]=48;
	data['M'][4]=2;
	data['M'][5]=2;
	data['M'][6]=0;
	data['M'][7]=0;
	data['M'][8]=12;
	data['M'][9]=0;
	
	for(i=0;i<128;i++)
	{
		for(j=0;j<128;j++)
		updata[i][j]=-1;
	}
	updata['a']['b']=3;
	updata['a']['c']=7;
	updata['a']['d']=3;
	updata['b']['c']=5;
	updata['b']['d']=2;
	updata['d']['b']=2;
	updata['h']['i']=5;
	updata['h']['j']=7;
	updata['o']['p']=6;
	updata['o']['q']=3;
	updata['o']['r']=5;
	updata['o']['s']=4;
	updata['q']['p']=4;
	updata['q']['r']=3;
	updata['q']['s']=2;
	updata['s']['q']=2;
	updata['a']['o']=2;
	updata['b']['q']=2;
	updata['c']['r']=2;
	updata['d']['s']=3;
	updata['u']['v']=4;
	updata['u']['w']=2;
	updata['E']['F']=12;
	updata['L']['M']=4;
	updata['D']['E']=10;
}
