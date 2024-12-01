#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
using namespace std;

class Program;
class CLO;
class Course;
class PLO;
class User;
class AcademicOfficier;
class Topic;
class Evaluation;
class Questions;
class Teacher;

class CLO
{
private:
    string description;
    Topic *topics[5];
    int topicCount = 0;
    Evaluation *evaluations[5];
    int evaluationCount = 0;

public:
    CLO(string _description) : description(_description) {}

    string getDescription() const
    {
        return description;
    }

    void setDescription(string newD)
    {
        description = newD;
    }

    void addTopic(Topic *topic)
    {
        if (topicCount < 5)
        {
            topics[topicCount++] = topic;
        }
        else
        {
            cout << "Maximum number of topics reached for this CLO." << endl;
        }
    }

    void addEvaluation(Evaluation *evaluation)
    {
        if (evaluationCount < 5)
        {
            evaluations[evaluationCount++] = evaluation;
        }
        else
        {
            cout << "Maximum number of evaluations reached for this CLO." << endl;
        }
    }

    int getTopicCount() const
    {
        return topicCount;
    }

    int getEvaluationCount() const
    {
        return evaluationCount;
    }

    Topic *getTopic(int index) const
    {
        if (index >= 0 && index < topicCount)
        {
            return topics[index];
        }
        else
        {
            return nullptr;
        }
    }

    Evaluation *getEvaluation(int index) const
    {
        if (index >= 0 && index < evaluationCount)
        {
            return evaluations[index];
        }
        else
        {
            return nullptr;
        }
    }

    ~CLO() {}
};

class Course
{
private:
    string name;
    string description;
    CLO *cloPointers[5];
    int cloCount = 0;

public:
    Course(string n, string desc) : name(n), description(desc) {}

    void setName(const string &newName)
    {
        name = newName;
    }

    void setDescription(const string &newDesc)
    {
        description = newDesc;
    }

    string getName() const
    {
        return name;
    }

    string getDescription() const
    {
        return description;
    }

    bool addCLO(CLO *newCLO)
    {
        if (cloCount >= 5)
        {
            return false;
        }
        cloPointers[cloCount] = newCLO;
        cloCount++;
        return true;
    }

    void displayCLOs() const
    {
        if (cloCount == 0)
        {
            cout << "No CLOs available for this course." << endl;
            return;
        }
        cout << "List of CLOs for course '" << name << "':" << endl;
        for (int i = 0; i < cloCount; ++i)
        {
            cout << i + 1 << ". " << cloPointers[i]->getDescription() << ", ";
        }
    }

    bool updateCLO(int index, const string &newDescription)
    {
        if (index >= 0 && index < cloCount)
        {
            cloPointers[index]->setDescription(newDescription);
            return true;
        }
        return false;
    }

    bool deleteCLO(int index)
    {
        if (index >= 0 && index < cloCount)
        {
            delete cloPointers[index];
            for (int i = index; i < cloCount - 1; ++i)
            {
                cloPointers[i] = cloPointers[i + 1];
            }
            cloCount--;
            return true;
        }
        return false;
    }

    CLO *getCLO(int index) const
    {
        if (index >= 0 && index < getNumberOfCLOs())
        {
            return cloPointers[index];
        }
        return nullptr;
    }

    int getNumberOfCLOs() const
    {
        return cloCount;
    }

    void displayCLOsToFile(ofstream &outFile) const
    {
        for (int i = 0; i < cloCount; ++i)
        {
            outFile << cloPointers[i]->getDescription() << "\n";
        }
    }

    ~Course()
    {
        for (int i = 0; i < cloCount; ++i)
        {
            delete cloPointers[i];
        }
    }
};

class PLO
{
private:
    string description;
    Course *coursePointers[3];
    int courseCount = 0;

public:
    PLO(string _description) : description(_description) {}

    void setDescription(const string &newDescription)
    {
        description = newDescription;
    }

    string getDescription() const
    {
        return description;
    }

    bool addCourse(Course *newCourse)
    {
        if (courseCount >= 3)
        {
            return false;
        }
        coursePointers[courseCount] = newCourse;
        courseCount++;
        return true;
    }

    void displayCourses() const
    {
        for (int i = 0; i < courseCount; ++i)
        {
            cout << i + 1 << ". " << coursePointers[i]->getName() << ": " << coursePointers[i]->getDescription() << endl;
        }
    }

    Course *getCourse(int index) const
    {
        if (index >= 0 && index < courseCount)
        {
            return coursePointers[index];
        }
        return nullptr;
    }

    bool deleteCourse(int index)
    {
        if (index >= 0 && index < courseCount)
        {
            delete coursePointers[index];
            for (int i = index; i < courseCount - 1; ++i)
            {
                coursePointers[i] = coursePointers[i + 1];
            }
            courseCount--;
            return true;
        }
        return false;
    }

    bool updateCourse(int index, const string &newName, const string &newDescription)
    {
        if (index >= 0 && index < courseCount)
        {
            Course *course = coursePointers[index];
            if (course)
            {
                course->setName(newName);
                course->setDescription(newDescription);
                return true;
            }
        }
        return false;
    }

    int getNumberOfCourses() const
    {
        return courseCount;
    }

    void saveToFile(ofstream &outFile, ofstream &outFile1)
    {
        for (int i = 0; i < courseCount; ++i)
        {
            Course *course = coursePointers[i];
            if (course)
            {
                outFile << course->getName() << "," << course->getDescription() << "\n";
                course->displayCLOsToFile(outFile);
                outFile1 << "Courses:\n";
                outFile1 << course->getName() << "," << course->getDescription() << "\n";
                course->displayCLOsToFile(outFile1);
            }
        }
    }

    ~PLO()
    {
        for (int i = 0; i < courseCount; ++i)
        {
            delete coursePointers[i];
        }
    }
};

class Program
{
private:
    string name;
    string description;
    PLO *ploPointers[15];
    int ploCount = 0;

public:
    Program(string n, string desc) : name(n), description(desc) {}

    string getName() const
    {
        return name;
    }
    string getDescription() const
    {
        return description;
    }

