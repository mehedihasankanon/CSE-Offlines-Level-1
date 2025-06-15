#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Course
{
    string name;
    float creditHour;

public:
    Course()
    {
        name = "";
        creditHour = 0.0;
    }
    Course(string name, float creditHour)
    {
        this->name = name;
        this->creditHour = creditHour;
    }

    string getName() { return name; }
    float getCreditHour() { return creditHour; }

    void setName(string name) { this->name = name; }
    void setCreditHour(float creditHour) { this->creditHour = creditHour; }

    void display()
    {
        cout << "Course Name: " << name << ", Credit Hour: " << creditHour;
    }
};

class Student
{
    string name;
    int id;
    Course *courses;
    int totalCourses;
    int maxCourses;
    float *gradePoints;

public:
    Student()
    {
        name = "";
        id = totalCourses = maxCourses = 0;
        courses = nullptr;
        gradePoints = nullptr;
    }
    Student(string name, int id, int maxCourses)
    {
        this->name = name;
        this->id = id;
        totalCourses = 0;
        this->maxCourses = maxCourses;

        courses = new Course[maxCourses];
        gradePoints = new float[maxCourses];
    }
    Student(const Student &st)
    {
        name = st.name;
        id = st.id;
        courses = new Course[st.maxCourses];
        totalCourses = st.totalCourses;
        maxCourses = st.maxCourses;
        gradePoints = new float[maxCourses];

        for (int i = 0; i < totalCourses; i++)
        {
            gradePoints[i] = st.gradePoints[i];
            courses[i].setName(st.courses[i].getName());
            courses[i].setCreditHour(st.courses[i].getCreditHour());
        }
    }
    ~Student()
    {
        delete[] courses;
        delete[] gradePoints;
    }

    void setName(string name) { this->name = name; }
    void setId(int id) { this->id = id; }
    void setInfo(string name, int id)
    {
        setName(name);
        setId(id);
    }

    void addCourse(Course c)
    {
        if (totalCourses == maxCourses)
        {
            cout << "Cannot add more courses to " << name << endl;
            return;
        }
        courses[totalCourses].setCreditHour(c.getCreditHour());
        courses[totalCourses].setName(c.getName());
        gradePoints[totalCourses] = 0.0;
        totalCourses++;
    }
    void addCourse(Course c, float gradePoint)
    {
        if (totalCourses == maxCourses)
        {
            cout << "Cannot add more courses to " << name << endl;
            return;
        }
        if (gradePoint < 0)
        {
            cout << "Error: grade point cannot be less than zero" << endl;
            return;
        }
        if (gradePoint > 4.0)
        {
            cout << "Error: grade point must be less than or equal to 4.0" << endl;
            return;
        }

        addCourse(c);
        gradePoints[totalCourses - 1] = gradePoint; // totalCourses already increased by one
    }

    void setGradePoint(Course c, float gradePoint)
    {
        for (int i = 0; i < totalCourses; i++)
        {
            if (courses[i].getName() == c.getName())
            {
                gradePoints[i] = gradePoint;
                return;
            }
        }
        cout << "Not registered for the course" << endl;
        return;
    }
    void setGradePoint(float *gradePoints, int n)
    {
        if (n > totalCourses)
        {
            cout << "Error: number of courses to change is more than total courses taken" << endl;
            return;
        }

        for (int i = 0; i < n; i++)
        {
            if (gradePoints[i] < 0 || gradePoints[i] > 4.0)
            {
                cout << "Error: " << i + 1 << "-th course invalid grade point " << endl;
                continue;
            }
            this->gradePoints[i] = gradePoints[i];
        }
    }

    string getName() { return name; }
    float getCGPA()
    {
        // CGPA == SUM(grade * cr. hr) / SUM(cr. hr)

        float CG = 0, TC = 0;
        if(totalCourses == 0) return 0.0;

        for (int i = 0; i < totalCourses; i++)
        {
            CG += gradePoints[i] * courses[i].getCreditHour();
            TC += courses[i].getCreditHour();
        }

        return CG / TC;
    }
    float getGradePoint(Course c)
    {
        for (int i = 0; i < totalCourses; i++)
        {
            if (courses[i].getName() == c.getName())
                return gradePoints[i];
        }
        return -1.0;
    }
    int getTotalCourses() { return totalCourses; }
    float getTotalCreditHours()
    {
        float TC = 0;
        for (int i = 0; i < totalCourses; i++)
        {
            TC += courses[i].getCreditHour();
        }
        return TC;
    }
    Course getMostFavoriteCourse()
    {
        int mx = 0;
        for (int i = 0; i < totalCourses; i++)
        {
            mx = gradePoints[i] > gradePoints[mx] ? i : mx;
        }
        return Course(courses[mx]);
    }
    Course getLeastFavoriteCourse()
    {
        int mn = 0;
        for (int i = 0; i < totalCourses; i++)
        {
            mn = gradePoints[i] < gradePoints[mn] ? i : mn;
        }
        return Course(courses[mn]);
    }
    Course *getFailedCourses(int &count)
    {
        int failed[totalCourses] = {0}, cnt = 0;
        for (int i = 0; i < totalCourses; i++)
        {
            if (gradePoints[i] < 2.0)
            {
                cnt++;
                failed[i]++;
            }
        }
        count = cnt;

        // cerr << endl << endl << count << endl << endl;

        if (cnt == 0)
            return nullptr;

        Course *failedCourses = new Course[cnt];
        int idx = 0;
        for (int i = 0; i < totalCourses; i++)
        {
            if (failed[i])
            {
                failedCourses[idx].setName(courses[i].getName());
                failedCourses[idx].setCreditHour(courses[i].getCreditHour());
                idx++;
            }
        }
        return failedCourses;
    }

