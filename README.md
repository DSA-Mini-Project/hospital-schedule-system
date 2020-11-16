# Hospital Schedule Management System

###### v1.0-beta.1

_Developed by **Akash Bagchi, Akshaya Nadathur, Anirudh Preeth and Anup Venkat** for the Data Structures and Algorithms Mini Project at Dayananda Sagar University, Kudlu Gate_

This is a schedule management system designed for modern hospitals to use as a next-day appointment booking and management application, assigning appointments to patients based on their preferences as well as allowing for cancellation and dynamic(automatic) rescheduling.
Our code employs the implementation of linked lists using structures and pointers in C, as well as various other Object Oriented methodologies to achieve the functionality of the system. The base C code uses a simple command line menu for user operations, but also has a Python3 based TKinter GUI ready for implementation, only awaiting integration with the C language script.

## Functionality:

1. Appointment Creation
   - Different Schedules for different doctors (eg: X-Rays are handled by the radiologist whereas minor surgeries are handled by the General surgeon.)
   - Mechanisms in place to prevent overwriting of existing appointments by new ones
   - User is given the choice to opt-in for automatic rescheduling
   - Appointment confirmed acknowledgement messages to verify successful booking
2. Appointment Viewing
   - Any user can review their appointment details simply by entering their appointment type and contact information as a search parameter.
3. Appointment Cancellation
   - User can cancel their appointment by entering their details.
   - Automatic Rescheduling: Upon cancellation, the schedule is scanned for following appointments that have opted-in for automatic rescheduling. Should such an appointment be encountered that can be accommodated in the number of slots freed by the cancellation, it is automatically moved to the earlier time, and the old times are made available for bookings once more.
4. Admin View
   - Enabled mechanism for hospital staff to access password-protected view of all staff member's schedules, to ensure there is no confusion, and to facilitate manual cancellation by hospital staff in case of disparity or errors (negligible probability).

## Working - Backend

### The Schedule

Our schedule for this system considers a 12-hour working day in a hospital, comprised of 24 half-hour time slots. The user defined data structure _node_ is used to create the basic data structure for any one appointment slot, containing the patient's name, contact information, appointment details, timeslot (position in schedule) and link to the next node.

```c
typedef struct node
{
    int timeslot;
    char name[40];
    char contact_number[10];
    char type[25];
    char reschedule_preference[10];
    struct node * next;
}node;

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
```

### The Main Menu

The base C-script for our program employs a rudimentary command-line menu for the user to interact with, using switch cases linked to the appropriate functions.

```c
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

```

![](https://github.com/DSA-Mini-Project/hospital-schedule-system/blob/main/Images/mainmenu_withouttkinter.PNG)

### Appointment Creation

The "input_details" function takes in the user's Name, Contact information and desired appointment type. Based on type, the user is shown all the unoccupied timeslots of the appropriate doctor's schedule, accounting also for the size of their desired appointment type, to ensure that an appointment doesn't accidentally overwrite another appointment slot, or try to exceed the schedule's total size of 24 slots.
The user is also asked for their automatic rescheduling preferences, which will determine if their appointment is dynamically moved to earlier times that can accomodate them, should any open up.

```c
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
    .
    .
    .
    .
  
```

The script then uses the "insert_new_appointment" and "appointmentconfirmed_acknowledge" methods to update the respective doctor's schedule with the new appointment.

```c
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

```

<img src="https://github.com/DSA-Mini-Project/hospital-schedule-system/blob/main/Images/book1.PNG" style="zoom: 67%;" />

<img src="https://github.com/DSA-Mini-Project/hospital-schedule-system/blob/main/Images/book2.PNG" style="zoom:67%;" />



### Appointment Cancellation

The "cancelinput" function takes all relevant information from the user and calls the "cancel" function to scan through the appropriate schedule for the right slots, and empty the same. The method then makes all the timeslots previously occupied by said appointment available for booking again, to ensure that time is not wasted in the working day.

Further, the method calls the "reschedule_appointment" function when working is complete, to dynamically reschedule any following appointments wishing for earlier times, granted that it can be accommodated in the newly emptied slots.

```c
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
```

```c
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
```

<img src="https://github.com/DSA-Mini-Project/hospital-schedule-system/blob/main/Images/cancellation.PNG" style="zoom:67%;" />

**Automatic Rescheduling example:**

- Before Cancellation:

  <img src="https://github.com/DSA-Mini-Project/hospital-schedule-system/blob/main/Images/reschedule 1.PNG" style="zoom:67%;" />

  Notice how the appointment booked by Akshaya for 12:00p.m. has its reschedule preference set to "y", thus allowing the automatic_rescheduling function to move it to earlier slots when they open up

- After Cancellation:

  ![](https://github.com/DSA-Mini-Project/hospital-schedule-system/blob/main/Images/reschedule2.PNG)

  After Anirudh cancels his appointment, the automatic rescheduling moves Akshaya's appointment up to the newly emptied slots, and makes the remaining time slots available for booking again.

### Viewing your appointment

A user can revisit the portal to view his/her appointment details once they've already booked one, to be reminded of any important information and timings. This is made possible through the "viewapp" function that takes the user's appointment type and contact number as search parameters and returns to them the necessary details using it's associated "view" function.

```c
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
```

```c
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
```

<img src="https://github.com/DSA-Mini-Project/hospital-schedule-system/blob/main/Images/viewapp.PNG" style="zoom:67%;" />

### Admin View

The admin view function enables any logistical hospital staff with the (customizable by hospital) username and password to view the current state of all staff members' schedules.

```c
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
```

<img src="https://github.com/DSA-Mini-Project/hospital-schedule-system/blob/main/Images/admin.PNG" style="zoom:67%;" />

## Working - Frontend

The front - end for our program is made possible using the TKinter module in Python 3, using which we created a rudimentary GUI with buttons for all primary user functions. The front - end code (and thus the scheduling system as a whole) runs until the GUI is closed. This system is designed to always be open on a hospital computer, and refreshed at the start of every working day.

```python
import sys
from tkinter import *
%run backend.ipynb

def term():
    window.destroy()
    sys.exit("Thank you for using our Schedule Management System")

window = Tk()
window.title("Hospital Schedule Management System")
.
.
.
```

![](https://github.com/DSA-Mini-Project/hospital-schedule-system/blob/main/Images/gui.PNG)

This GUI is currently disconnected to the main working C script of our program, and integration of the two using Cython or similar methods is being looked into.



###### [View on github](https://github.com/DSA-Mini-Project/hospital-schedule-system)
