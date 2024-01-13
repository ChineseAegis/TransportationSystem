/*
 * UtilitiesSpeedTest.h
 * �����ʵ������ο����������ͨ��ѯTrafficAdvisory�ຯ����ִ�Еr�g���ܵ�ͳ����ع���������SpeedTest
 * @author ����<guoyan410@cug.edu.cn>
 * @date ���� 2024-1-7
 */
#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <iomanip> //std::setw��setprecision
#include "eigen-3.4.0\Eigen\Dense" //�ṩ��Ϲ��ܵĿ�Դ���������
#include "eigen-3.4.0/Eigen/QR"
#include "UtilitiesTime.h" //��ʱ����Timer
#include "UtilitiesRandom.h" //makeUniqueRandomArray<T>()

#define maxN 8
#define maxE 30
#define numTrials 50
#define incN 2
#define incE 1

using std::vector;
using std::string;
using std::set;
using std::stringstream;
using std::cout;
using std::endl;
using std::setw;
using std::fixed;
using std::scientific;
using std::setprecision;
using namespace Eigen;

int function() {
	int x = 0;
	for (int i = 0; i < 350; i++)
	{
		x++;
	}
	return x;
}
//�ο�O(n+e)������
class O_n_add_e {
public:
	O_n_add_e() {};
	void run(int n, int e) {//�ο�����
		for (int i = 0; i < n; i++) {
			function(); //ѭ��......
		}
		for (int i = 0; i < 2*e; i++) {
			function(); //ѭ��......
		}
	}
};

//�ο�O(n*n)������
class O_n_square {
public:
	O_n_square() {};
	void run(int n) {//�ο�����
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				function(); //ѭ��......
		}
	}
};

//�ο�O(n*n*n)������
class O_n_cube {
public:
	O_n_cube() {};
	void run(int n) {//�ο�����
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++) {
					function();
				}					 //ѭ��......
		}
	}
};

//�ο�O(elogn)������
class O_elogn {
public:
	O_elogn() {};
	void run(int n,int e) {//�ο�����
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2*e; j++) {
				function(); //ѭ��......
			}
			i = i << 1;
		}
	}
};

//�ο�O(n*e)������
class O_n_multiply_e {
public:
	O_n_multiply_e() {};
	void run(int n,int e) {//�ο�����
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2*e; j++)
				function(); //ѭ��......
		}
	}
};

// ʹ��Eigen����ж�Ԫ���ζ���ʽ�ع�:ʹ����Ϻ���f(x1,x2)=c0+c1*x1+c2*x2+c3*x1^2+c4*x1*x2+c5*x2^2+c6*x1^3+c7*x1^2*x2+c8*x1*x2^2+c9*x2^3��
Eigen::VectorXd multivariateCubicPolynomialRegression(const std::vector<double>& x1, const std::vector<double>& x2, const std::vector<double>& y) {
	int dataSize = x1.size();
	Eigen::MatrixXd A(dataSize, 10);  // Ten coefficients for a cubic polynomial
	Eigen::VectorXd b(y.size());

	for (size_t k = 0; k < dataSize; ++k) {
		A(k, 0) = 1.0;
		A(k, 1) = x1[k];
		A(k, 2) = x2[k];
		A(k, 3) = std::pow(x1[k], 2);
		A(k, 4) = x1[k] * x2[k];
		A(k, 5) = std::pow(x2[k], 2);
		A(k, 6) = std::pow(x1[k], 3);
		A(k, 7) = std::pow(x1[k], 2) * x2[k];
		A(k, 8) = x1[k] * std::pow(x2[k], 2);
		A(k, 9) = std::pow(x2[k], 3);

		b(k) = y[k];
	}

	Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeThinU | Eigen::ComputeThinV);// ʹ��JacobiSVD������С���˷����
	Eigen::VectorXd result = svd.solve(b);
	return result;
}

