#ifndef YADB_DATABASE_H
#define YADB_DATABASE_H

#include <iostream>
#include <ctime>
#include <vector>

class Date{
public:
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;

  Date() { //мышиная возня с ctime-овским определением даты
    time_t now = time(0);
    tm *ltm = localtime(&now);
    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
    hour = ltm->tm_hour;
    minute = ltm->tm_min;
    second = ltm->tm_sec;
  }
};

/*Я хз, как у нас будет изнутри выглядеть БАЗА, поэтому я набросал как в ms
 * access - таблички с ключевыми полями и связи между ключами*/

class Attribute{
public:
  std::string name;
  bool is_key;
  std::string type; //тип данных аттрибута пока стринг

  Attribute() {

  }
};

class Table{
public:
  std::vector<Attribute> attributes;

  Table() {

  }
};

class Database{
public:
  Date creation_date;
  std::vector<Table> tables;

  Database() {

  }

};


#endif //YADB_DATABASE_H
