// Nombre de estudiantes: Samantha Acu?a Montero, Katherine Amador Gonz?lez, Jose Serrano Quesada.
// Fecha de inicio: 31/08/2021
// Fecha de finalizacion:



using namespace std;
#include <iostream>


// Structures.
struct Administrator {
    int id;
    string name;
    Administrator* sig;


    Administrator(int idd, string n) {
        id = idd;
        name = n;
        sig = NULL;
    }
};

struct Course {
    int id;
    string name;
    int credits;
    Course* sig;
    struct Group* enlaceGrupoC; //Relation of course-group.

    Course(int idd, string n, int cr) {
        id = idd;
        name = n;
        credits = cr;
        sig = NULL;
        enlaceGrupoC = NULL;
    }
};

struct Teacher {
    int id;
    string name;
    Teacher* sig;
    Teacher* ant;
    struct GroupAssignment* subListGroupT; //Relation of teacher-group.

    Teacher(int idp, string namep) {
        id = idp;
        name = namep;
        sig = NULL;
        ant = NULL;
        subListGroupT = NULL;
    }
};

struct Student {
    int id;
    string name;
    Student* sig;
    struct GroupAssignment* sublistGroup; //Relation of student-group.

    Student(int idd, string n) {
        id = idd;
        name = n;
        sig = NULL;
        sublistGroup = NULL;
    }
};

struct Semester {
    int semester;
    int year;
    int week;
    Semester* sig;
    Semester* ant;
    struct CourseAssignment* subListCourse; // Relation of semester-course.
    struct generalTalks* bondTalk; // Relation of semester-general talks.

    Semester(int s, int y, int w) {
        semester = s;
        year = y;
        week = w;
        sig = NULL;
        ant = NULL;
        subListCourse = NULL;
        bondTalk = NULL;
    }
};


struct Evaluation {
    int idE;
    string name;
    int percentage;
    int day, month, year; // Fecha de entrega.
    Evaluation* sig;

    Evaluation(int idd, string n, int p, int d, int m, int y) {
        idE = idd;
        name = n;
        percentage = p;
        day = d;
        month = m;
        year = y;
        sig = NULL;
    }
};


struct generalTalks {
    int number;
    string name;
    generalTalks* sig;

    generalTalks(int num, string n) {
        number = num;
        name = n;
        sig = NULL;
    }
};


struct Group {
    int number;

    Group* sig;
    struct Course* enlaceCourse; //Relation of group-course.

    struct Evaluation* sublistaTarea; //Relation of group-homework.
    struct Evaluation* sublistaProyectos; //Relation of group-projects.
    struct Evaluation* sublistaGiras; //Relation of group-tours.
    struct Evaluation* sublistaExamen; //Relation of group-exam.

    Group(int num, int s) {
        number = num;

        sig = NULL;
        enlaceCourse = NULL;
        sublistaTarea = NULL;
        sublistaProyectos = NULL;
        sublistaGiras = NULL;
        sublistaExamen = NULL;
    }
};


//SubLists.
struct assignmentsDelivered {

    assignmentsDelivered* sig;
    struct Evaluation* bondAssignments;

    assignmentsDelivered()
    {
        sig = NULL;
        bondAssignments = NULL;
    }
};


struct CourseAssignment {

    CourseAssignment* sig;
    struct Course* bondCourse;

    CourseAssignment()
    {
        sig = NULL;
        bondCourse = NULL;
    }
};

struct GroupAssignment{

    GroupAssignment* sig;
    struct Group * bondGroup;

    GroupAssignment(){
        sig = NULL;
        bondGroup = NULL;
    }
};

//PUNTEROS GLOBALES
Teacher* firstTeacher;
Administrator* firstAdmin;
Student* firstStudent;
Semester* firstSemester;
Course* firstCourse;

//----------------------------------------------------------------------------------------------------------------------
Teacher* searchTeacher(int id) {     //search for the list of the struct teacher
    Teacher* temp = firstTeacher;
    while (temp != NULL)
    {
        if (id == temp->id) { return temp; }

        temp = temp->sig;
    }

    return NULL;
}

void teacherInsert(int id, string name)     //insert the data to the list of firstTeacher
{
    Teacher* temp = searchTeacher(id);

    if ((firstTeacher == NULL) || (temp == NULL))
    {
        Teacher* nn = new Teacher(id, name);

        nn->sig = firstTeacher;
        if (firstTeacher != NULL) { firstTeacher->ant = nn; }
        firstTeacher = nn;
    }
    else { cout << "Teacher was repeated" << endl; }

    return;
}



void teacherMod(int id, int idMod, string nameMod) {        //it modifies a variable of the teacher list
    Teacher* temp = searchTeacher(id);
    if (temp == NULL) { cout << "Data not found"; }
    else
    {
        temp->id = idMod;
        temp->name = nameMod;
        cout << "the data were modified";
    }
    return;
}