    void display()
    {
        cout << "==================================" << endl;
        cout << "Student Name: " << name << ", ID: " << id << endl;
        for (int i = 0; i < totalCourses; i++)
        {
            courses[i].display();
            cout << ", gradePoint: " << gradePoints[i] << endl;
        }
        cout << "CGPA: " << getCGPA() << endl;
        cout << "Total Credit Hours Earned: " << getTotalCreditHours() << endl;
        cout << "Most Favorite Course: " << getMostFavoriteCourse().getName() << endl;
        cout << "Least Favorite Course: " << getLeastFavoriteCourse().getName() << endl;
        cout << "==================================" << endl;
    }
};

Student *students[100];
int totalStudents = 0;

Student getTopper()
{
    if (totalStudents == 0)
        return Student();

    float cg = students[0]->getCGPA();

    for (int i = 1; i < totalStudents; i++)
    {
        cg = cg > students[i]->getCGPA() ? cg : students[i]->getCGPA();
    }

    for (int i = 0; i < totalStudents; i++)
    {
        // the first student who got the highest CG
        // cerr << students[i]->getName() << endl;
        if (fabs(cg - students[i]->getCGPA()) < 1e-9)
            return Student(*students[i]);
    }
}

Student getTopper(Course c)
{
    float gr = -1;

    for (int i = 0; i < totalStudents; i++)
    {
        gr = gr > students[i]->getGradePoint(c) ? gr : students[i]->getGradePoint(c);
    }

    if (gr < 0)
        return Student();

    for (int i = 0; i < totalStudents; i++)
    {
        if (fabs(gr - students[i]->getGradePoint(c)) < 1e-9)
            return Student(*students[i]);
    }
}

int main()
{
    // freopen("error.txt","w",stderr);

    // generate courses  const
    int COURSE_COUNT = 6;
    Course courses[COURSE_COUNT] = {
        Course("CSE107", 3),
        Course("CSE105", 3),
        Course("CSE108", 1.5),
        Course("CSE106", 1.5),
        Course("EEE164", 0.75),
        Course("ME174", 0.75),
    };
    float gradePoints[COURSE_COUNT] = {4.0, 4.0, 3.5, 3.5, 4.0, 3.25};

    // generate students
    Student s1 = Student("Sheldon", 1, 5);
    students[totalStudents++] = &s1;

    // add courses to s1
    s1.addCourse(courses[0]);
    s1.addCourse(courses[1]);
    s1.addCourse(courses[2]);
    s1.addCourse(courses[3]);
    s1.addCourse(courses[4]);
    s1.addCourse(courses[5]);
    s1.setGradePoint(gradePoints, s1.getTotalCourses());
    s1.display();
    Student s2 = Student("Penny", 2, 5);
    students[totalStudents++] = &s2;
    s2.addCourse(courses[0]);
    s2.addCourse(courses[2]);
    s2.addCourse(courses[5]);
    s2.setGradePoint(gradePoints, s2.getTotalCourses());
    s2.setGradePoint(courses[0], 3.25);
    s2.display();
    Student s3 = s2;
    students[totalStudents++] = &s3;
    s3.setName("Leonard");
    s3.setId(3);
    s3.setGradePoint(gradePoints, s3.getTotalCourses());
    s3.addCourse(courses[1], 3.75);
    s3.display();
    Student s4 = s3;
    students[totalStudents++] = &s4;
    s4.setInfo("Howard", 4);
    s4.setGradePoint(gradePoints, s4.getTotalCourses());
    s4.addCourse(courses[3], 3.75);
    s4.display();
    Student s5 = s4;
    students[totalStudents++] = &s5;
    s5.setInfo("Raj", 5);
    s5.setGradePoint(gradePoints, s5.getTotalCourses());
    s5.setGradePoint(courses[0], 1.5);
    s5.setGradePoint(courses[2], 2.0);
    s5.setGradePoint(courses[5], 1.75);
    s5.setGradePoint(courses[3], 3.75);
    s5.display();
    int failedCount;
    Course *failedCourses = s5.getFailedCourses(failedCount);
    cout << "Failed Courses for " << s5.getName() << ":" << endl;
    for (int i = 0; i < failedCount; ++i)
    {
        failedCourses[i].display();
        cout << endl;
    }
    delete[] failedCourses;
    cout << "==================================" << endl;
    Student topper = getTopper();
    cout << "Topper: " << topper.getName() << endl;
    cout << "Topper CGPA: " << topper.getCGPA() << endl;
    cout << "==================================" << endl;
    for (int i = 0; i < COURSE_COUNT; ++i)
    {
        Course c = courses[i];
        Student topperInCourse = getTopper(c);
        cout << "Topper in " << c.getName() << ": " << topperInCourse.getName() << endl;
        cout << "Topper in " << c.getName() << " gradePoint: " << topperInCourse.getGradePoint(c) << endl;
        cout << "==================================" << endl;
    }
    return 0;
}
