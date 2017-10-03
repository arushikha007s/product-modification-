#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include<math.h>
COORD coord={0,0};
//x for x axis ,, y for y axis
void gotoxy(int x,int y){

            coord.X=x;
            coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);


}


int main()
{
      FILE *fp,*ft;

      char another,choice;

    struct ent{

            int productID;
            char productnam[20];
            int buyerID;
            char date[20];
            long int phoneno;

    };

    struct ent e;
//changed character size to 60

    char na[60];

    long int recsize;

fp = fopen("AC.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("AC.DAT","wb+");
        if(fp == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }


     recsize = sizeof(e);


    while(1)
    {
        system("cls");
        gotoxy(40,10);
        printf("******* AMAZON CART *******");
        gotoxy(30,12);
        printf("1. Add product");
        gotoxy(30,14);
        printf("2. list Records");
        gotoxy(30,16);
        printf("3. modify Records");
        gotoxy(30,18);
        printf("4. delete completed record");
        gotoxy(30,20);
         printf("5.exit");
        gotoxy(30,22);
        printf("Your Choice: ");
        fflush(stdin);
        choice  = getche();
//for the choices used
         switch(choice)
        {
        case '1':
            system("cls");
            fseek(fp,0,SEEK_END);

            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter product ID: ");
                scanf("%d",&e.productID);
                 printf("\n Enter product name: ");
                scanf("%s",e.productnam);
                printf("\nEnter Buyer ID : ");
                scanf("%d", &e.buyerID);
                printf("\nEnter date: ");
                scanf("%s",e.date);
                printf("\nEnter phone number: ");
                scanf("%d", &e.phoneno);

                fwrite(&e,recsize,1,fp);

                printf("\nAdd another record(y/n) ");
                fflush(stdin);
                another = getche();
            }
            break;


          case '2':
            system("cls");
            rewind(fp);
            while(fread(&e,recsize,1,fp)==1)
            {
                printf("\n%d %s %d %s %d ",e.productID,e.productnam,e.buyerID,e.date,e.phoneno);
            }
            getch();
            break;

     case '3':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("Enter the product name to modify: ");
                scanf("%s", na);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1)
                {
                    if(strcmp(e.productnam,na) == 0)
                    {
                        printf("\nEnter new productID,product name,buyerID,date,phone no : ");
                        scanf("%d %s %d %s %d ",&e.productID,e.productnam,&e.buyerID,e.date,&e.phoneno);
                        fseek(fp,-recsize,SEEK_CUR);
                        fwrite(&e,recsize,1,fp);
                        break;
                    }
                }
                printf("\nModify another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;

      case '4':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter name of product to delete: ");
                scanf("%s",na);
                ft = fopen("Temp.dat","wb");
                rewind(fp);
                while(fread(&e,recsize,1,fp) == 1)
                {
                    if(strcmp(e.productnam,na) != 0)
                    {
                        fwrite(&e,recsize,1,ft);
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT");
                rename("Temp.dat","EMP.DAT");
                fp = fopen("EMP.DAT", "rb+");
                printf("Delete another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;

         case '5':
            fclose(fp);
            exit(0);
             }

         }

    return 0;
}
