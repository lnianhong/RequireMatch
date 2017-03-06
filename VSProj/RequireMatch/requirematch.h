#pragma once
#ifndef REQUIREMATCH_h
#define REQUIREMATCH_h
#include"Exchange_Item.h"
#include <vector> 
#include <list> 
#include <string>

typedef std::list<Exchange_Item> ExContainer;
typedef std::list<Exchange_Item> ExSaver;
typedef ExContainer::iterator Itertype;
typedef ExContainer::difference_type difftype;


bool compID(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compOrder(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compItemNoMaxWeight(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compItem(const Exchange_Item& Item1, const Exchange_Item& Item2);

bool readCSVdata(ExContainer& Rers, const std::string csvfilename);
bool readCSVdata(ExContainer& Rers, const std::string csvfilename, int startOrder);
size_t dealRepetition(ExContainer& Rers, ExContainer& Ters);
difftype finishedNum(ExContainer& Rers);


bool has2sum(Itertype& first, Itertype& last, Exchange_Item& target, Itertype& it1, Itertype& it2);


void exchangeFunc(ExContainer& largeCont, ExContainer& smallCont,
	ExSaver & largeSaver, ExSaver & smallSaver);


std::vector<int> getExTimes(ExSaver& Rers);
int sumExTimes(ExSaver& Rers);
ExSaver::iterator maxExTimes(ExSaver& Rers);
void writeResult(ExSaver& Rers, std::string result_file);
void writeLog(std::string result_log, ExSaver& Rers, ExSaver& Ters, double t);


#endif // !REQUIREMATCH_h


//bool compID(const Exchange_Item& Item1, const Exchange_Item& Item2);
////�Ƚ��û�ID��Ҳ�����ַ����Ƚϣ���һ���ȵڶ���С�򷵻�true
//
//bool compOrder(const Exchange_Item& Item1, const Exchange_Item& Item2);
////�Ƚ��û�ԭʼ����˳�򣬵�һ����order�ȵڶ���orderС�򷵻�true
//
//bool compItemNoMaxWeight(const Exchange_Item& Item1, const Exchange_Item& Item2);
////������Ȩ�أ������Ƚ�����һ�����С���򷵻�true
//
//bool compItem(const Exchange_Item& Item1, const Exchange_Item& Item2);
////����Ȩ�ؽ��бȽ�
//
//bool readCSVdata(ExContainer& Rers, const std::string csvfilename);
//// ��CSV��ȡ���ݵ�list������
//bool readCSVdata(ExContainer& Rers, const std::string csvfilename, int startOrder);
//// ��CSV��ȡ���ݵ�list�����в�������ʼ˳����
//
//size_t dealRepetition(ExContainer& Rers, ExContainer& Ters);
//// ������Rers��Ters�п��Ե��������ݷ�����������¼�����ص����ı���
//difftype finishedNum(ExContainer& Rers);
//// ��ȡliast�����Ϊ0������
//
//bool has2sum(Itertype& first, Itertype& last, Exchange_Item& target, Itertype& it1, Itertype& it2);
//// �ڵ�����ָ����Χ[first,last)�ڣ������Ƿ�������Ԫ�ص����ĺ���target��������
////�������ָ����Ԫ�ص���������it1��it2��������true
//
//void exchangeFunc(ExContainer& largeCont, ExContainer& smallCont,
//	ExSaver & largeSaver, ExSaver & smallSaver);
////����������Ԫ�ط������ף�����ɽ��׵Ĵ洢����һ��������ԭ��������ɾ��
//
//std::vector<int> getExTimes(ExSaver& Rers);
//// ����ÿ��Ԫ�صĽ��״���������
//
//int sumExTimes(ExSaver& Rers);
//// �����ܽ��״���
//
//ExSaver::iterator maxExTimes(ExSaver& Rers);
//// ��������״���
//
//void writeResult(ExSaver& Rers, std::string result_file);
////�����д��CSV
//
//void writeLog(std::string result_log, ExSaver& Rers, ExSaver& Ters, double t);
////������ʱ�䣬����״������ܽ��״���д��log