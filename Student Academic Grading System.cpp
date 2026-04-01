#include <iostream> 	//for cin and cout function
#include<iomanip>		//for precise formatting of output
#include <string>		//for seamless work with sequences of characters
#include <conio.h>		//for clear screen function
#include <limits>		//to clarify the limit of user inputs

using namespace std;

char decision_of_grade(double average);	//Function declaration

void clear_screen() {
    cout << "Press any key to continue..." << endl;
    getch();  		// Wait for a key press
    system("cls");  	// Clear screen
}

void mainscreen() {
    cout << "                  Welcome to the                   " << endl
         << "===================================================" << endl
         << "|                                                 |" << endl
         << "|          % % % % % % % % % % % % % % %          |" << endl
         << "|         %                             %         |" << endl
         << "|        %    Student's Grading System   %        |" << endl
         << "|         %                             %         |" << endl
         << "|           % % % % % % % % % % % % % %           |" << endl
         << "|                                                 |" << endl
         << "===================================================" << endl;
    clear_screen();	//Clear screen function is called
}

void GradeTable(){		//Function to display grade table
    int number_of_grades=5; //There is 5 range of grades
    int range_of_grades[number_of_grades][2]={{80,100},{70,79 },{60,69 },{50,59},{0,49 }};
    string grades[number_of_grades]={"A","B","C","D","F"};
    double points[number_of_grades]={4.0,3.0,2.0,1.0,0.0};

    cout << "+--------------+-----------------+-----------------+" << endl;
    cout << "|    Marks     |     Grade       |     Points      |" << endl;
    cout << "+--------------+-----------------+-----------------+"<< endl;

    for(int i=0;i<number_of_grades;i++){
        cout << "| " << setw(8) << right << range_of_grades[i][0] << "-" << setw(3) << right <<range_of_grades[i][1];
        cout<<" | " << setw(15) << left << grades[i] << " |" ;
        cout<<fixed << setprecision(2)<<setw(16)<<left<<points[i]<<" |"<<endl;
        cout << "+--------------+-----------------+-----------------+" << endl;
    }
}

