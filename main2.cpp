#include <bits/stdc++.h>

using namespace std;

class BITS;
class Admin;
class Subject;

/*std::map<Student, string, compare> subject_students_list;
struct compare
{
    bool operator()(const Student &a, const Student &b) const
    {
        if (a.student_ID == b.student_ID)
        {
            return a.student_ID < b.student_ID;
        }
        return a.student_ID < b.student_ID;
    }
};
*/
class Student
{

public:
    string student_name;
    string student_ID;
    friend class Admin;
    friend class BITS;

    void DisplayMarks(string student_ID);

    void printChoicesStudent()
    {
        cout << "Please enter one of the following choices:\n";
        cout << "1:- Display marks of a student \n";
        cout << "2:- Exit \n";
    }
    std::map<string, double> courses;
};
class BITS
{
public:
    friend class Admin;
    void DisplayStudentMarks(string student_ID)
    {
        if (registered_students.find(student_ID) != registered_students.end())
        {
            Student s = registered_students[student_ID];
            cout << "Name of the student : " << s.student_name << endl;
            cout << "Student ID : " << s.student_ID << endl;
            cout << "List of courses taken by the student and the marks scored " << endl;
            for (auto itr : s.courses)
            {
                cout << itr.first << " " << itr.second << endl;
            }
        }
        else
            cout << "Invalid Student ID" << endl;
    }

private:
    std::map<string, Student> registered_students;
    std::map<string, Student> admin;
    std::map<string, Subject> registered_courses;
};

BITS master;
class Subject
{
public:
    string subject_name;
    string subject_ID;
    friend class Admin;
    friend class BITS;

private:
    map<string, pair<Student, string>> subject_students_list; // student container in a subject
};

class Admin
{
public:
    string faculty_name;
    string faculty_department;

    void addStudent()
    {
        Student s;
        int user_response;
        cout << "Enter Name of the Student" << endl;
        cin >> s.student_name;
        cout << "Enter Student ID" << endl;
        cin >> s.student_ID;
        int flag_for_subjects = 1;
        while (flag_for_subjects)
        {
            cout << "Input Course Code" << endl;
            string course_code;
            cin >> course_code;
            transform(course_code.begin(), course_code.end(), course_code.begin(), ::toupper);
            cout << "Enter Marks" << endl;
            double marks;
            cin >> marks;
            s.courses[course_code] = marks;
            cout << "Do you wish to add more subjects? 1. Yes 2. Exit" << endl;
            cin >> user_response;
            if (user_response == 1)
                continue;
            else
                break;
        }
        master.registered_students[s.student_ID] = s;
    }
    void addStudentsToCourse(){
        int user_response;
        int flag_for_subjects = 1;
        cout << "Input course code \n";
        string course_ID_response;
        cin >> course_ID_response;
        auto itrz =  master.registered_courses.find(course_ID_response);
        Subject s = itrz->second;
        while (flag_for_subjects)
        {
            cout << "Do you want to add students to the course? \n";
            cout << "1. Add student \n";
            cout << "2. Exit \n";
            cin >> user_response;
            if (user_response == 2)
                break;
            while (user_response != 2)
            {
                cout << "Enter student ID \n";
                string student_ID;
                cin >> student_ID;
                if (master.registered_students.find(student_ID) != master.registered_students.end())
                {
                    cout << "Enter Marks" << endl;
                    double marks;
                    cin >> marks;
                    s.subject_students_list[student_ID].second = marks;
                    cout << "Do you wish to add more students? 1. Yes 2. Exit" << endl;
                    cin >> user_response;
                    if (user_response == 1)
                        continue;
                    else
                        break;
                }
                else
                    cout << "Invalid student ID \n";
                break;
            }
        }
    }
    void addSubject()
    {
        int user_response;
        string subject_name_response;
        string subject_ID_response;
        cout << "Enter Name of the Subject" << endl;
        cin >> subject_name_response;
        cout << "Enter Subject ID" << endl;
        cin >> subject_ID_response;
        Subject s;
        s.subject_name = subject_name_response;
        s.subject_ID = subject_ID_response;
        int flag_for_subjects = 1;
        while (flag_for_subjects)
        {
            cout << "Do you want to add students to the course? \n";
            cout << "1. Add student \n";
            cout << "2. Exit \n";
            cin >> user_response;
            if (user_response == 2)
                break;
            while (user_response != 2)
            {
                cout << "Enter student ID \n";
                string student_ID;
                cin >> student_ID;
                if (master.registered_students.find(student_ID) != master.registered_students.end())
                {
                    cout << "Enter Marks" << endl;
                    double marks;
                    cin >> marks;
                    s.subject_students_list[student_ID].second = marks;
                    cout << "Do you wish to add more students? 1. Yes 2. Exit" << endl;
                    cin >> user_response;
                    if (user_response == 1)
                        continue;
                    else
                        break;
                }
                else
                    cout << "Invalid student ID \n";
                break;
            }
        }
        master.registered_courses[s.subject_ID] = s;
    }