    bool addPLO(PLO *newPLO)
    {
        if (ploCount >= 15)
        {
            return false;
        }
        ploPointers[ploCount] = newPLO;
        ploCount++;
        return true;
    }

    void displayPLO() const
    {
        for (int i = 0; i < ploCount; ++i)
        {
            cout << i + 1 << ". " << ploPointers[i]->getDescription() << endl;
        }
    }

    PLO *getPLO(int index) const
    {
        if (index >= 0 && index < ploCount)
        {
            return ploPointers[index];
        }
        return nullptr;
    }

    bool deletePLO(int index)
    {
        if (index >= 0 && index < ploCount)
        {
            delete ploPointers[index];
            for (int i = index; i < ploCount - 1; ++i)
            {
                ploPointers[i] = ploPointers[i + 1];
            }
            ploCount--;
            return true;
        }
        return false;
    }

    int getNumberOfPLOs() const
    {
        return ploCount;
    }

    void saveToFile(ofstream &outFile, ofstream &outFile1)
    {
        outFile << name << "," << description << endl;
        for (int i = 0; i < ploCount; ++i)
        {
            PLO *plo = ploPointers[i];
            if (plo)
            {
                outFile << "PLOs:" << endl;
                outFile << plo->getDescription() << "\n";
                plo->saveToFile(outFile, outFile1);
            }
        }
    }

    ~Program()
    {
        for (int i = 0; i < ploCount; ++i)
        {
            delete ploPointers[i];
        }
    }
};

class User
{
public:
    virtual bool login() = 0;
    virtual void display() = 0;
    virtual string getUsername() = 0;
    virtual string getPassword() = 0;
};

class AcademicOfficer : public User
{
private:
    string username;
    string password;
    Program *programPointers[10];
    int programCount = 0;
    int findProgramIndex(const string &name)
    {
        for (int i = 0; i < programCount; ++i)
        {
            if (programPointers[i]->getName() == name)
            {
                return i;
            }
        }
        return -1;
    }

public:
    AcademicOfficer() {}

    void setName(const string &n)
    {
        username = n;
    }

    string getUsername() override
    {
        return username;
    }

    string getPassword() override
    {
        return password;
    }

    bool login() override
    {
        cout << "------------------------------------" << endl;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;
        cout << "------------------------------------" << endl;
        setName(username);

        ifstream inFile("officers.txt");
        string stored_username, stored_password;
        while (getline(inFile, stored_username, ' ') && getline(inFile, stored_password))
        {
            if (stored_username == username && stored_password == password)
            {
                cout << "Login successful." << endl;
                inFile.close();
                return true;
            }
        }
        inFile.close();

        char choice;
        cout << "User not found. Do you want to sign up? (Y/N): ";
        cin >> choice;
        if (toupper(choice) == 'Y')
        {
            ofstream outFile("officers.txt", ios::app);
            outFile << username << " " << password << endl;
            outFile.close();
            cout << "Account created successfully." << endl;
        }

        return false;
    }

    void display() override
    {
        cout << "Academic Officer: " << username << endl;
    }

    void manageProgram()
    {
        int option;
        do
        {
            cout << "------------------------------------" << endl;
            cout << "Select an option:" << endl;
            cout << "0. Exit" << endl;
            cout << "1. Add Program" << endl;
            cout << "2. Display Programs" << endl;
            cout << "3. Update Program" << endl;
            cout << "4. Delete Program" << endl;
            cout << "------------------------------------" << endl;
            cout << "Enter your choice: ";
            cin >> option;

            switch (option)
            {
            case 0:
                cout << "------------------------------------" << endl;
                cout << "Exiting..." << endl;
                break;
            case 1:
            {
                if (programCount >= 10)
                {
                    cout << "Cannot add more Programs. Maximum limit reached." << endl;
                    return;
                }
                string Name, Desc;
                cout << "Enter the name of the Program: ";
                cin.ignore();
                getline(cin, Name);
                cout << "Enter the description of the Program: ";
                getline(cin, Desc);

                programPointers[programCount] = new Program(Name, Desc);
                programCount++;

                cout << "New Program added successfully: " << Name << endl;
                break;
            }
            case 2:
            {
                if (programCount == 0)
                {
                    cout << "No Programs available." << endl;
                    return;
                }
                cout << "List of Programs:" << endl;
                for (int i = 0; i < programCount; ++i)
                {
                    cout << i + 1 << ". " << programPointers[i]->getName() << " - " << programPointers[i]->getDescription() << endl;
                }
                break;
            }
            case 3:
            {
                string oldName, newName, newDesc;
                cin.ignore();
                cout << "Enter the description of the Program you want to update: ";
                getline(cin, oldName);

                int index = findProgramIndex(oldName);
                if (index != -1)
                {
                    cout << "Enter the new Name for the Program: ";
                    getline(cin, newName);
                    cout << "Enter the new description for the Program: ";
                    getline(cin, newDesc);

                    programPointers[index] = new Program(newName, newDesc);
                    cout << "Program updated successfully. Old Name: " << oldName << ", New Name: " << newName << endl;
                }
                else
                {
                    cout << "Program not found: " << oldName << endl;
                }
                break;
            }
            case 4:
            {
                string name;
                cin.ignore();
                cout << "Enter the name of the Program you want to delete: ";
                getline(cin, name);

                int index = findProgramIndex(name);
                if (index != -1)
                {
                    delete programPointers[index];
                    for (int i = index; i < programCount - 1; ++i)
                    {
                        programPointers[i] = programPointers[i + 1];
                    }
                    programCount--;
                    cout << "Program deleted successfully: " << name << endl;
                }
                else
                {
                    cout << "Program not found: " << name << endl;
                }
                break;
            }
            default:
                cout << "Invalid option." << endl;
                break;
            }
        } while (option != 0);
    }