//ʹ��Eigen�������ϳ̶�ָ��SSE��R2
vector<double> calculateSSE_RSquared(const Eigen::VectorXd& coefficients, const std::vector<double>& x1, const std::vector<double>& x2, const std::vector<double>& y) {
	vector<double> returnVec;
	int dataSize = x1.size();
	Eigen::VectorXd predicted(dataSize);
	Eigen::VectorXd yVector = Eigen::Map<const Eigen::VectorXd>(y.data(), y.size());
	double meanY = yVector.mean();

	for (size_t k = 0; k < dataSize; ++k) {
		predicted(k) = coefficients[0] +
			coefficients[1] * x1[k] +
			coefficients[2] * x2[k] +
			coefficients[3] * std::pow(x1[k], 2) +
			coefficients[4] * x1[k] * x2[k] +
			coefficients[5] * std::pow(x2[k], 2) +
			coefficients[6] * std::pow(x1[k], 3) +
			coefficients[7] * std::pow(x1[k], 2) * x2[k] +
			coefficients[8] * x1[k] * std::pow(x2[k], 2) +
			coefficients[9] * std::pow(x2[k], 3);
	}

	Eigen::VectorXd residuals = yVector - predicted;
	double SSE = residuals.squaredNorm();
	double SST = (yVector.array() - meanY).square().sum();  // Corrected line:Now, the SST calculation uses the .array() method to convert yVector to an array, and then the .square().sum() methods for element-wise squaring and summing, which should resolve the error you encountered.
	double RSquared = 1.0 - (SSE / SST);
	returnVec.push_back(SSE);
	returnVec.push_back(RSquared);
	return returnVec;
}

//��������ʱ���ƽ���ݶ�ģ����ӳ�㷨��ʱ��Ч��
double calculateAverageGradientMagnitude_10(const Eigen::VectorXd& coefficients, const std::vector<double>& x1, const std::vector<double>& x2) {
	int dataSize = x1.size();
	double sumGradientMagnitude = 0.0;

	for (size_t k = 0; k < dataSize; ++k) {
		// Gradient vector for the cubic polynomial
		Eigen::VectorXd gradient(2);
		gradient << coefficients[1] + 2 * coefficients[3] * x1[k] + coefficients[4] * x2[k] + 3 * coefficients[6] * std::pow(x1[k], 2) + 2 * coefficients[7] * x1[k] * x2[k] + coefficients[8] * std::pow(x2[k], 2),
			coefficients[2] + coefficients[4] * x1[k] + 2 * coefficients[5] * x2[k] + 3 * coefficients[9] * std::pow(x2[k], 2) + 2 * coefficients[8] * x1[k] * x2[k] + coefficients[7] * std::pow(x1[k], 2);

		// Calculate the gradient magnitude
		sumGradientMagnitude += gradient.norm();
	}

	return sumGradientMagnitude / dataSize;
}

// TestClass���Ͷ�����������������ο������ʱ�����ܱȽ�
template<typename T, typename E, typename TestClass>
class SpeedTest {
public:
	SpeedTest() {};
	
