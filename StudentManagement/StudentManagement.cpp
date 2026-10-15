#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
// Nasser Khaled Nasser ALsaiyli
// CS
const string StudentsFileName = "Students.txt";

struct stSubject
{
    string SubjectNmae = "";
    float Mark = 0;
};
struct stStudent
{
    int ID = 0;
    string StudentName = "";
    string Dept = "";
    short Level = 0;
    stSubject Subject[2];
    bool MarkForDelete = false;
};
enum enManageStudentsMenueOptions
{
    eListStudents = 1,eAddNewStudent = 2, eDeleteStudent = 3,
    eUpdateStudent = 4, eFindStudent = 5,eMainMenue = 6
};

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short Pos = 0;
    string sWord = "";

    while ((Pos = S1.find(Delim)) != string::npos)
    {
        sWord = S1.substr(0, Pos);

        if (sWord != "")
            vString.push_back(sWord);

        S1.erase(0, Pos + Delim.length());
    }

    if (S1 != "")
        vString.push_back(S1);

    return vString;
}
stStudent ConvertStudentLineToRecord(string Line, string Separator = "#//#")
{
    stStudent Student;
    vector<string> vStudentData = SplitString(Line, Separator);

    if (vStudentData.size() < 8)
        return Student;

    Student.StudentName = vStudentData[0];
    Student.ID = stoi(vStudentData[1]);
    Student.Dept = vStudentData[2];
    Student.Level = stoi(vStudentData[3]);

    for (short i = 0; i < 2; i++)
    {
        Student.Subject[i].SubjectNmae = vStudentData[4 + (i * 2)];
        Student.Subject[i].Mark = stof(vStudentData[5 + (i * 2)]);
    }

    return Student;
}
string ConvertRecordToLine(stStudent Student, string Separator = "#//#")
{
    string Line;

    Line += Student.StudentName + Separator;
    Line += to_string(Student.ID) + Separator;
    Line += Student.Dept + Separator;
    Line += to_string(Student.Level);

    for (short i = 0; i < 2; i++)
    {
        Line += Separator;
        Line += Student.Subject[i].SubjectNmae;
        Line += Separator;
        Line += to_string(Student.Subject[i].Mark);
    }

    return Line;
}
vector<stStudent> LoadStudentDataFromFile(string FileName)
{
    vector<stStudent> vStudents;
    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;

        while (getline(MyFile, Line))
        {
            if (Line.empty())
                continue;

            stStudent Student = ConvertStudentLineToRecord(Line);

            if (Student.ID != 0)
                vStudents.push_back(Student);
        }

        MyFile.close();
    }

    return vStudents;
}
void SaveStudentDataToFile(string FileName, vector<stStudent> vStudents)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (stStudent Student : vStudents)
        {
            if (!Student.MarkForDelete)
                MyFile << ConvertRecordToLine(Student) << endl;
        }

        MyFile.close();
    }
}
bool FindStudentByID(int ID, vector<stStudent> vStudents, stStudent& Student)
{
    for (stStudent S : vStudents)
    {
        if (S.ID == ID)
        {
            Student = S;
            return true;
        }
    }

    return false;
}
void PrintStudentCard(stStudent Student)
{
    cout << "\n---------------------------------------------\n";
    cout << "Student ID   : " << Student.ID << endl;
    cout << "Student Name : " << Student.StudentName << endl;
    cout << "Department   : " << Student.Dept << endl;
    cout << "Level        : " << Student.Level << endl;

    for (short i = 0; i < 2; i++)
    {
        cout << "Subject " << i + 1 << "    : " << Student.Subject[i].SubjectNmae << endl;
        cout << "Mark         : " << Student.Subject[i].Mark << endl;
    }

    cout << "---------------------------------------------\n";
}
void PrintStudentRecordLine(stStudent Student)
{
     cout << "| " << setw(10) << left << Student.ID;
    cout << "| " << setw(35) << left << Student.StudentName;
    cout << "| " << setw(12) << left << Student.Dept;
    cout << "| " << setw(7) << left << Student.Level;
    cout << "| " << setw(25) << left << Student.Subject[0].SubjectNmae;
    cout << "| " << setw(25) << left << Student.Subject[1].SubjectNmae;
    cout << "|\n";

    cout << "| " << setw(10) << left << "";
    cout << "| " << setw(35) << left << "";
    cout << "| " << setw(12) << left << "";
    cout << "| " << setw(7) << left << "";
    cout << "| " << setw(25) << left << Student.Subject[0].Mark;
    cout << "| " << setw(25) << left << Student.Subject[1].Mark;
    cout << "|\n";
}
void ShowAllStudentsScreen()
{
    vector<stStudent> vStudents = LoadStudentDataFromFile(StudentsFileName);

    cout << "\n\t\t\t\t\tStudent List (" << vStudents.size() << ") Student(s).\n";

    cout << "-----------------------------------------------------------------------------------------------------------------------------\n";

    cout << "| " << setw(10) << left << "ID";
    cout << "| " << setw(35) << left << "Student Name";
    cout << "| " << setw(12) << left << "Dept";
    cout << "| " << setw(7) << left << "Level";
    cout << "| " << setw(25) << left << "Subject 1";
    cout << "| " << setw(25) << left << "Subject 2";
    cout << "|\n";

    cout << "| " << setw(10) << left << "";
    cout << "| " << setw(35) << left << "";
    cout << "| " << setw(12) << left << "";
    cout << "| " << setw(7) << left << "";
    cout << "| " << setw(25) << left << "Name / Mark";
    cout << "| " << setw(25) << left << "Name / Mark";
    cout << "|\n";

    cout << "-----------------------------------------------------------------------------------------------------------------------------\n";

    if (vStudents.empty())
    {
        cout << "\t\t\tNo Students Available In The System!\n";
    }
    else
    {
        for (stStudent Student : vStudents)
        {
            PrintStudentRecordLine(Student);
            cout << "-----------------------------------------------------------------------------------------------------------------------------\n";
        }
    }
}

