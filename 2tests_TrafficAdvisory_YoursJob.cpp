///*
// * 2tests_TrafficAdvisory_YoursJob.cpp
// * ��ʵ�ֽ�ͨ��ѯ������TrafficAdvisory����������߸���������
// */
//
//#include <iostream>
//#include <string>
//#include "catch.hpp"  //���Թ���
//#include "TrafficAdvisory.h" //TrafficAdvisory��
//using std::cout;
//using std::endl;
//using std::string;
//
//TEST_CASE("TrafficAdvisory::numVertices_from::yours Test 1", "[part = 1][weight = 2]") {
//	//��Ĳ������񣺱�д���TrafficAdvisory::numVertices_from()�Ĳ��������������������������ܵ���ϣ��滻������Ķ��ԡ�
//	REQUIRE("��û�����TrafficAdvisory::numVertices_from()�����Ĳ����������Լ����������ܵ���ϲ��ԡ�" == "���Ѿ�ʵ����TrafficAdvisory::numVertices_from()����������д�˶���Ĳ����������Լ����������ܵ���ϲ��ԣ�");
//}
//
//TEST_CASE("TrafficAdvisory::Dijkstra::yours  Test 2", "[part = 1][weight = 1]") {
//	//��Ĳ������񣺱�д���TrafficAdvisory::Dijkstra()�Ĳ��������������������������ܵ���ϣ��滻������Ķ��ԡ�
//	REQUIRE("��û�����TrafficAdvisory::Dijkstra()�����Ĳ����������Լ����������ܵ���ϲ��ԡ�" == "���Ѿ�ʵ����TrafficAdvisory::Dijkstra()����������д�˶���Ĳ����������Լ����������ܵ���ϲ��ԣ�");
//
//}
//
//TEST_CASE("TrafficAdvisory::All_nonrepetition_paths::yours Test 3", "[part = 1][weight = 2]") {
//	//��Ĳ������񣺱�д���TrafficAdvisory::All_nonrepetition_paths()�Ĳ��������������������������ܵ���ϣ��滻������Ķ��ԡ�
//	REQUIRE("��û�����TrafficAdvisory::All_nonrepetition_paths()�����Ĳ����������Լ����������ܵ���ϲ��ԡ�" == "���Ѿ�ʵ����TrafficAdvisory::All_nonrepetition_paths()����������д�˶���Ĳ����������Լ����������ܵ���ϲ��ԣ�");
//
//}
//
//TEST_CASE("TrafficAdvisory::Kth_ShortestPath::yours Test 4", "[part = 1][weight = 2]") {
//	//��Ĳ������񣺱�д���TrafficAdvisory::Kth_ShortestPath()�Ĳ��������������������������ܵ���ϣ��滻������Ķ��ԡ�
//	REQUIRE("��û�����TrafficAdvisory::Kth_ShortestPath()�����Ĳ����������Լ����������ܵ���ϲ��ԡ�" == "���Ѿ�ʵ����TrafficAdvisory::Kth_ShortestPath()����������д�˶���Ĳ����������Լ����������ܵ���ϲ��ԣ�");
//
//}
//
//TEST_CASE("TrafficAdvisory::Floyd::yours Test  5", "[part = 1][weight = 1]") {
//	//��Ĳ������񣺱�д���TrafficAdvisory::Floyd()�Ĳ��������������������������ܵ���ϣ��滻������Ķ��ԡ�
//	REQUIRE("��û�����TrafficAdvisory::Floyd()�����Ĳ����������Լ����������ܵ���ϲ��ԡ�" == "���Ѿ�ʵ����TrafficAdvisory::Floyd()����������д�˶���Ĳ����������Լ����������ܵ���ϲ��ԣ�");
//
//}
//
//TEST_CASE("TrafficAdvisory::Dijkstra::yours  Test 6", "[part = 1][weight = 1]") {
//	//��Ĳ������񣺱�д���TrafficAdvisory::Dijkstra()���ƹ�ĳ�����й��ܵĲ��������������������������ܵ���ϣ��滻������Ķ��ԡ�
//	//�ƹ�ĳ������
//	REQUIRE("��û�����TrafficAdvisory::Dijkstra()�������ƹ�ĳ�����й��ܵĲ����������Լ����������ܵ���ϲ��ԡ�" == "���Ѿ�ʵ����TrafficAdvisory::Dijkstra()�������ƹ�ĳ�����й��ܣ�����д�˶���Ĳ����������Լ����������ܵ���ϲ��ԣ�");
//
//}
//
//TEST_CASE("TrafficAdvisory::Floyd::yours Test  7", "[part = 1][weight = 1]") {
//	//��Ĳ������񣺱�д���TrafficAdvisory::Floyd()���ƹ�ĳ�����й��ܵĲ��������������������������ܵ���ϣ��滻������Ķ��ԡ�
//	//�ƹ�ĳ������
//	REQUIRE("��û�����TrafficAdvisory::Floyd()�������ƹ�ĳ�����й��ܵĲ����������Լ����������ܵ���ϲ��ԡ�" == "���Ѿ�ʵ����TrafficAdvisory::Floyd()�������ƹ�ĳ�����еĹ��ܣ�����д�˶���Ĳ����������Լ����������ܵ���ϲ��ԣ�");
//
//}