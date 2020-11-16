//Program to implement automatic dynamic schedule system for a hospital with multiple working staff
//Contributors : Akash Bagchi   Akshaya Nadathur   Anirudh Preeth   Anup Venkat
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>


//Arrays to represent the 0 or vacant status of the timeslots in staff members' schedules (0 represents 0)
char physician_timeslot_availability[24][8] = {"9:00","9:30","10:00","10:30","11:00","11:30","12:00","12:30","13:00","13:30","14:00","14:30","15:00","15:30","16:00","16:30","17:00","17:30","18:00","18:30","19:00","19:30","20:00","20:30"};
char gensurgeon_timeslot_availability[24][8] = {"9:00","9:30","10:00","10:30","11:00","11:30","12:00","12:30","13:00","13:30","14:00","14:30","15:00","15:30","16:00","16:30","17:00","17:30","18:00","18:30","19:00","19:30","20:00","20:30"};
char radiologist_timeslot_availability[24][8] = {"9:00","9:30","10:00","10:30","11:00","11:30","12:00","12:30","13:00","13:30","14:00","14:30","15:00","15:30","16:00","16:30","17:00","17:30","18:00","18:30","19:00","19:30","20:00","20:30"};


//Structure used to represent one in 24 half-hour timeslots, i.e. one node in the linked list.
typedef struct node
{
    int timeslot;
    char name[40];
    char contact_number[10];
    char type[25];
    char reschedule_preference[10];
    struct node * next;
}node;

//Function to create linked list with 'n' (24) timeslots, all initialised with "To Be Entered" values, representing a free time slot that an appointment may be booked into
node * createLinkedList(int n)
{
    node * head = NULL;
    node * temp = NULL;
    node * cur = NULL;

    for(int i=0;i<n;i++)
    {
        //Isolated node
        temp = (node*)malloc(sizeof(node));
        temp->timeslot = i+1;
        strcpy(temp->name , "TBE");
        strcpy(temp->contact_number , "TBE");
        strcpy(temp->type , "TBE");
        strcpy(temp->reschedule_preference , "TBE");
        temp->next = NULL;

        if(head == NULL)
        {
            head = temp;
        }
        else
        {
            cur = head;
            while(cur->next != NULL)
                cur = cur->next;
            cur->next = temp;
        }
    }
    return head;
}

void display(node * head)
{
    int i;
    node * cur = head;
    printf("\nTimeslot\t\tName\t\tContact number\t\tAppointment type\t\tReschedule?");
    char timings[24][8] = {"9:00","9:30","10:00","10:30","11:00","11:30","12:00","12:30","13:00","13:30","14:00","14:30","15:00","15:30","16:00","16:30","17:00","17:30","18:00","18:30","19:00","19:30","20:00","20:30"};
    while(cur->next != NULL)
    {
        i=cur->timeslot;
        printf("\n%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s",timings[i-1],cur->name,cur->contact_number,cur->type,cur->reschedule_preference);
        cur=cur->next;
    }
    if(cur->next==NULL)
    {
        printf("\n%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s",timings[i],cur->name,cur->contact_number,cur->type,cur->reschedule_preference);
    }
    printf("\n");
}

void insert_new_appointment(node * head, int timeslot, char name[], char contact_number[], char type[], char reschedule_preference[])
{
    node * cur = head;

    while(cur->next != NULL)
    {
        if(cur->timeslot == timeslot)
        {
            strcpy(cur->name, name);
            strcpy(cur->contact_number, contact_number);
            strcpy(cur->type, type);
            strcpy(cur->reschedule_preference, reschedule_preference);
        }
        cur = cur->next;
    }
}


void printconfirmation(node * head, int timeslot, char name[], char type[], char time[])
{
    node * cur = head;
    while(cur->next!=NULL)
    {
        cur = cur->next;
        if(cur->timeslot == timeslot)
            break;
    }
    printf("\n\nHi %s. Your %s appointment for %s has been successfully booked!\n",name, type, time);
    getchar();
}


