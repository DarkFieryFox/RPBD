
#include "Schoolchildren_Mapper.h"//school
#include "Parents_Mapper.h"//parennts
#include "Progress_Mapper.h"//progress


enum option {
	NONE_OPT,
	MATERIAL_OPT,
	SPECIALIZATION_OPT
};


void printSchoolchildren(const vector<Schoolchildren*>& schoolchildren) {
	for (int i = 0; i < schoolchildren.size(); i++) {
		cout << "\t" << i + 1 << ") "
			"Name: " << schoolchildren[i]->getName()
			<< "\t" << "Surname: " << schoolchildren[i]->getSurname()
			<< "\t" << "Patronymic: " << schoolchildren[i]->getPatronymic() << endl
			<< "\t" << "Birthday: " << schoolchildren[i]->toStringDate() << endl
			<< "\t" << "Address: " << schoolchildren[i]->getAddress() << endl
			<< "\t" << "Year_admission: " << schoolchildren[i]->getYear_admission() << endl << endl;

	}
}

void printParents(const vector<Parents*>& parentss) {
	for (int i = 0; i < parentss.size(); i++) {
		cout << "\t" << i + 1 << ") "
			"Name: " << parentss[i]->getName()
			<< "\t" << "Surname: " << parentss[i]->getSurname()
			<< "\t" << "Patronymic: " << parentss[i]->getPatronymic() << endl
			<< "\t" << "Degree: " << parentss[i]->getDegree() << endl
			<< "\t" << "Address: " << parentss[i]->getAddress() << endl << endl;

	}
}



void printProgress(const vector<Progress*>& progress) {
	for (int i = 0; i < progress.size(); i++) {
		cout << "\t" << i + 1 << ") "
			"Classs: " << progress[i]->getClasss()
			<< "\t" << "Subject: " << progress[i]->getSubject() 
			<< "\t" << "Year: " << progress[i]->getYear() 
			<< "\t" << "Half_yearly: " << progress[i]->getHalf_yearly()
			<< "\t" << "Quarter: " << progress[i]->getQuarter()
			<< "\t" << "Yearly: " << progress[i]->getYearly()
			<< "\t" << "Exam: " << progress[i]->getExam() 
			<< "\t" << "Finaly: " << progress[i]->getFinaly() << endl << endl;

	}
}



pair<long, long> choice(const vector<Schoolchildren*>& schoolchild, const vector<Parents*>& parents, const vector<Progress*>& progress, option opt) {
	long num, num2;
	cout << "Enter schoolchild number from (or 0 to break)" << endl;
	printSchoolchildren(schoolchild);
	cin >> num;
	if (opt == MATERIAL_OPT) {
		cout << "Enter number of parents (or 0 to break)" << endl;
		printParents(parents);
		cin >> num2;
	}
	if (opt == SPECIALIZATION_OPT) {
		cout << "Enter number of progress (or 0 to break)" << endl;
		printProgress(progress);
		cin >> num2;
	}
	return { num, num2 };
}



