#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std ;
struct  Date
{
    unsigned short int Year ;
    unsigned short int Month ;
    unsigned short int Day ;
}date;
struct Student
{
    string Firstname ;
    string Lastname ;
    unsigned long long int ID ;
    Date Birthday ;
    float Grade ;
};
struct Class
{
    string ClassName ;
    float average ;
    unsigned short int Capacity ;
    vector <Student> Data ;
};

vector <Class> Database ;
vector <string> order ;
string CurrentClass , namestu , first , last ;
unsigned long long int idd , identify;
float ggrade ;
bool f= true ;

void Help()    //showing how program`s functions work
{
    cout<<"**********************"<<setw(103)<<"****************************************************************"<<endl ;
    cout<<"basu add class order :"<<setw(100)<<"get the name of a file and add the filel`s class to database."<<endl ;
    cout<<"basu remove class :"<<setw(98)<<"get the name of a class and and remove it from database."<<endl ;
    cout<<"basu basu add student :"<<setw(73)<<"add a student to an optional class."<<endl ;
    cout<<"basu remove student :"<<setw(95)<<" get student`s ID and remove it from an optional class. "<<endl ;
    cout<<"basu select class :"<<setw(74)<<" put the class on optional state."<<endl ;
    cout<<"basu select none :"<<setw(96)<<" a neutral state that in which has chosen any classes."<<endl ;
    cout<<"basu search <ID> :"<<setw(94)<<" get the student`s ID and show it`s characteristics."<<endl ;
    cout<<"basu search <fullname> :"<<setw(95)<<" get the student`s fullname and show it`s characteristics. "<<endl ;
    cout<<"basu sort name :"<<setw(110)<<" get the name of a class and sort the students by their last name."<<endl ;
    cout<<"basu sort id :"<<setw(105)<<" get the id of a student and sort the students by their id."<<endl ;
    cout<<"basu show <class name> :"<<setw(73)<<"get the name of a class and show it."<<endl ;
    cout<<"basu show :"<<setw(83)<<"show all the classes in database."<<endl ;
    cout<<"basu save :"<<setw(100)<<" saving the information of files in seperate files."<<endl ;
    cout<<"exit :"<<setw(75)<<" exit of the program."<<endl ;
    cout<<"**********************"<<setw(103)<<"****************************************************************"<<endl ;
}
void exit()     //exit of the program
{
    cout<<"program finished . "<<endl ;
    f = false ;
}
void SelectClass( string classname )     //put the class on optional state
    {
        ifstream input1 ;
        input1.open(classname,ios::in) ;
        if( !input1 )
        {
            cerr<<"there isn`t any file! " ;
            exit(1) ;
        }
        Class newclassname ;
        getline(input1,newclassname.ClassName) ;
        cout<<"Database:"<<newclassname.ClassName<<endl ;
        CurrentClass = newclassname.ClassName ;
        input1.close() ;
    }
void AddClass( string filename )   //get the name of a file and add the filel`s class to database
{
    ifstream input2 ;
    input2.open(filename,ios::in) ;
    if( !input2 )
        {
            cerr<<"there isn`t any file! " ;
            exit(1) ;
        }
    Class newClass ;
    getline(input2,newClass.ClassName) ;
    cout<<"name of class:"<<newClass.ClassName<<endl ;
    input2>>newClass.Capacity ;
    cout<<"capacity of class :"<<newClass.Capacity<<endl ;
    for (size_t i = 0; i < newClass.Capacity; i++)
    {
        string date;
        Student newStudent;
        input2>> newStudent.Firstname;
        cout<<"first name :"<<newStudent.Firstname<<endl ;
        input2>> newStudent.Lastname ;
        cout<<"last name :"<<newStudent.Lastname <<endl ;
        input2>> date;
        string temp[3];
        size_t counter = 0;
        for(auto j : date)
        {
            if (j != '/')
                temp[counter] += j;
            else
                counter++;
        }
        newStudent.Birthday.Year = stoi(temp[0]) ;
        newStudent.Birthday.Month = stoi(temp[1]) ;
        newStudent.Birthday.Day = stoi(temp[2]) ;
        cout<<"date of birth :"<<newStudent.Birthday.Year <<"/"<<newStudent.Birthday.Month<<"/"<<newStudent.Birthday.Day <<endl ;
        input2 >> newStudent.Grade ;
        cout<<"grade:"<< newStudent.Grade<<endl ;
        input2 >> newStudent.ID ;
        cout<<"id:"<< newStudent.ID<<endl<<"................................"<<endl ;
        newClass.Data.push_back(newStudent) ;
    }
    Database.push_back(newClass) ;
    input2.close() ;
}
void Search(string first , string last )   //get the student`s fullname and show it`s characteristics
{
    for( auto &i : Database )
    {
        if( i.ClassName == CurrentClass )
        {
            for( auto j : i.Data )
            {
                if( j.Firstname == first && j.Lastname == last )
                cout<<"first name :"<<" "<<j.Firstname<<"\t"<<"last name :"<<" "<<j.Lastname<<"\t"<<"id :"<<"  "<<j.ID<<"\t"<<"grade :"<<" "<<j.Grade<<"\t"<<"date of birth :"<<" "<<j.Birthday.Year<<"/"<<j.Birthday.Month<<"/"<<j.Birthday.Day<<endl ;
            }
        }
    }
} 
 void Search( string identify )           //get the student`s ID and show it`s characteristics
 {
    for( auto i : Database )
        if( i.ClassName == CurrentClass )
    {
            for( auto j : i.Data )
                if( to_string(j.ID) == identify )
                   cout<<"first name :"<<" "<<j.Firstname<<"\t"<<"last name :"<<" "<<j.Lastname<<"\t"<<"id :"<<"  "<<j.ID<<"\t"<<"grade :"<<" "<<j.Grade<<"\t"<<"date of birth :"<<" "<<j.Birthday.Year<<"/"<<j.Birthday.Month<<"/"<<j.Birthday.Day<<endl ;
    }
 }
