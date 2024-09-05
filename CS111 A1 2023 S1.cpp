/*This CS111 Assignment was created by :
Name : George Fong        Student ID : S11220337 */

//This program is used to calculate the tax due of employees depending on their gross pay per week, age, annual gross pay ,with an additional feature to compute the annual net pay//
#include<iostream>
using namespace std;

int main(){
	
	cout<<"\t\t\t\t\tSALARY CALCULATOR\n\n";
	cout<<"\t*********************************************************************************\n\n";
	
	
	
	int year_of_birth,age;
	double grosspay_per_week,annual_income,annual_net_pay;
	string first_name,surname;
	string employee_id;
	double hours_worked, tax_amount;
	char gender;
	char continue_;
	
	const int PAY_RATE = 20;
	const int TIME_LIMIT_1 = 40,TIME_LIMIT_2 = 45,TIME_LIMIT_3=0;
	const int CURRENT_YEAR=2023,MINIMUM_YEAR=1900;
	const int TOTAL_WEEKS = 52;
	const int AGE_LIMIT_1=55,AGE_LIMIT_2=80;
	const int INCOME_LIMIT_1 = 10000 ,INCOME_LIMIT_2 = 12000,INCOME_LIMIT_3 = 30000,INCOME_LIMIT_4 = 35000,INCOME_LIMIT_5=50000,INCOME_LIMIT_6=70000, INCOME_LIMIT_7 = 100000,INCOME_LIMIT_8=150000;
	const double RATE_1 = 0.10,RATE_2 = 0.20,RATE_3 = 0.30, RATE_4=0;
	const double OVERTIME_RATE_1 = 1.5,OVERTIME_RATE_2 = 2.0;
	const double DOUBLE_TIME_RATE = 2.0;

	//if press capital C the program will continue whereas you press capital Q it quits//

	while (continue_ != 'C' && continue_ != 'Q') {
	
		if(continue_ != 'C' && continue_ != 'Q'){ // also take note that this program is validated for the user to only enter C and Q anything else is not accepted.Hence it will be displaying the samething until capital C or Q is entered//
		
	    	cout<<" Please Enter 'C' to continue or 'Q to quit"<<endl;
			cin>>continue_;
			cout<<"--------------------------------------------------------------"<<endl;
			//once the user enters c all of this will take place
			 if(continue_=='C')
			{
				while(continue_=='C'){ //if the user  enters all of this will happen until you press capital Q//
				
					//Input users details//
					cout<<"\nPlease enter first name : \n";
					cin>>first_name;
					cout<<"--------------------------------------------------------------"<<endl;
					cout<<"\nPlease enter Surname : \n";
					cin>>surname;
					cout<<"--------------------------------------------------------------"<<endl;
					cout<<"\nPlease enter Your Id : \n";
					cin>>employee_id;
					cout<<"--------------------------------------------------------------"<<endl;
					cout<<"\nPlease Define Your Gender......Enter M =>  male and F => female  : \n";
					cin>>gender;
					
					while (gender != 'M' &&  gender != 'F'){ //To Enter the gender of the workers the user has to only enter Capital M if male and F if Female.Also take note that this part is also validated //
					    cout << "Invalid input. Please enter 'M' for male or 'F' for female: \n";
					    cin >> gender;
					}
		
					cout<<"--------------------------------------------------------------"<<endl;
					
					cout<<"\nPlease year of Birth : \n";
					cin>>year_of_birth;
					while (year_of_birth <= MINIMUM_YEAR || year_of_birth > CURRENT_YEAR || cin.fail() ){ //Take note for this program the current year is 2023 and the minimum year is 1900. Any one born below the minimum age and above the current age will be an invalid input//
				
						if(cin.fail()){
				
						cin.clear();
						string temp_string;
						cin >> temp_string;
						}
				
			
						cout<<"Invalid input .Please enter year of birth"<<endl;
						cin>>year_of_birth;
					}
					
				
					cout<<"--------------------------------------------------------------"<<endl;
					cout<<"\nEnter Hours Worked : \n";
					cin>>hours_worked;
					while (hours_worked <TIME_LIMIT_3|| cin.fail() ){//to enter the number of hours worked .The program only accepts numbers greater than 0, anything else is an invalid input//
				
						if(cin.fail()){
				
						cin.clear();
						string temp_string;
						cin >> temp_string;
						}
				
			
						cout<<"Invalid input .Please enter hours worked"<<endl;
						cin>>hours_worked;
					}
					
					
					
					//calculation of  weekly income//
					if (hours_worked > TIME_LIMIT_2)	
					{
						grosspay_per_week=(TIME_LIMIT_1 * PAY_RATE + ((TIME_LIMIT_2 - TIME_LIMIT_1)* PAY_RATE * OVERTIME_RATE_1)) + ((hours_worked-TIME_LIMIT_2)* PAY_RATE* OVERTIME_RATE_2);
						
						}
							
					else if (hours_worked >TIME_LIMIT_1 && hours_worked < TIME_LIMIT_2 )	
					{
						grosspay_per_week= TIME_LIMIT_1 * PAY_RATE  + (hours_worked - TIME_LIMIT_1) * PAY_RATE * OVERTIME_RATE_1;
					}
					else 
					{
						grosspay_per_week=hours_worked * PAY_RATE;
					}
					
					
					//calculation of Age//
					age=CURRENT_YEAR - year_of_birth;
				
					//calculation of annual_income//	
					annual_income=grosspay_per_week*TOTAL_WEEKS;
				
					//Calculation of the amount of tax//
					if(age < AGE_LIMIT_1)//age of people whose age are less than 55 years old//
					if(annual_income < INCOME_LIMIT_1 && gender=='M')
					{
				
						tax_amount=annual_income * RATE_4;
					}
					
					else if((annual_income >= INCOME_LIMIT_1 && annual_income <= INCOME_LIMIT_3) && gender=='M')
					{
						
					tax_amount=annual_income * RATE_1;
					}
					
					else if((annual_income > INCOME_LIMIT_3 && annual_income <=INCOME_LIMIT_7) && gender=='M')
					{
						
					tax_amount=annual_income * RATE_2;
					}
					
					else if(annual_income > INCOME_LIMIT_7 && gender=='M')
					{
						
					tax_amount=annual_income * RATE_3;
					
					}
					
					else if(annual_income < INCOME_LIMIT_2 &&gender=='F')
					{
					
						tax_amount=annual_income *RATE_4;
					}
					
					else if((annual_income >= INCOME_LIMIT_2 && annual_income <= INCOME_LIMIT_4) && gender=='F')
					{
						
					tax_amount=annual_income * RATE_1;
					}
					
					else if((annual_income > INCOME_LIMIT_4 && annual_income <=INCOME_LIMIT_7) && gender=='F')
					{
						
					tax_amount=annual_income * RATE_2;
					}
					
					else if(annual_income > INCOME_LIMIT_7 && gender=='F')
					
					{
						
					tax_amount=annual_income * RATE_3;
					}
					else if(age >= AGE_LIMIT_1 && age < AGE_LIMIT_2)	
					{
					if(annual_income < INCOME_LIMIT_5)
					{
						tax_amount =annual_income * RATE_4 ;
					}
					
					else if(annual_income >= INCOME_LIMIT_5 && annual_income <= INCOME_LIMIT_6)
					{
					tax_amount=annual_income * RATE_1;	
					}
					
					else if(annual_income > INCOME_LIMIT_6 && annual_income <= INCOME_LIMIT_8)
					{
					tax_amount=annual_income * RATE_2;	
					}
					
					else if(annual_income > INCOME_LIMIT_8)
					{
					tax_amount=annual_income * RATE_3;	
					}
					
					}
				
					else if(age >= AGE_LIMIT_2)
					{
					tax_amount = annual_income *RATE_4;
					}
				
				
				
				
					cout<<"\n\t******************************************************************************************"<<endl;
				
				
				
				
					//output//
					cout<<"\t\t\tIncome Tax Calculator "<<endl;
					cout<<"\t\t-----------------------------------------\n\n";
				
					//Output of users information//
					cout<<"\t Employees Name : "<<first_name<<" "<<surname<<endl;
					cout<<"\t Employees ID : "<<employee_id<<endl;
					cout<<"\t Age is : "<<age<<endl;
					cout<<"\t Gross pay per week $"<<grosspay_per_week<<endl;
					cout<<"\t Annual income : $"<<annual_income<<endl;
					cout<<"\t Tax amount due : $"<<tax_amount<<endl;
					annual_net_pay=annual_income-tax_amount;
					cout<<"\t  Annual Net pay : $"<<annual_net_pay<<endl;
					cout<<"--------------------------------------------------"<<endl;
					cout<<" Please Enter 'C' to continue or 'Q to quit"<<endl;
					cin>>continue_;
						if(continue_=='Q'){
							cout<<"THANK YOU FOR USING THIS PROGRAM "<<endl;
							cout<<"-------------------------------------------------------------"<<endl;
						}
				}
			}
		
			else if(continue_=='Q')
			{
				cout<<"THANK YOU FOR USING THIS PROGRAM "<<endl;
				cout<<"-------------------------------------------------------------"<<endl;
					
			}
			
		
		}
	
	}
	
	
	return 0;
	
	}