void get_previous_semester_info(double& cumulative_grade_points, double& cumulative_credit_hours) {	//Function to check validation of previous semester info
    bool valid_input = false; //start with invalid input state
    const int MAX_CREDITS_PER_SEMESTER=20; //maximum credit hours per semster
    const int MAX_SEMESTERS=27; //maximum semesters,equal to 9 years
    const int MAX_POSSIBLE_CREDIT_HOURS=MAX_CREDITS_PER_SEMESTER*MAX_SEMESTERS;
    const double MAX_POSSIBLE_GRADE_POINTS=MAX_POSSIBLE_CREDIT_HOURS*4.0;

    // First, get and validate cumulative grade points
    do {
        cout << "Enter the cumulative total grade points from previous semesters: ";
        if (!(cin >> cumulative_grade_points)) {
            cout << "Invalid input. Please enter a numeric value." << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');//handle input buffer
            continue;
        }

        if (cumulative_grade_points < 0) {
            cout << "Cumulative total grade points cannot be less than zero." << endl << endl;
            continue;
        }
        if(cumulative_grade_points>MAX_POSSIBLE_GRADE_POINTS){
                cout<<"Invalid grade points.Maximum possible grade point is ";
                cout<<MAX_POSSIBLE_GRADE_POINTS<<endl;
                continue;
        }
        valid_input = true;
    } while (!valid_input);

    valid_input = false; // Reset for credit hours validation

    // Second, get and validate cumulative credit hours
    do {
        cout << "Enter the cumulative total credit hours from previous semesters: ";
        if (!(cin >> cumulative_credit_hours)) {
            cout << "Invalid input. Please enter a numeric value." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (cumulative_credit_hours < 0) {
            cout << "Cumulative total credit hours cannot be less than zero." << endl;
            continue;
        }

        if (cumulative_credit_hours > MAX_POSSIBLE_CREDIT_HOURS) {
            cout<<"Invalid credit hours. Maximum possible credit hours is " ;
            cout<<MAX_POSSIBLE_CREDIT_HOURS<<endl;
            continue;
        }

        // Validate the relationship between grade points and credit hours
        if (cumulative_grade_points > (cumulative_credit_hours * 4.0)) {
            cout << "Invalid combination. Grade points cannot exceed (credit hours x 4.0)." << endl;
            valid_input = false;
            continue;
        }

        valid_input = true;
    } while (!valid_input);
    cout<<endl;
}


double calculate_GPA(double marks[], int creditHours[], int numSubjects) {	//Function to calculate GPA
    double total_credits = 0.0;
    double total_quality_points = 0.0;

    for (int i = 0; i < numSubjects; i++) {
        char grade = decision_of_grade(marks[i]);	//Function call to determine grade based on grade points
        double grade_points;

        switch (grade) {
            case 'A':
                grade_points = 4.0;
                break;
            case 'B':
                grade_points = 3.0;
                break;
            case 'C':
                grade_points = 2.0;
                break;
            case 'D':
                grade_points = 1.0;
                break;
            case 'F':
                grade_points = 0.0;
                break;
            default:
                cout << "Invalid grade: " << grade << endl;
                return 0.0;
        }

        total_credits += creditHours[i];
        total_quality_points += grade_points * creditHours[i];
    }

    if (total_credits == 0.0) {
        cerr << "Error: No valid marks or credit hours entered." << endl;
        return 0.0; 	// Handle error or return a default value
    }

    return total_quality_points / total_credits;
}

double calculate_CGPA(double current_semester_GPA, double cumulative_grade_points, double cumulative_credit_hours, double current_semester_credits) {	//Function to calculate CGPA
    double total_grade_points = cumulative_grade_points + (current_semester_GPA * current_semester_credits);
    double total_credit_hours = cumulative_credit_hours + current_semester_credits;
    return total_grade_points / total_credit_hours;
}

int main()			//main function started
{
    string name;			//data declarations
    int num_of_subjects;
    char is_first_semester;
    double total_marks=0.0;
    char choice;

    system ("color E0");	//for the output screen background and font colours

    do{
    mainscreen(); 	//Function call to display main screen
    cout<<"Here are the Grade Table"<<endl;

    GradeTable();	//Function call to display the grade table

    do{
       cout<<"Please enter student name: ";
       getline(cin,name);
       if (name.empty()){
        cout<<"Name cannot be empty"<<endl;
       }
    }while(name.empty());
    cout<<endl;

    char course;
    cout << "Which course are you from?" << endl
         << "(Enter 'E' for Engineering OR 'N' for Non-Engineering): ";
    cin >> course;
    do {			//do-while loop for invalid input
        if ((course != 'E') && (course != 'e') && (course != 'N') && (course != 'n')) {
            cout << "Please enter a valid input (E or N only)" << endl << endl;
            cout << "Which course are you from?" << endl
                 << "(Enter 'E' for Engineering OR 'N' for Non-Engineering): ";
            cin >> course;
        }
    } while ((course != 'E') && (course != 'e') && (course != 'N') && (course != 'n'));
    cout << endl;

    cout << "Is this " << name << "'s first semester? (y/n): ";
    cin >> is_first_semester;
    do {			//do-while loop for invalid input
        if ((is_first_semester != 'Y') && (is_first_semester != 'y') && (is_first_semester != 'N') && (is_first_semester != 'n')) {
            cout << "Please enter a valid input (Y or N only)" << endl << endl;
            cout << "Is this " << name << "'s first semester? (y/n): ";
            cin >> is_first_semester;
        }
    } while ((is_first_semester != 'Y') && (is_first_semester != 'y') && (is_first_semester != 'N') && (is_first_semester != 'n'));
    cin.ignore(); 	//to ignore or discard characters from the input buffer
    cout << endl;

    if (is_first_semester == 'y' || is_first_semester == 'Y'){
        clear_screen();
    }

    double cumulative_grade_points = 0.0;
    double cumulative_credit_hours = 0.0;
    if(is_first_semester=='N'||is_first_semester=='n'){

        get_previous_semester_info(cumulative_grade_points, cumulative_credit_hours); 	//function call for calculating previous semester gpa to get cgpa

        cout<<"Thank you for inserting last semester information."<< endl << endl;
        clear_screen();
        cout<<"Insert "<<name<<"'s"<<" current semester information"<<endl;
        cout<<endl;
    }

    cout<<"Enter the number of subjects :";
    cin>>num_of_subjects;
    cout<<endl;

    if (num_of_subjects <= 0) {	//error handling if user inputs number less than zero
    do {
        cout << "Number of subjects must be greater than zero." << endl;
        cout << "Enter the number of subjects: ";
        cin >> num_of_subjects;
        cout << endl;
    } while (num_of_subjects <= 0);
    }

    string name_of_subjects[num_of_subjects];
    double marks[num_of_subjects];
    int creditHours[num_of_subjects];

    if (num_of_subjects > 0) {
        cin.ignore();

        for(int i=0; i<num_of_subjects; i++){
            cout << "Enter the names of ";
            cout << "Subject "<<i+1<<": ";
            getline(cin, name_of_subjects[i]);
        }		//for users to input the name of subjects registered
    }
    else {
        cout << "Number of subjects must be greater than zero" << endl;
    }
    cout<<endl;


    for(int i=0;i<num_of_subjects;i++){
        double tempMark;
        do{		//user input on marks for each subjects and range declaration
            cout<<"Please enter marks for subject ";
            cout<<name_of_subjects[i]<<": ";
            cin>>tempMark;
            if(tempMark > 100){
                cout << "Marks cannot more than 100. Please enter a valid marks."<<endl<<endl;
            } else if (tempMark < 0) {
                cout << "Marks cannot be less than zero. Please enter a valid marks." << endl<<endl;
            }
        }while(tempMark > 100 || tempMark < 0);
    marks[i] = tempMark;
    total_marks += marks[i];
    }
    cout<<endl;

//user inputs on credit hours for each subjects and range declaration
    for(int i=0;i<num_of_subjects;i++){
        int tempCreditHour;
        double pointHours;
        cout<<"Please enter the credit hour for "<< name_of_subjects[i]<<":";
        cin>>tempCreditHour;
        do {
            if (tempCreditHour < 0) {
                cout << "Credit hour cannot be less than zero." << endl << endl;
                cout<<"Please enter the credit hour for "<< name_of_subjects[i]<<":";
                cin>>tempCreditHour;
            } else if (tempCreditHour > 4) {
                cout << "Credit hour cannot be more than 4 per subject." << endl << endl;
                cout<<"Please enter the credit hour for "<< name_of_subjects[i]<<":";
                cin>>tempCreditHour;
            }
        } while (tempCreditHour < 0 || tempCreditHour > 4);

        creditHours[i]=tempCreditHour;
    }

    double current_semester_GPA = calculate_GPA(marks, creditHours, num_of_subjects);
    double total_credits = 0;
    for (int i = 0; i < num_of_subjects; i++) {
        total_credits += creditHours[i];
    }
    cout<<endl;

    clear_screen();

    double GPA = calculate_GPA(marks, creditHours, num_of_subjects); //Function call to calculate GPA
    double CGPA = calculate_CGPA(current_semester_GPA, cumulative_grade_points, cumulative_credit_hours, total_credits);	//Function call to calculate CGPA
    double average_marks=total_marks/num_of_subjects;	//Calculate average of marks
    char grade=decision_of_grade(average_marks);	//Function call for decision grade of average mark

//result screen: display results of inserted inputs
    cout<<"==================================================="<<endl;
    cout<<" Student Name: "<<name<<endl;

    if (course == 'n' || course == 'N') {
        cout << " Course: Non-Engineering" << endl;
    } else {
        cout << " Course: Engineering" <<endl;
    }

    cout<<" Average Marks: "<<average_marks<<endl;
    cout<<" Grade Average Mark: " << grade << endl;
    cout<<" GPA: " << GPA << endl;
    cout<<" CGPA: " << CGPA << endl;
    cout<<"==================================================="<<endl;
    cout<<" Grades for each subject: "<<endl;
    cout<<"==================================================="<<endl;
    for(int i=0;i<num_of_subjects;i++){
        char grade=decision_of_grade(marks[i]);	//Function call for decision grade of each subject marks
        cout<<name_of_subjects[i]<<": "<<marks[i]<<"  (Grade:"<<grade<<")"<<endl;
    }
       cout<<"==================================================="<<endl;
       cout<<"Do you want to input another student grade?(y/n): ";
       cin>>choice;	//ask the user if the user wants to repeat the process or not

    do {			//for invalid input
        if ((choice != 'Y') && (choice != 'y') && (choice != 'N') && (choice != 'n')) {
            cout << "Please enter a valid input (Y or N only)" << endl << endl;
            cout<<"Do you want to input another student grade?(y/n): ";
            cin>>choice;
        }
    } while ((choice != 'Y') && (choice != 'y') && (choice != 'N') && (choice != 'n'));

       if (choice=='y'||choice=='Y') {
        clear_screen();
        }
    }while((choice=='y')||(choice=='Y'));

    cout<< endl << "----------------------------------------------------"<<endl;
    cout<<"Thank you for using this program :) Have a nice day!"<<endl;
    cout<<"----------------------------------------------------"<<endl;

    return 0;
}

char decision_of_grade(double average){	//Function definition
    if (average >= 80) {
        return 'A';
    } else if (average >= 70) {
        return 'B';
    } else if (average >= 60) {
        return 'C';
    } else if (average >= 50) {
        return 'D';
    } else {
        return 'F';
    }
}
