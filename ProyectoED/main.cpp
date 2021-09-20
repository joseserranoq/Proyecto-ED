}// Nombre de estudiantes: Samantha Acuña Montero, Katherine Amador González, Jose Serrano Quesada.
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

    Group(int num) {
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

struct GroupAssignment {

    GroupAssignment* sig;
    struct Group* bondGroup;

    GroupAssignment() {
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

Student* searchStudent(int id) {  //
    Student* local = firstStudent;
    while (local != NULL) {
        if (local->id == id) { return local; }
        local = local->sig;
    }
    return NULL;
}

Student* inserStudent(int id, string name) {   //To insert student
    Student* nn = new Student(id, name);

    if (searchStudent(id) != NULL) {     //To verify that not repeated data
        cout << "The student is already registered: " << id <<endl;
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

bool modifyStudent(int id, int idN, string nameN) {      //To modify student data
    Student* temp = searchStudent(id);
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
    return false;
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
    //it verifies if the element to delete exist
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

//----------------------------------------------------------------------------------------------------------------------
void insertGroupToCourse(int idC, int numG) //It is used for insert groups as a sublist in courses
{
    Course* tempCourse = searchCourse(idC);
    if (tempCourse == NULL)     //to verify if the course exists
    {
        cout << "Data not found" << endl;
    }
    Group* nnG = new Group(numG);

    if (tempCourse->enlaceGrupoC == NULL)      //if the list is empty
    {
        tempCourse->enlaceGrupoC = nnG;
        nnG->enlaceCourse = tempCourse;     //it links the group with the course
        cout << "element inserted in the empty list...already is not empty. Function insertGroupC" << endl;
    }

    else if (nnG->number < tempCourse->enlaceGrupoC->number)   //if the element is minor than the first
    {   //it is going to position in the first place in the list
        nnG->sig = tempCourse->enlaceGrupoC;
        tempCourse->enlaceGrupoC = nnG; //it inserts in the first position of the list
        nnG->enlaceCourse = tempCourse; //it links the list with the course
        cout << "element inserted in the first position. Function insertGroupC" << endl;
    }
    else    //if the element is in between or in the final position
    {
        //we need to create the temps with the instance group to make the changes
        Group* temp = tempCourse->enlaceGrupoC;
        Group* tempPrev = tempCourse->enlaceGrupoC;
        while (temp != NULL && nnG->number > temp->number)
        {
            tempPrev = temp;
            temp = temp->sig;
        }
        if (temp == NULL) //if the element is the greatest
        {
            tempPrev->sig = nnG;
            nnG->enlaceCourse = tempCourse;
            cout << "element inserted in the last position. Function insertGroupC" << endl;
        }
        else    //if the element is between the list
        {
            nnG->sig = temp;
            tempPrev->sig = nnG;
            nnG->enlaceCourse = tempCourse;
            cout << "element inserted in the middle position. Function insertGroupC" << endl;
        }
    }




}
//----------------------------------------------------------------------------------------------------------------------
Group* searchGroupInCourse(int idC, int idG)   //it is used to find the group in linked to course
{
    Course* tempC = searchCourse(idC);
    Group* tempG = tempC->enlaceGrupoC;

    while (tempG != NULL)
    {
        if (tempG->number == idG) { return tempG; }
        tempG = tempG->sig;
    }
    return NULL;
}

//----------------------------------------------------------------------------------------------------------------------
void linkTeacherToGroup(int idProf, int idCourse, int idGroup)    //it is used to link teacher with its groups
{
    Teacher* tempT = searchTeacher(idProf);
    Course* tempC = searchCourse(idCourse);
    Group* tempG = searchGroupInCourse(idCourse, idGroup);  //it makes a search of the element in group
    if (tempT == NULL || tempC == NULL || tempG == NULL) { cout << "There is an element that does not exist" << endl; }
    else
    {
        //linking the lists
        GroupAssignment* nnL = new GroupAssignment();

        nnL->bondGroup = tempG; //it adds the link of the group

        //beginning insert
        nnL->sig = tempT->subListGroupT;
        tempT->subListGroupT = nnL;

    }
}
void deleteTeacherToGroup(int idTeacher,int idCourse,int idGroup)
{
    Teacher* tempTeacher = searchTeacher(idTeacher);
    Group* tempGroup = searchGroupInCourse(idCourse, idGroup);

    if (tempTeacher == NULL || tempGroup == NULL || tempTeacher->subListGroupT == NULL) { cout << "There is an element that does not exist in function deleteTeacherToGroup"<<endl; }
    else
    {
        GroupAssignment* temp = tempTeacher->subListGroupT;
        GroupAssignment* tempPrev = tempTeacher->subListGroupT;
        if (temp->bondGroup->number == idGroup) // if it is the first element in the list
        {
            temp = temp->sig;
            tempTeacher->subListGroupT = temp;
        }
        else
        {
            while (temp->bondGroup != tempGroup)
            {
                tempPrev = temp;
                temp = temp->sig;
            }
            tempPrev->sig = temp->sig;
            cout << "the element has been deleted in function deleteTeacherToGroup" << endl;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
//To bond the struct student with group
void bondStudentGroup(int idS, int idG, int idC) {
    Student* ss = searchStudent(idS);
    Group* gg = searchGroupInCourse(idC, idG);
    Course* cc = searchCourse(idC);

    if (ss == NULL || gg == NULL || cc == NULL) {//For elements not exist
        cout << "Elements does not exit";
    }
    else {//To elements exist
        GroupAssignment* SG = new GroupAssignment();
        SG->bondGroup = gg;  //Unit the group

        //To insert
        SG->sig = ss->sublistGroup;
        ss->sublistGroup = SG;
    }
}
//----------------------------------------------------------------------------------------------------------------------
//To bond semester with course
void bondSemesterCourse(int yearS, int numS, int idC) {
    Semester* se = searchSemester(yearS, numS);
    Course* cou = searchCourse(idC);
    if (se == NULL || cou == NULL) {//To elements not exist
        cout << "The element does not exist";
    }
    else {//To elements exist
        CourseAssignment* SC = new CourseAssignment();
        SC->bondCourse = cou;

        //To insert
        SC->sig = se->subListCourse;
        se->subListCourse = SC;
    }
}

//----------------------------------------------------------------------------------------------------------------------
int main()
{

    teacherInsert(123, "HHH");
    //teacherInsert(1234, "AAA");

    insertCourse(1, "A", 3);
    insertCourse(2, "B", 4);

    insertGroupToCourse(1, 51);
    insertGroupToCourse(1, 52);
    insertGroupToCourse(1, 50);
    insertGroupToCourse(1, 49);

    insertGroupToCourse(2, 60);
    insertGroupToCourse(2, 61);
    insertGroupToCourse(2, 62);

    linkTeacherToGroup(123, 1, 51);
    linkTeacherToGroup(123, 2, 60);
    linkTeacherToGroup(123, 2, 61);
    linkTeacherToGroup(123, 1, 52);
    linkTeacherToGroup(123, 2, 59); //it does not exist

    deleteTeacherToGroup(123, 2, 60);

    //inserStudent(7, "Sammi");
    //bondStudentGroup(7, 51, 1);
    //bondStudentGroup(7, 49, 1);

    //semesterInsert(1, 2020, 6);
    //semesterInsert(2, 2022, 6);
    //semesterInsert(1, 2019, 2);

    //bondSemesterCourse(2019, 1, 1);
    //bondSemesterCourse(2019, 1, 2);

    Teacher* temp = firstTeacher;
    GroupAssignment* tempaux = temp->subListGroupT;
    while (tempaux != NULL)
    {
        cout << tempaux->bondGroup->number<<endl;
        tempaux = tempaux->sig;
    }



   /*  Student* temp1 = firstStudent;
    cout << temp1->sublistGroup->bondGroup->number << endl << temp1->sublistGroup->sig->bondGroup->number<<endl;Semester* temp2 = firstSemester;

    cout << temp2->subListCourse->bondCourse->name << endl;
    cout << temp2->subListCourse->sig->bondCourse->name << endl;

    Course* temp = firstCourse;
    Group * tempaux = firstCourse->sig->enlaceGrupoC;
    while(tempaux!=NULL)
    {
        cout<<tempaux->number<<endl<<"Del curso: "<<tempaux->enlaceCourse->id<<endl;
        tempaux = tempaux->sig;
    }
    */


}