    void DisplayStudentMarks()
    {
        string student_ID;
        cout << "Enter Student_ID for which marks need to be displayed \n";
        cin >> student_ID;
        if (master.registered_students.find(student_ID) != master.registered_students.end())
        {
            Student s = master.registered_students[student_ID];
            cout << "Name of the student : " << s.student_name << endl;
            cout << "Student ID : " << s.student_ID << endl;
            cout << "List of courses taken by the student and the marks scored " << endl;
            for (auto itr : s.courses)
            {
                cout << itr.first << " " << itr.second << endl;
            }
        }
        else
            cout << "Invalid Student ID" << endl;
    }

    void DisplayCourseDetails()
    {
        string course_code;
        cout << "Enter the course code to be viewed \n";
        cin >> course_code;
        Subject s = master.registered_courses[course_code];
        cout << "Student Name and Marks scored" << endl;
        int number_of_students_registered = 0;
        double total_marks_scored = 0;
        Student max_marks_student;
        int max_marks = 0;
        /* for (auto itr : s.subject_students_list)
        {
            cout << itr.first << " " << itr.second.second << endl;
            number_of_students_registered++;
            total_marks_scored += stoi(itr.second.second);
            if (max_marks > stoi(itr.second.second)){
                max_marks=stoi(itr.second.second);
                max_marks_student=itr.second.first;
            }
        } */
        if (number_of_students_registered == 0)
        {
            cout << "No students registered in this course" << endl;
        }
        else
        {
            cout << "The average marks scored in the course " << course_code << " is " << (total_marks_scored / number_of_students_registered) << endl;
            cout << "Maximum scoring student is " << max_marks_student.student_name << " scoring " << max_marks << endl;
        }
    }

    void DeleteCourses()
    {
        string student_ID, course_code;
        cout << "Input student ID and the course to be dropped \n";
        cin >> student_ID;
        cin >> course_code;
        if (master.registered_students.find(student_ID) != master.registered_students.end())
        {
            Student s = master.registered_students[student_ID];
            s.courses.erase(course_code);
            cout << "Course successfully deleted" << endl;
        }
        else
            cout << "Invalid Student ID" << endl;
    }

    void DeleteStudentRecord()
    {
        string student_ID;
        cout << "Enter the student ID to be removed from the records \n";
        cin >> student_ID;
        if (master.registered_students.find(student_ID) != master.registered_students.end())
        {
            master.registered_students.erase(student_ID);
            cout << "Student record successfully deleted \n";
        }
        else
            cout << "Invalid Student ID" << endl;
    }

    void printChoicesAdmin()
    {
        cout << "Please enter one of the following choices:\n";
        cout << "1:- Add a new student \n";
        cout << "2:- Add a new course \n";
        cout << "3:- Display marks for one student \n";
        cout << "4:- Display marks of all students registered in a course \n";
        cout << "5:- Drop a registered course \n";
        cout << "6:- Remove a student record from the database \n";
        cout << "7:- Edit a student's marks \n";
        cout << "8:- Exit \n";
    }
};

void Student::DisplayMarks(string student_ID_to_be_viewed)
{
    master.DisplayStudentMarks(student_ID_to_be_viewed);
}

Student student_obj;
Admin master_admin;

string admin_access_key = "admin";
map<string, string> admin_list;
map<string, string> student_list;

void authentication();

