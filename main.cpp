#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
 
using namespace std;

class Person
{
public:
	string mName;
	uint16_t mAge;
	double mSalary;

	Person()
	{
		mAge = 0;
		mSalary = 0;
		mName = "";
	}
	Person(string arg_name, uint16_t arg_age, double arg_salary)
	{
		mAge = arg_age;
		mSalary = arg_salary;
		mName = arg_name;
	}

	bool operator ==(const Person& arg_person) const
	{
		if (mName == arg_person.mName && mAge == arg_person.mAge && mSalary == arg_person.mSalary)
		{
			return true;
		}
		else return false;
	}
	bool operator < (const Person& arg_person) const
	{
		if (mName < arg_person.mName)
		{
			return true;
		}
		else return false;
	}
};

class Building
{
protected:
	string mBuildingName;
	string mType;
	Person mCoordinator;
	vector<Person> mEmployees;
	vector<Person> mCitizens;
public:
	Building()
	{

	}
	Building(string arg_mBuildingName, string arg_mType)
	{
		mType = arg_mType;
		mBuildingName = arg_mBuildingName;
	}

	virtual void add(const Person& arg_person) = 0;
	virtual void remove(const Person& arg_person) = 0;
	virtual Building* operator +(const Person& arg_person) = 0;
	virtual Building* operator -()
	{
	    return nullptr;
	}
	virtual Building* operator -(const Person& arg_person)
	{
	    return nullptr;
	}

	string getBuildingName() const
	{
		return mBuildingName;
	}
	string getType() const
	{
		return mType;
	}
	uint16_t getEmployeesSize() const
	{
		return mEmployees.size();
	}
	uint16_t getCitizensSize() const
	{
		return mCitizens.size();
	}
	Person getEmployee(uint16_t arg_index) const
	{
		return mEmployees[arg_index];
	}
	Person getCitizen(uint16_t arg_index) const
	{
		return mCitizens[arg_index];
	}
	Person getCoordinator() const
	{
		return mCoordinator;
	}
};

class CityHall : public Building
{
public:
    CityHall(){}
	CityHall (string arg_mBuildingName) : Building(arg_mBuildingName,"CityHall")
	{
		mCitizens.clear();
		mCoordinator = Person();
	}

	virtual Building* operator +(const Person& arg_person)
	{
		if (mCoordinator.mName == "")
		{
			mCoordinator = arg_person;
		}
		return this;
	}
	virtual Building* operator -()
	{
		Person mCoordinator;
		return this;
	}
	virtual void add(const Person& arg_person)
	{
		mCitizens.push_back(arg_person);
	}
	virtual void remove(const Person& arg_person)
	{
		mCitizens.erase(find(mCitizens.begin(), mCitizens.end(), arg_person));
	}
};
class Hospital : public Building
{
public:
	Hospital(string arg_mBuildingName): Building(arg_mBuildingName,"Hospital")
	{
		mCitizens.clear();
		mEmployees.clear();
	}

	virtual Building* operator +(const Person& arg_person)
	{
		mEmployees.push_back(arg_person);
		return this;
	}
	virtual Building* operator -(const Person& arg_person)
	{
		mEmployees.erase(find(mCitizens.begin(), mCitizens.end(), arg_person));
		return this;
	}
	virtual void add(const Person& arg_person)
	{
		mCitizens.push_back(arg_person);
	}
	virtual void remove(const Person& arg_person)
	{
		mCitizens.erase(find(mCitizens.begin(), mCitizens.end(), arg_person));
	}
};

class PoliceStation : public Building
{
public:
	PoliceStation(string arg_mBuildingName): Building(arg_mBuildingName,"PoliceStation")
	{
		mCitizens.clear();
		mEmployees.clear();
	}