void reschedule(node * head, int atype, int startpos)
{
    char dicttime[24][8]={"9:00","9:30","10:00","10:30","11:00","11:30","12:00","12:30","13:00","13:30","14:00","14:30","15:00","15:30","16:00","16:30","17:00","17:30","18:00","18:30","19:00","19:30","20:00","20:30"};
    int elen, alen, oldstart;
    char oldtype[25], con[10];
    if(atype==1 || atype==2 || atype==7)
        elen = 1;
    else if(atype==3 || atype==4 || atype==5 || atype==8)
        elen = 2;
    else
        elen = 6;

    node * old = head;
    while(old->next!=NULL)
    {
        if(old->timeslot==startpos)
            break;
        old = old->next;
    }

    node * cur = old;
    for(int i=0; i<elen; i++)
        cur = cur->next;

    while(cur->next != NULL)
    {
        if(!strcmp(cur->reschedule_preference, "y"))
        {
            if(!strcmp(cur->type,"General Consultancy") || !strcmp(cur->type,"Blood Test/Vaccinations") || !strcmp(cur->type,"X-Ray"))
                alen = 1;
            else if(!strcmp(cur->type,"ECG Test") || !strcmp(cur->type, "Routine Checkup") || !strcmp(cur->type, "Minor Surgery") || !strcmp(cur->type, "Ultrasound"))
                alen = 2;
            else
                alen = 6;

            if(alen<=elen)
            {
                oldstart = cur->timeslot;
                strcpy(oldtype, cur->type);
                strcpy(con, cur->contact_number);

                for(int i=0; i<alen; i++)
                {
                    insert_new_appointment(head, startpos+i, cur->name, cur->contact_number, cur->type, cur->reschedule_preference);
                }

                for(int i=0; i<alen; i++)
                {
                    strcpy(cur->name, "TBE");
                    strcpy(cur->contact_number, "TBE");
                    strcpy(cur->type, "TBE");
                    strcpy(cur->reschedule_preference, "TBE");

                    if(!strcmp(oldtype,"General Consultancy") || !strcmp(oldtype,"Blood Test/Vaccinations") || strcmp(oldtype,"X-Ray"))
                        strcmp(physician_timeslot_availability[cur->timeslot-1],dicttime[oldstart-1+i]);
                    else if(!strcmp(cur->type,"ECG Test") || !strcmp(cur->type, "Routine Checkup") || !strcmp(cur->type, "Minor Surgery") || !strcmp(cur->type, "Ultrasound"))
                        strcmp(gensurgeon_timeslot_availability[cur->timeslot-1],dicttime[oldstart-1+i]);
                    else
                        strcmp(radiologist_timeslot_availability[cur->timeslot-1],dicttime[oldstart-1+i]);

                    cur = cur->next;
                }
                return;
            }

        }
        else
            cur = cur->next;

    }
}

void view(node * head)
{
    int i;
    char contactnum[10];
    char timings[24][8] = {"9:00","9:30","10:00","10:30","11:00","11:30","12:00","12:30","13:00","13:30","14:00","14:30","15:00","15:30","16:00","16:30","17:00","17:30","18:00","18:30","19:00","19:30","20:00","20:30"};
    printf("Enter your contact number to view your appointment:\t");
    scanf("%s",&contactnum);
    node * cur = head;
   while(cur->next!=NULL)
   {
      if(!strcmp(cur->contact_number, contactnum))
      {
        i=cur->timeslot;
        printf("\nHi %s, your %s appointment is booked for %s.\n",cur->name,cur->type,timings[i-1]);
        getchar();
        return;
      }
      cur = cur->next;
   }
}

void viewapp(node * physician_schedule, node * gensurgeon_schedule, node * radiologist_schedule)
{
    int choose;
    printf("\nIf you would like to view your appointment timings and type, kindly enter the appropriate alphabet below for your category.\n1. Physical check-up\n2. Surgery\n3. Radiology/scans\n");
    scanf(" %d",&choose);
    switch(choose)
    {
    case 1:
        view(physician_schedule);
        break;
    case 2:
        view(gensurgeon_schedule);
        break;
    case 3:
        view(radiologist_schedule);
        break;
    default:
        printf("Invalid, please try again.");
        viewapp(physician_schedule,gensurgeon_schedule,radiologist_schedule);
        break;
    }
}