int schoolchildMenu(int variant,
	Schoolchildren& schoolchild, Schoolchildren_Mapper& schoolchild_mapper, vector<Schoolchildren*>& schoolchildren,
	Parents& parents, Parents_Mapper& parents_mapper, vector<Parents*>& parentss,
	Progress& progress, Progress_Mapper& progress_mapper,
	vector<Progress*>& progresss) {
	string surname,name, patronymic,address,birthday;
	int id,year_admission;
	long num, num_;
	Date birthday_;
	pair<long, long> choice_;
	switch (variant)
	{
	case 1:
		printSchoolchildren(schoolchild_mapper.findAll());
		break;
	case 2:
		cout << "Enter name of the schoolchild:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, name);

		cout << "Enter surname of the schoolchild:" << endl;
		getline(cin, surname);

		cout << "Enter patronymic:" << endl;
		getline(cin, patronymic);

		cout << "Enter birthday (year-month-day):" << endl;
		getline(cin, birthday);
	
		cout << "Enter address:" << endl;
		getline(cin, address);

		cout << "Enter year_admission:" << endl;
		cin >> year_admission;

		schoolchild.setId(-1);
		schoolchild.setName(name);
		schoolchild.setSurname(surname);
		schoolchild.setPatronymic(patronymic);
		birthday_ = schoolchild.setStringDate(birthday);
		schoolchild.setDate(birthday_);
		schoolchild.setAddress(address);
		schoolchild.setYear_admission(year_admission);
		schoolchild_mapper.save(schoolchild);
		break;

	case 3:
		num = choice(schoolchildren = schoolchild_mapper.findAll(),
			parentss = parents_mapper.findAll(),
			progresss = progress_mapper.findAll(), NONE_OPT).first;
		if (!num) break;

		cout << "Enter name of the schoolchild:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, name);

		cout << "Enter surname of the schoolchild:" << endl;
		getline(cin, surname);

		cout << "Enter patronymic:" << endl;
		getline(cin, patronymic);

		cout << "Enter birthday (year-month-day):" << endl;
		getline(cin, birthday);

		cout << "Enter address:" << endl;
		getline(cin, address);

		cout << "Enter year_admission:" << endl;
		cin >> year_admission;

		schoolchild.setId(schoolchildren[num - 1L]->getId());
		schoolchild.setName(name);
		schoolchild.setSurname(surname);
		schoolchild.setPatronymic(patronymic);
		birthday_ = schoolchild.setStringDate(birthday);
		schoolchild.setDate(birthday_);
		schoolchild.setAddress(address);
		schoolchild.setYear_admission(year_admission);
		schoolchild_mapper.save(schoolchild);

		break;

	case 4:
		printSchoolchildren(schoolchildren = schoolchild_mapper.findAll());
		num = choice(schoolchildren = schoolchild_mapper.findAll(),
			parentss = parents_mapper.findAll(),
			progresss = progress_mapper.findAll(), NONE_OPT).first;
		if (!num) return 0;
		schoolchild_mapper.remove(schoolchildren[num - 1]->getId());
		break;
	case 5:
		choice_ = choice(schoolchildren = schoolchild_mapper.findAll(),
			parentss = parents_mapper.findAll(),
			progresss = progress_mapper.findAll(), MATERIAL_OPT);
		num = choice_.first;
		num_ = choice_.second;
		if (!(num && num_)) break;
		
		schoolchild_mapper.addParents(schoolchildren[num - 1]->getId(), parentss[num_ - 1]->getId());
		break;

	case 6:
		choice_ = choice(schoolchildren = schoolchild_mapper.findAll(),
			parentss = parents_mapper.findAll(),
			progresss = progress_mapper.findAll(), MATERIAL_OPT);
		num = choice_.first;
		num_ = choice_.second;
		if (!(num && num_)) break;
	
		schoolchild_mapper.removeParents(schoolchildren[num - 1]->getId(), parentss[num_ - 1]->getId());

		break;

	case 7:
		/*cout << "7. Add progress to schoolchild" << endl;*/
		choice_ = choice(schoolchildren = schoolchild_mapper.findAll(),
			parentss = parents_mapper.findAll(),
			progresss = progress_mapper.findAll(), SPECIALIZATION_OPT);
		num = choice_.first;
		num_ = choice_.second;
		if (!(num && num_)) break;
		schoolchild_mapper.addProgress(schoolchildren[num - 1]->getId(), progresss[num_ - 1]->getId());
		break;

	case 8:
		/*cout << "8. Remove progress from schoolchild" << endl; */
		choice_ = choice(schoolchildren = schoolchild_mapper.findAll(),
			parentss = parents_mapper.findAll(),
			progresss = progress_mapper.findAll(), SPECIALIZATION_OPT);
		num = choice_.first;
		num_ = choice_.second;
		if (!(num && num_)) break;
		schoolchild_mapper.removeProgress(schoolchildren[num - 1]->getId(), progresss[num_ - 1]->getId());
		break;

	default:
		break;
	}
	return 0;
}

int parentsMenu(int variant, Parents& parents,
	Parents_Mapper& parents_mapper, vector<Parents*>& parentss) {
	string name, surname, patronymic, degree, address;
	int id;
	switch (variant)
	{
	case 1:
		printParents(parents_mapper.findAll());
		break;
	case 2:
		cout << "Enter name:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, name);

		cout << "Enter surname:" << endl;
		getline(cin, surname);

		cout << "Enter patronymic:" << endl;
		getline(cin, patronymic);

		cout << "Enter degree:" << endl;
		getline(cin, degree);
		cout << "Enter address:" << endl;
		getline(cin,  address);


		parents.setId(-1);
		parents.setName(name);
		parents.setSurname(surname);
		parents.setPatronymic(patronymic);
		parents.setDegree(degree);
		parents.setAddress(address);

		parents_mapper.save(parents);
		break;

	case 3:

		printParents(parentss = parents_mapper.findAll());
		cout << "Enter parents id" << endl;
		cin >> id;
		cout << "Enter new name:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, name);
		cout << "Enter surname:" << endl;
		getline(cin, surname);

		cout << "Enter patronymic:" << endl;
		getline(cin, patronymic);

		cout << "Enter degree:" << endl;
		getline(cin, degree);
		cout << "Enter address:" << endl;
		getline(cin, address);

		parents.setId(parentss[id - 1L]->getId());
		parents.setName(name);
		parents.setSurname(surname);
		parents.setPatronymic(patronymic);
		parents.setDegree(degree);
		parents.setAddress(address);
		parents_mapper.save(parents);
		break;

	case 4:
		printParents(parentss = parents_mapper.findAll());
		cout << "Enter parents id" << endl;
		cin >> id;
		parents_mapper.remove(parentss[id - 1L]->getId());
		break;


	default:
		break;
	}
	return 0;
}

