// Nombre de estudiantes: Samantha Acuña Montero, Katherine Amador González, Jose Serrano Quesada.
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
    struct DeliveredActivities* linkToScore;
    struct GeneralTalkAssistance* linkToGeneralTA;


    Student(int idd, string n) {
        id = idd;
        name = n;
        sig = NULL;
        sublistGroup = NULL;
        linkToScore = NULL;
    }
};

struct Semester {
    int semester;
    int year;
    int week;
    Semester* sig;
    Semester* ant;
    struct CourseAssignment* subListCourse; // Relation of semester-course.
    struct GeneralTalks* bondTalk; // Relation of semester-general talks.

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


struct Evaluation { //used to create the list of exam,project,excursion, task
    int idE;
    string name;
    int percentage;
    int day, month, year;
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

struct GeneralTalkAssistance {

    GeneralTalkAssistance* sig;
    struct GeneralTalks* linkToGeneralT;

    GeneralTalkAssistance() {
        sig = NULL;
        linkToGeneralT = NULL;
    }

};
struct GeneralTalks {
    int number;
    string name;
    int day;
    int month;
    int year;
    GeneralTalks* sig;

    GeneralTalks(int num, string n, int d, int m, int y) {
        number = num;
        name = n;
        day = d;
        month = m;
        year = y;
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

struct CourseAssignment {

    CourseAssignment* sig;
    struct Course* bondCourse;

    CourseAssignment()
    {
        sig = NULL;
        bondCourse = NULL;
    }
};

struct DeliveredActivities //used to assign scores to activities
{
    int score;
    DeliveredActivities* sig;
    struct Evaluation* linkActivity;
    DeliveredActivities(int s)
    {
        score = s;
        sig = NULL;
        linkActivity = NULL;
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

Administrator* searchAdministrator(int idAdm) { // To search in the list an administrator.
    Administrator* tempAdm = firstAdmin;
    while (tempAdm != NULL) {
        if (tempAdm->id == idAdm) {
            return tempAdm;
            tempAdm = tempAdm->sig;
        }
    }return NULL;
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

Student* insertStudent(int id, string name) {   //To insert student
    Student* nn = new Student(id, name);

    if (searchStudent(id) != NULL) {     //To verify that not repeated data
        cout << "The student is already registered: " << id << endl;
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
    Semester* temp = searchSemester(year, semester);
    if (temp != NULL) { cout << "The semester is repeated"; }   //to make sure the semester inserted is not repeated
    else
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

void modCourse(int id, int idm, string namem, int credistm)   //It is used to modify the list of courses
{
    Course* temp = searchCourse(id);
    if (temp != NULL)
    {
        temp->id = idm;
        temp->name = namem;
        temp->credits = credistm;
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
Group* searchGroup(int idCourse, int idGroup)  //used to search group in a course
{
    Course* tempCourse = searchCourse(idCourse);
    if (tempCourse != NULL)
    {
        Group* tempGroup = tempCourse->enlaceGrupoC;
        while (tempGroup != NULL)
        {
            if (tempGroup->number == idGroup) { return tempGroup; }
            tempGroup = tempGroup->sig;
        }
        return NULL;
    }
    cout << "The course does not exist" << endl;
    return NULL;
}

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
void linkTeacherToGroup(int idProf, int idCourse, int idGroup)    //it is used to link teacher with its groups
{
    Teacher* tempT = searchTeacher(idProf);
    Course* tempC = searchCourse(idCourse);
    Group* tempG = searchGroup(idCourse, idGroup);  //it makes a search of the element in group
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
void deleteTeacherToGroup(int idTeacher, int idCourse, int idGroup)
{
    Teacher* tempTeacher = searchTeacher(idTeacher);
    Group* tempGroup = searchGroup(idCourse, idGroup);

    if (tempTeacher == NULL || tempGroup == NULL || tempTeacher->subListGroupT == NULL) { cout << "There is an element that does not exist in function deleteTeacherToGroup" << endl; }
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
    Group* gg = searchGroup(idC, idG);
    Course* cc = searchCourse(idC);

    if (ss == NULL || gg == NULL || cc == NULL) {//if the elements does not exist
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

void deleteStudentGroup(int idStu, int idGro, int idCour) {//To delete the bond of student with group
    Student* student = searchStudent(idStu);
    Group* group = searchGroup(idCour, idGro);
    if (student == NULL || group == NULL || student->sublistGroup == NULL) {//To verify if both student or group exist
        cout << "Some elements of student or group do not exist" << endl;
    }
    else {
        GroupAssignment* studentemp = student->sublistGroup;
        GroupAssignment* tempS = student->sublistGroup;

        if (studentemp->bondGroup->number == idGro) {//To first elements of the list
            studentemp = studentemp->sig;
            student->sublistGroup = studentemp;
            cout << "The student has been removed from the group" << endl;
        }
        else {//For the others elements of the list, that not first
            while (studentemp->bondGroup != group) {
                tempS = studentemp;
                studentemp = studentemp->sig;
            }
            tempS->sig = studentemp->sig;
            cout << "The student has been removed from the group" << endl;
        }
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

Group* verifyTeacherLinkToGroup(int idTeacher, int idGroup) // to verify if teacher has the group assigned in the function insertTeacherActivities and to search for the links of groups
{
    Teacher* tempTeacher = searchTeacher(idTeacher);
    GroupAssignment* temp = tempTeacher->subListGroupT; //instance of the sublist that links the Teacher to Group
    while (temp != NULL)
    {
        if (temp->bondGroup->number == idGroup) {
            Group* tempG = temp->bondGroup;
            return tempG;

        }

        temp = temp->sig;
    }
    return NULL;
}

Evaluation* sortDateActivities(Evaluation* first, Evaluation* nnE)
{
    Evaluation* temp = first;
    Evaluation* tempPrev = first;
    if (first == NULL) //if the list is empty
    {
        nnE->sig = first;
        first = nnE;

        return first;
    }

    else
    {
        if ((nnE->year < first->year) || (nnE->year == first->year && nnE->month < first->month) || (nnE->year == first->year && nnE->month) == (first->month && nnE->day < first->day)) //if its the lowest element
        {
            nnE->sig = first;
            first = nnE;

            return first;
        }
        else
        {
            while ((temp != NULL) && (nnE->year > temp->year)) //the whiles in this fuction locates the variable temp where it should be
            {
                tempPrev = temp;
                temp = temp->sig;
            }
            if (temp == NULL) //in its the mayor number in the list
            {
                nnE->sig = temp;
                tempPrev->sig = nnE;

                return first;
            }
            else if (nnE->year == temp->year)    //it verifies which is the lowest element
            {
                while (temp != NULL && nnE->month > temp->month && nnE->year == temp->year)  //to sort based in equal year but different month
                {
                    tempPrev = temp;
                    temp = temp->sig;
                }
                if (temp == NULL)
                {
                    nnE->sig = temp;
                    tempPrev->sig = nnE;

                    return first;
                }
                else if (nnE->month == temp->month) //to sort based in day with equal month and year
                {
                    while (temp != NULL && nnE->day >= temp->day && nnE->month == temp->month && nnE->year == temp->year)
                    {
                        tempPrev = temp;
                        temp = temp->sig;
                    }
                    nnE->sig = temp;
                    tempPrev->sig = nnE;

                    return first;
                }
                //if is not equal nne month != temp month. It goes between.
                nnE->sig = temp;
                tempPrev->sig = nnE;

                return first;
            }
            //if nnE year!= temp year if its between.
            nnE->sig = temp;
            tempPrev->sig = nnE;

            return first;
        }
    }
}

Evaluation* typeActivity(Group* tempGroup, int option)   //used to assign the variable temp in the function searchActivities
{

    if (option == 1) {
        Evaluation* temp = tempGroup->sublistaTarea;
        return temp;
    }
    else if (option == 2) {
        Evaluation* temp = tempGroup->sublistaProyectos;
        return temp;
    }
    else if (option == 3) {
        Evaluation* temp = tempGroup->sublistaExamen;
        return temp;
    }
    else if (option == 4) {
        Evaluation* temp = tempGroup->sublistaGiras;
        return temp;
    }
    else {
        cout << "The option does not exist" << endl;
        return NULL;
    }

}

Evaluation* searchTeacherActivities(int teacherId, int idGroup, int idEvaluation, int option) // used to see if there are activities with repeated ids
{

    Group* tempG = verifyTeacherLinkToGroup(teacherId, idGroup);

    Evaluation* temp = typeActivity(tempG, option);   // used to create the variable temp

    if (temp != NULL) {
        while (temp != NULL)
        {
            if (temp->idE == idEvaluation) { return temp; }  // used to see if there is an element in the list repeated
            temp = temp->sig;
        }
        return NULL;
    }
    return NULL;

}

void insertTeacherActivities(int idTeacher, int idGroup, int idCourse, int optionAssignment, int idEvaluation, string subject, int percentage, int day, int month, int year)
{
    //it is used to insert the activities in the different assignments

    Group* temp = verifyTeacherLinkToGroup(idTeacher, idGroup);   //to see if the group exist
    if (temp == NULL) { cout << "First you need to assign a group to the Teacher or the activity id is repeated " << endl; }
    else
    {
        //int option;
        //cout << endl << "Select the option you want \n1-Task\n2-Project\n3-Exam\n4-Excursion\nPresione cualquier otra tecla para salir...";
        //cin >> option;
        Evaluation* check = searchTeacherActivities(idTeacher, idGroup, idEvaluation, optionAssignment);//used to see if there is repeated elements

        if (optionAssignment == 1 && check == NULL)
        {

            Evaluation* nnTask = new Evaluation(idEvaluation, subject, percentage, day, month, year);
            temp->sublistaTarea = sortDateActivities(temp->sublistaTarea, nnTask); //it used to insert the element with date order
            cout << "the element were assigned to Task Activity" << endl;
        }
        else if (optionAssignment == 2 && check == NULL)
        {
            Evaluation* nnProject = new Evaluation(idEvaluation, subject, percentage, day, month, year);
            temp->sublistaProyectos = sortDateActivities(temp->sublistaProyectos, nnProject); //it used to insert the element with date order
            cout << "the element were assigned to project Activity" << endl;
        }
        else if (optionAssignment == 3 && check == NULL)
        {
            Evaluation* nnExam = new Evaluation(idEvaluation, subject, percentage, day, month, year);
            temp->sublistaExamen = sortDateActivities(temp->sublistaExamen, nnExam); //it used to insert the element with date order
            cout << "the element were assigned to exam Activity" << endl;
        }
        else if (optionAssignment == 4 && check == NULL)
        {
            Evaluation* nnExcursion = new Evaluation(idEvaluation, subject, percentage, day, month, year);
            temp->sublistaGiras = sortDateActivities(temp->sublistaGiras, nnExcursion); //it used to insert the element with date order
            cout << "the element were assigned to excursion Activity" << endl;
        }
        else
        {
            cout << "There is a repated element" << endl;
            return;
        }
    }
}

//used to modify the list of exam,task,project and excursions of teacher activities
void modifyAssignmentsTeacherProfile(int idTeacher, int idGroup, int idEvaluation, string subject, int percentage, int option)
{

    //cout << "Select the option you want \n1-Task\n2-Project\n3-Exam\n4-Excursion\nPress any key to exit..."<<endl;
    //int option;
    //cin >> option;

    Evaluation* tempSearched = searchTeacherActivities(idTeacher, idGroup, idEvaluation, option); // it is used if there is repeated id activities
    if (tempSearched != NULL)
    {
        tempSearched->name = subject;
        tempSearched->percentage = percentage;
        cout << "The teacher sublist was modified" << endl;
    }

}

void deleteAssignmentProfileTeacher(int idTeacher, int idGroup, int idEvaluation, int option)//used to delete activities assigned to a teacher
{
    Evaluation* temp = searchTeacherActivities(idTeacher, idGroup, idEvaluation, option);//used to locate the element to delete it
    Group* tempG = verifyTeacherLinkToGroup(idTeacher, idGroup);//locates the group where is the sublist
    Evaluation* tempFirst = typeActivity(tempG, option);//locates the type of activity to get the first position of the list;
    Evaluation* tempPrev = tempFirst; //used to make the delete
    if (temp != NULL)
    {
        if (temp == tempFirst) {//if its the first element in the list
            tempFirst = tempFirst->sig;
            cout << "first element in the list will be deleted... function deleteAssignmentProfileTeacher" << endl;
            if (option == 1) { tempG->sublistaTarea = tempFirst; }  //it needs to change the link
            else if (option == 2) { tempG->sublistaProyectos = tempFirst; }
            else if (option == 3) { tempG->sublistaExamen = tempFirst; }
            else if (option == 4) { tempG->sublistaGiras = tempFirst; }
            else { cout << "The option does not exist... function deleteAssignmentProfileTeacher" << endl; }

        }
        else //is the element is between or is the last in the list
        {
            while (tempPrev->sig != temp)   //to be before the element to delete
            {
                tempPrev = tempPrev->sig;
            }
            temp = temp->sig;
            tempPrev->sig = temp;
            cout << "The element was deleted... function deleteAssignmentProfileTeacher" << endl;

        }
    }
}

GeneralTalks* sortDateGeneralTalks(GeneralTalks* first, GeneralTalks* nnE)
{
    GeneralTalks* temp = first;
    GeneralTalks* tempPrev = first;
    if (first == NULL) //if the list is empty
    {
        nnE->sig = first;
        first = nnE;

        return first;
    }

    else
    {
        if ((nnE->year < first->year) || (nnE->year == first->year && nnE->month < first->month) || (nnE->year == first->year && nnE->month == first->month && nnE->day < first->day)) //if its the lowest element
        {
            nnE->sig = first;
            first = nnE;

            return first;
        }
        else
        {
            while ((temp != NULL) && (nnE->year > temp->year))//the whiles in this fuction locates the variable temp where it should be
            {
                tempPrev = temp;
                temp = temp->sig;
            }
            if (temp == NULL)//in its the mayor number in the list
            {
                nnE->sig = temp;
                tempPrev->sig = nnE;

                return first;
            }
            else if (nnE->year == temp->year)    //it verifies which is the lowest element
            {
                while (temp != NULL && nnE->month > temp->month && nnE->year == temp->year) //to sort based in equal year but different month
                {
                    tempPrev = temp;
                    temp = temp->sig;
                }
                if (temp == NULL)
                {
                    nnE->sig = temp;
                    tempPrev->sig = nnE;

                    return first;
                }
                else if (nnE->month == temp->month) //to sort based in day with equal month and year
                {
                    while (temp != NULL && nnE->day >= temp->day && nnE->month == temp->month && nnE->year == temp->year)
                    {
                        tempPrev = temp;
                        temp = temp->sig;
                    }
                    nnE->sig = temp;
                    tempPrev->sig = nnE;

                    return first;
                }
                //if is not equal nne month != temp month. it goes between
                nnE->sig = temp;
                tempPrev->sig = nnE;

                return first;
            }
            //if nnE year!= temp year   if its between
            nnE->sig = temp;
            tempPrev->sig = nnE;

            return first;
        }
    }
}
GeneralTalks* searchGeneralTalks(int semesterNum, int semesterYear, int idgeneralTalk)
{
    Semester* tempS = searchSemester(semesterYear, semesterNum);
    GeneralTalks* temp = tempS->bondTalk;
    while (temp != NULL)
    {
        if (temp->number == idgeneralTalk) { return temp; }
        temp = temp->sig;
    }
    return NULL;
}
void insertGeneralTalksToSemester(int semester, int semesterYear, int idGeneralTalk, string subject, int gtDay, int gtMonth, int gtYear)
{
    Semester* temp = searchSemester(semesterYear, semester);
    GeneralTalks* tempGT = searchGeneralTalks(semester, semesterYear, idGeneralTalk);//used ti see if there is no general talk id repeated
    if (temp != NULL && tempGT == NULL) {
        GeneralTalks* nnGT = new GeneralTalks(idGeneralTalk, subject, gtDay, gtMonth, gtYear);
        temp->bondTalk = sortDateGeneralTalks(temp->bondTalk, nnGT);
        cout << "General Talk inserted" << endl;
    }
    else
    {
        cout << "Semester does not exist" << endl;
    }
}

Group* verifyStudentLinkToGroup(int idStudent, int idCourse, int idGroup)//used to verify if there is a link of student to group
{
    Student* tempS = searchStudent(idStudent);
    GroupAssignment* temp = tempS->sublistGroup;
    while (temp != NULL)
    {
        if (temp->bondGroup->enlaceCourse->id == idCourse && temp->bondGroup->number == idGroup)
        {
            Group* tempG = temp->bondGroup;
            return tempG;
        }
        temp = temp->sig;
    }
    return NULL;
}

Evaluation* searchStudentActivity(int idStudent, int idCourse, int idGroup, int idEvaluation, int option)//used to find if student is linked with an activity
{
    Group* tempS = verifyStudentLinkToGroup(idStudent, idCourse, idGroup);
    Evaluation* temp = typeActivity(tempS, option);

    if (temp != NULL)
    {
        while (temp != NULL)
        {
            if (temp->idE == idEvaluation) { return temp; }  //used to see if there is an element in the list repeated
            temp = temp->sig;
        }
        return NULL;
    }
    return NULL;
}

DeliveredActivities* searchDeliveredActivities(int idStudent, int idCourse, int idGroup, int idEvaluation, int option) //used to see if there is no repeated delivered activities
{
    Student* tempStudent = searchStudent(idStudent);
    DeliveredActivities* temp = tempStudent->linkToScore;
    Evaluation* tempActivity = searchStudentActivity(idStudent, idCourse, idGroup, idEvaluation, option);
    while (temp != NULL)
    {
        if (tempActivity == temp->linkActivity) { return temp; } //it is repeated
        temp = temp->sig;
    }
    return NULL;
}

void registerActivitiesToStudents(int idStudent, int idCourse, int idGroup, int optionActivity, int idEvaluation, int score)//used to register the activities made of the students
{
    DeliveredActivities* tempDA = searchDeliveredActivities(idStudent, idCourse, idGroup, idEvaluation, optionActivity);
    Evaluation* temp = searchStudentActivity(idStudent, idCourse, idGroup, idEvaluation, optionActivity);

    if (tempDA != NULL && temp == NULL) { cout << "The delivered activity is repated.... in fuction registerActivitiesToStudents" << endl; }
    else
    {
        Student* tempTeacher = searchStudent(idStudent);
        DeliveredActivities* nnDA = new DeliveredActivities(score);
        nnDA->sig = tempTeacher->linkToScore;
        tempTeacher->linkToScore = nnDA;
        nnDA->linkActivity = temp;
        cout << "The delivered Activity registered" << endl;
    }

}

void registerAssistanceToGeneralTalks(int idStudent, int idGeneralTalk, int semesterNum, int semesterYear)
{
    Student* tempS = searchStudent(idStudent);
    GeneralTalks* tempGT = searchGeneralTalks(semesterNum, semesterYear, idGeneralTalk);
    GeneralTalkAssistance* nn = new GeneralTalkAssistance();
    if (tempS != NULL && tempGT != NULL)
    {

        nn->sig = tempS->linkToGeneralTA;
        tempS->linkToGeneralTA = nn;
        nn->linkToGeneralT = tempGT;

    }
}//la sublista de grpup assignment se podría utilizar para que se linkee con la asistencia a charlas

//___________________________Reports_____________________________________

//2- A teacher can consult the activities scheduled during the semester for all courses.
void CheckactivitiesTeacher(int idTeacher, int year, int numS, int numGroup, int idCourse)
{
    Teacher* tempT = searchTeacher(idTeacher);
    if (tempT == NULL)
    {
        cout << "Teacher does not exist." << endl;

    }
    else
    {
        Semester* tempS = searchSemester(year, numS);

        if (tempS != NULL)
        {

            Group* tempG = searchGroup(idCourse, numGroup);

            if (tempG !=NULL)
            {
                while (tempG->sig != NULL)
                {
                    cout << "Homework" << tempG->sublistaTarea << endl;
                    cout << "Projects" << tempG->sublistaProyectos << endl;
                    cout << "Exams" << tempG->sublistaExamen << endl;
                    cout << "Tours" << tempG->sublistaGiras << endl;
                }
            }else
            {
                cout << "No logged activities" << endl;
            }
            tempG = tempG->sig;
        }
    }
}

//3- A teacher can check the delivery of each of the tasks already completed in a course.

/*void checkTeacherDelivery(int idTeacher, int idStudent, int idCourse, int idGroup, int idEvaluation, int optionActivity)
{

     Teacher* tempT = searchTeacher(idTeacher);
     if(tempT!=NULL)
     {

         Evaluation* tempE = searchTeacherActivities(int idTeacher, int idGroup, int idEvaluation, int optionActivity);

        if(tempE != NULL)
        {


            cout << "" << endl;
        }
        else
        {
            cout << "The teacher has no assigned activities" << endl;
        }
     }
     else
     {
          cout<<"The teacher not exist"<<endl;
     }
}*/



//4- A teacher can see which students attended all the scheduled talks during a semester.



//5- A teacher can see which students have not turned in different assignments in a course.

//7- An administrator can view students who have not submitted an act in a course.

void menu()
{
    int option;
    bool repeat = true;

    do {
        system("cls");


        cout << "\n\t\tOption Menu\n" << endl;
        cout << "1- Administrator." << endl;
        cout << "2- Teacher." << endl;
        cout << "3- Students." << endl;
        cout << "4- Exit" << endl;

        cout << "\nEnter one option: ";
        cin >> option;
        if (option == 1)
        {
            int option1;
            cout << "1. Register Administrator." << endl;
            cout << "2. Login Administrator." << endl;
            cout << "\nEnter one option: ";
            cin >> option1;
            if (option1 == 1)
            {
                int idAdmi;
                string nameAdmin;
                cout << "Insert administrator." << endl;

                cout << "Enter the ID: " << endl;
                cin >> idAdmi;
                cout << "Enter the name: " << endl;
                cin >> nameAdmin;
                administratorInsert(idAdmi, nameAdmin);
            }
            if (option1 == 2)
            {
                int option11;
                int idAdm;
                cout << "Enter the administrator ID: " << endl;
                cin >> idAdm;
                if (searchAdministrator(idAdm) != NULL)
                {
                    cout << "1- Teacher options." << endl;
                    cout << "2- Student options." << endl;
                    cout << "3- Course options." << endl;
                    cout << "4- Group options." << endl;
                    cout << "5- Semester options." << endl;
                    cout << "6- Check the absence of work submitted by students." << endl;
                    cout << "7- Check capacity for talks." << endl;

                    cout << "\nEnter one option: ";
                    cin >> option11;
                    if (option11 == 1)
                    {
                        int option2;
                        cout << "1- Insert teacher." << endl;
                        cout << "2- Delete teacher." << endl;
                        cout << "3- Modify teacher." << endl;
                        cout << "4- Match teacher with groups." << endl;

                        cout << "\nEnter one option: ";
                        cin >> option2;
                        if (option2 == 1)
                        {
                            int idTeacher;
                            string nameTeacher;
                            cout << "Insert Teacher" << endl;

                            cout << "Enter the ID: " << endl;
                            cin >> idTeacher;
                            cout << "Enter the name: " << endl;
                            cin >> nameTeacher;
                            teacherInsert(idTeacher, nameTeacher);
                        }
                        if (option2 == 2)
                        {
                            int idTeacher;
                            cout << "Enter the ID: " << endl;
                            cin >> idTeacher;

                            teacherDelete(idTeacher);
                        }
                        if (option2 == 3)
                        {
                            int idTeacher;
                            int idTeacherNew;
                            string nameTeacherNwew;
                            cout << "Enter the ID: " << endl;
                            cin >> idTeacher;
                            cout << "Enter the new ID: " << endl;
                            cin >> idTeacherNew;
                            cout << "Enter the new name: " << endl;
                            cin >> nameTeacherNwew;

                            teacherMod(idTeacher, idTeacherNew, nameTeacherNwew);
                        }
                        if (option2 == 4)
                        {
                            int idTe, idCour, idGro;
                            cout << "Enter the ID teacher: " << endl;
                            cin >> idTe;
                            cout << "Enter the ID course: " << endl;
                            cin >> idCour;
                            cout << "Enter the ID group: " << endl;
                            cin >> idGro;
                            linkTeacherToGroup(idTe, idCour, idGro);
                        }
                    }
                    if (option11 == 2)
                    {
                        int option22;
                        cout << "1- Insert student." << endl;
                        cout << "2- Delete student." << endl;
                        cout << "3- Modify student." << endl;
                        cout << "4- Match student with groups." << endl;

                        cout << "\nEnter one option: ";
                        cin >> option22;
                        if (option22 == 1)
                        {
                            int idStudent;
                            string nameStudent;
                            cout << "Insert Student" << endl;

                            cout << "Enter the ID: " << endl;
                            cin >> idStudent;
                            cout << "Enter the name: " << endl;
                            cin >> nameStudent;
                            insertStudent(idStudent, nameStudent);
                        }
                        if (option22 == 2)
                        {
                            int idStudent;
                            string nameStu;
                            cout << "Enter the ID: " << endl;
                            cin >> idStudent;
                            cout << "Enter the name: " << endl;
                            cin >> nameStu;

                            remStudent(idStudent, nameStu);
                        }
                        if (option22 == 3)
                        {
                            int idStudent;
                            int idStudentNew;
                            string nameStudentNew;
                            cout << "Enter the ID: " << endl;
                            cin >> idStudent;
                            cout << "Enter the new ID: " << endl;
                            cin >> idStudentNew;
                            cout << "Enter the new name: " << endl;
                            cin >> nameStudentNew;

                            modifyStudent(idStudent, idStudentNew, nameStudentNew);
                        }
                        if (option22 == 4)
                        {
                            int idStu, idCour, idGro;
                            cout << "Enter the ID teacher: " << endl;
                            cin >> idStu;
                            cout << "Enter the ID group: " << endl;
                            cin >> idGro;
                            cout << "Enter the ID course: " << endl;
                            cin >> idCour;
                            bondStudentGroup(idStu, idGro, idCour);
                        }
                    }
                    if (option11 == 3)
                    {
                        int option3;
                        cout << "1- Insert course." << endl;
                        cout << "2- Delete course." << endl;
                        cout << "3- Modify course." << endl;
                        cout << "\nEnter one option: ";
                        cin >> option3;
                        if (option3 == 1)
                        {
                            int idCourse;
                            string nameCourse;
                            int credits;
                            cout << "Insert Course" << endl;

                            cout << "Enter the ID: " << endl;
                            cin >> idCourse;
                            cout << "Enter the name: " << endl;
                            cin >> nameCourse;
                            cout << "Enter the credits: " << endl;
                            cin >> credits;
                            insertCourse(idCourse, nameCourse, credits);
                        }
                        if (option3 == 2)
                        {
                            int idCourse;
                            cout << "Enter the ID: " << endl;
                            cin >> idCourse;
                            delCourse(idCourse);
                        }
                        if (option3 == 3)
                        {

                            int idCourse;
                            int idCourseNew;
                            string nameCourseNew;
                            int creditsNew;
                            cout << "Enter the ID: " << endl;
                            cin >> idCourse;
                            cout << "Enter the new ID: " << endl;
                            cin >> idCourseNew;
                            cout << "Enter the new name: " << endl;
                            cin >> nameCourseNew;
                            cout << "Enter the new credits: " << endl;
                            cin >> creditsNew;

                            modCourse(idCourse, idCourseNew, nameCourseNew, creditsNew);
                        }
                    }
                    if (option11 == 4)
                    {
                        int idCourse;
                        int numGroup;
                        cout << "Enter the ID of course: " << endl;
                        cin >> idCourse;
                        cout << "Enter the number of group: " << endl;
                        cin >> numGroup;

                        insertGroupToCourse(idCourse, numGroup);

                    }
                    if (option11 == 5)
                    {
                        int option5;
                        cout << "1- Insert semester." << endl;
                        cout << "2- Delete semester." << endl;
                        cout << "3- Modify semester." << endl;
                        cout << "4- Match semester with course." << endl;
                        cout << "\nEnter one option: ";
                        cin >> option5;
                        if (option5 == 1)
                        {
                            int numS, year, week;
                            cout << "Enter the number semester: " << endl;
                            cin >> numS;
                            cout << "Enter the year: " << endl;
                            cin >> year;
                            cout << "Enter the number of weeks in the semester: " << endl;
                            cin >> week;
                            semesterInsert(numS, year, week);
                        }
                        if (option5 == 2)
                        {
                            int numS, year;
                            cout << "Enter the year: " << endl;
                            cin >> year;
                            cout << "Enter the number semester: " << endl;
                            cin >> numS;
                            semesterDelete(year, numS);
                        }
                        if (option5 == 3)
                        {
                            int numS, year, newS, nYear, nWeek;
                            cout << "Enter the year: " << endl;
                            cin >> year;
                            cout << "Enter the number semester: " << endl;
                            cin >> numS;
                            cout << "Enter the new number semester: " << endl;
                            cin >> newS;
                            cout << "Enter the new year: " << endl;
                            cin >> nYear;
                            cout << "Enter the new number of weeks in the semester: " << endl;
                            cin >> nWeek;
                            semesterMod(year, numS, newS, nYear, nWeek);
                        }
                        if(option5 == 4)
                        {
                            int numS, year, idCourse;
                            cout << "Enter the year: " << endl;
                            cin >> year;
                            cout << "Enter the number semester: " << endl;
                            cin >> numS;
                            cout << "Enter the ID of course: " << endl;
                            cin >> idCourse;
                            bondSemesterCourse(year, numS, idCourse);
                        }
                    }

                    if (option11 == 6)
                    {
                        cout << "Reporte";
                    }
                    if (option11 == 7)
                    {
                        cout << "Reporte";
                    }
                }
            }

        }
        if (option == 2)
        {
            int option1;
            int idTeacher;
            cout << "\n Enter the ID Teacher: "; cin >> idTeacher;

            if (searchTeacher(idTeacher) != NULL)
            {
                cout << "1. Activity Options. " << endl;
                cout << "2. General Talks Options. " << endl;
                cout << "3. Homework Delivery Options. " << endl;
                cout << "4. Consult Attendance of Scheduled Talks. " << endl;
                cout << "5. Consultation of Pending Student Work. " << endl;
                cout << "6. Consultation Best Professor with Delivery Compliance. " << endl;

                cout << " \n Enter Option: "; cin >> option1;

                if (option1 == 1) {//Activity Options
                    int actiOption;
                    cout << "1. Insert Activity."<<endl;
                    cout << "2. Change Activity. " << endl;
                    cout << "3. Delete Activity. " << endl;

                    cout << "\nEnter Option: "; cin >> actiOption;

                    if(actiOption==1)
                    {
                        int idTeacher;
                        int idGroup;
                        int idCourse;
                        int optionA;
                        int idEva;
                        string nameEva;
                        int por;
                        int day, month, year;
                        cout << "Enter the ID teacher: " << endl;
                        cin >> idTeacher;
                        cout << "Enter the ID group: " << endl;
                        cin >> idGroup;
                        cout << "Enter the ID course: " << endl;
                        cin >> idCourse;
                        cout << "1. Homework." << endl;
                        cout << "2. Project." << endl;
                        cout << "3. Exam." << endl;
                        cout << "4. Tour." << endl;
                        cout << "Enter the option assigment: " << endl;
                        cin >> optionA;
                        cout << "Enter the ID evaluation: " << endl;
                        cin >> idEva;
                        cout << "Enter the name of evaluation: " << endl;
                        cin >> nameEva;
                        cout << "Enter the porcentage: " << endl;
                        cin >> por;
                        cout << "Enter day: " << endl;
                        cin >> day;
                        cout << "Enter month: " << endl;
                        cin >> month;
                        cout << "Enter year: " << endl;
                        cin >> year;
                        insertTeacherActivities(idTeacher, idGroup, idCourse, optionA, idEva, nameEva, por, day,month,year);
                    }
                    if(actiOption==2){
                        int idTeacher;
                        int idGroup;
                        int idEvaluation;
                        string subject;
                        int percentage;
                        int option;
                        cout << "Insert the new id of teacher: " << endl; cin >> idTeacher;
                        cout << "Insert the new id of group: " << endl; cin >> idGroup;
                        cout << "Insert the new id of evalution: " << endl; cin >> idEvaluation;
                        cout << "Insert the new of subject: " << endl; cin >> subject;
                        cout << "Insert the new of percentage: " << endl; cin >> percentage;
                        cout << "What activity would you like insert? \n 1. Homework \n 2. Project \n 3. Exams \n 4.Tour" << endl;
                        cout << "Insert the new type of activity: "; cin >> option;
                        modifyAssignmentsTeacherProfile(idTeacher, idGroup, idEvaluation, subject, percentage, option);
                    }
                    if(actiOption==3){
                    int idTeacher;
                    int idGroup;
                    int idEvaluation;
                    int option;
                    cout << "Insert the id of teacher that would like deleted: " << endl; cin >> idTeacher;
                    cout << "Insert the id of group that would like deleted: " << endl; cin >> idGroup;
                    cout << "Insert the id of evalution that would like deleted: " << endl; cin >> idEvaluation;
                    cout << "What activity would you like deleted? \n 1. Homework \n 2. Project \n 3. Exams \n 4.Tour" << endl;
                    cout << "Insert the type of activity: "; cin >> option;
                    deleteAssignmentProfileTeacher(idTeacher, idGroup, idEvaluation, option);
                    }
                }
                if (option1 == 2)
                {//General Talks Options

                }
                if (option1 == 3) {//Homework Delivery Options
                }
                if (option1 == 4) {//Consult Attendance of Scheduled Talks
                }
                if (option1 == 5) {//Consultation of Pending Student Work
                }
                if (option1 == 6) {//Consultation Best Professor with Delivery Compliance
                }
            }

        }

        if (option == 3)
        {
            int option1;
            int idStudent;
            cout << " \n Enter the ID Student: "; cin >> idStudent;

            if (searchStudent(idStudent) != NULL)
            {
                cout << "1. Activity Register. " << endl;
                cout << "2. Talks Attendance Record. " << endl;
                cout << "3. Check the activities scheduled in the week. " << endl;
                cout << "4. Consultation of students with more than 4 courses and 100% of works delivered. " << endl;

                cout << " \n Enter Option: "; cin >> option1;

                if (option1 == 1) {}
                if (option1 == 2) {}
                if (option1 == 3) {}
                if (option1 == 4) {}
            }
        }

        if (option == 4)
        {
            break;
        }


    } while (repeat);
}
int main()
{
    //Administrator
    administratorInsert(1, "Alejandra");
    administratorInsert(2, "Dave");
    administratorInsert(3, "María");
    administratorInsert(4, "Rosibel");
    administratorInsert(5, "Jose");

    //Teacher
    teacherInsert(1, "Katherine");
    teacherInsert(2, "Rosmery");
    teacherInsert(3, "Ignacio");
    teacherInsert(4, "Marco");
    teacherInsert(5, "Samantha");

    //Student
    insertStudent(1, "Andrey");
    insertStudent(2, "Emily");
    insertStudent(3, "Elizabeth");
    insertStudent(4, "Jazmin");
    insertStudent(5, "Gilberto");

    //Course
    insertCourse(1, "Estructuras", 3);
    insertCourse(2, "POO", 3);
    insertCourse(3, "Analisis", 4);
    insertCourse(4, "Taller", 4);
    insertCourse(5, "Matematicas", 2);

    //Groups.
    insertGroupToCourse(1, 51);
    insertGroupToCourse(1, 52);
    insertGroupToCourse(1, 50);
    insertGroupToCourse(1, 49);
    insertGroupToCourse(1, 40);

    insertGroupToCourse(2, 60);
    insertGroupToCourse(2, 61);
    insertGroupToCourse(2, 62);
    insertGroupToCourse(2, 63);
    insertGroupToCourse(2, 64);

    insertGroupToCourse(3, 49);
    insertGroupToCourse(3, 48);
    insertGroupToCourse(3, 47);
    insertGroupToCourse(3, 46);
    insertGroupToCourse(3, 45);

    insertGroupToCourse(4, 10);
    insertGroupToCourse(4, 20);
    insertGroupToCourse(4, 30);
    insertGroupToCourse(4, 40);
    insertGroupToCourse(4, 50);

    insertGroupToCourse(5, 70);
    insertGroupToCourse(5, 71);
    insertGroupToCourse(5, 72);
    insertGroupToCourse(5, 73);
    insertGroupToCourse(5, 74);

    //Semester
    semesterInsert(1, 2019, 16);
    semesterInsert(2, 2019, 16);
    semesterInsert(1, 2020, 16);
    semesterInsert(2, 2020, 16);
    semesterInsert(1, 2021, 16);
    semesterInsert(2, 2021, 16);

    //
    linkTeacherToGroup(1, 1, 51);
    linkTeacherToGroup(1, 1, 52);
    linkTeacherToGroup(1, 1, 50);
    linkTeacherToGroup(1, 1, 49);
    linkTeacherToGroup(1, 1, 40);

    linkTeacherToGroup(2, 2, 60);
    linkTeacherToGroup(2, 2, 61);
    linkTeacherToGroup(2, 2, 62);
    linkTeacherToGroup(2, 2, 63);
    linkTeacherToGroup(2, 2, 64);

    linkTeacherToGroup(3, 3, 49);
    linkTeacherToGroup(3, 3, 48);
    linkTeacherToGroup(3, 3, 47);
    linkTeacherToGroup(3, 3, 46);
    linkTeacherToGroup(3, 3, 45);

    linkTeacherToGroup(4, 4, 10);
    linkTeacherToGroup(4, 4, 20);
    linkTeacherToGroup(4, 4, 30);
    linkTeacherToGroup(4, 4, 40);
    linkTeacherToGroup(4, 4, 50);

    linkTeacherToGroup(5, 5, 70);
    linkTeacherToGroup(5, 5, 71);
    linkTeacherToGroup(5, 5, 72);
    linkTeacherToGroup(5, 5, 73);
    linkTeacherToGroup(5, 5, 74);

    //
    bondStudentGroup(1, 51, 1);
    bondStudentGroup(1, 60, 2);
    bondStudentGroup(1, 49, 3);
    bondStudentGroup(1, 10, 4);
    bondStudentGroup(1, 70, 5);

    bondStudentGroup(2, 50, 1);
    bondStudentGroup(2, 60, 2);
    bondStudentGroup(2, 10, 3);
    bondStudentGroup(2, 40, 4);
    bondStudentGroup(2, 71, 5);

    bondStudentGroup(3, 51, 1);
    bondStudentGroup(3, 60, 2);
    bondStudentGroup(3, 49, 3);
    bondStudentGroup(3, 10, 4);
    bondStudentGroup(3, 70, 5);

    bondStudentGroup(4, 51, 1);
    bondStudentGroup(4, 60, 2);
    bondStudentGroup(4, 49, 3);
    bondStudentGroup(4, 10, 4);
    bondStudentGroup(4, 72, 5);

    bondStudentGroup(5, 51, 1);
    bondStudentGroup(5, 60, 2);
    bondStudentGroup(5, 49, 3);
    bondStudentGroup(5, 10, 4);
    bondStudentGroup(5, 73, 5);

    //
    bondSemesterCourse(2019, 1, 1);
    bondSemesterCourse(2019, 1, 2);
    bondSemesterCourse(2019, 1, 3);
    bondSemesterCourse(2019, 1, 4);
    bondSemesterCourse(2019, 1, 5);
    bondSemesterCourse(2019, 2, 1);
    bondSemesterCourse(2019, 2, 2);
    bondSemesterCourse(2019, 2, 3);
    bondSemesterCourse(2019, 2, 4);
    bondSemesterCourse(2019, 2, 5);

    bondSemesterCourse(2020, 1, 1);
    bondSemesterCourse(2020, 1, 2);
    bondSemesterCourse(2020, 1, 3);
    bondSemesterCourse(2020, 1, 4);
    bondSemesterCourse(2020, 1, 5);
    bondSemesterCourse(2020, 2, 1);
    bondSemesterCourse(2020, 2, 2);
    bondSemesterCourse(2020, 2, 3);
    bondSemesterCourse(2020, 2, 4);
    bondSemesterCourse(2020, 2, 5);

    bondSemesterCourse(2021, 1, 1);
    bondSemesterCourse(2021, 1, 2);
    bondSemesterCourse(2021, 1, 3);
    bondSemesterCourse(2021, 1, 4);
    bondSemesterCourse(2021, 1, 5);
    bondSemesterCourse(2021, 2, 1);
    bondSemesterCourse(2021, 2, 2);
    bondSemesterCourse(2021, 2, 3);
    bondSemesterCourse(2021, 2, 4);
    bondSemesterCourse(2021, 2, 5);


    insertTeacherActivities(1, 52, 1, 1, 1, "Tarea1", 10, 20, 7, 2021);
   /* insertTeacherActivities(1, 51, 1, 1, 22, "Tarea2", 10, 2, 7, 2019);
    insertTeacherActivities(1, 50, 1, 2, 23, "Proyecto1", 40, 20, 7, 2021);
    insertTeacherActivities(1, 40, 1, 3, 24, "Examen1", 40, 5, 12, 2021);
    insertTeacherActivities(1, 49, 1, 4, 25, "Gira1", 15, 5, 12, 2020);

    insertTeacherActivities(2, 60, 2, 1, 24, "Tarea1", 10, 23, 7, 2021);
    insertTeacherActivities(2, 61, 2, 2, 25, "Proyecto1", 15, 20, 7, 2019);
    insertTeacherActivities(2, 62, 2, 2, 25, "Proyecto2", 15, 1, 7, 2021);
    insertTeacherActivities(2, 63, 2, 3, 20, "Examen1", 20, 20, 7, 2020);
    insertTeacherActivities(2, 64, 2, 4, 21, "Gira1", 15, 2, 7, 2020);

    insertTeacherActivities(3, 49, 3, 1, 24, "Tarea1", 10, 23, 7, 2021);
    insertTeacherActivities(3, 48, 3, 1, 25, "Tarea1", 15, 20, 7, 2019);
    insertTeacherActivities(3, 47, 3, 1, 25, "Tarea1", 15, 1, 7, 2021);
    insertTeacherActivities(3, 46, 3, 1, 20, "Tarea1", 20, 20, 7, 2020);
    insertTeacherActivities(3, 45, 3, 1, 21, "Tarea1", 15, 2, 7, 2020);

    insertTeacherActivities(4, 10, 4, 2, 24, "Proyecto1", 20, 23, 7, 2021);
    insertTeacherActivities(4, 20, 4, 2, 25, "Proyecto1", 20, 20, 7, 2019);
    insertTeacherActivities(4, 30, 4, 2, 25, "Proyecto1", 20, 1, 7, 2021);
    insertTeacherActivities(4, 40, 4, 2, 20, "Proyecto1", 20, 20, 7, 2020);
    insertTeacherActivities(4, 50, 4, 3, 21, "Examen1", 60, 2, 7, 2020);

    insertTeacherActivities(5, 70, 5, 1, 10, "T1", 9, 20, 7, 2021);
    insertTeacherActivities(5, 71, 5, 2, 12, "Proyecto3", 20, 5, 12, 2021);*/
    //insertTeacherActivities(5, 72, 5, 3, 13, "Examen2", 20, 23, 7, 2021);
    //insertTeacherActivities(5, 73, 5, 3, 14, "Examen1", 40, 20, 7, 2025);
    //insertTeacherActivities(5, 74, 5, 4, 15, "Gira5", 10, 1, 7, 2019);



    //Insert activities to students
    /*registerActivitiesToStudents(1, 2, 60, 1, 24, 80);
    registerActivitiesToStudents(1, 1, 51, 1, 22, 100);
    registerActivitiesToStudents(2, 1, 50, 2, 23, 95);
    registerActivitiesToStudents(3, 3, 49, 1, 24, 75);
    registerActivitiesToStudents(1, 3, 49, 1, 24, 87);
    registerActivitiesToStudents(2, 4, 40, 2, 20, 86);
    registerActivitiesToStudents(1, 4, 10, 2, 24, 52);
    registerActivitiesToStudents(3, 4, 10, 2, 24, 78);
    registerActivitiesToStudents(2, 4, 40, 2, 20, 94);
    registerActivitiesToStudents(5, 5, 70, 1, 10, 98);
*/
    //
    insertGeneralTalksToSemester(1, 2019, 1, "Primera charla", 20, 2, 2019);
    insertGeneralTalksToSemester(1, 2019, 2, "Segunda charla", 15, 4, 2019);
    insertGeneralTalksToSemester(1, 2019, 3, "Tercera charla", 1, 5, 2019);
    insertGeneralTalksToSemester(2, 2019, 1, "Primera charla", 1, 8, 2019);
    insertGeneralTalksToSemester(2, 2019, 2, "Segunda charla", 1, 10, 2019);
    insertGeneralTalksToSemester(2, 2019, 3, "Tercera charla", 20, 10, 2019);

    insertGeneralTalksToSemester(1, 2020, 1, "Primera charla", 20, 2, 2020);
    insertGeneralTalksToSemester(1, 2020, 2, "Segunda charla", 15, 3, 2020);
    insertGeneralTalksToSemester(1, 2020, 3, "Tercera charla", 1, 4, 2020);
    insertGeneralTalksToSemester(2, 2020, 1, "Primera charla", 1, 7, 2020);
    insertGeneralTalksToSemester(2, 2020, 2, "Segunda charla", 1, 8, 2020);
    insertGeneralTalksToSemester(2, 2020, 3, "Tercera charla", 1, 9, 2020);

    insertGeneralTalksToSemester(1, 2021, 1, "Primera charla", 20, 3, 2021);
    insertGeneralTalksToSemester(1, 2021, 2, "Segunda charla", 15, 4, 2021);
    insertGeneralTalksToSemester(1, 2021, 3, "Tercera charla", 1, 5, 2021);
    insertGeneralTalksToSemester(2, 2021, 1, "Primera charla", 1, 8, 2021);
    insertGeneralTalksToSemester(2, 2021, 2, "Segunda charla", 1, 11, 2021);
    insertGeneralTalksToSemester(2, 2021, 3, "Tercera charla", 15, 11, 2021);

    //
    registerAssistanceToGeneralTalks(1, 1, 1, 2019);
    registerAssistanceToGeneralTalks(1, 2, 1, 2020);
    registerAssistanceToGeneralTalks(1, 3, 1, 2021);
    registerAssistanceToGeneralTalks(2, 1, 1, 2019);
    registerAssistanceToGeneralTalks(2, 2, 1, 2020);
    registerAssistanceToGeneralTalks(2, 3, 1, 2021);
    registerAssistanceToGeneralTalks(3, 1, 1, 2019);
    registerAssistanceToGeneralTalks(3, 2, 1, 2020);
    registerAssistanceToGeneralTalks(3, 3, 1, 2021);
    registerAssistanceToGeneralTalks(4, 1, 1, 2019);
    registerAssistanceToGeneralTalks(4, 2, 1, 2020);
    registerAssistanceToGeneralTalks(4, 3, 1, 2021);
    registerAssistanceToGeneralTalks(5, 1, 1, 2019);
    registerAssistanceToGeneralTalks(5, 2, 1, 2020);
    registerAssistanceToGeneralTalks(5, 3, 1, 2021);

    //Reports
    //CheckactivitiesTeacher(4, 2020, 2, 60, 2);

    return 0;
}
