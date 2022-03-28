#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//store information about client
typedef struct data_client
{
    int code;
    long long int Phone;
    char name[30];

}Data_Client;
// store type of order
typedef struct order
{
    char first_food[25];
    char second_food [25];
    char juice[25];
    char desert [25];
    int sum;
}Order;
//end store order
//queue for orders
typedef struct queuenode
{
    Order entry_order;
    struct queuenode *link_order;

}QueueNode_Order;
typedef struct queue
{
     QueueNode_Order *rear_order;
     QueueNode_Order *front_order;
     int size_order;
}Queue_Order;

//queue for data of clients
typedef struct queuenode_client
{
    Data_Client entry_client;
    struct queuenode_client *link_client;

}QueueNode_client;
typedef struct queue_client
{
     QueueNode_client *rear_client;
     QueueNode_client *front_client;
     int size_client;
}Queue_client;

//global variables
Order or;
Queue_Order qo;
Data_Client dc;
Queue_client qc;
int money;
//--------------------

//implementation of queue of orders
void  CreatQueue_order    (Queue_Order *);
void  EnQueue_order       (Order ,Queue_Order *);
void    DeQueue_order       (Queue_Order *);
int   QueueSize_order     (Queue_Order *);
void  ClearQueue_order    (Queue_Order *);
void  TraverseQueue_order (Queue_Order *,void (*)(Order));


//implementaion of queue for data clients
void  CreatQueue_client (Queue_client *);
void  EnQueue_client    (Data_Client ,Queue_client *);
void   DeQueue_client    (Queue_client *);
void  TraverseQueue_client (Queue_client *,void (*)(Data_Client));
void  ClearQueue_client    (Queue_client *);

//Auxiliary Functions
void  Start ();
void  Mainmenu ();
void  get_food(Order *);
void  data_clients (int,Data_Client *);
void  get_dessert(Order *);
void  get_juice (Order *);
void  print_client(Data_Client e);
void  choose ();
void  The_bill ();
void  start_file ();
void  info ();
void  get_info ();
void  Loading ();

int main()
{
    FILE *ptr;
    char line [81];
   start_file ();
   CreatQueue_order (&qo);
   CreatQueue_client (&qc);
   Start ();
   get_info ();

   ptr = fopen ("restaurant.txt","r");

   while (fgets(line,80,ptr)!=NULL)
   {
       puts (line);
   }
   fclose (ptr);
   return 0;
}
//queue structures;
void CreatQueue_order (Queue_Order *pq)
{
    pq->front_order=NULL;
    pq->rear_order=NULL;
    pq->size_order=0;
}
void EnQueue_order (Order item, Queue_Order *pq)
{
    QueueNode_Order *pn=(QueueNode_Order *)malloc (sizeof (QueueNode_Order));
    pn->link_order=NULL;
    strcpy(pn->entry_order.first_food,item.first_food);
    strcpy(pn->entry_order.second_food,item.second_food);
    strcpy(pn->entry_order.juice,item.juice);
    strcpy(pn->entry_order.desert,item.desert);
    pn->entry_order.sum=item.sum;
    if (!pq->rear_order)
        pq->front_order=pn;
    else
    pq->rear_order->link_order=pn;
    pq->rear_order=pn;
    pq->size_order++;
}
void DeQueue_order (Queue_Order *pq)
{
    QueueNode_Order *pn=pq->front_order;

   printf ("\n\t\t\t\t\tfirst_food: %s\n",pn->entry_order.first_food);
   printf ("\t\t\t\t\tSecond_food: %s\n",pn->entry_order.second_food);
   printf ("\t\t\t\t\tJuice: %s\n",pn->entry_order.juice);
   printf ("\t\t\t\t\tDessert: %s\n\n",pn->entry_order.desert);
   printf ("\t\t\t\t\tPrice: %d\n\n",pn->entry_order.sum);
   printf ("\t\t\t\t\t\tThank You\n");
   printf ("\t\t\t\t***********************************************\n\n");
    pq->front_order=pn->link_order;
    free (pn);
    if (!pq->front_order)
        pq->rear_order=NULL;
}
int QueueSize_order (Queue_Order *pq)
{
    return pq->size_order;
}
void ClearQueue_order (Queue_Order *pq)
{
    while (pq->front_order)
    {
        pq->rear_order=pq->front_order->link_order;
        free (pq->front_order);
        pq->front_order=pq->rear_order;
    }
}
void TraverseQueue_order (Queue_Order *pq,void (*pf)(Order))
{
    QueueNode_Order *pn=pq->front_order;
    for ( ;pn;pn=pn->link_order)
        (*pf)(pn->entry_order);
}

