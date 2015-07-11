#include <iostream>
#include <fstream>
#include <math.h> 
#include "Matrix.h"
#include "BinaryImage.h"
using namespace std;

double* readTXT(char *fileName, int sizeR, int sizeC);
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q); 
void Task1SSD(double* shuffled, double* noise); void Task1NC(double* shuffled, double* noise);
void Task2NC(double* scene, double* wally); void Task2SSD(double* scene, double* wally);

int main()
{
	// Loads the images into the program.
	bool run = true; int user = 0;
	double *shuffled = readTXT("Files\\logo_shuffled.txt", 512, 512);
	double *noise = readTXT("Files\\logo_with_noise.txt", 512, 512);
	double *scene = readTXT("Files\\Cluttered_scene.txt", 768, 1024);
	double *wally = readTXT("Files\\Wally_grey.txt", 49, 36);

	// Runs the user interface for the program.
	while (run)
	{
		cout << "1: for Task 1" << endl << "2: for Task 2" << endl << "3: for Both" << endl << "0: to Exit" << endl;
		cout << "What would you like to run?    ";
		cin >> user;
		switch (user)
		{
			case 0:
				run = false;
				break;
			case 1:
				Task1NC(shuffled, noise);	Task1SSD(shuffled, noise);
				break;
			case 2:
				Task2NC(scene, wally);	Task2SSD(scene, wally);
				break;
			case 3:
				Task1NC(shuffled, noise);	Task1SSD(shuffled, noise); 
				Task2NC(scene, wally);	Task2SSD(scene, wally);
				break;
			default:
				cout << "1: for Task 1" << endl << "2: for Task2" << endl << "0: to exit" << endl;
				break;
		}
	}
	return 0;
}

// Read .txt file with image of size RxC, and convert to an array of doubles.
double* readTXT(char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (myfile.good())
		{
			if (i>sizeR*sizeC - 1) break;
			myfile >> *(data + i);	i++;
		}
		myfile.close();
	}
	else cout << "Unable to open file: " << fileName << endl;
	return data;
}

// Convert data from double to .pgm stored in filename.
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{
	int i; unsigned char *image; ofstream myfile;
	image = (unsigned char *) new unsigned char[sizeR*sizeC];
	// convert the integer values to unsigned char
	for (i = 0; i<sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];
	myfile.open(filename, ios::out | ios::binary | ios::trunc);
	if (!myfile)
	{
		cout << "Can't open file: " << filename << endl; exit(1);
	}
	myfile << "P5" << endl << sizeC << " " << sizeR << endl << Q << endl;
	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));
	if (myfile.fail())
	{
		cout << "Can't write image " << filename << endl; exit(0);
	}
	myfile.close(); delete[] image;
}

// Task that runs Task 1 using the Sum of the Squared Diffrence NNS.
void Task1SSD(double* shuffled, double* noise)
{
	BinaryImage<double> Shuffled(512, 512, shuffled);
	BinaryImage<double> Cleaned(512, 512, noise, 170);
	Matrix<double> shuffledBlock;	Matrix<double> cleanedBlock;
	double SSD = 100000000;	double current = 0;

	for (int ci = 0; ci < 512; ci += 32)						
		for (int cj = 0; cj < 512; cj += 32)
		{
			cleanedBlock = Cleaned.getBlock(ci, ci + 31, cj, cj + 31);
			SSD = 100000000;
			for (int si = 0; si < 512; si += 32)				
				for (int sj = 0; sj < 512; sj += 32)
				{
					shuffledBlock = Shuffled.getBlock(si, si + 31, sj, sj + 31);
					current = shuffledBlock.SSD(cleanedBlock);	
					if (current < SSD)
					{
						Cleaned.setBlock(ci, cj, shuffledBlock);	
						SSD = current; if (SSD == 0) { break; }
					}
					if (SSD == 0) { break; }
				}
			cout << "Finshed block " << ci << "," << cj << " Using SSD: "<< SSD << endl;
		}
	WritePGM("Output\\Task1SSD.pgm", Cleaned.getData(), 512, 512, 1);
	cout << "Finshed Task 1 using SSD" << endl;
}

// Function that runs Task 1 using the Normalised Correlation NNS.
void Task1NC(double* shuffled, double* noise)
{
	BinaryImage<double> Shuffled(512, 512, shuffled);
	BinaryImage<double> Cleaned(512, 512, noise, 170);
	Matrix<double> shuffledBlock; Matrix<double> cleanedBlock;
	double NC = -1; double current = 0;

	for (int ci = 0; ci < 512; ci += 32)
		for (int cj = 0; cj < 512; cj += 32)
		{
			cleanedBlock = Cleaned.getBlock(ci, ci + 31, cj, cj + 31);
			NC = -1;
			for (int si = 0; si < 512; si += 32)
				for (int sj = 0; sj < 512; sj += 32)
				{
					shuffledBlock = Shuffled.getBlock(si, si + 31, sj, sj + 31);
					current = shuffledBlock.NC(cleanedBlock);
					if (current > NC)
					{
						Cleaned.setBlock(ci, cj, shuffledBlock);
						NC = current; if (NC == 1) { break; }
					}
					if (NC == 1){ break; }
				}
			cout << "Finshed block " << ci << "," << cj << " Using NC: " << NC << endl;
		}
	WritePGM("Output\\Task1NC.pgm", Cleaned.getData(), 512, 512, 1);
	cout << "Finshed Task 1 using NC" << endl;
}

// Function that runs Task 2 using the Normalised Correlation NSS.
void Task2NC(double* scene, double* wally)
{
	Matrix<double> Cluttered(768, 1024, scene);
	Matrix<double> Wally(49, 36, wally);

	double NC = -1.0; double current = 0;
	int Ai = 0; int Aj = 0;

	for (int i = 0; i < 720; i += 12)
		for (int j = 0; j < 988; j += 9)
		{
			current = Cluttered.getBlock(i, i + 48, j, j + 35).NC(Wally);
			if (NC < current)
			{
				NC = current;
				Ai = i;	Aj = j;
			}
		}
	Cluttered.setBlock(Ai, Aj, Matrix<double>(49, 36, (double)0));
	WritePGM("Output\\Task2NC.pgm", Cluttered.getData(), 768, 1024, 255);
	cout << "Finshed Task 2 using NC at position: " << Ai << ", " << Aj << endl;
}

// Function that runs Task 2 using the Sum of the Squared Diffrence NSS.
void Task2SSD(double* scene, double* wally)
{
	Matrix<double> Cluttered(768, 1024, scene);
	Matrix<double> Wally(49, 36, wally);

	double SSD = 10000000; double current = 0;
	int Ai = 0; int Aj = 0;

	for (int i = 0; i < 720; i += 12)
		for (int j = 0; j < 988; j += 9)
		{
			current = Cluttered.getBlock(i, i + 48, j, j + 35).SSD(Wally);
			if (SSD > current)
			{
				SSD = current;
				Ai = i; Aj = j;
			}
		}
	Cluttered.setBlock(Ai, Aj, Matrix<double>(49, 36, (double)0));
	WritePGM("Output\\Task2SSD.pgm", Cluttered.getData(), 768, 1024, 255);
	cout << "Finshed Task 2 using SSD at position: " << Ai << ", " << Aj << endl;
}