void teacherDelete(int id_)
{
    Teacher* del = searchTeacher(id_);
    if (del == NULL) { cout << "The variable to delete was not found"; }

    else
    {
        Teacher* nodeAnt = del->ant;
        Teacher* nodeSig = del->sig;

        //ask if there is only one node in the list
        if (del->ant == NULL && del->sig == NULL)
        {
            firstTeacher = NULL;
            cout << "There is only one element in the list... it was deleted successfully" << endl;
        }
        //to ask if the element is the fist of the list
        else if (del == firstTeacher)
        {
            firstTeacher = firstTeacher->sig;
            firstTeacher->ant = NULL;
            cout << "The first element of teacher was deleted successfully";
        }
        //when the element is in the final or between position of the list
        else
        {
            nodeAnt->sig = nodeSig;
            if (nodeSig != NULL) { nodeSig->ant = nodeAnt; }
            cout << "The element of teacher was deleted successfully" << endl;
        }
    }
    return;
}

//----------------------------------------------------------------------------------------------------------------------
Administrator* administratorInsert(int id, string name) {
    Administrator* nn = new Administrator(id, name);
    nn->sig = firstAdmin;
    if (firstAdmin != NULL)
    {
        firstAdmin->sig = nn;
    }
    firstAdmin = nn;
    return firstAdmin;
}

//----------------------------------------------------------------------------------------------------------------------

Student* searchStudent(int id, string name) {  //
    Student* local = firstStudent;
    while (local != NULL) {
        if ((local->id == id) && (local->name == name))
            return local;
        local = local->sig;
    }
    return NULL;
}

Student* inserStudent(int id, string name) {   //To insert student
    Student* nn = new Student(id, name);

    if (searchStudent(id, name) != NULL) {     //To verify that not repeated data
        cout << "The student is already registered: " << id << ", " << name << endl;
    }

    else {
        if (firstStudent == NULL)
            firstStudent = nn;

        else if (id < firstStudent->id) {
            nn->sig = firstStudent;
            firstStudent = nn;
        }
        else {
            Student* temp = firstStudent;
            Student* tempAnt = firstStudent;
            while ((temp != NULL) && (id > temp->id)) {
                tempAnt = temp;
                temp = temp->sig;
            }
            tempAnt->sig = nn;
            nn->sig = temp;
        }
    }
    return firstStudent;
}

bool modifyStudent(int id, string name, int idN, string nameN) {      //To modify student data
    Student* temp = searchStudent(id, name);
    if (temp == NULL) {
        cout << "\nUnregistered student";
        return false;
    }
    else {
        temp->id = idN;
        temp->name = nameN;
        cout << "\nModified data.\n";
        return true;
    }
}

