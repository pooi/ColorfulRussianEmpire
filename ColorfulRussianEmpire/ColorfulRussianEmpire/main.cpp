#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <time.h> // 처리 시간을 확인하기 위해 추가


int main() {

	printf("=============================================\n");
	printf("Dept. of Digital Contents, Sejong University\n");
	printf("Multimedia Programming Homework #4\n");
	printf("Colorful Russian Empire in 1907\n");
	printf("Made by 13011187 유태우\n");
	printf("=============================================\n\n");

	IplImage* src; // 원본 이미지가 저장될 변수
	char fileName[200]; // 파일 이름을 받을 변수

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

	clock_t start, finish; // 프로그램 시작, 종료 시간을 저장할 변수
	start = clock(); // 실행시간 측정 시작

	double eachHeight = src->height / 3; // 이미지를 3등분 하므로 한 이미지의 높이를 저장함
	double eachWidth = src->width; // 이미지의 너비를 저장함

	CvSize eachSize = cvSize(eachWidth, eachHeight);
	IplImage* blue = cvCreateImage(eachSize, 8, 3); // 파란색 값을 저장하고 있는 이미지를 저장할 변수
	IplImage* green = cvCreateImage(eachSize, 8, 3); // 초록색 값을 저장하고 있는 이미지를 저장할 변수
	IplImage* red = cvCreateImage(eachSize, 8, 3); // 빨간색 값을 저장하고 있는 이미지를 저장할 변수
	IplImage* dst = cvCreateImage(eachSize, 8, 3); // 최종적으로 빨,파,초 이미지가 합쳐질 이미지 변수




	// 원본에서 가장 위부터 파랑, 초록, 빨강 순으로 이미지를 나누기 위한 반복문
	// 속도와 불필요한 반복문을 없애고자 하나의 반복문에서 3가지 색을 전부 처리
	for (int y = 0; y < eachHeight; y++) {
		for (int x = 0; x < eachWidth; x++) {

			CvScalar blueColor = cvGet2D(src, y, x); // 원본에서 원본 높이의 0~1/3지점까지의 색을 가져오게 됨

			cvSet2D(blue, y, x, blueColor); // 파랑색 이미지에 저장

			/*----------여기까지 파랑색 저장----------*/

			CvScalar greenColor = cvGet2D(src, y + eachHeight, x); // eachHeight를 더해줌으로써 원본 높이의 1/3~2/3지점까지의 색을 가져오게 됨

			cvSet2D(green, y, x, greenColor); // 초록색 이미지에 저장

			/*----------여기까지 초록색 저장----------*/

			CvScalar redColor = cvGet2D(src, y + (eachHeight * 2), x); // eachHeight*2를 더해줌으로써 원본 높이의 2/3~3/3지점까지의 색을 가져오게 됨

			cvSet2D(red, y, x, redColor); // 빨강색 이미지에 저장

			/*----------여기까지 빨강색 저장----------*/

		}
	}

	/*----------여기까지 원본으로부터 3색의 이미지를 나누는 구문----------*/
	/**************************************************/



	// 분해된 그림의 중심 좌표를 구함
	int centerX = eachWidth / 2;
	int centerY = eachHeight / 2;

	// 분해된 그림의 중심 좌표를 기준으로 특정 크기만큼의 작은 이미지를 가져오기 위한 변수
	int setArea = eachWidth / 9; // 이미지를 비교하기에 가장 최적의 사이즈가 너비의 8등분이라고 판단하여 정한 임의의값
	if (setArea % 2 == 1) setArea--; // 홀수일때 발생할 수 있는 에러를 방지하기 위해 무조건 짝수화함
	if (setArea <= 80) setArea = 100; // setArea가 너무 작으면 비교가 힘들어지므로 100으로 고정함

	int halfSetArea = setArea / 2;

	// 분해된 r, g, b 이미지로부터 setArea^2 사이즈 만큼의 이미지만 빼오기 위한 함수
	IplImage* blueArea = cvCreateImage(cvSize(setArea, setArea), 8, 3);
	IplImage* greenArea = cvCreateImage(cvSize(setArea, setArea), 8, 3);
	IplImage* redArea = cvCreateImage(cvSize(setArea, setArea), 8, 3);

	IplImage* blueHisto = cvCreateImage(cvSize(setArea, setArea), 8, 3);  // 파란색 값을 저장하고 있는 이미지를 저장할 변수
	IplImage* greenHisto = cvCreateImage(cvSize(setArea, setArea), 8, 3);  // 초록색 값을 저장하고 있는 이미지를 저장할 변수
	IplImage* redHisto = cvCreateImage(cvSize(setArea, setArea), 8, 3);  // 빨간색 값을 저장하고 있는 이미지를 저장할 변수



	// 분해된 그림의 중심 좌표로 부터 상, 하, 좌, 우 setArea/2만큼의 위치에서 그림을 가져옴
	// 속도와 불필요한 반복문을 없애고자 하나의 반복문에서 3가지 색을 전부 처리
	for (int y = -halfSetArea; y < halfSetArea; y++) {
		for (int x = -halfSetArea; x < halfSetArea; x++) {

			CvScalar blueColor = cvGet2D(blue, y + centerY, x + centerX); // 파란색 원본이미지의 중심으로부터의 (x, y)만큼 떨어진 곳의 색을 가져옴

			cvSet2D(blueArea, y + halfSetArea, x + halfSetArea, blueColor); // 그림의 좌표는 (0,0)부터 이므로 시작점만큼 더해줌

			/*----------여기까지 파랑색 저장----------*/

			CvScalar greenColor = cvGet2D(green, y + centerY, x + centerX); // 초록색 원본이미지의 중심으로부터의 (x, y)만큼 떨어진 곳의 색을 가져옴

			cvSet2D(greenArea, y + halfSetArea, x + halfSetArea, greenColor);

			/*----------여기까지 초록색 저장----------*/

			CvScalar redColor = cvGet2D(red, y + centerY, x + centerX); // 빨강색 원본이미지의 중심으로부터의 (x, y)만큼 떨어진 곳의 색을 가져옴
			cvSet2D(redArea, y + halfSetArea, x + halfSetArea, redColor);

			/*----------여기까지 빨강색 저장----------*/

		}
	}


	/*-----여기 까지 3색의 나눠진 이미지를 사용하여 특정사이즈의  작은 이미지를 뽑아내는 구문-----*/
	/*******************************************************************/

	// 각 색의 히스토그램 정보가 들어갈 변수들
	int histo_blue[256][3] = { 0 };
	int histo_green[256][3] = { 0 };
	int histo_red[256][3] = { 0 };

	// 각 색의 히스토그램 정보를 저장하는 반복문
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

	// 각 색의 히스토그램 누적값이 들어갈 변수들
	int cumul_blue[256][3] = { 0 };
	int cumul_green[256][3] = { 0 };
	int cumul_red[256][3] = { 0 };

	// 각 색의 히스토그램 누적값을 구하는 반복문
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

	// 구해진 히스토그램 누적값을 토대로 ~Histo이미지 변수에 적용시키는 반복문
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

			/*------------여기까지 파란색------------*/

			f = cvGet2D(greenArea, y, x);
			for (int k = 0; k < 3; k++)
			{
				g.val[k] = cumul_green[int(f.val[k])][k]
					/ float(cumul_green[255][k]) * 255;
			}
			cvSet2D(greenHisto, y, x, g);

			/*------------여기까지 초록색------------*/

			f = cvGet2D(redArea, y, x);
			for (int k = 0; k < 3; k++)
			{
				g.val[k] = cumul_red[int(f.val[k])][k]
					/ float(cumul_red[255][k]) * 255;
			}
			cvSet2D(redHisto, y, x, g);

			/*------------여기까지 빨강색------------*/
		}
	}


	/*----------여기까지 히스토그램을 사용하여 각 이미지의 전체적인 대비값을 맞춤----------*/
	/**************************************************************/



	// 처리 속도를 위해 이미지를 가로, 세로50%만큼 씩 줄여주기 위한 부분

	// 역변환을 사용하여 이미지 축소
	double M[2][2]; // 정행렬
	double sx = 0.5, sy = 0.5; // 0.5배 만큼 축소하기위함
	M[0][0] = sx;		M[0][1] = 0;
	M[1][0] = 0;			M[1][1] = sy;

	double invM[2][2]; // 역행렬
	double det = M[0][0] * M[1][1] - M[0][1] * M[1][0]; // determinant(행렬식)

	if (abs(det) < 0.000001) { // determinant가 0이라면 안내문 출력과 함께 프로그램 종료
		printf("계산이 불가능합니다.\n");
		return 0;
	}

	// 역행렬 값을 각각 저장함
	invM[0][0] = M[1][1] / det;		invM[0][1] = -M[0][1] / det;
	invM[1][0] = -M[1][0] / det;		invM[1][1] = M[0][0] / det;

	// blueArea, greenArea, redArea의 가로, 세로 50%씩 축소한
	// 이미지의 색 정보를 저장하기 위한 2차원 동차 배열 선언 및 메모리 할당
	double **blueArray = (double**)malloc(sizeof(double*)*halfSetArea);
	double **greenArray = (double**)malloc(sizeof(double*)*halfSetArea);
	double **redArray = (double**)malloc(sizeof(double*)*halfSetArea);

	for (int i = 0; i < halfSetArea; i++) {
		blueArray[i] = (double*)malloc(sizeof(double)*halfSetArea);
		greenArray[i] = (double*)malloc(sizeof(double)*halfSetArea);
		redArray[i] = (double*)malloc(sizeof(double)*halfSetArea);
	}


	// 축소된 이미지를 저장하기 위한 반복문
	// 속도와 불필요한 반복문을 없애고자 하나의 반복문에서 3가지 색을 전부 처리
	for (int x2 = 0; x2 < blueArea->width*sx; x2++) {
		for (int y2 = 0; y2 < blueArea->height*sy; y2++) {

			double x1 = invM[0][0] * x2 + invM[0][1] * y2;
			double y1 = invM[1][0] * x2 + invM[1][1] * y2;

			// 만약을 위한 범위 초과 예외처리
			if (x1<0 || x1>blueArea->width - 1) continue;
			if (y1<0 || y1>blueArea->height - 1) continue;

			/*----------여기까지 좌표값 결정----------*/

			CvScalar blueColor = cvGet2D(blueHisto, y1, x1);
			blueArray[y2][x2] = blueColor.val[0];

			/*----------여기까지 파랑색 저장----------*/

			CvScalar greenColor = cvGet2D(greenHisto, y1, x1);
			greenArray[y2][x2] = greenColor.val[0];

			/*----------여기까지 초록색 저장----------*/

			CvScalar redColor = cvGet2D(redHisto, y1, x1);
			redArray[y2][x2] = redColor.val[0];

			/*----------여기까지 빨강색 저장----------*/

		}
	}

	/*----------여기까지 특정 사이즈의 작은이미지를 가로, 세로 50%씩 축소시키는 구문----------*/
	/*****************************************************************/

	// 두색간의 거리차를 저장하고 비교하는 것과 관련된 변수들
	double sumBToG = 0, sumBToR = 0; // 두 색의 거리차의 누적값이 계속해서 저장될 변수
	double minSumBToG = FLT_MAX, minSumBToR = FLT_MAX; // 두 색의 거리차 중 최소거리차가 저장될 변수
	int count = 0; // 두 색의 거리차를 비교한 영역의 넓이의 크기가 얼마인지 저장할 변수

				   // 초록색 이미지와 빨강색 이미지의 예상 이동 값이 저장될 변수
	int tempGx = 0, tempGy = 0; // 초록색 이미지의 예상 이동 픽셀을 저장
	int tempRx = 0, tempRy = 0; // 빨강색 이미지의 예상 이동 픽셀을 저장

								// 비교 이미지인 small이미지들을 small이미지 사이즈의 몇%만큼 움직이면서
								// 적절한 위치를 찾을 것인지를 정하는 변수 (임의의 값)
	int moveX = halfSetArea*(2.0 / 10); // x축을 좌, 우로 각각 20%만큼 움직이면서 비교함
	int moveY = halfSetArea*(8.0 / 10); // y축을 위, 아래로 각각 80%만큼 움직이면서 비교함

										// 정해진 비교 영역으로 부터 비교하기 위한 반복문
	for (int v = -moveY; v <= moveY; v++) {
		for (int u = -moveX; u <= moveX; u++) {

			// 비교 영역이 바뀔 때마다 새로 구해야하므로 변수 초기화 (최솟값을 저장하는 변수는 예외)
			count = 0;
			sumBToG = 0;
			sumBToR = 0;

			// 비교 이미지 간의 누적 거리값을 구하기 위한 반복문 
			for (int x = 0; x < blueArea->width*sx; x++) {

				// 불필요한 계산 및 반복 방지를 위해 x2값을 미리 계산함
				int x2 = x + u; // x축으로 u만큼 이동한 x좌표
				if (x2 < 0) continue; // x2가 0보다 작으면 계속 진행

				for (int y = 0; y < blueArea->height*sy; y++) {


					int y2 = y + v; // y축으로 v만큼 이동한 y좌표

					// 이미지 영역을 벗어날 확률이 매우 높으므로 예외처리
					if (y2 < 0) continue; // y2가 0보다 작을 경우는 계속 진행하지만
					if (y2 > blueArea->height*sy - 1) break; // y2가 이미지의 높이를 초과한다면 반복문 종료 (진행하는 것은 무의미하기 때문)
					if (x2 > blueArea->width*sx - 1) continue;

					/*----------여기까지 좌표값 결정----------*/

					double blueColor = blueArray[y][x];//blueArray[int(y*halfSetArea+x)];
					double greenColor = greenArray[y2][x2];//greenArray[int(y2*halfSetArea+x2)];
					double redColor = redArray[y2][x2];//redArray[int(y2*halfSetArea+x2)];

					double disG = (blueColor - greenColor)*(blueColor - greenColor);
					double disR = (blueColor - redColor)*(blueColor - redColor);

					sumBToG += disG; // 파랑색 이미지와 초록색 이미지의 거리차 누적값을 저장
					sumBToR += disR; // 파랑색 이미지와 빨강색 이미지의 거리차 누적값을 저장

					count++; // 비교한 영역의 넓이를 카운트함

					 /*----------여기까지 두 색간의 거리 계산----------*/

				} // y for문 끝

				if (x2 > blueArea->width*sx - 1) // x2가 이미지의 너비를 초과한다면 반복문 종료 (진행하는 것은 무의미하기 때문)
					break;

			} // x for문 끝

			  // 초록색 이미지의 이동 좌표를 결정하기 위한 조건문
			if (sumBToG / count < minSumBToG) { // 누적된 거리값을 비교한 영역만큼의 평균을 구하고 최소 누적값이랑 비교

				minSumBToG = sumBToG / count; // 누적된 거리값을 비교한 영역만큼의 평균을 다시 최솟값으로 설정
				tempGx = u; // x축만큼 이동한 값을 저장
				tempGy = v; // y축만큼 이동한 값을 저장

			}

			// 빨강색 이미지의 이동 좌표를 결정하기 위한 조건문
			if (sumBToR / count < minSumBToR) { // 위와 동일

				minSumBToR = sumBToR / count;
				tempRx = u;
				tempRy = v;

			}

		} // u for문 끝
	} // v for문 끝

	// 이미지를 빠르게 비교하기 위해 50%만큼 줄였으므로
	// 예상 이동 픽셀도 50%만큼 줄어들은 관계로
	// 다시 2배를 해줌
	tempGx *= 2;
	tempGy *= 2;
	tempRx *= 2;
	tempRy *= 2;


	/*----------여기까지 이동해야하는 좌표를 구하는 구문----------*/
	/********************************************/


	// 계산된 이동 좌표값을 토대로 최종 이미지에
	// 대입하기 위한 반복문
	// 파랑색은 기준색, 기준위치
	for (int y = 0; y < dst->height; y++) {
		for (int x = 0; x < dst->width; x++) {

			// green이미지의 예상 이동 좌표
			int y2 = y + tempGy;
			int x2 = x + tempGx;

			// red이미지의 예상 이동 좌표
			int y3 = y + tempRy;
			int x3 = x + tempRx;

			// 범위 초과 방지를 위한 예외 처리
			if (y2<0 || y2>dst->height - 1 || x2<0 || x2>dst->width - 1) { // green이미지의 예상 이동 좌표가 범위를 초과하였을 경우

				if (y3<0 || y3>dst->height - 1 || x3<0 || x3>dst->width - 1) { // 또한 red이미지의 예상 이동 좌표도 범위를 초과하였을 경우
					// 아무것도 안함
					continue;
				}
				else { // red이미지의 예상 이동 좌표는 범위를 초과하지 않았을 경우
					// 파랑-빨강만 합침

					CvScalar stdColor = cvGet2D(blue, y, x); // 초기 파랑색의 색을 가져옴
					CvScalar redColor = cvGet2D(red, y3, x3); // 초기 빨강색의 색을 가져옴

					stdColor.val[2] = redColor.val[2]; // 기준색에 빨간색 값을 대입

					cvSet2D(dst, y, x, stdColor); // 완성된 r,g,b색 정보를 dst에 최종 저장

				}

			}
			else { // green 이미지의 예상 이동 좌표가 범위를 초과하지 않았을 경우

				if (y3<0 || y3>dst->height - 1 || x3<0 || x3>dst->width - 1) { // 하지만 red이미지의 예상 이동 좌표는 범위를 초과하였을 경우
					// 파랑-초록만 합침

					CvScalar stdColor = cvGet2D(blue, y, x); // 초기 파랑색의 색을 가져옴
					CvScalar greenColor = cvGet2D(green, y2, x2); // 초기 초록색의 색을 가져옴

					stdColor.val[1] = greenColor.val[1]; // 기준색에 초록색 값을 대입

					cvSet2D(dst, y, x, stdColor);

				}
				else { // green, red이미지 모두 예상 이동 좌표가 범위를 초과하지 않았을 경우
					// 파랑-초록-빨강 모두 합침

					CvScalar stdColor = cvGet2D(blue, y, x); // 초기 파랑색의 색을 가져옴
					CvScalar greenColor = cvGet2D(green, y2, x2); // 초기 초록색의 색을 가져옴
					CvScalar redColor = cvGet2D(red, y3, x3); // 초기 빨강색의 색을 가져옴

					stdColor.val[1] = greenColor.val[1]; // 기준색에 초록색 값을 대입
					stdColor.val[2] = redColor.val[2]; // 기준색에 빨간색 값을 대입

					cvSet2D(dst, y, x, stdColor); // 완성된 r,g,b색 정보를 dst에 최종 저장
				}

			}


		}
	}

	/*----------여기까지 이동해야하는 좌표를 통해 3색을 합치는 구문----------*/
	/****************************************************/



	finish = clock(); // 실행시간 측정 종료
	printf("처리 시간 : %.3f초\n", (double)(finish - start) / CLOCKS_PER_SEC); // 초 단위로 출력함

	// 원본 이미지와 완성된 이미지 출력
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();


	// 모든 메모리 해제
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