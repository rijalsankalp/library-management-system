
#include <windows.h>
#include<stdio.h>            //contains printf,scanf etc
#include<conio.h>            //contains delay(),getch(),gotoxy(),etc
#include <stdlib.h>
#include<string.h>          //contains strcmp(),strcpy(),Strlen(),etc
#include<ctype.h>           //contains toupper(),tolower(),etc
#include<dos.h>             //contains dos getdate
#include<time.h>
#define RETURNTIME 1 	// contains return date, etc
//list of function prototype
void returnfunc(void);		//it simply display an option to return to the main menu
void mainmenu(void);		//declaration for the menu function
void addbooks(void);		//declaration for the adding books function
void editbooks(void);		//declaration for the edit function
void searchbooks(void);		//declaration for search function
void issuebooks(void);		//declaration for issuing function
void bookslist(void);		//declaration for viewing book list function
void exitapplication(void);		//declaration for exiting function
int  getdata();
int  checkid(int);
int t(void);
void issuerecord();       //declaration for issuing record
FILE *fp,*ft,*fs;	     //file pointer declarations
int s;
char findbook;

struct Date
{
    char user[10];
    int mm,dd,yy;
};
struct books
{
    char status[10];
    int id;
    struct stdinf{
        char stname[20];
        char rollno[15];
        int booktaken;
    }s;
    char name[20];
    char Writer[20];
    int quantity;
    float Amount;
    char rackno[4];
    char cat[15];