    void managePLO()
    {
        if (programCount == 0)
        {
            cout << "No Program available. Please add Programs first." << endl;
            return;
        }
        string programName;
        cout << "Enter the name of the Program where you want to add the PLO: ";
        cin.ignore();
        getline(cin, programName);

        int programIndex = findProgramIndex(programName);
        if (programIndex != -1)
        {
            int option;
            do
            {
                cout << "------------------------------------" << endl;
                cout << "Select an option:" << endl;
                cout << "0. Exit" << endl;
                cout << "1. Add PLO" << endl;
                cout << "2. Display PLOs" << endl;
                cout << "3. Update PLO" << endl;
                cout << "4. Delete PLO" << endl;
                cout << "------------------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> option;

                switch (option)
                {
                case 0:
                    cout << "Exiting..." << endl;
                    break;
                case 1:
                {
                    string Desc;
                    cout << "Enter the description of the PLO: ";
                    cin.ignore();
                    getline(cin, Desc);

                    PLO *newPLO = new PLO(Desc);

                    if (programPointers[programIndex]->addPLO(newPLO))
                    {
                        cout << "PLO Added successfully: " << newPLO->getDescription() << endl;
                    }
                    else
                    {
                        cout << "Failed to add PLO. Maximum limit reached for Program: " << programName << endl;
                        delete newPLO;
                    }
                    break;
                }
                case 2:
                {
                    if (programPointers[programIndex]->getNumberOfPLOs() > 0)
                    {
                        cout << "PLOs in Program '" << programName << "':" << endl;
                        programPointers[programIndex]->displayPLO();
                    }
                    else
                    {
                        cout << "No PLOs found in Program '" << programName << "'." << endl;
                    }
                    break;
                }
                case 3:
                {
                    if (programPointers[programIndex]->getNumberOfPLOs() > 0)
                    {
                        cout << "Select a PLO to update from the following:" << endl;
                        programPointers[programIndex]->displayPLO();
                        int PLOchoice;
                        cout << "Enter the PLO number: ";
                        cin >> PLOchoice;
                        PLOchoice--;

                        if (PLOchoice >= 0 && PLOchoice < programPointers[programIndex]->getNumberOfPLOs())
                        {
                            string newDesc;
                            cin.ignore();
                            cout << "Enter the new description for the PLO: ";
                            getline(cin, newDesc);

                            programPointers[programIndex]->getPLO(PLOchoice)->setDescription(newDesc);
                            cout << "PLO updated successfully." << endl;
                        }
                        else
                        {
                            cout << "Invalid PLO number." << endl;
                        }
                    }
                    else
                    {
                        cout << "There are no PLO in Program '" << programName << "'." << endl;
                    }
                    break;
                }
                case 4:
                {
                    if (programPointers[programIndex]->getNumberOfPLOs() > 0)
                    {
                        cout << "Select a PLO to delete from the following:" << endl;
                        for (int i = 0; i < programPointers[programIndex]->getNumberOfPLOs(); ++i)
                        {
                            PLO *currentPLO = programPointers[programIndex]->getPLO(i);
                            if (currentPLO)
                            {
                                cout << i + 1 << ". " << currentPLO->getDescription() << endl;
                            }
                        }
                        int PLOchoise;
                        cout << "Enter the PLO number: ";
                        cin >> PLOchoise;
                        PLOchoise--;

                        if (PLOchoise >= 0 && PLOchoise < programPointers[programIndex]->getNumberOfPLOs())
                        {
                            PLO *selectedPLO = programPointers[programIndex]->getPLO(PLOchoise);
                            if (selectedPLO)
                            {
                                if (programPointers[programIndex]->getPLO(PLOchoise))
                                {
                                    delete programPointers[programIndex]->getPLO(PLOchoise);
                                    programPointers[programIndex]->deletePLO(PLOchoise);
                                    cout << "PLO deleted successfully." << endl;
                                }
                                else
                                {
                                    cout << "Failed to delete PLO." << endl;
                                }
                            }
                            else
                            {
                                cout << "PLO not found." << endl;
                            }
                        }
                        else
                        {
                            cout << "Invalid PLO number." << endl;
                        }
                    }
                    else
                    {
                        cout << "There are no PLO in Program '" << programName << "'." << endl;
                    }
                    break;
                }
                default:
                    cout << "Invalid option." << endl;
                    break;
                }
            } while (option != 0);
        }
        else
        {
            cout << "Program not found: " << programName << endl;
        }
    }