	virtual Building* operator +(const Person& arg_person)
	{
		mEmployees.push_back(arg_person);
		return this;
	}
	virtual Building* operator -(const Person& arg_person)
	{
		mEmployees.erase(find(mCitizens.begin(), mCitizens.end(), arg_person));
		return this;
	}
	virtual void add(const Person& arg_person)
	{
		mCitizens.push_back(arg_person);
	}
	virtual void remove(const Person& arg_person)
	{
		mCitizens.erase(find(mCitizens.begin(), mCitizens.end(), arg_person));
	}
};

class House : public Building
{
private:
	uint16_t mMaxNumber;
public:
	House(string arg_mBuildingName, uint16_t arg_mMaxNumber): Building(arg_mBuildingName,"House")
	{
		mCitizens.clear();
		mCoordinator = Person();
		mMaxNumber = arg_mMaxNumber;
	}

	virtual Building* operator +(const Person& arg_person)
	{
		if (mCoordinator.mName == "")
		{
			mCoordinator = arg_person;
		}
		return this;
	}
	virtual Building* operator -()
	{
		Person* mCoordinator = new Person();
		return this;
	}
	virtual void add(const Person& arg_person)
	{
		if (mCitizens.size() < mMaxNumber)
		{
			mCitizens.push_back(arg_person);
		}
	}
	virtual void remove(const Person& arg_person)
	{
		if (arg_person.mAge >= 18)
		{
			mCitizens.erase(find(mCitizens.begin(), mCitizens.end(), arg_person));
		}
	}
};

class Block : public Building
{
private:
	uint16_t mMaxNumberPerFloor;
public:
	Block(string arg_mBuildingName, const uint16_t arg_no_of_floors, const uint16_t arg_max_no_per_floor) : Building(arg_mBuildingName,"Block")
	{
		mMaxNumberPerFloor = arg_max_no_per_floor;
		mCoordinator = Person();
		mCitizens.clear();
		mCitizens.reserve(arg_no_of_floors * mMaxNumberPerFloor);
	}

	virtual Building* operator +(const Person& arg_person)
	{
		if (mCoordinator.mName == "")
		{
			mCoordinator = arg_person;
		}
		return this;
	}
	virtual Building* operator -()
	{
		mCoordinator = Person();
		return this;
	}
	virtual void add(const Person& arg_person)
	{
		if (mCitizens.size() < mCitizens.capacity())
		{
			mCitizens.push_back(arg_person);
		}
	}
	virtual void remove(const Person& arg_person)
	{
		if (arg_person.mAge >= 18)
		{
			mCitizens.erase(find(mCitizens.begin(), mCitizens.end(), arg_person));
		}
	}
};