    struct Date issued;
    struct Date duedate;
};
struct books r;
int main()	//the main or entry function to the program
{
	printf("\t\t\t\tBy : THA075BCT039\n\t\t\t\t\tTHA075BCT042\n\t\t\t\t\tTHA075BCT037");
	printf("\n\n\n\n\t\t\tWELCOME TO LIBRARY MANAGEMENT SYSTEM");
	printf("\n\n\n\t\t\tPress any key to proceed:");
	getch();		//holds the screen unless a key is pressed
	mainmenu();
	return 0;
}
void mainmenu()        //function that displays the main menu i.e. the options to use
{

    system("cls");
	int i; //local variable for switch options
	printf(" \t\t\t\t\tMAIN MENU\n ");
	printf("\n\n1. Add Books   ");
	printf("\n\n2. Search Books");
	printf("\n\n3. Issue Books");
	printf("\n\n4. Book list");
	printf("\n\n5. Edit Book's Record");
	printf("\n\n6. Exit Application\n\n\t\t");
	t();
	printf("\n\nEnter your choice:");
	switch(getch())
	{
    case '1':
		addbooks();
		break;
    case '2':
		searchbooks();
	    break;
	case '3':
		issuebooks();
	    break;
    case '4':
		bookslist();
		break;
    case '5':
		editbooks();
		break;
    case '6':
	    {
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tExiting......");
		exit(0);
	    }
	    default:
		{
		printf("\n\n\nWrong Entry!!");
		if(getch())
		mainmenu();
		}

    }
}
void addbooks(void)    //function to add books
{
	system("cls");
	fp=fopen("booklist.dat","ab+");
	if(getdata()==1)
	{
	fseek(fp,0,SEEK_END);			//fseek sets the file position of the given offset
	fwrite(&r,sizeof(r),1,fp);		//size_r this is the unsigned integral type and is the result of the sizeof keyword.
	fclose(fp);
	printf("\n\t\t\t\t\tThe record is successfully saved");
	printf("\n\n\t\t\t\t\tSave any more?(Y / N):");
	if(getch()=='n'||getch()=='N')
	    mainmenu();
	else
	    system("cls");
	    addbooks();
	}
}
void searchbooks()	    //function that search items burned or stored inn the file fp.
{
    system("cls");
    int d;
    printf("\t\t\t\t\t\tSearch Books ");
    printf("\n\n\t\t\t 1. Search By ID");
    printf("\n\n\t\t\t 2. Search By Name");
    printf("\n\n\t\t\t\tEnter Your Choice");
    fp=fopen("booklist.dat","rb+"); 		    //open file in read mode
    rewind(fp);   		                    //sets the file position to the beginning of the file of the given stream
    switch(getch())
    {
	  case '1':
	{
	    system("cls");
	    printf("\n\t\t\t\t\t\tSearch Books By Id ");
	    printf("\n\n\t\tEnter the book id:");
	    scanf("%d",&d);
	    printf("\n\n\n");
	    while(fread(&r,sizeof(r),1,fp)==1)
	    {
		if(r.id==d)
		{
		    printf("\t\t\t\tThe Book is available");
		    printf(" \n\n\tID:%d",r.id);
		    printf(" \n\tCategory:%s",r.cat);
		    printf(" \n\tName:%s",r.name);
		    printf(" \n\tWriter:%s ",r.Writer);
		    printf(" \n\tAmount:Rs.%.2f",r.Amount);
		    printf(" \n\tRack No:%d ",r.rackno);

		    findbook='t';
		}

	    }
	    if(findbook!='t')  		//it checks weather the condition is entered loop or not
	    {
	        printf("\rNo Record Found");
	    }
	    printf("Try another search?(Y/N)");
	    if(getch()=='y'||getch()=='Y')
	    searchbooks();
	    else
	    mainmenu();
	    break;
	}
	case '2':
	{
	    char s[15];
	    system("cls");
	    printf("\n\t\t\t\t\t\tSearch Books By Name ");
	    printf("\n\tEnter Book Name:");
	    scanf("%s",s);
	    int d=0;
	    while(fread(&r,sizeof(r),1,fp)==1)
	    {
		if(strcmp(r.name,(s))==0) 		//it checks weather r.name is equal to s or not
		{
		    printf("\n\n\tThe Book is available");
		    printf(" \n\n\tID:%d",r.id);
		    printf(" Category:%d",r.cat);
		    printf(" \n\tName:%s",r.name);
		    printf(" \n\tWriter:%s",r.Writer);
		    printf(" \n\tAmount:Rs.%.2f",r.Amount);
		    printf(" \n\tRack No:%d ",r.rackno);
		    d++;
		}

	    }
	    if(d==0)
	    {
		printf("\n\n\t\t\t\rNo Record Found");
	    }
	    printf("\n\t\t\t\tTry another search?(Y/N)");
	    if(getch()=='y')
	    searchbooks();
	    else
	    mainmenu();
	    break;
	}
	default :
	getch();
	searchbooks();
    }
    fclose(fp);
}
void issuebooks(void)  	//function for the issuing or issued books
{
    int t;		//local variable for switch option to get a cide value
    system("cls");
    printf("   \t\t\t\t\tISSUE SECTION ");
    printf(" \n\n\t1. Issue a Book");
    printf(" \n\t2. View Issued Book");
    printf(" \n\t3. Search Issued Book");
    printf(" \n\t4. Remove Issued Book");
    printf("\n\n\t\t\tEnter a Choice:");
    switch(getch())
    {
	case '1':  //issue book
	{
		system("cls");
		int c=0;
		char another='y';
		while(another=='y')		//infinite loop
		{
			system("cls");
			printf(" \t\t\t\t\tBook Issuing section ");
			printf("\n\n\tEnter the Book Id:");
			scanf("%d",&t);
			fp=fopen("booklist.dat","rb");
			fs=fopen("Issue.dat","a+b");
			if(checkid(t)==0) 		//check weather the book is available in library or not
			{
			    if(r.status=="Available")
                {
			           printf("\n\n\t\t\tThe book record is available");
			           printf("\n\n\t\t\tBook Name:\t%s",r.name);
			           printf("\n\t\tWriter:\t%s",r.Writer);
			           printf("\n\n\t\t\tFill up the following informations:\n ");
			           printf("\n\n\tEnter student name:");
			           scanf("%s",r.s.stname);
			           printf("\n\tEnter roll no:");
			           scanf("%s",r.s.rollno);
			     //if(r.s.booktaken<=6)
			     //{
			         printf("\n\n\tThe BOOK of ID %d is issued",r.id);
			         printf("\n\n\t\tIssued date:\t%d-%d-%d",r.issued.dd,r.issued.mm,r.issued.yy);	//for current date
                     r.duedate.dd=r.issued.dd+RETURNTIME;   		//for return date
                     r.duedate.mm=r.issued.mm;
                     r.duedate.yy=r.issued.yy;
                     if(r.duedate.dd>30)
                     {
                    r.duedate.mm+=r.duedate.dd/30;
                    r.duedate.dd-=30;

                    }
                    if(r.duedate.mm>12)
			        {
                    r.duedate.yy+=r.duedate.mm/12;
				    r.duedate.mm-=12;

			        }
			        printf("\n\n\t\tReturning Deadline:\t%d-%d-%d",r.duedate.dd,r.duedate.mm,r.duedate.yy);
			        strcpy(r.status,"Issued");
			    // }
			    /* else
                 {
                     printf("\n\n\t\tYou cannot issue more than 6 books.");
                 }*/
			     }
                 else
                 {
                     printf("\n\n\t\tThis book is not available now for issue.");
                     printf("\n\nStatus:%s",r.status);
                 }
			        fseek(fs,sizeof(r),SEEK_END);		//end of the file
			        fwrite(&r,sizeof(r),1,fs);
			        fclose(fs);
			        c=1;
			}
			if(c==0)
			{
			printf("\n\n\tNo record found");
			}
			printf("\n\n\tIssue any more(Y/N):");
			fflush(stdin);
			another=getche();
			fclose(fp);
		}
	}

		break;
	case '2':  	//case shows the issue books list
	{
		system("cls");
		printf("\t\t                          Issued book list                               ");
		printf("\n\n%-25s%-15s%-15s%-20s%-20s5-20s\n\n","STUDENT NAME","CATEGORY","ID","BOOK NAME","ISSUED DATE","RETURN DATE");
	       fs=fopen("Issue.dat","rb");
		while(fread(&r,sizeof(r),1,fs)==1)
		{
			printf("%-25s",r.s.stname);
			printf("%-15s",r.cat);
			printf("%-15d",r.id);
			printf("%-20s",r.name);
			printf("%-20d-%d-%d",r.issued.dd,r.issued.mm,r.issued.yy );
			printf("%-20d-%d-%d",r.duedate.dd,r.duedate.mm,r.duedate.yy);
			printf("\n\n");
		}
		fclose(fs);
		printf("\n\n\t\t\t");
		returnfunc();
	}
	break;
	case '3':   //search issued books by id
	{
		system("cls");
		printf("\n\n\t\t\tEnter Book ID:");
		int p,c=0;
		char another='y';
		while(another=='y')
		{

			scanf("%d",&p);
			fs=fopen("Issue.dat","rb");
			while(fread(&r,sizeof(r),1,fs)==1)
			{
				if(r.id==p)
				{
					issuerecord();
					printf("\n\n\n\t\t\tPress any key.......");
					getch();
					issuerecord();
					c=1;
				}

			}
			fflush(stdin);
			fclose(fs);
			if(c==0)
			{
				printf("\n\n\t\t\tNo Record Found");
			}
			printf("\n\n\t\t\tTry Another Search?(Y/N)");
			another=getch();
		}
	}
	break;
	case '4':  	//case return issued books from list
	{
		system("cls");
		int b;
		float fine;
		FILE *fg;  	//delete for temporary file is declared
		char another='y';
		while(another=='y'||another=='Y')
		{
			printf("\n\n\t\t\tEnter book id to remove:");
			scanf("%d",&b);
			fs=fopen("Issue.dat","r+b");
			while(fread(&r,sizeof(r),1,fs)==1)
			{
				if(r.id==b)
				{
					issuerecord();
					findbook='t';
				}
				if(findbook=='t')
				{
					printf("\n\n\tDo You Want to Remove it?(Y/N)");
					if(getch()=='y')
					{
						fg=fopen("record.dat","w+b");
						rewind(fs);
						r.s.booktaken--;
						while(fread(&r,sizeof(r),1,fs)==1)
						{
							if(r.id!=b)
							{
							fseek(fs,0,SEEK_CUR);
							fwrite(&r,sizeof(r),1,fg);
							}
						}
						fclose(fs);
						fclose(fg);
						remove("Issue.dat");
						rename("record.dat","Issue.dat");
						printf("\n\n\tThe issued book is removed from list");

				       }

				}
				if(findbook!='t')
				{
					printf("\n\n\t\t\tNo Record Found");
				}
			}
			printf("\n\n\t\t\tDelete any more?(Y/N)");
			another=getch();
		}
	}
	default:
	printf("\n\n\nWrong Entry!!");
    getch();
	issuebooks();
	break;
      }
      printf("\n\n\n");
      returnfunc();
}
void bookslist(void)  	//function for showing the list of books available in library
{
    int i=0;
    system("cls");
    printf("                              Book List                                   \n");
    printf("\n\n%-15s%-15s%-20s%-15s%-15s%-15s%-15s","CATEGORY","ID","BOOK NAME","STATUS","WRITER","AMOUNT","RACK NO");
    printf("\n\n");
    fp=fopen("booklist.dat","rb");
    while(fread(&r,sizeof(r),1,fp)==1)
    {
	printf("%-15s",r.cat);
	printf("%-15d",r.id);
	printf("%-20s",r.name);
	printf("%-15s",r.status);
	printf("%-15s",r.Writer);
	printf("%-15.2f",r.Amount);
	printf("%-15s",r.rackno);
	printf("\n\n");
	i=i+r.quantity;
      }
      printf("\n\n\t\t\tTotal Books =%d\n\n",i);
      fclose(fp);
      returnfunc();
}
void editbooks(void)  //function edit information about book
{
	system("cls");
	int c=0;
	int d,e;
	printf("\t\t\t\t\t\tEdit Books Section");
	char another='y';
	while(another=='y')
	{
		system("cls");
		printf("\n\n\t\tEnter Book Id to be edited:");
		scanf("%d",&d);
		fp=fopen("booklist.dat","rb+");
		while(fread(&r,sizeof(r),1,fp)==1)
		{
			if(checkid(d)==0)
			{
				printf("\n\n\tThe book is available");
				printf("\n\n\tBook ID:\t%d",r.id);
				printf("\n\tCategory:\t%s",r.cat);
	            printf("\n\tBook Name:\t%s",r.name);
	            printf("\n\tBook's Status:\t%s",r.status);
	            printf("\n\tWriter:\t%s",r.Writer);
	            printf("\n\tAmount:\t%.2f",r.Amount);
                printf("\n\tRack No:\t%d",r.rackno);
                printf("\n\n\t\t\tEnter the following cases");
				printf("\n\tEnter new name:\t");scanf("%s",r.name);
				printf("\n\tWhat is the status of the book?\n\t    1.Available\n\t    2.Issued\n\t    3.Lost\t");
				if(getch()=='1')
                {
                    strcpy(r.status,"Available");
                }
                else if(getch()=='2')
                {
                     strcpy(r.status,"Issued");
                }
                else if(getch()=='3')
                {
                     strcpy(r.status,"Lost");
                }
                else
                    {
                        printf("\n\n\t\t\tInvalid entry!!");
                        returnfunc();
                    }
                printf("\n\tEnter the new category:\t"); scanf("%s",r.cat);
				printf("\n\tEnter new Writer:\t");scanf("%s",r.Writer);
				printf("\n\tEnter new amount:\t");scanf("%f",&r.Amount);
				printf("\n\tEnter new rack no:\t");scanf("%d",&r.rackno);
				printf("\n\n\t\t\tThe record is edited");
				fseek(fp,ftell(fp)-sizeof(r),0);	//ftell returns the current file position of the given stream.
				fwrite(&r,sizeof(r),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				printf("\n\n\t\t\tNo record found");
			}
		}
		printf("\n\n\t\tEdit another Record?(Y/N)");
		fflush(stdin);
		another=getch() ;
	}
		returnfunc();
}
void returnfunc(void)  //for giving option to return to the main menu after completion of every task
{
    {
	printf("\n\n\n\t\t\t Press ENTER to return to main menu");
    }
    if(getch()==13) 	//allow only the use of enter
    mainmenu();
    else
    returnfunc();
}
int getdata()          //for input of data in the structure while adding books
{
	int t;
	system("cls");
	printf("\nBook ID:\t");
	scanf("%d",&t);
	if(checkid(t) == 0)
	{
		printf("\n!!!The book id is already occupied.\n");
		printf("\n\nDo you want to enter again?(y/n)");
		if(getch()=='y')
        {
            getdata();
        }
        else
        {
            mainmenu();
            return 0;
        }
	}
	r.id=t;
	strcpy(r.status,"Available");
	r.quantity=1;
    printf("\n\n\t\t\tEnter the Information Below\n");
    printf("\n\t\tCategory:\t");
	scanf("%s",r.cat);
	printf("\n\n\t\tBook Name:\t");
	scanf("%s[^\n]",r.name);
	printf("\n\t\tWriter:\t");
	scanf("%s[^\n]",r.Writer);
	printf("\n\t\tAmount:\t");
	scanf("%f",&r.Amount);
	printf("\n\t\tRack No:\t");
	scanf("%s",r.rackno);
	return 1;
}
int checkid(int t)  	//checks weather the book exist in library or not
{
	rewind(fp);
	while(fread(&r,sizeof(r),1,fp)==1)
	if(r.id==t)
	return 0;  		//return 0 if book exist
      return 1; 	//return 1 if book not exist
}
int t(void) 	//for adding time but don't know exactly how does this work
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}
void issuerecord()  	//function that display the issued book's information
{
		 system("cls");
		 printf("\n\n\tThe Book has taken by %s",r.s.stname);
		 printf("\n\tRoll No:",r.s.rollno);
		 printf("\n\n\n\n\tIssued Date:%d-%d-%d",r.issued.dd,r.issued.mm,r.issued.yy);
		 printf("\n\n\tReturning Deadline:%d-%d-%d",r.duedate.dd,r.duedate.mm,r.duedate.yy);
}
// End of program