void  ClearQueue_client  (Queue_client *qcr)
{
     while (qcr->front_client)
    {
        qcr->rear_client=qcr->front_client->link_client;
        free (qcr->front_client);
        qcr->front_client=qcr->rear_client;
    }
    qcr->size_client=0;
}
void  CreatQueue_client (Queue_client *qcr)
{
    qcr->front_client=NULL;
    qcr->rear_client=NULL;
    qcr->size_client=0;
}
void  EnQueue_client (Data_Client element ,Queue_client *qcr)
{
     QueueNode_client *pn2=(QueueNode_client *)malloc (sizeof (QueueNode_client));
    pn2->link_client=NULL;
    strcpy(pn2->entry_client.name,element.name);
    pn2->entry_client.Phone=element.Phone;
    pn2->entry_client.code=element.code;

    if (!qcr->rear_client)
        qcr->front_client=pn2;
    else
    qcr->rear_client->link_client=pn2;
    qcr->rear_client=pn2;
    qcr->size_client++;
}
void DeQueue_client (Queue_client *qcr)
{
    system ("cls");
   QueueNode_client *pn2=qcr->front_client;
   printf ("\t\t\t\t***********************************************\n");
   printf ("\t\t\t\t\tCode: %d\n",pn2->entry_client.code+100);
   printf ("\t\t\t\t\tName: %s\n",pn2->entry_client.name);
   printf ("\t\t\t\t\tPhone: %lld\n",pn2->entry_client.Phone);
    qcr->front_client=pn2->link_client;
    free (pn2);
    if (!qcr->front_client)
        qcr->rear_client=NULL;
    qcr->size_client--;
}
void  TraverseQueue_client (Queue_client *qcr,void (*qcf)(Data_Client))
{
     QueueNode_client *qcn=qcr->front_client;
     (*qcf)(qcn->entry_client);
}