void RemoveClass( string classname )        //get the name of a class and and remove it from database
{
    for( auto &i : Database )
    {
        if ( i.ClassName == classname )
        {
            for ( size_t j = 0 ; j < i.Capacity ; j++ )
            {
                Database.erase( Database.begin() + j ) ;
                i.Capacity-- ;
            }
        }
    }
}void ShowClass( string classname )      //get the name of a class and show it
{
   for( auto &i : Database )
   {
       cout<<"name of the student of "<<i.ClassName<<" :"<<endl ;
       if( i.ClassName == classname )
       {
           for ( auto k:i.Data )
            {
               cout<<k.Firstname <<setw(10) ;
               cout<<"*.*" ;
            }
       }
   }
   cout<<endl ;
}
void AddStudent( string namestu ,Date date ,unsigned long long int idd ,float ggrade )   
    //add a student to an optional class
{
    cout<<"enter name of new student to add :"<<"\t" ;
    cin>>namestu ;
    cout<<"enter date of birth of new student to add :"<<"\n" ;
    cin>>date.Year>>date.Month>>date.Day  ;
    cout<<"enter id of new student to add :"<<"\t" ;
    cin>> idd ;
    cout<<"enter grade of new student to add :"<<"\t" ;
    cin>> ggrade ;
    for(auto &i : Database)
    {
        if( CurrentClass == i.ClassName )
        {
            Student newstudent ;
            for( auto &j : namestu )
            {
                newstudent.Firstname += j ;
                newstudent.Lastname += j ;               
           }
           newstudent.Birthday = date ;
           newstudent.ID = idd ;
           newstudent.Grade = ggrade ;
           i.Data.push_back( newstudent ) ;
        }
    }
} 
void RemoveStudent( string id )   //get student`s ID and remove it from an optional class
{
    for( auto &i : Database )
    {
        if( i.ClassName == CurrentClass )
        {
            int a = 0;
            for( auto &j : i.Data )
            {
                if( to_string( j.ID ) == id )
                i.Data.erase( i.Data.begin() + a);
                i.Capacity--;
                a++;
            }
        }
    }
} 
void SortByName()             //get the name of a class and sort the students by their last name
{
    for( auto &i :Database )
    {
        if( i.ClassName == CurrentClass )
        {
            for( auto &m : i.Data )
            {
                for( auto &n : i.Data )
                {
                    for(int k=0 ; k<7 ; k++ )
                    {
                        if( m.Lastname.at(k) < n.Lastname.at(k) )
                        {
                            Student newstu ;
                            newstu = m ;
                            m = n ;
                            n = newstu ;
                            break ;
                        }
                        else if( m.Lastname.at(k) == n.Lastname.at(k) )
                        {
                            continue ;
                        }
                        else 
                        break ;
                    }
                }
            }
        cout<<"sorted by last name :"<<endl ; 
        for( auto l : i.Data )
        cout<<l.Lastname<<endl ;
        }
    }
}
void SortByID()                 //get the id of a student and sort the students by their id
{
    for( auto &i :Database )
   {
        if( i.ClassName == CurrentClass )
       {
            for( auto &m : i.Data )
           {
                for( auto &n : i.Data )
               {
                    for( int k=0 ; k<10 ; k++ )
                   {
                        if( m.ID < n.ID )
                       {
                            Student newstu ;
                            newstu = m ;
                            m = n ;
                            n = newstu ;
                            break ;
                        }
                        else 
                        break ;
                    }
                }
            }
        cout<<"sorted by last id :"<<endl ; 
        for( auto l : i.Data )
        cout<<l.ID<<endl ;
        }
    }
}
void ShowAll()         //show all the classes in database
{
    for ( auto &i : Database )
    {
        cout<<"name of class :"<<"  "<<i.ClassName<<endl ;
        cout<<"capacity of class :"<<"  "<<i.Capacity<<endl ;
    for( auto &j :i.Data )
   {
     cout<<"first name :"<<"  "<<j.Firstname<<endl ;
     cout<<"last name :"<<"  "<<j.Lastname<<endl ;
     cout<<"date of birth :"<<"  "<<j.Birthday.Year<<"/"<<j.Birthday.Month<<"/"<<j.Birthday.Day<<endl ;
     cout<<"grade :"<<"  "<<j.Grade<<"  "<<endl ;
     cout<<"id :"<<"  "<<j.ID<<endl;
     cout<<"************"<<endl ;
   }
    }
}
void Start() 
{   
    string input ;       
    while(f == true)    // will continue program
    {
        cout<<"*****************" ;
        cout<<endl<< "Database>>" ;    
        getline(cin,input) ;
        string temp = "" ;
        for(char &i : input )
    {
            if(i != ' ' )
            temp += i ;
    else
        { 
            order.push_back(temp) ;
            temp = "" ;
        }
    }
        order.push_back(temp); 

        if( (order.at(0) == "basu" || order.at(0) == "BASU") && (order.at(1) == "select" || order.at(1) == "SELECT" ) && (order.at(2) == "class" || order.at(2) == "CLASS") )
        { 
            SelectClass( order.at(3) ) ; 
        } 

        if( (order.at(0) == "basu" || order.at(0) == "BASU" ) && (order.at(1) == "add" || order.at(1) == "ADD" ) && (order.at(2) == "class" || order.at(2) == "CLASS") )
        {   
            AddClass( order.at(3) ) ;
        }

        if( (order.at(0) == "basu" || order.at(0) == "BASU") && (order.at(1) == "remove" || order.at(1) == "REMOVE") && (order.at(2) == "student" || order.at(2) == "STUDENT" ) ) 
        {
            RemoveStudent( order.at(3) ) ;
        } 

        if( (order.at(0) == "basu" || order.at(0) == "BASU") && (order.at(1) == "search" || order.at(1) == "SEARCH") && order.at(2).size() == 5 && order.at(3).size() == 7 )
        {
            Search( order.at(2) ,order.at(3) ) ;
        }

        if( (order.at(0) == "basu" || order.at(0) == "BASU") && (order.at(1) == "search" || order.at(1) == "SEARCH") && order.at(2).size() == 10 )
        {
            Search( order.at(2) ) ;
        }

        if( (order.at(0) == "basu"|| order.at(0) == "BASU") && (order.at(1) == "select" || order.at(1) == "SELECT") && (order.at(2) == "none" || order.at(2) == "NONE" ))
        { 
            //a neutral state that in which has chosen any classes
            CurrentClass.clear();
            cout<<"Database: --- "<<endl;
        }

        if( (order.at(0) == "basu"|| order.at(0) == "BASU") && (order.at(1) == "sort" || order.at(1) == "SORT") && (order.at(2) == "name" || order.at(2) == "NAME") )
        {
            SortByName() ;
        }

        if( (order.at(0) == "basu" || order.at(0) == "BASU") && (order.at(1) == "sort" || order.at(1) == "SORT") && (order.at(2) == "id" || order.at(2) == "ID")  )
        {
            SortByID() ;
        }

        if( (order.at(0) == "basu" || order.at(0) == "BASU") && (order.at(1) == "remove" || order.at(1) == "REMOVE") && (order.at(2) == "class" || order.at(2) == "CLASS") )
        {
            RemoveClass(order.at(3)) ;
        }

        if( (order.at(0) == "basu" || order.at(0) == "BASU" ) && (order.at(1) == "show" || order.at(1) == "SHOW") )
        {
            ShowClass( order.at(2) ) ;
        }

        if( (order.at(0) == "basu" || order.at(0) == "BASU") && (order.at(1) == "add" || order.at(1) == "ADD") && (order.at(2) == "student" || order.at(2) == "STUDENT") )
        {
            AddStudent( namestu , date , idd , ggrade ) ;
        }

        if( (order.at(0) == "basu" || order.at(0) == "BASU") && (order.at(1) == "showall" || order.at(1) == "SHOWALL")  )
        {
            ShowAll() ;
        }

        if( (order.at(0) == "basu" || order.at(0) == "BASU") && (order.at(1) == "help" || order.at(1) == "HELP")  )
        {     
            Help() ;
        }

        if( order.at(0) == "exit" || order.at(0) == "EXIT"  )   
        {
            exit() ; 
        }   

        else if( order.at(0) != "basu" && order.at(0) != "BASU" && order.at(0) != "exit" && order.at(0) != "EXIT" )
        {
            cerr<<"worng order !"<<endl ;
        }
                    
    order.clear() ;
    }
}

int main()
{
    Start() ;
    return 0 ;
}