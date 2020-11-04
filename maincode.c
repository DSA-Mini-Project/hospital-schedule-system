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
    int n = 24;
    node * gensurgeon_schedule = NULL;
    node * physician_schedule = NULL;
    node * radiologist_schedule = NULL;

    physician_schedule = createLinkedList(n);
    gensurgeon_schedule = createLinkedList(n);
    radiologist_schedule = createLinkedList(n);

    input_details(physician_schedule, gensurgeon_schedule, radiologist_schedule);

}