    void manageCourse()
    {
        string programName;
        cout << "Enter the Name of the Program containing the PLO: ";
        cin.ignore();
        getline(cin, programName);

        int programIndex = findProgramIndex(programName);
        if (programIndex != -1)
        {
            if (programPointers[programIndex]->getNumberOfPLOs() > 0)
            {
                cout << "Select a PLO from the following:" << endl;
                for (int i = 0; i < programPointers[programIndex]->getNumberOfPLOs(); ++i)
                {
                    PLO *currentPLO = programPointers[programIndex]->getPLO(i);
                    if (currentPLO)
                    {
                        cout << i + 1 << ". " << currentPLO->getDescription() << endl;
                    }
                }
                int PLOchoice;
                cout << "Enter the PLO number: ";
                cin >> PLOchoice;
                PLOchoice--;

                if (PLOchoice >= 0 && PLOchoice < programPointers[programIndex]->getNumberOfPLOs())
                {
                    PLO *selectedPLO = programPointers[programIndex]->getPLO(PLOchoice);
                    if (selectedPLO)
                    {
                        int option;
                        do
                        {
                            cout << "Selected Course: " << selectedPLO->getDescription() << endl;
                            cout << "------------------------------------" << endl;
                            cout << "Select an option:" << endl;
                            cout << "0. Exit" << endl;
                            cout << "1. Add Course" << endl;
                            cout << "2. Display Courses" << endl;
                            cout << "3. Update Course" << endl;
                            cout << "4. Delete Course" << endl;
                            cout << "------------------------------------" << endl;
                            cout << "Enter your choice: ";
                            cin >> option;

                            switch (option)
                            {
                            case 0:
                                cout << "Exiting..." << endl;
                                break;
                            case 1:
                            {
                                string courseName, courseDesc;
                                cout << "Enter the Name of the Course: ";
                                cin.ignore();
                                getline(cin, courseName);
                                cout << "Enter the description of the Course: ";
                                getline(cin, courseDesc);
                                if (selectedPLO->getNumberOfCourses() < 5)
                                {
                                    cout << selectedPLO->getNumberOfCourses() << endl;
                                    selectedPLO->addCourse(new Course(courseName, courseDesc));
                                    cout << "Course Added successfully: " << selectedPLO->getDescription() << endl;
                                }
                                else
                                {
                                    cout << "Cannot add more then 3 courses to a PLO." << endl;
                                }
                                break;
                            }
                            case 2:
                                selectedPLO->displayCourses();
                                break;
                            case 3:
                            {
                                int courseIndex;
                                cout << "Enter the index of the Course you want to update: ";
                                cin >> courseIndex;
                                courseIndex--;
                                if (courseIndex >= 0 && courseIndex < selectedPLO->getNumberOfCourses())
                                {
                                    string newName, newDesc;
                                    cout << "Enter the new name for the Course: ";
                                    cin.ignore();
                                    getline(cin, newName);
                                    cout << "Enter the new description for the Course: ";
                                    getline(cin, newDesc);
                                    if (selectedPLO->updateCourse(courseIndex, newName, newDesc))
                                    {
                                        cout << "Course updated successfully." << endl;
                                    }
                                    else
                                    {
                                        cout << "Failed to update Course." << endl;
                                    }
                                }
                                else
                                {
                                    cout << "Invalid Course index." << endl;
                                }
                                break;
                            }
                            case 4:
                            {
                                int courseIndex;
                                cout << "Enter the index of the Course you want to delete: ";
                                cin >> courseIndex;
                                courseIndex--;
                                if (courseIndex >= 0 && courseIndex < selectedPLO->getNumberOfCourses())
                                {
                                    if (selectedPLO->deleteCourse(courseIndex))
                                    {
                                        cout << "Course deleted successfully." << endl;
                                    }
                                    else
                                    {
                                        cout << "Failed to delete Course." << endl;
                                    }
                                }
                                else
                                {
                                    cout << "Invalid Course index." << endl;
                                }
                                break;
                            }
                            default:
                                cout << "Invalid option." << endl;
                                break;
                            }
                        } while (option != 0);
                    }
                    else
                    {
                        cout << "PLO not found." << endl;
                    }
                }
                else
                {
                    cout << "Invalid PLO number." << endl;
                }
            }
            else
            {
                cout << "There are no PLO in Program '" << programName << "'." << endl;
            }
        }
        else
        {
            cout << "Program not found: " << programName << endl;
        }
    }

    void manageCLO()
    {
        string programName;
        cout << "Enter the name of the Program containing the PLO: ";
        cin.ignore();
        getline(cin, programName);

        int programIndex = findProgramIndex(programName);
        if (programIndex != -1)
        {
            if (programPointers[programIndex]->getNumberOfPLOs() > 0)
            {
                cout << "Select a PLO from the following:" << endl;
                for (int i = 0; i < programPointers[programIndex]->getNumberOfPLOs(); ++i)
                {
                    PLO *currentPLO = programPointers[programIndex]->getPLO(i);
                    if (currentPLO)
                    {
                        cout << i + 1 << ". " << currentPLO->getDescription() << endl;
                    }
                }
                int PLOchoice;
                cout << "Enter the PLO number: ";
                cin >> PLOchoice;
                PLOchoice--;

                if (PLOchoice >= 0 && PLOchoice < programPointers[programIndex]->getNumberOfPLOs())
                {
                    PLO *selectedPLO = programPointers[programIndex]->getPLO(PLOchoice);
                    if (selectedPLO)
                    {
                        int courseChoice;
                        cout << "Select a Course to manage CLO:" << endl;
                        selectedPLO->displayCourses();
                        cout << "Enter the Course number: ";
                        cin >> courseChoice;
                        courseChoice--;

                        if (courseChoice >= 0 && courseChoice < selectedPLO->getNumberOfCourses())
                        {
                            Course *selectedCourse = selectedPLO->getCourse(courseChoice);
                            if (selectedCourse)
                            {
                                int option;
                                do
                                {
                                    cout << "Selected Course: " << selectedCourse->getName() << endl;
                                    cout << "------------------------------------" << endl;
                                    cout << "Select an option:" << endl;
                                    cout << "0. Exit" << endl;
                                    cout << "1. Add CLO" << endl;
                                    cout << "2. Display CLOs" << endl;
                                    cout << "3. Update CLO" << endl;
                                    cout << "4. Delete CLO" << endl;
                                    cout << "------------------------------------" << endl;
                                    cout << "Enter your choice: ";
                                    cin >> option;

                                    switch (option)
                                    {
                                    case 0:
                                        cout << "Exiting..." << endl;
                                        break;
                                    case 1:
                                    {
                                        string cloDesc;
                                        cout << "Enter the description of the CLO: ";
                                        cin.ignore();
                                        getline(cin, cloDesc);
                                        if (selectedCourse->getNumberOfCLOs() < 5)
                                        {
                                            selectedCourse->addCLO(new CLO(cloDesc));
                                            cout << "CLO Added successfully: " << cloDesc << endl;
                                        }
                                        else
                                        {
                                            cout << "Cannot add more than 5 CLOs to a course." << endl;
                                        }
                                        break;
                                    }
                                    case 2:
                                        selectedCourse->displayCLOs();
                                        break;
                                    case 3:
                                    {
                                        int cloIndex;
                                        cout << "Enter the index of the CLO you want to update: ";
                                        cin >> cloIndex;
                                        cloIndex--;
                                        if (cloIndex >= 0 && cloIndex < selectedCourse->getNumberOfCLOs())
                                        {
                                            string newDesc;
                                            cout << "Enter the new description for the CLO: ";
                                            cin.ignore();
                                            getline(cin, newDesc);
                                            if (selectedCourse->updateCLO(cloIndex, newDesc))
                                            {
                                                cout << "CLO updated successfully." << endl;
                                            }
                                            else
                                            {
                                                cout << "Failed to update CLO." << endl;
                                            }
                                        }
                                        else
                                        {
                                            cout << "Invalid CLO index." << endl;
                                        }
                                        break;
                                    }
                                    case 4:
                                    {
                                        int cloIndex;
                                        cout << "Enter the index of the CLO you want to delete: ";
                                        cin >> cloIndex;
                                        cloIndex--;
                                        if (cloIndex >= 0 && cloIndex < selectedCourse->getNumberOfCLOs())
                                        {
                                            if (selectedCourse->deleteCLO(cloIndex))
                                            {
                                                cout << "CLO deleted successfully." << endl;
                                            }
                                            else
                                            {
                                                cout << "Failed to delete CLO." << endl;
                                            }
                                        }
                                        else
                                        {
                                            cout << "Invalid CLO index." << endl;
                                        }
                                        break;
                                    }
                                    default:
                                        cout << "Invalid option." << endl;
                                        break;
                                    }
                                } while (option != 0);
                            }
                            else
                            {
                                cout << "Course not found." << endl;
                            }
                        }
                        else
                        {
                            cout << "Invalid Course number." << endl;
                        }
                    }
                    else
                    {
                        cout << "PLO not found." << endl;
                    }
                }
                else
                {
                    cout << "Invalid PLO number." << endl;
                }
            }
            else
            {
                cout << "There are no PLOs in Program '" << programName << "'." << endl;
            }
        }
        else
        {
            cout << "Program not found: " << programName << endl;
        }
    }

