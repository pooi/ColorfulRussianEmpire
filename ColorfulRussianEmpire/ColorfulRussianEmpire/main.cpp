#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <time.h> // ó�� �ð��� Ȯ���ϱ� ���� �߰�


int main() {

	printf("=============================================\n");
	printf("Dept. of Digital Contents, Sejong University\n");
	printf("Multimedia Programming Homework #4\n");
	printf("Colorful Russian Empire in 1907\n");
	printf("Made by 13011187 ���¿�\n");
	printf("=============================================\n\n");

	IplImage* src; // ���� �̹����� ����� ����
	char fileName[200]; // ���� �̸��� ���� ����

	while (1) {

		printf("Input File Name : ");
		scanf("%s", fileName);

		src = cvLoadImage(fileName);

		if (src == NULL) {
			printf("File Not found!\n");
			continue;
		}
		else
			break;

	}

	clock_t start, finish; // ���α׷� ����, ���� �ð��� ������ ����
	start = clock(); // ����ð� ���� ����

	double eachHeight = src->height / 3; // �̹����� 3��� �ϹǷ� �� �̹����� ���̸� ������
	double eachWidth = src->width; // �̹����� �ʺ� ������

	CvSize eachSize = cvSize(eachWidth, eachHeight);
	IplImage* blue = cvCreateImage(eachSize, 8, 3); // �Ķ��� ���� �����ϰ� �ִ� �̹����� ������ ����
	IplImage* green = cvCreateImage(eachSize, 8, 3); // �ʷϻ� ���� �����ϰ� �ִ� �̹����� ������ ����
	IplImage* red = cvCreateImage(eachSize, 8, 3); // ������ ���� �����ϰ� �ִ� �̹����� ������ ����
	IplImage* dst = cvCreateImage(eachSize, 8, 3); // ���������� ��,��,�� �̹����� ������ �̹��� ����




	// �������� ���� ������ �Ķ�, �ʷ�, ���� ������ �̹����� ������ ���� �ݺ���
	// �ӵ��� ���ʿ��� �ݺ����� ���ְ��� �ϳ��� �ݺ������� 3���� ���� ���� ó��
	for (int y = 0; y < eachHeight; y++) {
		for (int x = 0; x < eachWidth; x++) {

			CvScalar blueColor = cvGet2D(src, y, x); // �������� ���� ������ 0~1/3���������� ���� �������� ��

			cvSet2D(blue, y, x, blueColor); // �Ķ��� �̹����� ����

			/*----------������� �Ķ��� ����----------*/

			CvScalar greenColor = cvGet2D(src, y + eachHeight, x); // eachHeight�� ���������ν� ���� ������ 1/3~2/3���������� ���� �������� ��

			cvSet2D(green, y, x, greenColor); // �ʷϻ� �̹����� ����

			/*----------������� �ʷϻ� ����----------*/

			CvScalar redColor = cvGet2D(src, y + (eachHeight * 2), x); // eachHeight*2�� ���������ν� ���� ������ 2/3~3/3���������� ���� �������� ��

			cvSet2D(red, y, x, redColor); // ������ �̹����� ����

			/*----------������� ������ ����----------*/

		}
	}

	/*----------������� �������κ��� 3���� �̹����� ������ ����----------*/
	/**************************************************/



	// ���ص� �׸��� �߽� ��ǥ�� ����
	int centerX = eachWidth / 2;
	int centerY = eachHeight / 2;

	// ���ص� �׸��� �߽� ��ǥ�� �������� Ư�� ũ�⸸ŭ�� ���� �̹����� �������� ���� ����
	int setArea = eachWidth / 9; // �̹����� ���ϱ⿡ ���� ������ ����� �ʺ��� 8����̶�� �Ǵ��Ͽ� ���� �����ǰ�
	if (setArea % 2 == 1) setArea--; // Ȧ���϶� �߻��� �� �ִ� ������ �����ϱ� ���� ������ ¦��ȭ��
	if (setArea <= 80) setArea = 100; // setArea�� �ʹ� ������ �񱳰� ��������Ƿ� 100���� ������

	int halfSetArea = setArea / 2;

	// ���ص� r, g, b �̹����κ��� setArea^2 ������ ��ŭ�� �̹����� ������ ���� �Լ�
	IplImage* blueArea = cvCreateImage(cvSize(setArea, setArea), 8, 3);
	IplImage* greenArea = cvCreateImage(cvSize(setArea, setArea), 8, 3);
	IplImage* redArea = cvCreateImage(cvSize(setArea, setArea), 8, 3);

	IplImage* blueHisto = cvCreateImage(cvSize(setArea, setArea), 8, 3);  // �Ķ��� ���� �����ϰ� �ִ� �̹����� ������ ����
	IplImage* greenHisto = cvCreateImage(cvSize(setArea, setArea), 8, 3);  // �ʷϻ� ���� �����ϰ� �ִ� �̹����� ������ ����
	IplImage* redHisto = cvCreateImage(cvSize(setArea, setArea), 8, 3);  // ������ ���� �����ϰ� �ִ� �̹����� ������ ����



	// ���ص� �׸��� �߽� ��ǥ�� ���� ��, ��, ��, �� setArea/2��ŭ�� ��ġ���� �׸��� ������
	// �ӵ��� ���ʿ��� �ݺ����� ���ְ��� �ϳ��� �ݺ������� 3���� ���� ���� ó��
	for (int y = -halfSetArea; y < halfSetArea; y++) {
		for (int x = -halfSetArea; x < halfSetArea; x++) {

			CvScalar blueColor = cvGet2D(blue, y + centerY, x + centerX); // �Ķ��� �����̹����� �߽����κ����� (x, y)��ŭ ������ ���� ���� ������

			cvSet2D(blueArea, y + halfSetArea, x + halfSetArea, blueColor); // �׸��� ��ǥ�� (0,0)���� �̹Ƿ� ��������ŭ ������

			/*----------������� �Ķ��� ����----------*/

			CvScalar greenColor = cvGet2D(green, y + centerY, x + centerX); // �ʷϻ� �����̹����� �߽����κ����� (x, y)��ŭ ������ ���� ���� ������

			cvSet2D(greenArea, y + halfSetArea, x + halfSetArea, greenColor);

			/*----------������� �ʷϻ� ����----------*/

			CvScalar redColor = cvGet2D(red, y + centerY, x + centerX); // ������ �����̹����� �߽����κ����� (x, y)��ŭ ������ ���� ���� ������
			cvSet2D(redArea, y + halfSetArea, x + halfSetArea, redColor);

			/*----------������� ������ ����----------*/

		}
	}


	/*-----���� ���� 3���� ������ �̹����� ����Ͽ� Ư����������  ���� �̹����� �̾Ƴ��� ����-----*/
	/*******************************************************************/

	// �� ���� ������׷� ������ �� ������
	int histo_blue[256][3] = { 0 };
	int histo_green[256][3] = { 0 };
	int histo_red[256][3] = { 0 };

	// �� ���� ������׷� ������ �����ϴ� �ݺ���
	for (int x = 0; x < setArea; x++) {
		for (int y = 0; y < setArea; y++)
		{
			CvScalar blueColor = cvGet2D(blueArea, y, x);
			CvScalar greenColor = cvGet2D(greenArea, y, x);
			CvScalar redColor = cvGet2D(redArea, y, x);

			for (int k = 0; k < 3; k++) {
				histo_blue[int(blueColor.val[k])][k] ++;
				histo_green[int(greenColor.val[k])][k] ++;
				histo_red[int(redColor.val[k])][k] ++;
			}

		}
	}

	// �� ���� ������׷� �������� �� ������
	int cumul_blue[256][3] = { 0 };
	int cumul_green[256][3] = { 0 };
	int cumul_red[256][3] = { 0 };

	// �� ���� ������׷� �������� ���ϴ� �ݺ���
	for (int k = 0; k < 3; k++) {
		cumul_blue[0][k] = histo_blue[0][k];
		cumul_green[0][k] = histo_green[0][k];
		cumul_red[0][k] = histo_red[0][k];

		for (int i = 1; i < 256; i++)
		{
			cumul_blue[i][k] = cumul_blue[i - 1][k] + histo_blue[i][k];
			cumul_green[i][k] = cumul_green[i - 1][k] + histo_green[i][k];
			cumul_red[i][k] = cumul_red[i - 1][k] + histo_red[i][k];
		}
	}

	// ������ ������׷� �������� ���� ~Histo�̹��� ������ �����Ű�� �ݺ���
	for (int y = 0; y < setArea; y++) {
		for (int x = 0; x < setArea; x++)
		{
			CvScalar f = cvGet2D(blueArea, y, x);
			CvScalar g;
			for (int k = 0; k < 3; k++)
			{
				g.val[k] = cumul_blue[int(f.val[k])][k]
					/ float(cumul_blue[255][k]) * 255;
			}
			cvSet2D(blueHisto, y, x, g);

			/*------------������� �Ķ���------------*/

			f = cvGet2D(greenArea, y, x);
			for (int k = 0; k < 3; k++)
			{
				g.val[k] = cumul_green[int(f.val[k])][k]
					/ float(cumul_green[255][k]) * 255;
			}
			cvSet2D(greenHisto, y, x, g);

			/*------------������� �ʷϻ�------------*/

			f = cvGet2D(redArea, y, x);
			for (int k = 0; k < 3; k++)
			{
				g.val[k] = cumul_red[int(f.val[k])][k]
					/ float(cumul_red[255][k]) * 255;
			}
			cvSet2D(redHisto, y, x, g);

			/*------------������� ������------------*/
		}
	}


	/*----------������� ������׷��� ����Ͽ� �� �̹����� ��ü���� ����� ����----------*/
	/**************************************************************/



	// ó�� �ӵ��� ���� �̹����� ����, ����50%��ŭ �� �ٿ��ֱ� ���� �κ�

	// ����ȯ�� ����Ͽ� �̹��� ���
	double M[2][2]; // �����
	double sx = 0.5, sy = 0.5; // 0.5�� ��ŭ ����ϱ�����
	M[0][0] = sx;		M[0][1] = 0;
	M[1][0] = 0;			M[1][1] = sy;

	double invM[2][2]; // �����
	double det = M[0][0] * M[1][1] - M[0][1] * M[1][0]; // determinant(��Ľ�)

	if (abs(det) < 0.000001) { // determinant�� 0�̶�� �ȳ��� ��°� �Բ� ���α׷� ����
		printf("����� �Ұ����մϴ�.\n");
		return 0;
	}

	// ����� ���� ���� ������
	invM[0][0] = M[1][1] / det;		invM[0][1] = -M[0][1] / det;
	invM[1][0] = -M[1][0] / det;		invM[1][1] = M[0][0] / det;

	// blueArea, greenArea, redArea�� ����, ���� 50%�� �����
	// �̹����� �� ������ �����ϱ� ���� 2���� ���� �迭 ���� �� �޸� �Ҵ�
	double **blueArray = (double**)malloc(sizeof(double*)*halfSetArea);
	double **greenArray = (double**)malloc(sizeof(double*)*halfSetArea);
	double **redArray = (double**)malloc(sizeof(double*)*halfSetArea);

	for (int i = 0; i < halfSetArea; i++) {
		blueArray[i] = (double*)malloc(sizeof(double)*halfSetArea);
		greenArray[i] = (double*)malloc(sizeof(double)*halfSetArea);
		redArray[i] = (double*)malloc(sizeof(double)*halfSetArea);
	}


	// ��ҵ� �̹����� �����ϱ� ���� �ݺ���
	// �ӵ��� ���ʿ��� �ݺ����� ���ְ��� �ϳ��� �ݺ������� 3���� ���� ���� ó��
	for (int x2 = 0; x2 < blueArea->width*sx; x2++) {
		for (int y2 = 0; y2 < blueArea->height*sy; y2++) {

			double x1 = invM[0][0] * x2 + invM[0][1] * y2;
			double y1 = invM[1][0] * x2 + invM[1][1] * y2;

			// ������ ���� ���� �ʰ� ����ó��
			if (x1<0 || x1>blueArea->width - 1) continue;
			if (y1<0 || y1>blueArea->height - 1) continue;

			/*----------������� ��ǥ�� ����----------*/

			CvScalar blueColor = cvGet2D(blueHisto, y1, x1);
			blueArray[y2][x2] = blueColor.val[0];

			/*----------������� �Ķ��� ����----------*/

			CvScalar greenColor = cvGet2D(greenHisto, y1, x1);
			greenArray[y2][x2] = greenColor.val[0];

			/*----------������� �ʷϻ� ����----------*/

			CvScalar redColor = cvGet2D(redHisto, y1, x1);
			redArray[y2][x2] = redColor.val[0];

			/*----------������� ������ ����----------*/

		}
	}

	/*----------������� Ư�� �������� �����̹����� ����, ���� 50%�� ��ҽ�Ű�� ����----------*/
	/*****************************************************************/

	// �λ����� �Ÿ����� �����ϰ� ���ϴ� �Ͱ� ���õ� ������
	double sumBToG = 0, sumBToR = 0; // �� ���� �Ÿ����� �������� ����ؼ� ����� ����
	double minSumBToG = FLT_MAX, minSumBToR = FLT_MAX; // �� ���� �Ÿ��� �� �ּҰŸ����� ����� ����
	int count = 0; // �� ���� �Ÿ����� ���� ������ ������ ũ�Ⱑ ������ ������ ����

				   // �ʷϻ� �̹����� ������ �̹����� ���� �̵� ���� ����� ����
	int tempGx = 0, tempGy = 0; // �ʷϻ� �̹����� ���� �̵� �ȼ��� ����
	int tempRx = 0, tempRy = 0; // ������ �̹����� ���� �̵� �ȼ��� ����

								// �� �̹����� small�̹������� small�̹��� �������� ��%��ŭ �����̸鼭
								// ������ ��ġ�� ã�� �������� ���ϴ� ���� (������ ��)
	int moveX = halfSetArea*(2.0 / 10); // x���� ��, ��� ���� 20%��ŭ �����̸鼭 ����
	int moveY = halfSetArea*(8.0 / 10); // y���� ��, �Ʒ��� ���� 80%��ŭ �����̸鼭 ����

										// ������ �� �������� ���� ���ϱ� ���� �ݺ���
	for (int v = -moveY; v <= moveY; v++) {
		for (int u = -moveX; u <= moveX; u++) {

			// �� ������ �ٲ� ������ ���� ���ؾ��ϹǷ� ���� �ʱ�ȭ (�ּڰ��� �����ϴ� ������ ����)
			count = 0;
			sumBToG = 0;
			sumBToR = 0;

			// �� �̹��� ���� ���� �Ÿ����� ���ϱ� ���� �ݺ��� 
			for (int x = 0; x < blueArea->width*sx; x++) {

				// ���ʿ��� ��� �� �ݺ� ������ ���� x2���� �̸� �����
				int x2 = x + u; // x������ u��ŭ �̵��� x��ǥ
				if (x2 < 0) continue; // x2�� 0���� ������ ��� ����

				for (int y = 0; y < blueArea->height*sy; y++) {


					int y2 = y + v; // y������ v��ŭ �̵��� y��ǥ

					// �̹��� ������ ��� Ȯ���� �ſ� �����Ƿ� ����ó��
					if (y2 < 0) continue; // y2�� 0���� ���� ���� ��� ����������
					if (y2 > blueArea->height*sy - 1) break; // y2�� �̹����� ���̸� �ʰ��Ѵٸ� �ݺ��� ���� (�����ϴ� ���� ���ǹ��ϱ� ����)
					if (x2 > blueArea->width*sx - 1) continue;

					/*----------������� ��ǥ�� ����----------*/

					double blueColor = blueArray[y][x];//blueArray[int(y*halfSetArea+x)];
					double greenColor = greenArray[y2][x2];//greenArray[int(y2*halfSetArea+x2)];
					double redColor = redArray[y2][x2];//redArray[int(y2*halfSetArea+x2)];

					double disG = (blueColor - greenColor)*(blueColor - greenColor);
					double disR = (blueColor - redColor)*(blueColor - redColor);

					sumBToG += disG; // �Ķ��� �̹����� �ʷϻ� �̹����� �Ÿ��� �������� ����
					sumBToR += disR; // �Ķ��� �̹����� ������ �̹����� �Ÿ��� �������� ����

					count++; // ���� ������ ���̸� ī��Ʈ��

					 /*----------������� �� ������ �Ÿ� ���----------*/

				} // y for�� ��

				if (x2 > blueArea->width*sx - 1) // x2�� �̹����� �ʺ� �ʰ��Ѵٸ� �ݺ��� ���� (�����ϴ� ���� ���ǹ��ϱ� ����)
					break;

			} // x for�� ��

			  // �ʷϻ� �̹����� �̵� ��ǥ�� �����ϱ� ���� ���ǹ�
			if (sumBToG / count < minSumBToG) { // ������ �Ÿ����� ���� ������ŭ�� ����� ���ϰ� �ּ� �������̶� ��

				minSumBToG = sumBToG / count; // ������ �Ÿ����� ���� ������ŭ�� ����� �ٽ� �ּڰ����� ����
				tempGx = u; // x�ุŭ �̵��� ���� ����
				tempGy = v; // y�ุŭ �̵��� ���� ����

			}

			// ������ �̹����� �̵� ��ǥ�� �����ϱ� ���� ���ǹ�
			if (sumBToR / count < minSumBToR) { // ���� ����

				minSumBToR = sumBToR / count;
				tempRx = u;
				tempRy = v;

			}

		} // u for�� ��
	} // v for�� ��

	// �̹����� ������ ���ϱ� ���� 50%��ŭ �ٿ����Ƿ�
	// ���� �̵� �ȼ��� 50%��ŭ �پ���� �����
	// �ٽ� 2�踦 ����
	tempGx *= 2;
	tempGy *= 2;
	tempRx *= 2;
	tempRy *= 2;


	/*----------������� �̵��ؾ��ϴ� ��ǥ�� ���ϴ� ����----------*/
	/********************************************/


	// ���� �̵� ��ǥ���� ���� ���� �̹�����
	// �����ϱ� ���� �ݺ���
	// �Ķ����� ���ػ�, ������ġ
	for (int y = 0; y < dst->height; y++) {
		for (int x = 0; x < dst->width; x++) {

			// green�̹����� ���� �̵� ��ǥ
			int y2 = y + tempGy;
			int x2 = x + tempGx;

			// red�̹����� ���� �̵� ��ǥ
			int y3 = y + tempRy;
			int x3 = x + tempRx;

			// ���� �ʰ� ������ ���� ���� ó��
			if (y2<0 || y2>dst->height - 1 || x2<0 || x2>dst->width - 1) { // green�̹����� ���� �̵� ��ǥ�� ������ �ʰ��Ͽ��� ���

				if (y3<0 || y3>dst->height - 1 || x3<0 || x3>dst->width - 1) { // ���� red�̹����� ���� �̵� ��ǥ�� ������ �ʰ��Ͽ��� ���
					// �ƹ��͵� ����
					continue;
				}
				else { // red�̹����� ���� �̵� ��ǥ�� ������ �ʰ����� �ʾ��� ���
					// �Ķ�-������ ��ħ

					CvScalar stdColor = cvGet2D(blue, y, x); // �ʱ� �Ķ����� ���� ������
					CvScalar redColor = cvGet2D(red, y3, x3); // �ʱ� �������� ���� ������

					stdColor.val[2] = redColor.val[2]; // ���ػ��� ������ ���� ����

					cvSet2D(dst, y, x, stdColor); // �ϼ��� r,g,b�� ������ dst�� ���� ����

				}

			}
			else { // green �̹����� ���� �̵� ��ǥ�� ������ �ʰ����� �ʾ��� ���

				if (y3<0 || y3>dst->height - 1 || x3<0 || x3>dst->width - 1) { // ������ red�̹����� ���� �̵� ��ǥ�� ������ �ʰ��Ͽ��� ���
					// �Ķ�-�ʷϸ� ��ħ

					CvScalar stdColor = cvGet2D(blue, y, x); // �ʱ� �Ķ����� ���� ������
					CvScalar greenColor = cvGet2D(green, y2, x2); // �ʱ� �ʷϻ��� ���� ������

					stdColor.val[1] = greenColor.val[1]; // ���ػ��� �ʷϻ� ���� ����

					cvSet2D(dst, y, x, stdColor);

				}
				else { // green, red�̹��� ��� ���� �̵� ��ǥ�� ������ �ʰ����� �ʾ��� ���
					// �Ķ�-�ʷ�-���� ��� ��ħ

					CvScalar stdColor = cvGet2D(blue, y, x); // �ʱ� �Ķ����� ���� ������
					CvScalar greenColor = cvGet2D(green, y2, x2); // �ʱ� �ʷϻ��� ���� ������
					CvScalar redColor = cvGet2D(red, y3, x3); // �ʱ� �������� ���� ������

					stdColor.val[1] = greenColor.val[1]; // ���ػ��� �ʷϻ� ���� ����
					stdColor.val[2] = redColor.val[2]; // ���ػ��� ������ ���� ����

					cvSet2D(dst, y, x, stdColor); // �ϼ��� r,g,b�� ������ dst�� ���� ����
				}

			}


		}
	}

	/*----------������� �̵��ؾ��ϴ� ��ǥ�� ���� 3���� ��ġ�� ����----------*/
	/****************************************************/



	finish = clock(); // ����ð� ���� ����
	printf("ó�� �ð� : %.3f��\n", (double)(finish - start) / CLOCKS_PER_SEC); // �� ������ �����

	// ���� �̹����� �ϼ��� �̹��� ���
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();


	// ��� �޸� ����
	free(blueArray);
	free(greenArray);
	free(redArray);

	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseImage(&blue);
	cvReleaseImage(&green);
	cvReleaseImage(&red);
	cvReleaseImage(&blueArea);
	cvReleaseImage(&greenArea);
	cvReleaseImage(&redArea);
	cvReleaseImage(&blueHisto);
	cvReleaseImage(&greenHisto);
	cvReleaseImage(&redHisto);

	cvDestroyAllWindows();


	return 0;
}