bool remStudent(int id, string name) { //To delete student
    Student* temp = firstStudent;
    if (firstStudent == NULL) {
        cout << "\nNo student data has been entered";
        return false;
    }
    else if ((firstStudent->id == id) && (firstStudent->name == name)) {
        firstStudent = firstStudent->sig;
        return true;
    }
    else {  //if it is in the middle or at the end of the list
        Student* temp = firstStudent;
        Student* tempAnt = firstStudent;
        while (temp != NULL) {
            if ((temp->id == id) && (temp->name == name)) { //Delete
                tempAnt->sig = temp->sig;
                return true;
            }
            tempAnt = temp;
            temp = temp->sig;
        }
        if (temp == NULL) {
            cout << "The student is not registered";
            return false;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
Semester* searchSemester(int year, int numSemester)  //search for the list of the struct Semester.
{

    Semester* temp = firstSemester;
    while (temp != NULL)
    {
        if ((temp->year == year) && (temp->semester == numSemester))
            return temp;

        temp = temp->sig;

    }


    return NULL;
}


void semesterInsert(int semester, int year, int week) //insert the data to the list of firstSemester.
{
    Semester* nn = new Semester(semester, year, week);

    if (firstSemester == NULL)  //if the list is empty add the element in the list
        firstSemester = nn;

    else if (nn->year <= firstSemester->year)    //To verify if the next element will be above the first element in the list
    {
        if (nn->year != firstSemester->year) //if the first
        {
            nn->sig = firstSemester;
            firstSemester->ant = nn;
            firstSemester = nn;
        }
        else if (nn->year == firstSemester->year && nn->semester < firstSemester->semester)   //if the first element is equal to nn and the semester of nn is below the semester of the first element in the list
        {
            nn->sig = firstSemester;
            firstSemester->ant = nn;
            firstSemester = nn;
        }
        //if it
        else
        {
            firstSemester->sig = nn;
            nn->ant = firstSemester;
        }

    }
    else
    {
        Semester* temp = firstSemester;
        Semester* tempAnt = NULL;

        while ((temp != NULL) && (nn->year > temp->year))   //if the nn element is mayor than the first element in the list
        {
            tempAnt = temp;
            temp = temp->sig;
        }

        if ((temp == NULL) || (temp->semester > nn->semester && temp->year == nn->semester)) //if the element is the greatest
        {
            tempAnt->sig = nn;
            nn->ant = tempAnt;
        }
        else            //to insert between the list
        {
            nn->sig = temp;
            nn->ant = tempAnt;
            tempAnt->sig = nn;
            temp->ant = nn;
        }
    }
    return;
}


void semesterMod(int year, int semester, int modSemester, int modYear, int modWeek)  //it modifies a variable of the semester list
{

    Semester* searchSem = searchSemester(year, semester);
    if (searchSem == NULL)
    {
        cout << "Data not found" << endl;
    }
    else
    {
        searchSem->semester = modSemester;
        searchSem->year = modYear;
        searchSem->week = modWeek;
        cout << "The data were modified" << endl;
    }
}


void semesterDelete(int year, int semester)
{
    Semester* semesterDel = searchSemester(year, semester);

    if (semesterDel == NULL)
    {
        cout << "The variable to delete was not found" << endl;
    }
    else
    {
        Semester* semesterAnt = semesterDel->ant;
        Semester* semesterSig = semesterDel->sig;

        if ((semesterDel->ant == NULL) && (semesterDel->sig == NULL))
        {
            firstSemester = NULL;
            cout << "There is only one element in the list... it was deleted successfully" << endl;
        }
        else if (semesterDel == firstSemester)
        {
            firstSemester = firstSemester->sig;
            firstSemester->ant = NULL;
            cout << "The first element of semester was deleted successfully" << endl;
        }
        else
        {
            semesterAnt->sig = semesterSig;
            if (semesterSig != NULL)
            {
                semesterSig->ant = semesterAnt;
                cout << "The element of semester was deleted successfully" << endl;
            }
        }

    }
    return;
}
//----------------------------------------------------------------------------------------------------------------------

Course* searchCourse(int id) //search for the list of the struct Course.
{
    Course* temp = firstCourse;
    do
    {
        if (temp->id == id) { return temp; }
        temp = temp->sig;

    } while (temp != firstCourse);
    return NULL;
}

void insertCourse(int id, string name, int credits)   //insertion to the final position, circular list.
{
    Course* nn = new Course(id, name, credits);
    //checking if the element is repeated in the list
    if (firstCourse == NULL)
    {
        firstCourse = nn;
        nn->sig = nn;
        cout << "insertCourse first element completed" << endl;
    }
    else
    {
        Course* check = searchCourse(id);
        if (check != NULL) { cout << "The element was repated in insertCourse" << endl; }
        else //if the parameters are not equal to any element in the list
        {
            Course* temp = firstCourse;
            nn->sig = firstCourse;

            while (temp->sig != firstCourse) { temp = temp->sig; }
            temp->sig = nn; //it inserts the element in the last position of the list
            cout << "insertCourse completed" << endl;
        }

    }
}

void modCourse(int idm, string namem, int id)   //It is used to modify the list of courses
{
    Course* temp = searchCourse(id);
    if (temp != NULL)
    {
        temp->id = idm;
        temp->name = namem;
        cout << "modCourse completed" << endl;
    }
    else { cout << "element of modCourse not found to modify" << endl; }
}


void delCourse(int id)  //it is used to delete elements of the list of courses
{
    Course* temp = searchCourse(id);
    Course* prev = firstCourse;
    if (temp == NULL) { cout << "The element to delete in delCourse was not found" << endl; }
    else if (firstCourse->id == temp->id) //if the element is the first in the list
    {

        while (prev->sig != temp) //used to connect the last element with the first
            prev = prev->sig;

        firstCourse = firstCourse->sig;
        prev->sig = firstCourse;

        cout << "The first element in the list was deleted in delCourse" << endl;
    }
    // if the element is between the list
    else
    {
        while (prev->sig != temp) //locating the element below temp
            prev = prev->sig;

        temp = temp->sig;
        prev->sig = temp;
        cout << "The element was deleted in delCourse" << endl;
    }
}
void insertGroupC(int id, int numG) //It is used for insert groups as a sublist in courses
{
    Course* tempCourse = searchCourse(id);
    if (tempCourse == NULL)
    {
        cout << "Data not found" << endl;
    }
    Group * nnG = new Group(numG);

    tempCourse->enlaceGrupoC = nnG;
}


//----------------------------------------------------------------------------------------------------------------------
int main()
{

    semesterInsert(2, 2021, 16);
    semesterInsert(1, 2021, 16);
    semesterInsert(2, 2019, 16);
    semesterInsert(1, 2019, 16);
    semesterInsert(2, 2020, 16);
    semesterInsert(1, 2020, 16);
    semesterInsert(1, 2017, 16);
    semesterInsert(2, 2150, 16);
    semesterInsert(1, 2150, 16);
    semesterInsert(1, 2016, 16);
    semesterInsert(2, 2012, 16);

    semesterMod(2017, 1, 2, 2018, 16);

    semesterDelete(2021, 1);

}