    void generateCourseListForPLO()
    {
        string programName;
        cout << "------------------------------------" << endl;
        cout << "Enter the Name of the Program containing the PLO: ";
        cin.ignore();
        getline(cin, programName);

        int programIndex = findProgramIndex(programName);
        if (programIndex != -1)
        {
            if (programPointers[programIndex]->getNumberOfPLOs() > 0)
            {
                cout << "Select a PLO from the following:" << endl;
                for (int i = 0; i < programPointers[programIndex]->getNumberOfPLOs(); ++i)
                {
                    PLO *currentPLO = programPointers[programIndex]->getPLO(i);
                    if (currentPLO)
                    {
                        cout << i + 1 << ". " << currentPLO->getDescription() << endl;
                    }
                }
                int PLOchoice;
                cout << "Enter the PLO number: ";
                cin >> PLOchoice;
                PLOchoice--;

                if (PLOchoice >= 0 && PLOchoice < programPointers[programIndex]->getNumberOfPLOs())
                {
                    PLO *selectedPLO = programPointers[programIndex]->getPLO(PLOchoice);
                    if (selectedPLO)
                    {
                        selectedPLO->displayCourses();
                    }
                }
            }
        }
    }

    void saveToFile(const string &filename, const string &filename1)
    {
        ofstream outFile(filename);
        ofstream outFile1(filename1);
        if (outFile.is_open() && outFile1.is_open())
        {
            for (int i = 0; i < programCount; ++i)
            {
                outFile << "Programs:\n";
                programPointers[i]->saveToFile(outFile, outFile1);
            }
            cout << "Save Data to file Successfully." << endl;
            outFile1.close();
            outFile.close();
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }

    void loadDataFromFile(const string &filename)
    {
        ifstream inFile(filename);
        if (inFile.is_open())
        {
            string line;
            Program *currentProgram = nullptr;
            PLO *currentPLO = nullptr;
            Course *currentCourse = nullptr;

            while (getline(inFile, line))
            {
                if (line == "Programs:")
                {
                    currentProgram = nullptr;
                    currentPLO = nullptr;
                    currentCourse = nullptr;
                    continue;
                }

                if (line.empty())
                {
                    continue;
                }

                if (currentProgram == nullptr)
                {
                    char commaPos = line.find(",");
                    string programName = line.substr(0, commaPos);
                    string programDesc = line.substr(commaPos + 1);
                    currentProgram = new Program(programName, programDesc);
                    addProgram(currentProgram);
                }
                else
                {
                    if (line == "PLOs:")
                    {
                        currentPLO = nullptr;
                        continue;
                    }
                    else if (currentPLO == nullptr)
                    {
                        currentPLO = new PLO(line);
                        currentProgram->addPLO(currentPLO);
                    }
                    else if (line.find(",") != string::npos)
                    {
                        char commaPos = line.find(",");
                        string courseName = line.substr(0, commaPos);
                        string courseDesc = line.substr(commaPos + 1);
                        currentCourse = new Course(courseName, courseDesc);
                        currentPLO->addCourse(currentCourse);
                    }
                    else
                    {
                        currentCourse->addCLO(new CLO(line));
                    }
                }
            }
            cout << "Load Data from file Successfully." << endl;
            inFile.close();
        }
        else
        {
            cout << "Error: Unable to open file for reading." << endl;
        }
    }

    void addProgram(Program *program)
    {
        if (programCount < 10)
        {
            programPointers[programCount] = program;
            programCount++;
        }
        else
        {
            cout << "Cannot add more Programs. Maximum limit reached." << endl;
        }
    }

    ~AcademicOfficer()
    {
        for (int i = 0; i < programCount; ++i)
        {
            delete programPointers[i];
        }
    }
};

class Topic
{
private:
    string description;

public:
    Topic(const string &desc) : description(desc) {}

    string getDescription() const
    {
        return description;
    }
};

class Question
{
private:
    string description;
    double marks;

public:
    Question(const string &desc, const double &m) : description(desc), marks(m) {}

    string getDescription() const
    {
        return description;
    }

    double getMarks() const
    {
        return marks;
    }
};

class Evaluation
{
private:
    string description;
    Question *questions[10];
    CLO *cloTested[5];
    int questionCount;
    int cloCount;

public:
    Evaluation(const string &desc) : description(desc), questionCount(0), cloCount(0) {}

    string getDescription() const
    {
        return description;
    }

    void addCLO(CLO *clo)
    {
        if (cloCount < 5)
        {
            cloTested[cloCount++] = clo;
        }
        else
        {
            cout << "Maximum number of CLOs tested reached for this evaluation." << endl;
        }
    }

