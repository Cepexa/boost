//#define FILESYSTEM
#ifdef FILESYSTEM
// test1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <filesystem> // C++17 standard header file name
#include <experimental/filesystem> // Header file for pre-standard implementation

using namespace std::experimental::filesystem::v1;
using namespace std;


int main()
{
    system("chcp 1251 > nul");
    cout << "Привет мир World!\n";
    std::string name;
    cin >> name;
    cout << name;

    {const string str = "!";
    cout << str;
    const string str = ", Мир!";
    cout << str;  }
    path p = current_path();
    cout << p;
}
#endif

//#define DATE_TIME
#ifdef DATE_TIME

#define BOOST_DATE_TIME_NO_LIB
#include <iostream>
#include<boost/date_time.hpp>

using std::cout; using std::endl;
int main() {

#pragma region gredorian date example
    using namespace boost::gregorian;
    //boost::gregorian::date
    date xGPWStart(1941, Jun, 22);
    date xNowdays = day_clock::local_day();
    cout << "The Great Patriotic War was started in " << xGPWStart << endl;
    cout << "And the current data is " << xNowdays;
    
    //boost::gregorian::date_duration
    date xSomeDay(1999, Jan, 28);
    date xDayInNextMonth;
    std::cout << "That's right: " << (xDayInNextMonth = xSomeDay + months(1)) << std::endl;
    std::cout << "And that's not: " << xDayInNextMonth + months(1)<<endl<<endl;

    //boost::gregorian::date_period
    date_period xGPWDuration(date(1941, Jun, 22), date(1945, May, 9));
    date_period xStalinLifeYears(date(1878, Dec, 18), date(1953, Mar, 6)); 
    date_period xJukovsIncorrectLifeYears(date(1896, Dec, 6), date(1974, Jun, 14));
    std::cout << "The Great Patriotic War duration is " << xGPWDuration << std::endl;
    std::cout << "Was the GPW inside the Stalin's life years? " << std::boolalpha << xStalinLifeYears.contains(xGPWDuration) << std::endl;
    std::cout << "Jukov's incorrect life years is " << xJukovsIncorrectLifeYears << std::endl;
    xJukovsIncorrectLifeYears.expand(days(5));
    std::cout << "Jukov's correct life years is " << xJukovsIncorrectLifeYears << std::endl;
    //Last day isn't included in the interval
    date_period xFirstPeriod(date(1999, Jan, 1), date(1999, Jan, 10));
    date_period xSecondPeriod(date(1999, Jan, 10), date(1999, Jan, 12));
    std::cout << "Does these periods intersect? " << std::boolalpha << xFirstPeriod.intersects(xSecondPeriod) << std::endl;//intersects - пересекается
    cout << endl<<endl;

    //boost::gregorian::date_iterator
    month_iterator xSomeDay_i(date(1999, Jan, 28));
    std::cout << "That's right: " << *++xSomeDay_i << std::endl;
    std::cout << "And that's too!: " << *++xSomeDay_i;
    cout << endl << endl;

    //Алгоритмы по работе с датами 
    last_day_of_the_week_in_month xLastFriday(Friday, Jul);
    partial_date xJunTen(10, Jun);
    std::cout << "What is the date of the last friday in the July 2009? " << xLastFriday.get_date(2009) << std::endl;
    std::cout << "Just dusplay 10 Jun of 2009 " << xJunTen.get_date(2009) << std::endl;
    std::cout << "How much days from now till next friday? " << days_until_weekday(day_clock::local_day(), greg_weekday(Friday)) << std::endl;
    cout << endl << endl;
    
    //boost::gregorian::gregorian_calendar
    std::cout << "What the day of the GPW begining? " << greg_weekday(gregorian_calendar::day_of_week(gregorian_calendar::ymd_type(1941, Jun, 22))).as_long_string() << std::endl;
    std::cout << "And what is the number of this day frome the epoch start? " << gregorian_calendar::day_number(gregorian_calendar::ymd_type(1941, Jun, 22)) << std::endl;
    std::cout << "And what is the number of this day frome the epoch start? " << gregorian_calendar::day_number(gregorian_calendar::ymd_type(1400, Jan, 1)) << std::endl;
    std::cout << "What is the last day in the February 1941? " << gregorian_calendar::end_of_month_day(1941, Feb) << std::endl;
    std::cout << "What is the date of the 3333333 day from the epoch start? " << date(gregorian_calendar::from_day_number(3333333)) << std::endl;
    std::cout << "Is the 2004 year a leap year? " << std::boolalpha << gregorian_calendar::is_leap_year(2004) << std::endl;
    cout << endl << endl;

#pragma endregion   

#pragma region posix_time 
    //высокая точность получения времени
    using namespace boost::posix_time;

    //boost::posix_time::ptime 
    ptime xTime(date(1961, Apr, 12), hours(9) + minutes(7));
    std::cout << "Did you know that Gagrin said \"Poehali\" at " << xTime << "\n";
    ptime xTimeStr(time_from_string("1961-04-12 09.07.00.0000"));
    std::cout << "And the same time point constructed from a string: " << xTimeStr << "\n";
    std::cout << "Current time with second resolution: " << second_clock::local_time() << "\nAnd with microsecond:" << microsec_clock::local_time();
    cout << endl << endl;

    //boost::posix_time::time_duration
    time_duration xTime1(1, 2, 3);
    std::cout << "Print time: " << xTime1 << "\n";
    std::cout << "Print increased time: " << xTime1 + hours(3) + seconds(2) + minutes(6) + milliseconds(15) + microseconds(25) << "\n";
    std::cout << "Print total seconds: " << xTime1.total_seconds() << " milliseconds: " <<
        xTime1.total_milliseconds() << " microseconds: " << xTime1.total_microseconds() << "\n";
    cout << endl << endl;

    //boost::posix_time::time_period
    ptime xDoomsday(date(2012, Jan, 1));
    time_period xArmageddonLast(xDoomsday, hours(1));
    time_period xChakNorrisSmoke(xDoomsday, minutes(1));
    std::cout << "Doomsday was during: " << xArmageddonLast << "\n";
    std::cout << "Chak Norris was smoking at " << xChakNorrisSmoke << "\n";
    std::cout << "Did Chak Norris smoke during Doomsday breathtaking?" << std::boolalpha << xArmageddonLast.contains(xChakNorrisSmoke);
    cout << endl << endl;

    //boost::posix_time::time_iterator
    ptime xTime2(date(2012, Jan, 1));
    time_iterator xIt(xTime2, hours(6));
    std::cout << "6 hours after Domsday has come!!!" << *++xIt;
    cout << endl << endl;

#pragma endregion

#pragma region Local Time System
    //работа со временем, в разных часовых поясах и с разными правилами перехода на летнее время
    using namespace boost::local_time;

    //boost::local_time::posix_time_zone
    posix_time_zone xZone("MSK+3MSD+01,M3.5.0/02:00,M10.5.0/02:00");
    std::cout << "Dailight period in 2009 started at " << xZone.dst_local_start_time(2009) << "\nAnd it will finish at " << xZone.dst_local_end_time(2009);
    cout << endl << endl;

    //boost::local_time::tz_database
    tz_database xDb;
    xDb.load_from_file("D:\\VS\\Projects\\boost_1_76_0\\lib64-msvc-14.1\\date_time\\data\\date_time_zonespec.csv");
    const std::vector<std::string>& xAllRegions = xDb.region_list();
    std::cout << "Print first 20 zone IDs from the boost time zone file:" << std::endl;
    for (std::vector<std::string>::const_iterator it = xAllRegions.begin(); it != xAllRegions.begin() + 20; ++it)
        std::cout << *it << std::endl;
    std::cout << "And time when daylight saving was started at 2009: " << xDb.time_zone_from_region("Europe/Dublin")->dst_local_start_time(2009) << std::endl;
    cout << endl << endl;

    //boost::local_time::custom_time_zone
    time_zone_names xNames("Moscow Standart Time", "MST", "Moscow Daylight Time", "MDT");
    time_duration xGMTOffset(3, 0, 0);
    dst_adjustment_offsets xRulesOffsets(time_duration(1, 0, 0), time_duration(2, 0, 0), time_duration(3, 0, 0));
    //Mak daylight's rule
    last_day_of_the_week_in_month xStartRule(Sunday, Mar);
    last_day_of_the_week_in_month xEndRule(Sunday, Oct);
    boost::shared_ptr<dst_calc_rule> xRules(new last_last_dst_rule(xStartRule, xEndRule));
    custom_time_zone xCustomTimeZone(xNames, xGMTOffset, xRulesOffsets, xRules);
    std::cout << "The our time zone name is: " << xCustomTimeZone.std_zone_name() << "\n"
        << "It has an " << xCustomTimeZone.base_utc_offset() << " offset from GMT.\n"
        << "And daylight period will end at " << xCustomTimeZone.dst_local_end_time(2009) << std::endl;
    std::cout << "Posix string which represents our custom_time_zone object is:\n" << xCustomTimeZone.to_posix_string();
    cout << endl << endl;

    //Классы 
    //boost::local_time::local_date_time и 
    //boost::local_time::local_time_period 
    //повторяют схожие классы из boost::posix_time, с привязкой к часовому поясу

#pragma endregion

    return 0;
}