void Start ()
{
    printf ("\t\t\t\t\t******************************************\n");
   printf ("\t\t\t\t\t*\t Welcome to Imyay restaurant\t *\n");
   printf ("\t\t\t\t\t******************************************\n");
   Loading ();
   Mainmenu ();
}
void choose ()
{

      printf ("\n\n\t\t\t\t-----------------------------------------------\n");
      printf ("\t\t\t\t1) Login\n\t\t\t\t2) Exit\n\t\t\t\t3) Rules\n");
      printf ("\t\t\t\t-----------------------------------------------\n\n");
      printf ("Enter:");
}
void Loading ()
{
     for (int load=0 ; load<=5000 ;load++)
      {
       printf ("\rLoading..%d",load/500);
      }
      printf ("\n");
}
//Introductory destination
void Mainmenu()
{

   int choice,i,menu_choice,back,choice_;
   //choose what you need
   for ( i=1 ; i<=7; i++)
   {
      if (i==2 || i==5)
      {
             TraverseQueue_client (&qc,&print_client);
             The_bill ();
      }
      else
      {
          choose ();
          scanf  ("%d",&choice);
       if     (choice==1)
       {
               data_clients (i,&dc);
               printf (" Enter..");
               getch();
               Loading ();
               get_food(&or);
       }
      //if exit
       else if (choice==2)
       {
          printf ("\t\t\t\t-----------------------------------------------\n");
          printf ("\t\t\t\t\tThank you for your visiting..\n");
          printf ("\t\t\t\t-----------------------------------------------\n");
          i--;
          continue ;
       }
      //rules
       else if (choice==3)
       {
          printf ("\t\t\t\t-----------------------------------------------\n");
          printf ("\t\t\t\tWelcome..\n");
          printf ("\t\t\t\tWe are here to help you..\n");
          printf ("\t\t\t\tYou can choose \n\t\t\t\t  1) Two Meals \n\t\t\t\t  2) One Juice\n\t\t\t\t  3) One Dessert\n");
          printf ("\t\t\t\tYour order will be ready in 15 minutes\n\t\t\t\tThank You..\n");
          printf ("\t\t\t\t-----------------------------------------------\n\n\n\n");
          printf ("\t\t\t\t-----------------------------------------------\n");
          printf ("\t\t\t\t1) Main\n\t\t\t\t2) Exit\n");
          printf ("\t\t\t\t-----------------------------------------------\n\n");
          printf ("Enter:");
          scanf ("%d",&back);

          if (back==1)
          {
              i--;
              Loading ();
              continue;
          }
          else
          {
              i--;
             printf ("\t\t\t\t-----------------------------------------------\n");
             printf ("\t\t\t\t\tThank you for your visiting..\n");
             printf ("\t\t\t\t-----------------------------------------------\n");
              continue;
          }
        }
      else
      {
          printf ("\nPlease Enter Valid number..\n");
          i--;
          continue;
      }
      //store the orders in queue
       EnQueue_order (or,&qo);
    }
   }

   for (i=1  ; i<=3  ; i++)
   {
       TraverseQueue_client (&qc,&print_client);
       The_bill ();
   }
}

//store the name of food
void get_food(Order *r)
{
    system ("cls");
    int fir_food,sec_food,choice;
    char *food[11];
    int   price[11];
    FILE *ffood;
     r->sum=0;
    //array for store food and price
    food[0]=  "Classic Burger";
    food[1]=  "cheese Burger";
    food[2]=  "Sticky Burger";
    food[3]=  "Chicken Burger";
    food[4]=  "Smokey Burger";
    food[5]=  "Gun Burger";
    food[6]=  "Doggy Burger";
    food[7]=  "cloud Bites";
    food[8]=  "Chessy Loaded";
    food[9]=  "Havana Burger";
    food[10]= "Fire Gun";

    price [0]=50;
    price [1]=30;
    price [2]=10;
    price [3]=20;
    price [4]=20;
    price [5]=100;
    price [6]=400;
    price [7]=300;
    price [8]=70;
    price [9]=40;
    price [10]=80;
    //print food and price
    printf ("\n\t\t\t\t-----------------------------------------------\n");
    printf ("\n\t\t\t\tFood\t\t\t\t\tPrice\n");
    printf ("\t\t\t\t-----------------------------------------------\n");
    printf ("\t\t\t\t1)%s\t\t\t250 EGP\n",food[0]);
    printf ("\t\t\t\t2)%s\t\t\t\t200 EGP\n",food[1]);
    printf ("\t\t\t\t3)%s\t\t\t\t100 EGP\n",food[2]);
    printf ("\t\t\t\t4)%s\t\t\t200 EGP\n",food[3]);
    printf ("\t\t\t\t5)%s\t\t\t\t200 EGP\n",food[4]);
    printf ("\t\t\t\t6)%s\t\t\t\t100 EGP\n",food[5]);
    printf ("\t\t\t\t7)%s\t\t\t\t400 EGP\n",food[6]);
    printf ("\t\t\t\t8)%s\t\t\t\t300 EGP\n",food[7]);
    printf ("\t\t\t\t9)%s\t\t\t\t150 EGP\n",food[8]);
    printf ("\t\t\t\t10)%s\t\t\t140 EGP\n",food[9]);
    printf ("\t\t\t\t11)%s\t\t\t\t180 EGP\n",food[10]);

    //store food and price in struct and queue
    printf ("\nEnter the number of first food:");
    scanf ("%d",&fir_food);
    if (fir_food>11)
    {
        get_food (&or);
    }
    else
    {
        strcpy (r->first_food,food[fir_food-1]);
        printf ("Enter the number of second food:");
        scanf ("%d",&sec_food);
        if (sec_food>11)
        {
           get_food (&or);
        }
        else
        {
           strcpy (r->second_food,food[sec_food-1]);
           (r->sum)+=price [fir_food-1]+price [sec_food-1];
            money+=r->sum;
             //end of store food
              ffood =fopen("restaurant.txt","a");
             fprintf (ffood,"first-food: %s\nSecond-food: %s\n",r->first_food,r->second_food);
             fclose (ffood);
             // go to another choice
             printf ("\n\nPress:");
             getch();
             Loading ();
             get_dessert(&or);
        }

    }
}

