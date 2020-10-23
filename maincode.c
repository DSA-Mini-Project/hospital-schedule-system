//Program to implement automatic dynamic schedule system for a hospital with multiple working staff
//Contributors : Akash Bagchi   Akshaya Nadathur   Anirudh Preeth   Anup Venkat

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

//Define data structure node that will be used as element of linked lists
typedef struct node{
    int timeslot;
    char name[40];
    char contact_number[10];
    char type[20];
    char reschedule_preference[5];
    struct node * next;
}node;


//Declaring nodes for each staff member's schedule, so they may be passed to the initializaiton function later
node * physician_schedule = NULL;
node * gensurgeon_schedule = NULL;
node * radiologist_schedule = NULL;

//Function to initialize a linked list with 24 nodes (time slots) to represent the schedule of the respective hospital staff
node * initialize_schedule(int n)
{
    int i = 0;
    node * head = NULL;
    node * temp = NULL;
    node * cur_node = NULL;

    for(i=0;i<n;i++)
    {
        //Create independant (unlinked) node temp to later attach onto linked list
        temp = (node*)malloc(sizeof(node));
        temp->timeslot = i+1;
        strcpy(temp->name, "---");
        strcpy(temp->contact_number, "---");
        strcpy(temp->type, "---");
        strcpy(temp->reschedule_preference, "---");
        temp->next = NULL;

        if(head == NULL) //Check if list is empty, and make temp the first element of the list if so
            head = temp;
        else    //If not, insert the temp node into the end of the list
        {
            cur_node = head;
            while(cur_node->next != NULL)
                cur_node = cur_node->next;
            cur_node->next = temp;
        }

    }
    return head;
}

void display_schedule(node * head)
{
    node * cur_node = head;

    while(cur_node != NULL)
    {
        printf("%d\n%s\n%s\n%s\n%s\n", cur_node->timeslot, cur_node->name, cur_node->contact_number, cur_node->type, cur_node->reschedule_preference);
        cur_node = cur_node ->next;
    }
}

//Function to insert a new appointment into an empty timeslot
void insert_new_appointment(node * head, int timeslot, char name[], char type[], char contact_number[], char reschedule_preference[])
{
    node * cur_node = head;
    while(cur_node != NULL)
    {
        cur_node = cur_node->next;
        if(cur_node->timeslot == timeslot)
        {
            strcpy(cur_node->name, name);
            strcpy(cur_node->contact_number, contact_number);
            strcpy(cur_node->type, type);
            strcpy(cur_node->reschedule_preference, reschedule_preference);
        }
    }
}

/* Commenting out for debugging
//Function to take input from user and create appointment in appropriate doctor's schedule based on appointment type
void appointment_details_primaryinput()
{
    //Arrays to represent the occupied or vacant status of the timeslots in staff members' schedules (0 represents occupied)
    char physician_timeslot_availability[24][5] = {"900","930","1000","1030","1100","1130","1200","1230","1300","1330","1400","1430","1500","1530","1600","1630","1700","1730","1800","1830","1900","1930","2000","2030"};
    char gensurgeon_timeslot_availability[24][5] = {"900","930","1000","1030","1100","1130","1200","1230","1300","1330","1400","1430","1500","1530","1600","1630","1700","1730","1800","1830","1900","1930","2000","2030"};
    char radiologist_timeslot_availability[24][5] = {"900","930","1000","1030","1100","1130","1200","1230","1300","1330","1400","1430","1500","1530","1600","1630","1700","1730","1800","1830","1900","1930","2000","2030"};

    printf("\nAPPOINTMENT BOOKING SCREEN ----------------------- \n");
    char typechoices[8][30] = {"1 : General Consultancy", "2 : Blood Test/Vaccinations", "3 : ECG Test", "4 : Routine Checkup", "5 : Minor Surgery", "6 : Major Surgery", "7 : X-Ray", "8 : Ultrasound"};
    char typeinput[8][30] = {"General Consultancy", "Blood Test/Vaccinations", "ECG Test", "Routine Checkup", "Minor Surgery", "Major Surgery", "X-Ray", "Ultrasound"};
    int typechoiceinput;
    int timechoiceinput;
    char time[5];
    char name[40];
    char contact_number[10];
    char type[30];
    char reschedule_preference[5];

    printf("\nFull Name: ");
    gets(name);
    printf("\nContact number: ");
    gets(contact_number);
    printf("\nAppointment type: (Enter serial number 1-8)\n");
    for(int i=0; i<8; i++)
        printf("%s\n",typechoices[i]);
    scanf("%d", &typechoiceinput);
    strcpy(type,typeinput[typechoiceinput]);

    switch(typechoiceinput)
    {
        case 1:
        case 2:
            printf("\nThe currently available timeslots are as follow: \n");
            for(int i=0; i<24; i++)
            {
                if(physician_timeslot_availability[i]!=' ')
                    printf("%d: %s\n", i+1, physician_timeslot_availability[i]);
            }
                printf("Please enter your preferred timeslot : ");
                scanf("%d", &timechoiceinput);
                strcpy(time, physician_timeslot_availability[timechoiceinput-1]);
                strcpy(physician_timeslot_availability[timechoiceinput-1], ' ');
                printf("\nOpt in for auto rescheduling when possible? You will be given an earlier appointment should one become vacant, please make sure your schedule is free to accomodate for the same. Type yes or no:");
                gets(reschedule_preference);
                insert_new_appointment(physician_schedule, timechoiceinput, name, type, contact_number, reschedule_preference);

    }

}
*/

int main()
{

    physician_schedule = initialize_schedule(24);
    gensurgeon_schedule = initialize_schedule(24);
    radiologist_schedule = initialize_schedule(24);

    printf("\nTest code -------------------------\n");
    
    return 0;
}