#endif // DATE_TIME

#define REGEX
#ifdef REGEX

#include <iostream>
#define BOOST_REGEX_MATCH_EXTRA
#include<boost/regex.hpp>
using std::cout; using std::endl;
int main() {

#pragma region boost::regex_match
    

    std::string xStr("AAAA-12222-BBBBB-44455");
    boost::regex xRegEx("(\\w+)-(\\d+)-(\\w+)-(\\d+)");
    boost::smatch xResults;
    std::cout << "==========================Results============================== \n";
    std::cout << "Does this line match our needs? " << std::boolalpha << boost::regex_match(xStr, xResults, xRegEx) << "\n";
    std::cout << "Print entire match:\n " << xResults[0] << std::endl;
    std::cout << "Print the former string into another format:\n" << xResults[1] << "+"
        << xResults[2] << "+"
        << xResults[3] << "+"
        << xResults[4] << std::endl;
    cout << endl << endl;

#pragma endregion

#pragma region результаты_нахождения_соответствий???

    std::string xStr1("The boost library has a great opportunity for the regex!");
    boost::regex xRegEx1("(\\b\\w{5}\\b)*");
    boost::smatch xResults1;
    std::cout << "==========================Results1============================== \n";
    if (boost::regex_search(xStr1, xResults1, xRegEx1, boost::match_extra))
    {
        std::cout << "Words consist from exact 5 digits have been found in our line:\n";
        for (int j = 0; j < xResults1.captures(1).size(); ++j)
            std::cout << xResults1.captures(1)[j] << std::endl;
    }
    cout << endl << endl;
#pragma endregion

#pragma region Partial match
    std::string xStr2("AAAA-12222");
    boost::regex xRegEx2("(\\w+)-(\\d+)");
    boost::smatch xResults2;
    std::cout << "==========================Results2============================== \n";
    std::cout << "Does this line match the regex? " << std::boolalpha << boost::regex_match(xStr2, xResults2, xRegEx2,
        boost::match_default | boost::match_partial) << "\n";
    std::cout << "Is it the partial match? " << std::boolalpha << !xResults2[0].matched << "\nPrint the partial match:\n" << xResults2[0] << std::endl;
    cout << endl << endl;
#pragma endregion
    
#pragma region regex_search

    std::string xStr3("The boost library has a great opportunity for the regex!");
    boost::regex xRegEx3("\\b(?:\\w+?)((\\w)\\2)(?:\\w+?)\\b");
    boost::smatch xResults3;
    std::cout << "==========================Results3============================== \n";
    std::string::const_iterator xItStart3 = xStr3.begin();
    std::string::const_iterator xItEnd3 = xStr3.end();
    while (boost::regex_search(xItStart3, xItEnd3, xResults3, xRegEx3))
    {
        std::cout << "Word, we've searched, is \"" << xResults3[0] << "\". It has two \"" << xResults3[2] << "\" inside itself.\n";
        xItStart3 = xResults3[1].second;
    }
    cout << endl << endl;

#pragma endregion

#pragma region regex_replace

    std::string xStr4("AAAA-12222-BBBBB-44455");
    boost::regex xRegEx4("(\\w+)-(\\d+)-(\\w+)-(\\d+)");
    std::string xFormatString4("$1*$2*$3*$4");
    boost::smatch xResults4;
    std::cout << "==========================Results4============================== \n";
    std::cout << "Print string after replace:\n " << boost::regex_replace(xStr4, xRegEx4, xFormatString4, boost::match_default | boost::format_perl) << std::endl;
    cout << endl << endl;

#pragma endregion

#pragma region regex_iterator

    std::string xStr5("AAAA-12222-BBBBB-44455");
    boost::regex xRegEx5("(\\w|\\d)+");
    boost::smatch xResults5;
    std::cout << "==========================Results5============================== \n";
    boost::sregex_iterator xIt5(xStr5.begin(), xStr5.end(), xRegEx5);
    boost::sregex_iterator xInvalidIt5;
    while (xIt5 != xInvalidIt5)
        std::cout << *xIt5++ << "*";
    cout << endl << endl;

#pragma endregion

#pragma region regex_token_iterator

    std::string xStrMy("AAAA-12222-BBBBB-44455");
    boost::regex xRegExMy("(\\w|\\d)+");
    boost::smatch xResultsMy;
    std::cout << "==========================ResultsMy============================== \n";
    boost::sregex_token_iterator xItFullMy(xStrMy.begin(), xStrMy.end(), xRegExMy, 0);
    boost::sregex_token_iterator xInvalidItMy;
    std::cout << "Result the same as the regex_iterator: \n";
    while (xItFullMy != xInvalidItMy)
        std::cout << *xItFullMy++ << "*";
    //Parts of captures
    boost::regex xRegEx2My("(\\w+)-(\\d+)");
    boost::sregex_token_iterator xItFirstCaptureMy(xStrMy.begin(), xStrMy.end(), xRegEx2My, 1);
    std::cout << "\nShow only first captures: \n";
    while (xItFirstCaptureMy != xInvalidItMy)
        std::cout << *xItFirstCaptureMy++ << "*";
    //Reverse order
    int aIndicesMy[] = { 2,1 };
    boost::sregex_token_iterator xItReverseCaptureMy(xStrMy.begin(), xStrMy.end(), xRegEx2My, aIndicesMy);
    std::cout << "\nShow captures in the reverse order: \n";
    while (xItReverseCaptureMy != xInvalidItMy)
        std::cout << *xItReverseCaptureMy++ << "*";
    //Delimiters
    boost::regex xRegEx3My("(\\w|\\d)+");
    boost::sregex_token_iterator xItDelimitersMy(xStrMy.begin(), xStrMy.end(), xRegEx3My, -1);
    std::cout << "\nShow delimiters: \n";
    while (xItDelimitersMy != xInvalidItMy)
        std::cout << *xItDelimitersMy++ << " ";
    cout << endl << endl;

#pragma endregion


    return 0;
}

#endif // REGEX