    int getCloCount() const
    {
        return cloCount;
    }

    void addQuestion(Question *question)
    {
        if (questionCount < 10)
        {
            questions[questionCount++] = question;
        }
        else
        {
            cout << "Maximum number of questions reached for this evaluation." << endl;
        }
    }

    void displayQuestions()
    {
        cout << "Questions:" << endl;
        for (int i = 0; i < questionCount; ++i)
        {
            cout << i + 1 << ". " << questions[i]->getDescription() << " - " << questions[i]->getMarks() << endl;
        }
    }

    bool containsCLO(const CLO *clo)
    {
        for (int i = 0; i < cloCount; ++i)
        {
            if (cloTested[i] == clo)
            {
                return true;
            }
        }
        return false;
    }

    int getQuestionCount() const
    {
        return questionCount;
    }

    Question *getQuestion(int index) const
    {
        if (index >= 0 && index < questionCount)
        {
            return questions[index];
        }
        else
        {
            return nullptr;
        }
    }

    ~Evaluation()
    {
        for (int i = 0; i < questionCount; ++i)
        {
            delete questions[i];
        }

        for (int i = 0; i < cloCount; ++i)
        {
            delete cloTested[i];
        }
    }
};

class Teacher : public User
{
private:
    string username;
    string password;
    string assignedProgram;
    string assignedCourses[2];
    Course *coursePointers[100];
    Evaluation *evaluations[5];
    Topic *topicsCovered[5];
    int assignedCourseCount = 0;
    int courseCount = 0;
    int evaluationCount = 0;
    int topicCount = 0;
    int findCourseIndex(const string &name)
    {
        for (int i = 0; i < courseCount; ++i)
        {
            if (coursePointers[i]->getName() == name)
            {
                return i;
            }
        }
        return -1;
    }

public:
    Teacher() {}

    Teacher(string uN, string pW) : username(uN), password(pW) {}

    string getUsername() override
    {
        return username;
    }

    string getPassword() override
    {
        return password;
    }

    bool login() override
    {
        cout << "------------------------------------" << endl;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;
        cout << "------------------------------------" << endl;

        setName(username);

        ifstream inFile("teachers.txt");
        string stored_username, stored_password;
        while (getline(inFile, stored_username, ' ') && getline(inFile, stored_password))
        {
            if (stored_username == username && stored_password == password)
            {
                cout << "Login successful." << endl;
                inFile.close();
                return true;
            }
        }
        inFile.close();

        char choice;
        cout << "User not found. Do you want to sign up? (Y/N): ";
        cin >> choice;
        if (toupper(choice) == 'Y')
        {
            ofstream outFile("teachers.txt", ios::app);
            outFile << username << " " << password << endl;
            outFile.close();
            cout << "Account created successfully." << endl;
        }

        return false;
    }

    void assignCourses(int numCourses)
    {
        for (int i = 0; i < 2; ++i)
        {
            int index = rand() % numCourses;
            assignedCourses[i] = coursePointers[index]->getName();
            cout << "Assigned course: " << assignedCourses[i] << endl;
        }
        assignedCourseCount = 2;
    }

    void displayAssignedCourses()
    {
        cout << "Assigned courses for " << username << ":" << endl;
        for (int i = 0; i < assignedCourseCount; ++i)
        {
            cout << assignedCourses[i] << endl;
        }
    }

    void display() override
    {
        cout << "Teacher: " << username << endl;
    }

    void setName(const string &n)
    {
        username = n;
    }

    string getName() const
    {
        return username;
    }

    string getPassword() const
    {
        return password;
    }

    void displayCLO()
    {
        cout << "Displaying CLOs for all courses:" << endl;
        for (int i = 0; i < courseCount; ++i)
        {
            Course *course = coursePointers[i];
            cout << endl;
            if (course)
            {
                course->displayCLOs();
            }
            cout << endl;
        }
    }

    void enterTopicsCovered()
    {
        displayAllCourses();
        cout << "------------------------------------" << endl;
        cout << "Enter course index: ";
        int courseIndex;
        cin >> courseIndex;
        courseIndex--;

        if (courseIndex >= 0 && courseIndex < courseCount)
        {
            Course *course = coursePointers[courseIndex];
            course->displayCLOs();
            cout << "\nEnter CLO index for course '" << course->getName() << "': ";
            int cloIndex;
            cin >> cloIndex;
            cloIndex--;

            if (cloIndex >= 0 && cloIndex < course->getNumberOfCLOs())
            {
                CLO *clo = course->getCLO(cloIndex--);

                cout << "Enter topics covered for CLO '" << clo->getDescription() << "':" << endl;
                cin.ignore();
                for (int i = 0; i < 5; ++i)
                {
                    cout << "Topic " << i + 1 << ": ";
                    string topicDescription;
                    getline(cin, topicDescription);
                    if (topicDescription.empty())
                    {
                        break;
                    }
                    Topic *topic = new Topic(topicDescription);
                    clo->addTopic(topic);
                    topicsCovered[topicCount++] = topic;
                }
            }
            else
            {
                cout << "Invalid CLO index." << endl;
            }
        }
        else
        {
            cout << "Invalid course index." << endl;
        }
    }

    void displayTopicsCovered()
    {
        cout << "Topics Covered:" << endl;
        for (int i = 0; i < topicCount; ++i)
        {
            cout << "- " << topicsCovered[i]->getDescription() << endl;
        }
    }