void cancel(node * head, int apptype, char contactn[])
{
   node * cur = head;
   int flag = 0;
   int startpos;

   while(cur->next!=NULL)
   {
      if(!strcmp(cur->contact_number, contactn))
      {
         if(flag==0)
         {
             startpos = cur->timeslot;
             flag = 1;
         }
         strcpy(cur->name, "TBE");
         strcpy(cur->contact_number, "TBE");
         strcpy(cur->type, "TBE");
         strcpy(cur->reschedule_preference, "TBE");
      }
      cur = cur->next;
   }
   reschedule(head, apptype, startpos);
    printf("Your appointment has been successfully cancelled.");
    getchar();
 }

void cancelinput(node * physician_schedule, node * gensurgeon_schedule, node * radiologist_schedule)
{
    char contactn[10];
    int apptype;
    printf("\nPlease enter your contact number:\n");
    scanf("%10s", &contactn);
    char typeinput[8][30] = {"General Consultancy", "Blood Test/Vaccinations", "ECG Test", "Routine Checkup", "Minor Surgery", "Major Surgery", "X-Ray", "Ultrasound"};
    printf("\nAppointment type: (Enter serial number 1-8)\n");
    for(int i=0; i<8; i++)
    {
        printf("%d : %s\n",i+1,typeinput[i]);
    }
    scanf("%d", &apptype);

    switch(apptype)
    {
        case 1:
        case 2:
        case 3:
        case 4:
            cancel(physician_schedule, apptype, contactn);
            break;
        case 5:
        case 6:
            cancel(gensurgeon_schedule, apptype, contactn);
            break;
        case 7:
        case 8:
            cancel(radiologist_schedule, apptype, contactn);
            break;
        default:
            printf("Invalid input.");
            cancelinput(physician_schedule, gensurgeon_schedule, radiologist_schedule);
            break;
    }
}


void enter(node * physician_schedule, node * gensurgeon_schedule, node * radiologist_schedule)
{
    int choice;
    printf("Please enter which doctor's schedule you would like to view:\n1. Physician\n2. General Surgeon\n3. Radiologist\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            display(physician_schedule);
            getchar();
            break;
        case 2:
            display(gensurgeon_schedule);
            getchar();
            break;
        case 3:
            display(radiologist_schedule);
            getchar();
            break;
        default:
            printf("Cannot find this schedule, please try again.");
            getchar();
            enter(physician_schedule,gensurgeon_schedule,radiologist_schedule);
            break;
    }
}


void admin(node * physician_schedule, node * gensurgeon_schedule, node * radiologist_schedule)
{
   char username[]="hospital";
   char password[]="doctor123";
   char user[9];
   char pw[10];
   int check=0, usercheck, passcheck;
   printf("Administrator credentials to be entered below.\nUsername:\t");
   scanf("%s",&user);
   printf("Password:\t");
   scanf("%s",&pw);
   usercheck=strcmp(username,user);
   passcheck=strcmp(password,pw);

   if(check==usercheck && check==passcheck)
   {
       printf("\nWelcome, Admin.\n");
       enter(physician_schedule, gensurgeon_schedule, radiologist_schedule);
   }
   else
   {
       printf("\nIncorrect username or password. Please try again.");
       admin(physician_schedule, gensurgeon_schedule, radiologist_schedule);
   }
}