int main()
{
    vector<Building*> v;
    string actiune,tip,nume,nume_cladire;
    uint16_t nr_max,nr_etaje,varsta;
    double salariu;
    int i,j,c1=0,c2=0,c3=0,c4=0,c5=0;
    while(!cin.eof())
    {
        cin>>actiune;
        if(actiune=="add")
        {
            cin>>tip>>nume;
            if(tip=="CityHall")
            {
                v.push_back(new CityHall(nume));
            }
            else if(tip=="Hospital")
            {
                v.push_back(new Hospital(nume));
            }
            else if(tip=="PoliceStation")
            {
                v.push_back(new PoliceStation(nume));
            }
            else if(tip=="House")
            {
                cin>>nr_max;
                v.push_back(new House(nume,nr_max));
            }
            else if(tip=="Block")
            {
                cin>>nr_etaje>>nr_max;
                v.push_back(new Block(nume,nr_etaje,nr_max));
            }
            else if(tip=="coordinator")
            {
                cin>>varsta>>salariu>>nume_cladire;
                for(i=0;i<v.size();i++)
                {
                    if((v[i]->getBuildingName())==nume_cladire)
                        break;
                }
                v[i]=v[i]->operator+(Person(nume,varsta,salariu));
            }
            else if(tip=="employee")
            {
                cin>>varsta>>salariu>>nume_cladire;
                for(i=0;i<v.size();i++)
                {
                    if((v[i]->getBuildingName())==nume_cladire)
                        break;
                }
                v[i]=v[i]->operator+(Person(nume,varsta,salariu));
            }
            else if(tip=="citizen")
            {
                cin>>varsta>>salariu>>nume_cladire;
                for(i=0;i<v.size();i++)
                {
                    if((v[i]->getBuildingName())==nume_cladire)
                        break;
                }
                v[i]->add(Person(nume,varsta,salariu));
            }
        }
        else if(actiune=="remove")
        {
            cin>>tip>>nume>>nume_cladire;
            for(i=0;i<v.size();i++)
            {
                if((v[i]->getBuildingName())==nume_cladire)
                    break;
            }
            if(tip=="coordinator")
            {
                v[i]=v[i]->operator-(v[i]->getCoordinator());
            }
            else if(tip=="employee")
            {
                for(j=0;j<v[i]->getEmployeesSize();j++)
                {
                    if((v[i]->getEmployee(j)).mName==nume)
                        break;
                }
                v[i]=v[i]->operator-(v[i]->getEmployee(j));
            }
            else if(tip=="citizen")
            {
                for(j=0;j<v[i]->getCitizensSize();j++)
                {
                    if((v[i]->getCitizen(j)).mName==nume)
                        break;
                }
                v[i]->remove(v[i]->getCitizen(j));
            }
        }
    }
    for(i=0;i<v.size();i++)
    {
        tip=v[i]->getType();
        if(tip=="CityHall")
        {
            c1++;
        }
        else if(tip=="Hospital")
        {
            c2++;
        }
        else if(tip=="PoliceStation")
        {
            c3++;
        }
        else if(tip=="House")
        {
            c4++;
        }
        else if(tip=="Block")
        {
            c5++;
        }
    }
    if(c1>=3 && c2>=2 && c3>=3 && c4>=8 && c5>=4)
    {
        cout<<"Type: Capital"<<endl;
    }
    else if (c1>=2 && c2>=1 && c3>=2 && c4>=4 && c5>=1)
    {
        cout<<"Type: City"<<endl;
    }
    else
    {
        cout<<"Type: Village"<<endl;
    }

    int nr=0,salariu2=0,salariu3,n=0,n2=0,n3=0,n4=0,n5=0,varsta5=0,salariu4=0;
    salariu=0;
    for(i=0;i<v.size();i++)
    {
        tip=v[i]->getType();
        if(tip=="Hospital")
        {
            nr+=v[i]->getCitizensSize();
            for(j=0;j<v[i]->getEmployeesSize();j++)
            {
                salariu=salariu+((v[i]->getEmployee(j)).mSalary);
            }
            n+=v[i]->getEmployeesSize();
        }
        else if(tip=="PoliceStation")
        {
            for(j=0;j<v[i]->getEmployeesSize();j++)
            {
                salariu2=salariu2+((v[i]->getEmployee(j)).mSalary);
            }
            n2+=v[i]->getEmployeesSize();
             for(j=0;j<v[i]->getCitizensSize();j++)
            {
                varsta5=varsta5+((v[i]->getCitizen(j)).mAge);
            }
            n5+=v[i]->getCitizensSize();
        }
        else if(tip=="CityHall")
        {
            salariu3+=(v[i]->getCoordinator()).mSalary;
            n3++;
            for(j=0;j<v[i]->getCitizensSize();j++)
            {
                salariu4=salariu4+((v[i]->getCitizen(j)).mSalary);
            }
            n4+=v[i]->getCitizensSize();
        }
        salariu=salariu/n;
        salariu2=salariu2/n2;
        salariu3=salariu3/n3;
        salariu4=salariu4/n4;
        varsta5=varsta5/n5;
    }
    cout<<"Number of patients in hospitals: "<<nr<<endl;
    cout<<"Average salary for doctors: "<<salariu<<endl;
    cout<<"Average salary for cops: "<<salariu2<<endl;
    cout<<"Average salary for mayors: "<<salariu3<<endl;
    cout<<"Average salary for city hall employees: "<<salariu4<<endl;
    cout<<"Average age of busted in police stations "<<varsta5<<endl;
}