int progressMenu(int variant, Progress& progress,
	Progress_Mapper& progress_mapper, vector<Progress*>& progresss) {
	string classs,subject;
	int id,year,yearly,half_yearly,exam,quarter,finaly;
	switch (variant)
	{
	case 1:
		printProgress(progress_mapper.findAll());
		break;
	case 2:
		cout << "Enter class:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, classs);
		cout << "Enter subject:" << endl;
		getline(cin, subject);
		cout << "Enter year:" << endl;
		cin >> year;
		cout << "Enter half_yearly:" << endl;
		cin >> half_yearly;
		cout << "Enter quarter:" << endl;
		cin >> quarter;
		cout << "Enter yearly:" << endl;
		cin >> yearly;
		cout << "Enter exam:" << endl;
		cin >> exam;
		cout << "Enter finaly:" << endl;
		cin >> finaly;

		progress.setId(-1);
		progress.setClasss(classs);
		progress.setSubject(subject);
		progress.setYear(year);
		progress.setHalf_yearly(half_yearly);
		progress.setQuarter(quarter);
		progress.setYearly(yearly);
		progress.setExam(exam);
		progress.setFinaly(finaly);

		progress_mapper.save(progress);
		break;

	case 3:
		printProgress(progresss = progress_mapper.findAll());
		cout << "Enter progress id" << endl;
		cin >> id;
		cout << "Enter new classs:" << endl;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, classs);
		cout << "Enter new subject:" << endl;
		getline(cin, subject);
		cout << "Enter year:" << endl;
		cin >> year;
		cout << "Enter half_yearly:" << endl;
		cin >> half_yearly;
		cout << "Enter quarter:" << endl;
		cin >> quarter;
		cout << "Enter yearly:" << endl;
		cin >> yearly;
		cout << "Enter exam:" << endl;
		cin >> exam;
		cout << "Enter finaly:" << endl;
		cin >> finaly;

		progress.setId(progresss[id - 1L]->getId());
		progress.setClasss(classs);
		progress.setSubject(subject);
		progress.setYear(year);
		progress.setHalf_yearly(half_yearly);
		progress.setQuarter(quarter);
		progress.setYearly(yearly);
		progress.setExam(exam);
		progress.setFinaly(finaly);
		progress_mapper.save(progress);
		break;

	case 4:
		printProgress(progresss = progress_mapper.findAll());
		cout << "Enter progress id" << endl;
		cin >> id;
		progress_mapper.remove(progresss[id - 1L]->getId());
		break;


	default:
		break;
	}
	return 0;
}




void menu() {
	DataBase db = DataBase();

	Parents_Mapper parentss_mapper(db);
	Progress_Mapper progress_mapper(db);
	Schoolchildren_Mapper schoolchildren_mapper(db, parentss_mapper, progress_mapper);

	vector<Schoolchildren*> schoolchildren;
	Schoolchildren schoolchild;

	vector<Parents*> parentss;
	Parents parents;


	vector<Progress*> progresss;
	Progress progress;



	pair<long, long> c;

	vector<int> nums;
	long num;
	long num2;
	double d_num;
	bool flag;
	int variant, sec_variant;
	while (true) {
		cout << "Journal" << endl;
		cout << "----------------------" << endl;
		cout << "1. Schoolchildren" << endl;
		cout << "2. Parents" << endl;
		cout << "3. Progress" << endl;
		cout << "0. Exit" << endl;
		cout << "\nEnter the item" << endl;

		cin >> variant;

		switch (variant) {
		
		
		case 1:
			cout << "Schoolchild:" << endl;
			cout << "1. List all schoolchildren" << endl;
			cout << "2. Add an schoolchild" << endl;
			cout << "3. Edit an schoolchild" << endl;
			cout << "4. Remove an schoolchild" << endl;
			cout << "5. Add parents to schoolchild" << endl;
			cout << "6. Remove parents from schoolchild" << endl;
			cout << "7. Add progress to schoolchild" << endl;
			cout << "8. Remove progress from schoolchild" << endl;
			cin >> sec_variant;
			schoolchildMenu(sec_variant, schoolchild, schoolchildren_mapper, schoolchildren,
				parents, parentss_mapper, parentss,
				progress, progress_mapper, progresss);
			cout << "Click the any button to continue";
			cin.get();
			cin.get();
			system("cls");
			break;

		case 2: //Parent menu
			cout << "Parents:" << endl;
			cout << "1. List all parentss" << endl;
			cout << "2. Add an parents" << endl;
			cout << "3. Edit an parents" << endl;
			cout << "4. Remove an parents" << endl;
			cout << "0. Back" << endl;
			cin >> sec_variant;
			parentsMenu(sec_variant, parents, parentss_mapper, parentss);
			cout << "Click the any button to continue";
			cin.get();
			cin.get();
			system("cls");
			break;
		case 3:
			//Progress menu
			cout << "Progress:" << endl;
			cout << "1. List all progresss" << endl;
			cout << "2. Add an progress" << endl;
			cout << "3. Edit an progress" << endl;
			cout << "4. Remove an progress" << endl;
			cout << "0. Back" << endl;
			cin >> sec_variant;
			progressMenu(sec_variant, progress, progress_mapper, progresss);
			cout << "Click the any button to continue";
			cin.get();
			cin.get();
			system("cls");
			break;
		
		
		case 0:
			return;
		}
	}
}

int main() {
	setlocale(0, "");
	menu();
	return 0;
}