	//������n��e�仯��ʮ���㷨��ִ��ʱ�����ߵ�б��
	vector<std::stringstream> run() {
		vector<std::stringstream> ss_Speed;
		vector<Timer> timer;//��ʱ��
		timer.resize(6, Timer());
		
		std::vector<double> vertexSequence;//����������
		std::vector<double> edgeSequence;//��������
		std::vector<std::vector<double>> runtimeSequence;//����ʱ������
			
		for (int i = 0; i < 6; i++)
			runtimeSequence.push_back(vector<double>());

		vector<string> algorithmtype;//ʮ���㷨	
		algorithmtype.push_back("O(n+e)");
		algorithmtype.push_back("O(n*n)");		
		algorithmtype.push_back("O(elogn)");
		algorithmtype.push_back("O(n*e)");
		algorithmtype.push_back("O(n*n*n)");
		//algorithmtype.push_back("numVertices_from");
		algorithmtype.push_back("Dijkstra");		
		//algorithmtype.push_back("Floyd");
		//algorithmtype.push_back("Kth_ShortestPath");
		//algorithmtype.push_back("All_nonrepetition_paths");

		for (int n = incN; n <= maxN; n = n + incN) {
			for (int e = incE; e <= n * (n - 1) / 2 && e <= maxE; e = e + incE) {
				vertexSequence.push_back(n);
				edgeSequence.push_back(e);
				//���ʵ�����
				vector<O_n_add_e> references0;//�ο��������1
				vector<O_n_square> references1;//�ο��������2
				vector<O_elogn> references2;//�ο��������3
				vector<O_n_multiply_e> references3;//�ο��������4
				vector<O_n_cube> references4;//�ο��������5
				vector<WUSGraph<std::string,int>*> tests;// ���ص��ע�ĳ������
				std::vector<std::vector<string>> testsLabels;//�����ǩ
				
				//�ֱ𹹽�numTrials������ο�������󡢶�����Ϊn������Ϊe��������TestClass�Ķ���
				for (int num_tests = 0; num_tests < numTrials; num_tests++) {
					O_n_add_e rObject0;
					references0.push_back(rObject0);
					O_n_square rObject1;
					references1.push_back(rObject1);
					O_elogn rObject2;
					references2.push_back(rObject2);
					O_n_multiply_e rObject3;
					references3.push_back(rObject3);
					O_n_cube rObject4;
					references4.push_back(rObject4);

					//�������һ��n�����㣬e���ߵ�TestClass���Ͷ��󣬵��������������Ƿ����
					//TestClass tObject(n, e);
					WUSGraphClient<std::string, int> toObject;
					WUSGraph<std::string, int> *g=new WUSGraph<std::string,int>(n,e);









					set<T> labelSet = g->getLabels();//�õ����еĶ����ǩ����
					std::vector<T> labelVector;
					if (labelSet.size() == 0) {
						cout << "===============================================================================\n";
						cout << "���ܽ���TrafficAdvisory�ຯ����ִ�Еr�g���ܵ�ͳ����ع������\n��Ϊ��û�����ͼ��getLabels��insertVertex�Ȳ���������Ҫ�������Щ������ʵ�֣�" << endl;
						cout << "===============================================================================\n";
						return ss_Speed;
						/*T *arr=makeUniqueRandomArray<T>(n, randomString);
						labelVector= std::vector<T>(arr, arr+n);						
						delete[] arr;*/
					}
					else {
						labelVector = std::vector<T>(labelSet.begin(), labelSet.end());
					}
					testsLabels.push_back(labelVector);
					tests.push_back(g);
				}

				//��¼ʮ����������numTrials�ε�����ʱ��

				//���в���ʱ�ο�����1
				timer[0].start();
				for (int num_tests = 0; num_tests < numTrials; num_tests++) //ʵ��numTrials��
					references0[num_tests].run(n, e);//O_n_add_e
				timer[0].stop();

				//���в���ʱ�ο�����1
				timer[1].start();
				for (int num_tests = 0; num_tests < numTrials; num_tests++) //ʵ��numTrials��
					references1[num_tests].run(n);//O_n_square
				timer[1].stop();

				//���в���ʱ�ο�����2
				timer[2].start();
				for (int num_tests = 0; num_tests < numTrials; num_tests++) //ʵ��numTrials��
					references2[num_tests].run(n, e);//O_elogn
				timer[2].stop();

				//���в���ʱ�ο�����3
				timer[3].start();
				for (int num_tests = 0; num_tests < numTrials; num_tests++) //ʵ��numTrials��
					references3[num_tests].run(n, e);//O_n_multiply_e
				timer[3].stop();

				//���в���ʱ�ο�����4
				timer[4].start();
				for (int num_tests = 0; num_tests < numTrials; num_tests++) //ʵ��numTrials��
					references4[num_tests].run(n);//O_n_cube
				timer[4].stop();

				////���в���ʱʵ�����2���㷨1
				//timer[5].start();
				//for (int num_tests = 0; num_tests < numTrials; num_tests++) {//ʵ��numTrials��
				//	int source = std::rand() % n;
				//	tests[num_tests].numVertices_from(testsLabels[num_tests][source]);//��source�����ٱ���
				//}				
				//timer[5].stop();

				//���в���ʱʵ�����2���㷨2
				timer[5].start();

				for (int num_tests = 0; num_tests < numTrials; num_tests++) { //ʵ��numTrials��
					int source = std::rand() % n;
					int destination = std::rand() % n;
					WUSGraphClient<std::string, int> toObject;
					toObject.Dijkstra(*tests[num_tests], testsLabels[num_tests][source], testsLabels[num_tests][destination]);//ʵ���ڶ�����n����Ϊe��ͼ��������·��
					delete tests[num_tests];
					tests[num_tests] = nullptr;
				}

				timer[5].stop();

				//���в���ʱʵ�����2���㷨3
				//timer[7].start();
				//for (int num_tests = 0; num_tests < numTrials; num_tests++) { //ʵ��numTrials��
				//	int source = std::rand() % n;
				//	int destination = std::rand() % n;
				//	tests[num_tests].Floyd(testsLabels[num_tests][source], testsLabels[num_tests][destination]);//���·��
				//}
				//timer[7].stop();

				////���в���ʱʵ�����2���㷨4
				//timer[8].start();
				//for (int num_tests = 0; num_tests < numTrials; num_tests++) { //ʵ��numTrials��
				//	int source = std::rand() % n;
				//	int destination = std::rand() % n;
				//	//int k = std::rand() % n;
				//	tests[num_tests].Kth_ShortestPath(testsLabels[num_tests][source], testsLabels[num_tests][destination], 5);//��K��·��
				//}
				//timer[8].stop();

				////���в���ʱʵ�����2���㷨5
				//timer[9].start();

				//for (int num_tests = 0; num_tests < numTrials; num_tests++) { //ʵ��numTrials��
				//	int source = std::rand() % n;
				//	int destination = std::rand() % n;
				//	tests[num_tests].All_nonrepetition_paths(testsLabels[num_tests][source], testsLabels[num_tests][destination], 6);//��������·��������10�����㣩
				//}
				//timer[9].stop();

				//�洢ͳ�Ƶ�����ʱ���Ա����ع����
				for (int i = 0; i < 6; i++)
					runtimeSequence[i].push_back(timer[i].diff_in_ms());
				
				//ÿ�����ͳ�Ƶ�����ʱ��
				std::cout << "\nn= " << n << " e= " << e;
				for (int i = 0; i < 6; i++)
					cout << " " << algorithmtype[i] << " " << std::fixed << std::setprecision(3) << runtimeSequence[i].back();
				
			}
		}
		cout << endl << endl;

		// ʹ����С���˷����ʮ������ʱ���붥�����������Ĺ�ϵ
		// �õ����ϵ��coefficients����ϳ̶�(SSE, RSquared)������ʱ���������ߵ�ƽ���ݶ�ģAverageGradientMagnitude��
		vector<Eigen::VectorXd> coefficients;
		vector<double> SSE, RSquared, AverageGradientMagnitude;
		
		// ʹ�ö�Ԫ���ζ���ʽ�ع��������ʱ��Ͷ������������Ĺ�ϵ
		for (size_t t = 0; t < 6; ++t) {
			coefficients.push_back(multivariateCubicPolynomialRegression(vertexSequence, edgeSequence, runtimeSequence[t]));
			std::cout << "�㷨 " << algorithmtype[t] << " ��Ԫ��������ʽ�ع�ϵ����" << std::fixed << std::setprecision(6) << coefficients[t].transpose() << std::endl;

			// Calculate SSE and R-squared
			vector<double> SSE_RSquared = calculateSSE_RSquared(coefficients[t], vertexSequence, edgeSequence, runtimeSequence[t]);
			double sse = SSE_RSquared[0];
			double rSquared = SSE_RSquared[1];

			// Calculate average gradient magnitude
			double averageGradientMagnitude = calculateAverageGradientMagnitude_10(coefficients[t], vertexSequence, edgeSequence);

			AverageGradientMagnitude.push_back(averageGradientMagnitude);
			SSE.push_back(sse);
			RSquared.push_back(rSquared);
		}		
		
		ss_Speed.push_back(std::stringstream());
		ss_Speed.push_back(std::stringstream());

		for (int i = 0; i < 6; i++)
			ss_Speed[0] << "\n" << setw(25) << algorithmtype[i] << "����ϲв�ƽ����SSE= " << std::scientific << std::setprecision(2) << setw(6) << SSE[i] << " ������ϵ��R-Squared= " << std::fixed<<std::setprecision(2)<<setw(5) << RSquared[i] << " ��ƽ���ݶ�ģAGM= " << std::scientific << std::setprecision(3) << setw(10) << AverageGradientMagnitude[i] << endl;
		
		ss_Speed[0] << endl << endl;		
		std::cout << ss_Speed[0].str();
		ss_Speed[1] << std::setiosflags(std::ios::fixed) << std::setprecision(2);//�������С����ʽ
		ss_Speed[1] << endl;
		//ss_Speed[1] << "       numVertices_from ����ʱ��AGM : O(n+e) ����ʱ��AGM = " << AverageGradientMagnitude[5] / AverageGradientMagnitude[0] << endl;
		ss_Speed[1] << "               Dijkstra ����ʱ��AGM : O(n*n) ����ʱ��AGM = " << AverageGradientMagnitude[5] / AverageGradientMagnitude[1] << endl;
		ss_Speed[1] << "               Dijkstra ����ʱ��AGM : O(elogn) ����ʱ��AGM = " << AverageGradientMagnitude[5] / AverageGradientMagnitude[2] << endl;
		//ss_Speed[1] << "                  Floyd ����ʱ��AGM : O(n*n*n) ����ʱ��AGM = " << AverageGradientMagnitude[7] / AverageGradientMagnitude[4] << endl;
		//ss_Speed[1] << "       Kth_ShortestPath ����ʱ��AGM : Dijkstra ����ʱ��AGM = " << AverageGradientMagnitude[8] / AverageGradientMagnitude[6] << endl;
		//ss_Speed[1] << "All_nonrepetition_paths ����ʱ��AGM : numVertices_from ����ʱ��AGM = " << AverageGradientMagnitude[9] / AverageGradientMagnitude[5] << endl;
		//ss_Speed[1] << endl;
		
		std::cout << ss_Speed[1].str();

		return ss_Speed;		
	}	
};