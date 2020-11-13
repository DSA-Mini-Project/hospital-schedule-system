//Program to implement automatic dynamic schedule system for a hospital with multiple working staff
//Contributors : Akash Bagchi   Akshaya Nadathur   Anirudh Preeth   Anup Venkat

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct node
{
    int timeslot;
    char name[40];
    char contact_number[10];
    char type[25];
    char reschedule_preference[10];
    struct node * next;
}node;

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
    node * cur = head;
    while(cur->next != NULL)
    {
        printf("\n%d\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s",cur->timeslot,cur->name,cur->contact_number,cur->type,cur->reschedule_preference);
        cur=cur->next;
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
}

void view(node * head)
{
    int i;
    char contactnum;
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
      }
      cur = cur->next;
      break;
   }
}

void viewapp(node * physician_schedule, node * gensurgeon_schedule, node * radiologist_schedule)
{
    view(physician_schedule);
    view(gensurgeon_schedule);
    view(radiologist_schedule);
}

void cancel(node * head, char contactn[])
{
   node * cur = head;
   while(cur->next!=NULL)
   {
      if(!strcmp(cur->contact_number, contactn))
      {
         strcpy(cur->name, "TBE");
         strcpy(cur->contact_number, "TBE");
         strcpy(cur->type, "TBE");
         strcpy(cur->reschedule_preference, "TBE");
      }
      cur = cur->next;
   }
    printf("Your appointment has been successfully cancelled.");
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
            cancel(physician_schedule, contactn);
            break;
        case 5:
        case 6:
            cancel(gensurgeon_schedule, contactn);
            break;
        case 7:
        case 8:
            cancel(radiologist_schedule, contactn);
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
            break;
        case 2:
            display(gensurgeon_schedule);
            break;
        case 3:
            display(radiologist_schedule);
            break;
        default:
            printf("Cannot find this schedule, please try again.");
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


void input_details(node * physician_schedule, node * gensurgeon_schedule, node * radiologist_schedule)
{
    //Arrays to represent the occupied or vacant status of the timeslots in staff members' schedules (0 represents occupied)
    char physician_timeslot_availability[24][8] = {"900","930","1000","1030","1100","1130","1200","1230","1300","1330","1400","1430","1500","1530","1600","1630","1700","1730","1800","1830","1900","1930","2000","2030"};
    char gensurgeon_timeslot_availability[24][8] = {"900","930","1000","1030","1100","1130","1200","1230","1300","1330","1400","1430","1500","1530","1600","1630","1700","1730","1800","1830","1900","1930","2000","2030"};
    char radiologist_timeslot_availability[24][8] = {"900","930","1000","1030","1100","1130","1200","1230","1300","1330","1400","1430","1500","1530","1600","1630","1700","1730","1800","1830","1900","1930","2000","2030"};

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
                if(physician_timeslot_availability[i]!="occupied")
                    printf("%d: %s\n", i+1, physician_timeslot_availability[i]);
            }
            printf("Please enter your preferred timeslot : ");
            scanf("%d", &timeslot);
            strcpy(time, physician_timeslot_availability[timeslot-1]);
            strcpy(physician_timeslot_availability[timeslot-1],"occupied");
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
                if(physician_timeslot_availability[i]!="occupied" && physician_timeslot_availability[i+1]!="occupied" && i+1 <24)
                    printf("%d: %s\n", i+1, physician_timeslot_availability[i]);
            }
            printf("Please enter your preferred timeslot : ");
            scanf("%d", &timeslot);
            strcpy(time, physician_timeslot_availability[timeslot-1]);
            strcpy(physician_timeslot_availability[timeslot-1],"occupied");
            strcpy(physician_timeslot_availability[timeslot],"occupied");
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
                if(gensurgeon_timeslot_availability[i] != "occupied" && gensurgeon_timeslot_availability[i+1] != "occupied" && i+1 < 24)
                    printf("%d: %s\n", i+1, gensurgeon_timeslot_availability[i]);
            }
            printf("Please enter your preferred timeslot : ");
            scanf("%d", &timeslot);
            strcpy(time, gensurgeon_timeslot_availability[timeslot-1]);
            strcpy(gensurgeon_timeslot_availability[timeslot-1],"occupied");
            strcpy(gensurgeon_timeslot_availability[timeslot],"occupied");
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
                if(gensurgeon_timeslot_availability[i] != "occupied" && gensurgeon_timeslot_availability[i+1] != "occupied" && i+1 < 24 && gensurgeon_timeslot_availability[i+2] != "occupied" && i+2 < 24 && gensurgeon_timeslot_availability[i+3] != "occupied" && i+3 < 24 && gensurgeon_timeslot_availability[i+4] != "occupied" && i+4 < 24 && gensurgeon_timeslot_availability[i+5] != "occupied" && i+5 < 24)
                    printf("%d: %s\n", i+1, gensurgeon_timeslot_availability[i]);
            }
            printf("Please enter your preferred timeslot : ");
            scanf("%d", &timeslot);
            strcpy(time, gensurgeon_timeslot_availability[timeslot-1]);
            for(int i=0;i<6;i++)
                strcpy(gensurgeon_timeslot_availability[timeslot-1+i],"occupied");
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
                if(radiologist_timeslot_availability[i]!="occupied")
                    printf("%d: %s\n", i+1, radiologist_timeslot_availability[i]);
            }
            printf("Please enter your preferred timeslot : ");
            scanf("%d", &timeslot);
            strcpy(time, gensurgeon_timeslot_availability[timeslot-1]);
            strcpy(radiologist_timeslot_availability[timeslot-1],"occupied");
            printf("\nOpt in for auto-rescheduling? (y/n)");
            scanf("%s", &reschedule_preference);
            insert_new_appointment(radiologist_schedule, timeslot, name, contact_number, type, reschedule_preference);
            printconfirmation(radiologist_schedule, timeslot, name, type, time);
            break;

        case 8:
            printf("\nThe currently available timeslots are as follow: \n");
            for(int i=0; i<24; i++)
            {
                if(radiologist_timeslot_availability[i]!="occupied" && radiologist_timeslot_availability[i+1]!="occupied" && i+1 < 24)
                    printf("%d: %s\n", i+1, radiologist_timeslot_availability[i]);
            }
            printf("Please enter your preferred timeslot : ");
            scanf("%d", &timeslot);
            strcpy(time, gensurgeon_timeslot_availability[timeslot-1]);
            strcpy(radiologist_timeslot_availability[timeslot-1],"occupied");
            strcpy(radiologist_timeslot_availability[timeslot],"occupied");
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

    printf("WELCOME TO THE AUTOMATED HOSPITAL SCHEDULE MANAGEMENT SYSTEM\n\n");

    input_details(physician_schedule, gensurgeon_schedule, radiologist_schedule);
    viewapp(physician_schedule,gensurgeon_schedule,radiologist_schedule);
/*
    mainmenu:
        printf("\n|| Main Menu ||\n\n");
        printf("\n\t1. Admin login.\n\t2. Book an appointment.\n\t3. View your appointment.\n\t4. Cancel an appointment.\n\t5. Exit");
        printf("\n(Enter index number to select operation)");
        scanf("%d",&menuchoice);
        switch(menuchoice)
        {
            //case 1:

            case 2:
                input_details(physician_schedule, gensurgeon_schedule, radiologist_schedule);
                break;
            //case 3:

            //case 4:

        }
        if(menuchoice!=5)
            goto mainmenu;
*/
}