//Appointment booking function.
void input_details(node * physician_schedule, node * gensurgeon_schedule, node * radiologist_schedule)
{

    printf("\nAPPOINTMENT BOOKING SCREEN ----------------------- \n");
    char typeinput[8][30] = {"General Consultancy", "Blood Test/Vaccinations", "ECG Test", "Routine Checkup", "Minor Surgery", "Major Surgery", "X-Ray", "Ultrasound"};
    int typechoice;
    int timeslot;
    char time[5];
    char name[40];
    char contact_number[10];
    char type[30];
    char reschedule_preference[5];

    printf("\nFull Name: ");
    scanf("%40s", &name);
    printf("\nContact number: ");
    scanf("%10s", &contact_number);
    printf("\nAppointment type: (Enter serial number 1-8)\n");
    for(int i=0; i<8; i++)
        printf("%d : %s\n",i+1,typeinput[i]);
    scanf("%d", &typechoice);
    strcpy(type,typeinput[typechoice-1]);

    switch(typechoice)
    {
        case 1:
        case 2:
            printf("\nThe currently available timeslots are as follow: \n");
            for(int i=0; i<24; i++)
            {
                if(!strcmp(physician_timeslot_availability[i],"0"))
                    continue;
                printf("%d: %s\n", i+1, physician_timeslot_availability[i]);
            }
            printf("Please enter your preferred timeslot : ");
            scanf("%d", &timeslot);
            strcpy(time, physician_timeslot_availability[timeslot-1]);
            strcpy(physician_timeslot_availability[timeslot-1],"0");
            printf("\nOpt in for auto-rescheduling? (y/n)");
            scanf("%s", &reschedule_preference);
            insert_new_appointment(physician_schedule, timeslot, name, contact_number, type, reschedule_preference);
            printconfirmation(physician_schedule, timeslot, name, type, time);
            break;

        case 3:
        case 4:
            printf("\nThe currently available timeslots are as follow: \n");
            for(int i=0; i<24; i++)
            {
                if(!strcmp(physician_timeslot_availability[i],"0") || !strcmp(physician_timeslot_availability[i+1],"0"))
                    continue;
                printf("%d: %s\n", i+1, physician_timeslot_availability[i]);
            }
            printf("Please enter your preferred timeslot : ");
            scanf("%d", &timeslot);
            strcpy(time, physician_timeslot_availability[timeslot-1]);
            strcpy(physician_timeslot_availability[timeslot-1],"0");
            strcpy(physician_timeslot_availability[timeslot],"0");
            printf("\nOpt in for auto-rescheduling? (y/n)");
            scanf("%s", &reschedule_preference);
            insert_new_appointment(physician_schedule, timeslot, name, contact_number, type, reschedule_preference);
            insert_new_appointment(physician_schedule, timeslot+1, name, contact_number, type, reschedule_preference);
            printconfirmation(physician_schedule, timeslot, name, type, time);
            break;

        case 5:
            printf("\nThe currently available timeslots are as follow: \n");
            for(int i=0; i<24; i++)
            {
                if(!strcmp(gensurgeon_timeslot_availability[i], "0") || !strcmp(gensurgeon_timeslot_availability[i+1], "0"))
                    continue;
                printf("%d: %s\n", i+1, gensurgeon_timeslot_availability[i]);
            }
            printf("Please enter your preferred timeslot : ");
            scanf("%d", &timeslot);
            strcpy(time, gensurgeon_timeslot_availability[timeslot-1]);
            strcpy(gensurgeon_timeslot_availability[timeslot-1],"0");
            strcpy(gensurgeon_timeslot_availability[timeslot],"0");
            printf("\nOpt in for auto-rescheduling? (y/n)");
            scanf("%s", &reschedule_preference);
            insert_new_appointment(gensurgeon_schedule, timeslot, name, contact_number, type, reschedule_preference);
            insert_new_appointment(gensurgeon_schedule, timeslot+1, name, contact_number, type, reschedule_preference);
            printconfirmation(gensurgeon_schedule, timeslot, name, type, time);
            break;

        case 6:
            printf("\nThe currently available timeslots are as follow: \n");
            for(int i=0; i<24; i++)
            {
                if(!strcmp(gensurgeon_timeslot_availability[i], "0") || !strcmp(gensurgeon_timeslot_availability[i+1], "0") || !strcmp(gensurgeon_timeslot_availability[i+2], "0") || !strcmp(gensurgeon_timeslot_availability[i+3], "0") || !strcmp(gensurgeon_timeslot_availability[i+4], "0") || !strcmp(gensurgeon_timeslot_availability[i+5], "0")!=0)
                    continue;
                printf("%d: %s\n", i+1, gensurgeon_timeslot_availability[i]);
            }
            printf("Please enter your preferred timeslot : ");
            scanf("%d", &timeslot);
            strcpy(time, gensurgeon_timeslot_availability[timeslot-1]);
            for(int i=0;i<6;i++)
                strcpy(gensurgeon_timeslot_availability[timeslot-1+i],"0");
            printf("\nOpt in for auto-rescheduling? (y/n)");
            scanf("%s", &reschedule_preference);
            for(int i=0;i<6;i++)
                insert_new_appointment(gensurgeon_schedule, timeslot+i, name, contact_number, type, reschedule_preference);
            printconfirmation(gensurgeon_schedule, timeslot, name, type, time);
            break;

        case 7:
            printf("\nThe currently available timeslots are as follow: \n");
            for(int i=0; i<24; i++)
            {
                if(!strcmp(radiologist_timeslot_availability[i], "0"))
                    continue;
                printf("%d: %s\n", i+1, radiologist_timeslot_availability[i]);
            }
            printf("Please enter your preferred timeslot : ");
            scanf("%d", &timeslot);
            strcpy(time, gensurgeon_timeslot_availability[timeslot-1]);
            strcpy(radiologist_timeslot_availability[timeslot-1],"0");
            printf("\nOpt in for auto-rescheduling? (y/n)");
            scanf("%s", &reschedule_preference);
            insert_new_appointment(radiologist_schedule, timeslot, name, contact_number, type, reschedule_preference);
            printconfirmation(radiologist_schedule, timeslot, name, type, time);
            break;

        case 8:
            printf("\nThe currently available timeslots are as follow: \n");
            for(int i=0; i<24; i++)
            {
                if(!strcmp(radiologist_timeslot_availability[i], "0") || !strcmp(radiologist_timeslot_availability[i+1], "0"))
                    continue;
                printf("%d: %s\n", i+1, radiologist_timeslot_availability[i]);
            }
            printf("Please enter your preferred timeslot : ");
            scanf("%d", &timeslot);
            strcpy(time, gensurgeon_timeslot_availability[timeslot-1]);
            strcpy(radiologist_timeslot_availability[timeslot-1],"0");
            strcpy(radiologist_timeslot_availability[timeslot],"0");
            printf("\nOpt in for auto-rescheduling? (y/n)");
            scanf("%s", &reschedule_preference);
            insert_new_appointment(radiologist_schedule, timeslot, name, contact_number, type, reschedule_preference);
            insert_new_appointment(radiologist_schedule, timeslot+1, name, contact_number, type, reschedule_preference);
            printconfirmation(radiologist_schedule, timeslot, name, type, time);
            break;
    }

}