void get_dessert(Order *r)
{
    system ("cls");
    char *dessert[6];
    int dessert_menu,choice;
    int pri_dessert [6];
    FILE *fdessert;
    dessert[0]="Banana Split";
    dessert[1]="Cherry Pie";
    dessert[2]="Choco Budoir";
    dessert[3]="Cookie Delite";
    dessert[4]="Apple Pie";
    dessert[5]="Fruit Smoothie";
    pri_dessert [0]=70;
    pri_dessert [1]=25;
    pri_dessert [2]=20;
    pri_dessert [3]=15;
    pri_dessert [4]=10;
    pri_dessert [5]=10;
    //print the dessert and the price of all of them
    printf ("\n\t\t\t\t-----------------------------------------------\n");
    printf ("\n\t\t\t\tDessert\t\t\t\t\tPrice\n");
    printf ("\t\t\t\t-----------------------------------------------\n");
    printf ("\t\t\t\t1)%s\t\t\t\t70 EGP\n",dessert[0]);
    printf ("\t\t\t\t2)%s\t\t\t\t25 EGP\n",dessert[1]);
    printf ("\t\t\t\t3)%s\t\t\t\t20 EGP\n",dessert[2]);
    printf ("\t\t\t\t4)%s\t\t\t\t15 EGP\n",dessert[2]);
    printf ("\t\t\t\t5)%s\t\t\t\t10 EGP\n",dessert[4]);
    printf ("\t\t\t\t6)%s\t\t\t10 EGP\n",dessert[5]);
    //store the dessert and price in struct and queue
    printf ("\n\nEnter the number of dessert:");
    scanf ("%d",&dessert_menu);
    if (dessert_menu>6)
    {
        get_dessert (&or);
    }
    else
    {
      strcpy (r->desert,dessert[dessert_menu-1]);
       r->sum+=pri_dessert [dessert_menu-1];
       money+=r->sum;
        fdessert=fopen("restaurant.txt","a");
     fprintf (fdessert,"Dessert: %s\n",r->desert);
     fclose (fdessert);
    //go to another choise
    printf ("\n\nPress:");
    getch();
    Loading ();
    get_juice(&or);
    }
}