int existingUser(string username, string password)
{
    int username_length = (int)username.length();
    if (username.substr(username_length - 5) == "admin")
    {
        if (admin_list.find(username) == admin_list.end() || admin_list[username] != password)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if (username.substr(username_length - 7) == "student")
    {
        if (student_list.find(username) == student_list.end() || student_list[username] != password)
        {
            return 0;
        }
        else
        {
            return 2;
        }
    }
}

void successfulStudentLogin()
{
    student_obj.printChoicesStudent();
    int student_input_choice = 1;
    while (student_input_choice != 2)
    {
        cin >> student_input_choice;
        switch (student_input_choice)
        {
        case 1:
        {
            cout << "Displaying the menu for student" << endl;
            string student_ID_to_be_viewed;
            cout << "Enter the student_ID_to_be_viewed" << endl;
            cin >> student_ID_to_be_viewed;
            student_obj.DisplayMarks(student_ID_to_be_viewed);
            break;
        }
        case 2:
        {
            cout << "Exiting the menu" << endl;
            break;
        }
        default:
        {
            cout << "Invalid Choice" << endl;
            break;
        }
        }
    }
}

void successfulAdminLogin()
{
    master_admin.printChoicesAdmin();
    int admin_input_choice = 1;
    while (admin_input_choice != 8)
    {
        cin >> admin_input_choice;
        switch (admin_input_choice)
        {
        case 1:
        {
            cout << "Add a new student in the database" << endl;
            master_admin.addStudent();
            master_admin.printChoicesAdmin();
            break;
        }
        case 2:
        {
            cout << "Add a new course to the database" << endl;
            master_admin.addSubject();
            master_admin.printChoicesAdmin();
        }
        case 3:
        {
            cout << "Displaying marks for a given student \n";
            master_admin.DisplayStudentMarks();
            master_admin.printChoicesAdmin();
            break;
        }
        case 4:
        {
            cout << "Displaying marks of all students registered in a course \n";
            master_admin.DisplayCourseDetails();
            master_admin.printChoicesAdmin();
            break;
        }
        case 5:
        {
            cout << "Dropping a registered course \n";
            master_admin.DeleteCourses();
            master_admin.printChoicesAdmin();
            break;
        }
        case 6:
        {
            cout << "Removing a student record from the database \n";
            master_admin.DeleteStudentRecord();
            master_admin.printChoicesAdmin();
            break;
        }
        case 7:
        {
            cout << "Editing a student's marks";
            cout << "Enter student ID";
            string student_ID;
            cin >> student_ID;
            cout << "Enter course ID";
            string course_ID;
            cin >> course_ID;
            cout << "Enter new marks";
            int marks;
            cin >> marks;
        }
        case 8:
        {
            cout << "Exiting the menu \n";
            break;
        }
        case 9:
        {
            cout << "Adding students to a course \n";
            
        }
        default:
        {
            cout << "Invalid Input" << endl;
            master_admin.printChoicesAdmin();
            break;
        }
        }
    }
}
bool createAdminAccount()
{
    string username, password;
    int user_response;
    int account_choice = 1;
    while (account_choice)
    {
        cout << "Create a username" << endl;
        cout << "Admin user account name must end with @admin\n";
        cin >> username;
        cout << "Create a password" << endl;
        cin >> password;
        if (admin_list.find(username) == admin_list.end())
        {
            admin_list[username] = password;
            cout << "New Admin account successfully created" << endl;
            return true;
        }
        else
        {
            cout << "Username already exists" << endl;
            cout << "Choose: 1: Enter a new username 2: Exit" << endl;
            cin >> user_response;
            if (user_response == 1)
                continue;
            else
                return false;
        }
    }
}
void authentication()
{
    int choice_status = 1;
    int user_response;
    while (choice_status)
    {
        int user_account_status_choice;
        string username, password;
        cout << "Choose account status choice : 1. Existing user 2. New user 3. Exit program \n";
        cin >> user_account_status_choice;

        // Check for exsiting user

        if (user_account_status_choice == 1)
        {
            cout << "You are an Existing user\n";
            cout << "Enter your username" << endl;
            cin >> username;
            cout << "Enter your password" << endl;
            cin >> password;
            int login_status = existingUser(username, password);
            if (login_status == 0)
            {
                cout << "Invalid username or password" << endl;
            }
            else if (login_status == 1)
            {
                cout << "successful admin login" << endl;
                // Display admin menu
                successfulAdminLogin();
            }
            else if (login_status == 2)
            {
                cout << "successful student login" << endl;
                // Display student menu
                successfulStudentLogin();
            }
        }
        // Create A new user
        else if (user_account_status_choice == 2)
        {
            bool account_creation_status;
            cout << "Creating a new user" << endl;
            cout << "Creating an Admin account" << endl;
            cout << "Input the admin access key to create a Admin account" << endl;
            string input_admin_access_key;
            cin >> input_admin_access_key;
            if (input_admin_access_key == admin_access_key)
            {
                cout << "You are eligible to create an admin account" << endl;
                account_creation_status = createAdminAccount();
                if (account_creation_status)
                {
                    // Display menu for admin menu
                    successfulAdminLogin();
                }
                else
                {
                    cout << "Account Creation failed" << endl;
                }
            }
            else
            {
                cout << "You do not have the access to create an admin account" << endl;
            }
        }
        else if (user_account_status_choice == 3)
        {
            cout << "Exit program \n";
            break;
        }
        else
        {
            cout << "Invalid user account status choice" << endl;
            cout << "Do you wish to re-enter user account status? \n 1.yes 2. Exit" << endl;
            cin >> user_response;
            if (user_response == 1)
                continue;
            else
            {
                cout << "Exiting the program" << endl;
                break;
            }
        }
    }
};
int main()
{
    authentication();
};