int ReadStudentID()
{
    int ID;

    cout << "Please Enter Student ID? ";
    cin >> ID;

    return ID;
}

stStudent ReadNewStudent()
{
    stStudent Student;

    cout << "\nPlease Enter Student ID? ";
    cin >> Student.ID;

    cout << "Please Enter Student Name? ";
    cin.ignore(1, '\n');
    getline(cin, Student.StudentName);

    cout << "Please Enter Department? ";
    getline(cin, Student.Dept);

    cout << "Please Enter Level? ";
    cin >> Student.Level;

    for (short i = 0; i < 2; i++)
    {
        cout << "Please Enter Subject Name " << i + 1 << "? ";
        getline(cin, Student.Subject[i].SubjectNmae);

        cout << "Please Enter Subject Mark " << i + 1 << "? ";
        cin >> Student.Subject[i].Mark;
    }

    return Student;
}

void AddStudent()
{
    vector<stStudent> vStudents = LoadStudentDataFromFile(StudentsFileName);
    stStudent Student = ReadNewStudent();

    stStudent TempStudent;

    if (FindStudentByID(Student.ID, vStudents, TempStudent))
    {
        cout << "\nStudent With ID [" << Student.ID << "] Already Exists!\n";
        return;
    }

    vStudents.push_back(Student);
    SaveStudentDataToFile(StudentsFileName, vStudents);

    cout << "\nStudent Added Successfully.\n";
}

void AddNewStudents()
{
    char AddMore = 'Y';

    do
    {
        cout << "\n---------------------------------------------\n";
        cout << "Add New Student\n";
        cout << "---------------------------------------------\n";

        AddStudent();

        cout << "\nDo You Want To Add More Students? Y/N? ";
        cin >> AddMore;

    } while (AddMore == 'Y' || AddMore == 'y');
}

void DeleteStudent()
{
    vector<stStudent> vStudents = LoadStudentDataFromFile(StudentsFileName);
    int ID = ReadStudentID();

    for (stStudent& Student : vStudents)
    {
        if (Student.ID == ID)
        {
            PrintStudentCard(Student);

            char Answer;

            cout << "\nAre You Sure You Want To Delete This Student? Y/N? ";
            cin >> Answer;

            if (Answer == 'Y' || Answer == 'y')
            {
                Student.MarkForDelete = true;
                SaveStudentDataToFile(StudentsFileName, vStudents);

                cout << "\nStudent Deleted Successfully.\n";
            }

            return;
        }
    }

    cout << "\nStudent With ID [" << ID << "] Not Found!\n";
}

