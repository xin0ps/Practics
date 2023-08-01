
#include <iostream>
#include <string>
#include <fstream>
            using namespace std;

        class Person
        {
        private:
            string _name, _surname, _email;
            int _age;

        public:
            Person(string name, string surname, int age, string email)
            {
                SetAge(age);
                SetEmail(email);
                SetName(name);
                SetSurname(surname);
            }

            // Accessors
            string GetName() const { return _name; }
            string GetSurname() const { return _surname; }
            string GetEmail() const { return _email; }
            int GetAge() const { return _age; }

            void SetName(string name)
            {
                if (!name.empty())
                {
                    if (name[0] >= 'A' && name[0] <= 'Z')
                    {
                        if (name.length() >= 3)
                            _name = name;
                        else
                            throw exception("Minimum 3 symbol olmalidir adda");
                    }
                    else
                        throw exception("Adin ilk symbolu buyuk olmalidir");
                }
                else
                    throw exception("Ad bosh ola bilmez");
            }

            void SetSurname(string surname)
            {
                if (!surname.empty())
                {
                    if (surname[0] >= 'A' && surname[0] <= 'Z')
                    {
                        if (surname.length() >= 3)
                            _surname = surname;
                        else
                            throw exception("Minimum 3 sembol olmalidir Soyadda");
                    }
                    else
                        throw exception("Soyadda ilk sembolu buyuk olmalidir");
                }
                else
                    throw exception("Soyad bosh ola bilmez");
            }

            void SetEmail(string email)
            {
                if (!email.empty())
                {
                    if (email.length() >= 8)
                        _email = email;
                    else
                        throw exception("Minimum 8 sembol olmalidir email");
                }
                else
                    throw exception("Email bosh ola bilmez");
            }

            void SetAge(int age)
            {
                if (age >= 18 && age <= 35)
                    _age = age;
                else
                    throw exception("Yas Maksimum 35 minimum 18 ola biler");
            }

            virtual void Show() const
            {
                cout << _name << " " << _surname << " " << _age << " " << _email << " ";
            }

            virtual string GetData() const = 0
            {
                string data = _name + " " + _surname + " " + to_string(_age) + " " + _email;
                return data;
            }
        };
        class Student : public Person
        {
        private:
            string _group;
            float _avg;

        public:
            Student(string name, string surname, int age, string email, float avg, const string group)
                : Person(name, surname, age, email)
            {
                SetAvg(avg);
                SetGroup(group);
            }

            float GetAvg() const { return _avg; }
            string GetGroup() const { return _group; }

            void SetAvg(float avg)
            {
                if (avg >= 1 && avg <= 12)
                    _avg = avg;
                else
                    throw exception("Qiymet ortalamasi dogru deyil");
            }

            void SetGroup(const string group)
            {
                if (!group.empty())
                    _group = group;
                else
                    throw exception("qrup dogru deyil");
            }

            void Show() const override
            {
                Person::Show();
                cout << _avg << endl;
                cout << _group << endl;
            }

            string GetData() const override
            {
                string data = Person::GetData() + " " + to_string(_avg) + " " + _group + "\n";
                return data;
            }
        };

        // Function to find a student by their name in the students array
        Student* findStudentByName(const string& name, Person** students, int count)
        {
            for (int i = 0; i < count; i++)
            {
                Student* student = dynamic_cast<Student*>(students[i]);
                if (student && student->GetName() == name)
                    return student;
            }
            return nullptr;
        }

        void getAllStudentFromFile(string filename, Person**& students, int& count)
        {
            ifstream file(filename, ios::in);

            if (file.is_open())
            {
                string name, surname, email, group;
                int age;
                float avg;
                while (!file.eof())
                {
                    if (!file.eof())
                    {
                        file >> name;
                        file >> surname;
                        file >> age;
                        file >> avg;
                        file >> group;
                        getline(file, email);

                        Student* newSt = new Student(name, surname, age, email, avg, group);

                        Person** newStudents = new Person * [count + 1];
                        for (size_t i = 0; i < count; i++)
                            newStudents[i] = students[i];
                        newStudents[count] = newSt;
                        count++;

                        if (students != nullptr)
                            delete[] students;
                        students = newStudents;
                    }
                }
                file.close();
            }
        }

        void WriteToFile(string fileName, Person**& students, int& count)
        {
            ofstream file(fileName, ios::out);

            if (file.is_open())
            {
                for (size_t i = 0; i < count; i++)
                    file << students[i]->GetData();
            }
        }

        class Teacher : public Person
        {
        private:
            Student** students;
            float _salary;

        public:
            Teacher(string name, string surname, int age, string email, float salary)
                : Person(name, surname, age, email)
            {
                SetSalary(salary);
            }

            float GetSalary() const { return _salary; }

            void SetSalary(float salary)
            {
                if (salary >= 2500 && salary <= 5500)
                    _salary = salary;
                else
                    throw exception("Maas dogru deyil");
            }

            void Show() const override
            {
                Person::Show();
                cout << _salary << endl;
            }

            string GetData() const override
            {
                string data = Person::GetData() + " " + to_string(_salary);
                return data;
            }
        };

     

        int main()
        {
            Teacher* teacher = new Teacher("Cavid", "Atamoghlanov", 25, "cavid@gmail.com", 3525);

            int count = 0;
            Person** students = nullptr;

            
            
            int selectFromMenu;
            while (true)
            {
             /*   cout << "\n\n[1] => Login\n"
                    << "[2] =>Register\n";
                cout << "Select an option from the menu: ";*/

                cout << "\n\n[1] => Show All Students\n"
                    << "[2] => Show Students in the Same Group\n"
                    << "[3] => Create Student\n"
                    << "[4] => Delete Student\n"
                    << "[5] => Save\n"
                    << "[0] => Exit\n";
                cout << "menudan secim et: ";
                cin >> selectFromMenu;

                if (selectFromMenu == 1)
                {
                    for (size_t i = 0; i < count; i++)
                        students[i]->Show();
                }
                else if (selectFromMenu == 2)
                {
                    string group;
                    cout << "Group daxil et: ";
                    cin.ignore();
                    getline(cin, group);
                    for (size_t i = 0; i < count; i++)
                    {
                        Student* student = dynamic_cast<Student*>(students[i]);
                        if (student && student->GetGroup() == group)
                            student->Show();
                    }
                }
                else if (selectFromMenu == 3)
                {
                    string name, surname, email, group;
                    int age;
                    float avg;
                    cout << "Enter the student details (name, surname, age, email, avg, group): ";
                    cin >> name >> surname >> age >> email >> avg >> group;

                    Student* newSt = new Student(name, surname, age, email, avg, group);

                    Person** newStudents = new Person * [count + 1];
                    for (size_t i = 0; i < count; i++)
                        newStudents[i] = students[i];
                    newStudents[count] = newSt;
                    count++;

                    if (students != nullptr)
                        delete[] students;
                    students = newStudents;

                    cout << "Student elave edildi.\n";
                }
                else if (selectFromMenu == 4)
                {
                    string nameToDelete;
                    cout << "Silmek istediyin telebenin adini daxil et: ";
                    cin >> nameToDelete;

                    Student* studentToDelete = findStudentByName(nameToDelete, students, count);
                    if (studentToDelete)
                    {
                        
                        int indexToDelete = -1;
                        for (int i = 0; i < count; i++)
                        {
                            if (students[i] == studentToDelete)
                            {
                                indexToDelete = i;
                                break;
                            }
                        }

                       
                        delete studentToDelete;
                        for (int i = indexToDelete; i < count - 1; i++)
                            students[i] = students[i + 1];

                        count--;
                        cout << "Student " << nameToDelete << " deleted.\n";
                    }
                    else
                    {
                        cout << "Student " << nameToDelete << " tapilmadi.\n";
                    }
                }
                else if (selectFromMenu == 5)
                {
                    WriteToFile("allStudents.txt", students, count);
                    cout << "yadda saxlandi.\n";
                }
                else if (selectFromMenu == 0)
                {
                    cout << "Bye Bye!\n";
                    break;
                }
                else
                {
                    cout << "\n\n!!!!! yanlis secim !!!!!\n\n";
                }
            }

          
            for (int i = 0; i < count; i++)
                delete students[i];
            delete[] students;

            delete teacher;

 
        }