    void addEvaluation()
    {
        displayAllCourses();
        cout << "------------------------------------" << endl;
        cout << "Enter course index: ";
        int courseIndex;
        cin >> courseIndex;
        courseIndex--;

        if (courseIndex >= 0 && courseIndex < courseCount)
        {
            Course *course = coursePointers[courseIndex];
            course->displayCLOs();
            cout << "\nEnter CLO index for course '" << course->getName() << "': ";
            int cloIndex;
            cin >> cloIndex;
            cloIndex--;

            if (cloIndex >= 0 && cloIndex < course->getNumberOfCLOs())
            {
                CLO *clo = course->getCLO(cloIndex--);

                cout << "Enter evaluation description: ";
                string description;
                cin.ignore();
                getline(cin, description);
                Evaluation *evaluation = new Evaluation(description);

                evaluation->addCLO(clo);

                cout << "Enter questions for evaluation (Enter empty string to finish):" << endl;
                while (true)
                {
                    cout << "Question: ";
                    string questionDescription;
                    double questionMarks = 0.0;
                    cout << "Question Description: ";
                    getline(cin, questionDescription);
                    if (questionDescription.empty())
                    {
                        break;
                    }
                    cout << "Question Marks: ";
                    cin >> questionMarks;
                    cin.ignore();
                    Question *question = new Question(questionDescription, questionMarks);
                    evaluation->addQuestion(question);
                }

                if (evaluationCount < 5)
                {
                    evaluations[evaluationCount++] = evaluation;
                }
                else
                {
                    cout << "Maximum number of evaluations reached." << endl;
                }
            }
            else
            {
                cout << "Invalid CLO index." << endl;
            }
        }
        else
        {
            cout << "Invalid course index." << endl;
        }
    }

    void TestEachCourse()
    {
        cout << "------------------------------------" << endl;
        cout << "Displaying each CLO to checkk evaluations:" << endl;
        displayAllCourses();

        cout << "Enter course index: ";
        int courseIndex;
        cin >> courseIndex;
        courseIndex--;

        if (courseIndex >= 0 && courseIndex < courseCount)
        {
            Course *course = coursePointers[courseIndex];
            course->displayCLOs();
            cout << "\nEnter CLO index for course '" << course->getName() << "': ";
            int cloIndex;
            cin >> cloIndex;
            cloIndex--;

            if (cloIndex >= 0 && cloIndex < course->getNumberOfCLOs())
            {
                CLO *clo = course->getCLO(cloIndex--);

                cout << "Evaluations for CLO '" << clo->getDescription() << "':" << endl;
                for (int i = 0; i < evaluationCount; ++i)
                {
                    if (evaluations[i]->containsCLO(clo))
                    {
                        cout << "------------------------------------" << endl;
                        cout << i + 1 << ". " << evaluations[i]->getDescription() << endl;
                        evaluations[i]->displayQuestions();
                    }
                    else
                    {
                        cout << "No Evaluation" << endl;
                    }
                }
            }
            else
            {
                cout << "Invalid CLO index." << endl;
            }
        }
        else
        {
            cout << "Invalid course index." << endl;
        }
    }

    void displayAllCourses()
    {
        cout << "Courses:" << endl;
        for (int i = 0; i < courseCount; ++i)
        {
            cout << i + 1 << ". " << coursePointers[i]->getName() << endl;
        }
    }