stStudent ChangeStudentRecord(int ID)
{
    stStudent Student;

    Student.ID = ID;

    cout << "Please Enter Student Name? ";
    cin.ignore(1, '\n');
    getline(cin, Student.StudentName);

    cout << "Please Enter Department? ";
    getline(cin, Student.Dept);

    cout << "Please Enter Level? ";
    cin >> Student.Level;

    for (short i = 0; i < 2; i++)
    {
        cout << "Please Enter Subject Name " << i + 1 << "? ";
        cin >> Student.Subject[i].SubjectNmae;

        cout << "Please Enter Subject Mark " << i + 1 << "? ";
        cin >> Student.Subject[i].Mark;
    }

    return Student;
}

void UpdateStudent()
{
    vector<stStudent> vStudents = LoadStudentDataFromFile(StudentsFileName);
    int ID = ReadStudentID();

    for (stStudent& Student : vStudents)
    {
        if (Student.ID == ID)
        {
            PrintStudentCard(Student);

            char Answer;

            cout << "\nAre You Sure You Want To Update This Student? Y/N? ";
            cin >> Answer;

            if (Answer == 'Y' || Answer == 'y')
            {
                Student = ChangeStudentRecord(ID);
                SaveStudentDataToFile(StudentsFileName, vStudents);

                cout << "\nStudent Updated Successfully.\n";
            }

            return;
        }
    }

    cout << "\nStudent With ID [" << ID << "] Not Found!\n";
}

void FindStudent()
{
    vector<stStudent> vStudents = LoadStudentDataFromFile(StudentsFileName);
    int ID = ReadStudentID();

    stStudent Student;

    if (FindStudentByID(ID, vStudents, Student))
        PrintStudentCard(Student);
    else
        cout << "\nStudent With ID [" << ID << "] Not Found!\n";
}

void ShowManageStudentsMenu()
{
    cout << "\n===============================================\n";
    cout << "\t\tManage Students Menu\n";
    cout << "===============================================\n";
    cout << "\t[1] List Students.\n";
    cout << "\t[2] Add New Student.\n";
    cout << "\t[3] Delete Student.\n";
    cout << "\t[4] Update Student.\n";
    cout << "\t[5] Find Student.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "===============================================\n";
}

short ReadManageStudentsMenuOption()
{
    short Choice;

    cout << "Choose What Do You Want To Do? [1 to 6]? ";
    cin >> Choice;

    return Choice;
}

void GoBackToManageStudentsMenu()
{
    cout << "\nPress Any Key To Go Back To Manage Students Menu...";
    system("pause>0");
    ShowManageStudentsMenu();
}

void PerformManageStudentsMenuOption(enManageStudentsMenueOptions ManageStudentsMenuOption)
{
    switch (ManageStudentsMenuOption)
    {
    case eListStudents:
        system("cls");
        ShowAllStudentsScreen();
        GoBackToManageStudentsMenu();
        break;

    case eAddNewStudent:
        system("cls");
        AddNewStudents();
        GoBackToManageStudentsMenu();
        break;

    case eDeleteStudent:
        system("cls");
        DeleteStudent();
        GoBackToManageStudentsMenu();
        break;

    case eUpdateStudent:
        system("cls");
        UpdateStudent();
        GoBackToManageStudentsMenu();
        break;

    case eFindStudent:
        system("cls");
        FindStudent();
        GoBackToManageStudentsMenu();
        break;

    case eMainMenue:
        break;
    }
}

void ShowManageStudentsMenuScreen()
{
    short Choice;

    do
    {
        system("cls");

        ShowManageStudentsMenu();
        Choice = ReadManageStudentsMenuOption();

        PerformManageStudentsMenuOption((enManageStudentsMenueOptions)Choice);

    } while (Choice != eMainMenue);
}

int main()
{
    ShowManageStudentsMenuScreen();

    return 0;
}