void get_juice (Order *r)
{
    system ("cls");
    char *juice[6];
    int juice_menu,choice;
    int pri_juice[5];
    FILE *fjuice;
    //arays for juice and price
    juice[0]="Bottle Of Water";
    juice[1]="Coffee";
    juice[2]="Fresh Juice";
    juice[3]="Tea";
    juice[4]="Soft drinks";
    pri_juice[0]=5;
    pri_juice[1]=20;
    pri_juice[2]=25;
    pri_juice[3]=5;
    pri_juice[4]=30;

    //print juice and price
    printf ("\n\t\t\t\t-----------------------------------------------\n");
    printf ("\n\t\t\t\tJuice\t\t\t\t\tPrice\n");
    printf ("\t\t\t\t-----------------------------------------------\n");
    printf ("\t\t\t\t1)%s\t\t\t 5 EGP\n",juice[0]);
    printf ("\t\t\t\t2)%s\t\t\t\t20 EGP\n",juice[1]);
    printf ("\t\t\t\t3)%s\t\t\t\t25 EGP\n",juice[2]);
    printf ("\t\t\t\t4)%s\t\t\t \t\t 5 EGP\n",juice[3]);
    printf ("\t\t\t\t5)%s\t\t\t\t30 EGP\n",juice[4]);
    //store juice and price
    printf ("\nEnter the number of juice:");
    scanf ("%d",&juice_menu);
    if (juice_menu>5)
    {
        get_juice (&or);
    }
    else
    {

        strcpy (r->juice,juice[juice_menu-1]);
         r->sum+=pri_juice [juice_menu-1];
          money+=r->sum;
        //store in file
        fjuice =fopen("restaurant.txt","a");
        fprintf (fjuice,"Juice: %s\nPrice: %d\n---------------------------------------\n",r->juice,r->sum);
        fclose (fjuice);
    //go to another choice
      printf ("\n\t\t\t  ------------------------------------------------------------------\n\n");
      printf ("\t\t\t\t   Please wait Your order will be ready in 15 minutes..\n\n");
      printf ("\t\t\t  ------------------------------------------------------------------\n\n\n");
      printf ("Press:");
      getch();
      Loading ();
      system("cls");
    }
}

void data_clients (int ele ,Data_Client *dcs)
{
    FILE *fclient;
    system ("cls");
    //store the data of clients
    printf("\nPlease Put your information:\n\n");
    printf("\t\t\t\t-----------------------------------------------\n");
    printf ("\t\t\t\tPhone:");
    scanf ("%lld",&dcs->Phone);
    fflush (stdin);
    printf("\t\t\t\tName:");
    gets(dcs->name);
    printf ("\t\t\t\tYour code: %d\n",dcs->code+100);
    EnQueue_client (dc,&qc);
    dcs->code++;
    printf("\t\t\t\t-----------------------------------------------\n\n");
    //store information in file
    fclient =fopen("restaurant.txt","a");
    fprintf (fclient,"\n---------------------------------------\nCode: %d\nName: %s\nPhone: %lld\n\n\n",dcs->code,dcs->name,dcs->Phone);
    fclose (fclient);

}
void print_client (Data_Client dc)
{
    //the order is ready
    printf ("\t\t\t\t-----------------------------------------------\n");
    printf ("\t\t\t\t\tMr : %s\n\t\t\t\t\tYour order is ready..\n",dc.name);
    printf ("\t\t\t\t-----------------------------------------------\n");
    printf ("Press to get the bill..");
    getch ();
}
void The_bill  ()
{
    DeQueue_client (&qc);
    DeQueue_order (&qo);
}
void start_file () {
    FILE *st_file ;
    st_file = fopen ("restaurant.txt","w");
    fclose (st_file);
}
void info ()
{
    system ("cls");
    printf ("\t\t\t\t-----------------------------------------------\n");
    printf ("\t\t\t\t\tRESULT = %d EGP\n",money);
    printf ("\t\t\t\t\tNUM-CLIENTS = %d\n",QueueSize_order (&qo));
    printf ("\t\t\t\t-----------------------------------------------\n");

}
void get_info ()
{
    int choice;
    printf ("\t\t\t\t-----------------------------------------------\n");
    printf ("\t\t\t\t1)To get information about the day\n");
    printf ("\t\t\t\t2)Close the restaurant\n");
    printf ("\t\t\t\t-----------------------------------------------\n");
    printf ("Enter:");
    scanf ("%d",&choice);
    if (choice==1)
    {
        info ();
    }
}