    void saveDataToFile(const string &filename)
    {
        ofstream outFile(filename);
        if (outFile.is_open())
        {
            // outFile << getName() << "," << getPassword() << endl;
            for (int i = 0; i < courseCount; ++i)
            {
                Course *course = coursePointers[i];
                if (course)
                {
                    outFile << "Courses:" << endl;

                    outFile << course->getName() << "," << course->getDescription() << endl;

                    for (int j = 0; j < course->getNumberOfCLOs(); ++j)
                    {
                        CLO *clo = course->getCLO(j);
                        if (clo)
                        {
                            outFile << clo->getDescription() << " - ";

                            outFile << "Topics: ";
                            for (int k = 0; k < clo->getTopicCount(); ++k)
                            {
                                outFile << clo->getTopic(k)->getDescription() << ", ";
                            }

                            outFile << "Evaluations: ";
                            for (int k = 0; k < evaluationCount; ++k)
                            {
                                Evaluation *evaluation = evaluations[k];
                                if (evaluation)
                                {
                                    if (evaluation->containsCLO(clo))
                                    {
                                        outFile << evaluation->getDescription() << ", ";

                                        outFile << "Questions: ";
                                        for (int l = 0; l < evaluation->getQuestionCount(); ++l)
                                        {
                                            outFile << evaluation->getQuestion(l)->getDescription() << ": " << evaluation->getQuestion(l)->getMarks() << ", ";
                                        }
                                    }
                                }
                            }
                            outFile << endl;
                        }
                    }
                }
            }
            outFile.close();
            cout << "Save Data to file successfully." << endl;
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

    void loadDataFromFile(const string &filename)
    {
        ifstream inFile(filename);
        if (inFile.is_open())
        {
            string line, courseName, courseDesc;
            Course *currentCourse = nullptr;

            while (getline(inFile, line))
            {
                if (line.empty())
                    continue;

                if (line == "Courses:")
                {
                    if (currentCourse)
                    {
                        coursePointers[courseCount++] = currentCourse;
                    }
                    currentCourse = nullptr;
                }
                else
                {
                    if (!currentCourse)
                    {
                        char commaPos = line.find(",");
                        courseName = line.substr(0, commaPos);
                        courseDesc = line.substr(commaPos + 1);
                        currentCourse = new Course(courseName, courseDesc);
                    }
                    else
                    {
                        CLO *clo = new CLO(line);
                        currentCourse->addCLO(clo);
                    }
                }
            }

            if (currentCourse)
            {
                coursePointers[courseCount++] = currentCourse;
            }
            cout << "Load Data from file Successfully." << endl;
            // assignCourses(6);
            inFile.close();
            // saveDataToFile("Evaluations.txt");
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

    void loadTEFromFile(const string &filename)
    {
        ifstream inFile(filename);
        int i = 0;
        if (inFile.is_open())
        {
            int courseIndex;
            string line, courseName, courseDesc;
            Course *currentCourse = nullptr;

            while (getline(inFile, line))
            {
                if (line.empty())
                    continue;

                if (line == "Courses:")
                {
                    currentCourse = nullptr;
                }
                else
                {
                    if (!currentCourse)
                    {
                        char commaPos = line.find(",");
                        courseName = line.substr(0, commaPos);
                        courseDesc = line.substr(commaPos + 1);
                        currentCourse = new Course(courseName, courseDesc);
                        courseIndex = findCourseIndex(courseName);
                    }
                    else
                    {
                        char dashPos = line.find("-");
                        string cloDesc = line.substr(0, dashPos - 1);
                        char topicsStart = line.find("Topics:") + 8;
                        char evalsStart = line.find("Evaluations:") + 12;
                        string cloTopicsStr = line.substr(topicsStart, evalsStart - topicsStart - 12);
                        string cloEvalsStr = line.substr(evalsStart);

                        if (i == coursePointers[courseIndex]->getNumberOfCLOs() - 1)
                        {
                            i = 0;
                        }
                        else
                        {
                            i++;
                        }
                        string topic;
                        char pos = 0;
                        while ((pos = cloTopicsStr.find(",")) != string::npos)
                        {
                            topic = cloTopicsStr.substr(0, pos);
                            coursePointers[courseIndex]->getCLO(i)->addTopic(new Topic(topic));
                            cloTopicsStr.erase(0, pos + 2);
                        }

                        string eval;
                        pos = 0;

                        // if (evaluationCount < 5)
                        // {
                        //     evaluations[evaluationCount++] = evaluation;
                        // }
                        // while ((pos = cloEvalsStr.find(",")) != string::npos)
                        // {
                        //     eval = cloEvalsStr.substr(0, pos);
                        //     Evaluation *evaluation = new Evaluation(eval);
                        //     evaluation->addCLO(coursePointers[courseIndex]->getCLO(i));
                        //     cloEvalsStr.erase(0, pos + 2);
                        // }
                    }
                }
            }
            inFile.close();
            saveDataToFile("Evaluations.txt");
            cout << "Data loaded from file successfully." << endl;
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

    ~Teacher()
    {
        for (int i = 0; i < courseCount; ++i)
        {
            delete coursePointers[i];
        }

        for (int i = 0; i < evaluationCount; ++i)
        {
            delete evaluations[i];
        }

        for (int i = 0; i < topicCount; ++i)
        {
            delete topicsCovered[i];
        }
    }
};

void displayMenu()
{
    cout << "\n\t\t\t\t\t\tWelcome to OBE System of FAST NUCES, Lahore\n"
         << endl;
    char userType;
    do
    {
        cout << "Who are you? (Enter 'E' to Exit or Enter 'A' for Academic Officer or 'T' for Teacher): ";
        cin >> userType;

        User *user = nullptr;
        if (userType == 'E' || userType == 'e')
        {
            cout << "------------------------------------" << endl;
            cout << "Exiting..." << endl;
            break;
        }
        else if (userType == 'A' || userType == 'a')
        {
            user = new AcademicOfficer();
            AcademicOfficer academicOfficer;
            if (user->login())
            {
                user->display();
                int option;
                do
                {
                    cout << "------------------------------------" << endl;
                    cout << "Select an option:" << endl;
                    cout << "0. Exit" << endl;
                    cout << "1. Manage Programs" << endl;
                    cout << "2. Manage PLOs" << endl;
                    cout << "3. Manage Courses" << endl;
                    cout << "4. Manage CLOs" << endl;
                    cout << "5. Save Data to File." << endl;
                    cout << "6. Load Data from File." << endl;
                    cout << "7. Display Course for Give PLO" << endl;
                    cout << "------------------------------------" << endl;
                    cout << "Enter your choice: ";
                    cin >> option;

                    switch (option)
                    {
                    case 0:
                    {
                        cout << "------------------------------------" << endl;
                        cout << "Exiting..." << endl;
                        break;
                    }
                    case 1:
                        academicOfficer.manageProgram();
                        break;
                    case 2:
                        academicOfficer.managePLO();
                        break;
                    case 3:
                        academicOfficer.manageCourse();
                        break;
                    case 4:
                        academicOfficer.manageCLO();
                        break;
                    case 5:
                        academicOfficer.saveToFile("PLOs.txt", "CLOs.txt");
                        break;
                    case 6:
                        academicOfficer.loadDataFromFile("PLOs.txt");
                        break;
                    case 7:
                        academicOfficer.generateCourseListForPLO();
                        break;
                    default:
                        cout << "Invalid option." << endl;
                        break;
                    }
                } while (option != 0);
            }
        }
        else if (userType == 'T' || userType == 't')
        {
            user = new Teacher();
            if (user->login())
            {
                user->display();
                // string Uname = user->getUsername();
                // string Pass = user->getPassword();
                Teacher teacher;
                int option;
                do
                {
                    cout << "------------------------------------" << endl;
                    cout << "Select an option:" << endl;
                    cout << "0. Exit" << endl;
                    cout << "1. Enter Topic Covered against each CLO" << endl;
                    cout << "2. Add Information about Evaluations conducted" << endl;
                    cout << "3. Save Data to File." << endl;
                    cout << "4. Load Data from File." << endl;
                    cout << "5. Display CLOs" << endl;
                    cout << "6. Test all CLOs in Courses" << endl;
                    cout << "------------------------------------" << endl;
                    cout << "Enter your choice: ";
                    cin >> option;

                    switch (option)
                    {
                    case 0:
                    {
                        cout << "------------------------------------" << endl;
                        cout << "Exiting..." << endl;
                    }
                    break;
                    case 1:
                        teacher.enterTopicsCovered();
                        break;
                    case 2:
                        teacher.addEvaluation();
                        break;
                    case 3:
                        teacher.saveDataToFile("TopicCovered.txt");
                        break;
                    case 4:
                        teacher.loadDataFromFile("CLOs.txt");
                        teacher.loadTEFromFile("TopicCovered.txt");
                        break;
                    case 5:
                        teacher.displayCLO();
                        break;
                    case 6:
                        teacher.TestEachCourse();
                        break;
                    default:
                        cout << "Invalid option." << endl;
                        break;
                    }
                } while (option != 0);
            }
        }
        else
        {
            cout << "Invalid user type." << endl;
        }
    } while (userType == 'A' || userType == 'a' || userType == 'T' || userType == 't');
}
int main()
{
    displayMenu();
    return 0;
}