int main()
{
    __label__ mainmenu;
    int n = 24;
    int menuchoice;
    node * gensurgeon_schedule = NULL;
    node * physician_schedule = NULL;
    node * radiologist_schedule = NULL;

    physician_schedule = createLinkedList(n);
    gensurgeon_schedule = createLinkedList(n);
    radiologist_schedule = createLinkedList(n);

    mainmenu:
        system("clear");
        printf("WELCOME TO THE AUTOMATED HOSPITAL SCHEDULE MANAGEMENT SYSTEM\n\n");
        printf("\n|| Main Menu ||\n\n");
        printf("\n\t1. Admin login.\n\t2. Book an appointment.\n\t3. View your appointment.\n\t4. Cancel an appointment.\n\t5. Exit");
        printf("\n(Enter index number to select operation): ");
        scanf("%d",&menuchoice);
        switch(menuchoice)
        {
            case 1:
                admin(physician_schedule, gensurgeon_schedule, radiologist_schedule);
                getchar();
                break;

            case 2:
                input_details(physician_schedule, gensurgeon_schedule, radiologist_schedule);
                getchar();
                break;

            case 3:
                viewapp(physician_schedule, gensurgeon_schedule, radiologist_schedule);
                getchar();
                break;

            case 4:
                cancelinput(physician_schedule, gensurgeon_schedule, radiologist_schedule);
                getchar();
                break;

            case 5:
                break;

            default:
                printf("\nInvalid input!! Please try again");
                getchar();
                goto mainmenu;
        }
        if(menuchoice!=5)
            goto mainmenu;

}

