#include <iostream>
#include <string>
#include <map>
#include <vector>
#include<bits/stdc++.h>
#include "fifomap.hpp"

// for convenience
using nlohmann::fifo_map;

std::vector<std::string> date={  "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat", "Sun"};

std::string Sakamoto(int d, int m, int y,std::vector<std::string> &date) {		
        
		static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    	y -= m < 3;
		int temp = ( y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
		if(temp == 0)
		    return date[6];
    	return date[temp - 1];
}


       

nlohmann::fifo_map<std::string, int>  solution(std::map<std::string, int> &D)
{
	nlohmann::fifo_map<std::string, int> final;
    
	for(int i  = 0; i < date.size(); i++)
        final[date[i]] = 0;
	
	for(auto imap = D.begin(); imap != D.end(); ++imap)
        {
            std::string s = imap -> first;
            
            //finding indivisual values of day month and year
            
            std::string year = s.substr(0, 4);
            int y = stoi(year);
			//std::cout << "year " << year << std::endl;
            
            std::string month = s.substr(5, 2);
            int m = stoi(month);
			//std::cout << "month " << month << std::endl;
            
            std::string day = s.substr(8, 2);
            int d = stoi(day);
			//std::cout << "day " << day << std::endl;
            
            //call function to get dayOfTheWeek
            
            std::string f = Sakamoto(d, m, y, date);
            
            if(imap -> second != 0)
                final[f] = final[f] + imap -> second;
		}
                                 
		//applying arithematic progression incase there are gaps of missing days

			for(int i  = 1; i < date.size(); i++)
			{
				if(final[date[i]] == 0 )
				{
					std::cout << final[date[i]] << std::endl;
					int begin = i;
					int min = final[date[i - 1]];
					std:: cout << "min"  << min << std::endl;
					int count = 0;
					
					while(final[date[i]] == 0)
					{
						count++;
						i++;
					}
					int max = final[date[i]];
					int diff = abs(((max - min)/count)) - 1;
					std::cout << "diff :" << diff << std::endl;

					//start from begin and go to end
					while(begin != (i))
					{
						final[date[begin]] = final[date[begin - 1]]+ diff;
						begin++;
					}			
				}	


			}
		    
        return final;    
    }

void testSakamoto() {
	
	//non-leap year
	int day = 19, month = 12, year = 2015;

    
	std::cout << "Result:" ;
	std::cout <<  Sakamoto(day, month, year, date) ;
	std::cout << std::endl;

	//leap-year
	day = 19, month = 12, year = 2020;
	std::cout << "Result :" ;
	std::cout <<  Sakamoto(day, month, year, date) ;
	std::cout  << std::endl;
	return;
}

void test_solution(){
	//all days present
	std::cout << "Test 1: " << std::endl;
		std::map<std::string,int> D;
		D.insert({"2020-01-01",4});
		D.insert({"2020-01-02",4});
		D.insert({"2020-01-03",6});
		D.insert({"2020-01-04",8});
		D.insert({"2020-01-05",2});
		D.insert({"2020-01-06",-6});
		D.insert({"2020-01-07",2});
		D.insert({"2020-01-08",-2});
		nlohmann::fifo_map<std::string, int> f = solution(D);

		for(auto it = f.begin(); it != f.end(); ++it)
			std::cout << it->first << " " << it->second << std::endl;
		
    D.clear();
	f.clear();

	std::cout << std::endl << "Test 2:" << std::endl;
	//all days not present
	    

		D.insert({"2020-01-01",6});
		D.insert({"2020-01-04",12});
		D.insert({"2020-01-05",14});
		D.insert({"2020-01-06",2});
		D.insert({"2020-01-07",4});
	

		f = solution(D);

		for(auto it = f.begin(); it != f.end(); ++it)
			std::cout << it->first << " " << it->second << std::endl;

}
int main()
{
	// test sakamoto
		//testSakamoto();

	//test solution
	  test_solution();       
}