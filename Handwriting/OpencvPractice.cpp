#include "OpencvPractice.h"

void OpencvPractice::ImgSizePrint(cv::String imgPath)
{
	cv::Mat img1 = cv::imread(imgPath);
	std::cout << "이미지 세로 : "<<img1.rows << std::endl;
	std::cout << "이미지 가로 : "<<img1.cols << std::endl;
}
void OpencvPractice::ImgInfoPrint(cv::String imgPath)
{
	cv::Mat img1 = cv::imread(imgPath);

	std::cout << "" << img1.cols << std::endl;
	std::cout << "" << img1.rows << std::endl;
	std::cout << "" << img1.channels() << std::endl;

	if (img1.type() == CV_8UC1) {
		std::cout << "" << std::endl;
	}
	else if (img1.type() == CV_8UC3) {
		std::cout << "" << std::endl;
	}

	double data[] = { 2.f, 1.414f, 3.f, 1.732f };
	cv::Mat mat1(2, 2, CV_64FC1, data);
	std::cout << "mat1:\n" << mat1 << std::endl;
}
void OpencvPractice::RandomImage(cv::String imgPath = "Resource/Image/lenna.bmp")
{
	cv::Mat img;
	img = cv::imread(imgPath);

	if (img.empty()) {
		std::cerr << "Image load failed!" << std::endl;
		return;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> posR(0, 1080);
	std::uniform_int_distribution<int> sizeR(100, 500);


	cv::namedWindow("Image");
	cv::imshow("Image", img);

	while (1)
	{
		cv::moveWindow("Image", posR(gen), posR(gen));
		cv::resizeWindow("Image", sizeR(gen), sizeR(gen));
		if (cv::waitKey(delay) == 27)
			break;
	}
	cv::destroyAllWindows();
}

void OpencvPractice::MatOp1()
{
	cv::Mat img1;

	cv::Mat img2(480, 640, CV_8UC1);
	cv::Mat img3(480, 640, CV_8UC3);
	cv::Mat img4(cv::Size(640, 480), CV_8UC3);

	cv::Mat img5(480, 640, CV_8UC1, cv::Scalar(128));
	cv::Mat img6(480, 640, CV_8UC3, cv::Scalar(0, 0, 255));

	cv::Mat mat1 = cv::Mat::zeros(3, 3, CV_32SC1);
	cv::Mat mat2 = cv::Mat::ones(3, 3, CV_32SC1);
	cv::Mat mat3 = cv::Mat::eye(3, 3, CV_32SC1);

	double data[] = { 1, 2,3,4,5,6 };
	cv::Mat mat4(2, 3, CV_64FC1, data);

	cv::Mat mat5 = (cv::Mat_<double>(2, 3) << 1, 2, 3, 4, 5, 6);
	cv::Mat mat6 = cv::Mat_<uchar>({ 2,3 }, { 1,2,3,4,5,6 });

	mat4.create(256, 256, CV_8UC3);
	mat5.create(4, 4, CV_64FC1);

	mat4 = cv::Scalar(255, 0, 0);
	mat5.setTo(1.f);

}

void OpencvPractice::ImagePrint(cv::String imgName)
{
	cv::Mat img1 = cv::imread(imgName);
	if (img1.empty()) {
		//std::cerr : 에러 출력에 주로 사용되는 스트림
		std::cerr << "Image load failed!" << std::endl;
		return;
	}
	cv::Mat img2 = img1(cv::Rect(220, 80, 340, 280));//값 참조
	cv::Mat img3 = img1(cv::Rect(220, 80, 340, 280)).clone();//값 복사

	img2 = ~img2; //이미지 컬러 반전

	cv::imshow("img1", img1);
	cv::imshow("img2", img2);
	cv::imshow("img3", img3);

	cv::waitKey();
	cv::destroyAllWindows();
}

void OpencvPractice::Camera_In()
{
	cv::VideoCapture cap(0); //0번째 카메라를 연다
	if (!cap.isOpened())
	{
		std::cerr << "Camera open failed!" << std::endl;
		return;
	}
	std::cout << "Frame width: " << cvRound(cap.get(cv::CAP_PROP_FRAME_WIDTH)) << std::endl;
	std::cout << "Frame height: " << cvRound(cap.get(cv::CAP_PROP_FRAME_HEIGHT)) << std::endl;

	cv::Mat frame, inversed;
	while (true) {
		if (!cap.read(frame))
			break;
		
		inversed = ~frame;

		cv::imshow("basic", frame);
		cv::imshow("inversed", inversed);
		

		if (cv::waitKey(delay) == 27) //ESC 키
			break;
	}
	cv::destroyAllWindows();
}

void OpencvPractice::Video_In(cv::String videoPath, double winScale)
{
	cv::VideoCapture cap(videoPath);
	
	if (!cap.isOpened()) {
		std::cerr << "Video open failed!" << std::endl;
		return;
	}

	std::cout << "Frame width: " << cvRound(cap.get(cv::CAP_PROP_FRAME_WIDTH)) << std::endl;
	std::cout << "Frame height: " << cvRound(cap.get(cv::CAP_PROP_FRAME_HEIGHT)) << std::endl;
	std::cout << "Frame count: " << cvRound(cap.get(cv::CAP_PROP_FRAME_COUNT)) << std::endl;

	cv::namedWindow("Basic", cv::WINDOW_NORMAL);
	cv::namedWindow("Inversed", cv::WINDOW_NORMAL);
	cv::resizeWindow("Basic", cap.get(cv::CAP_PROP_FRAME_WIDTH) * winScale, cap.get(cv::CAP_PROP_FRAME_HEIGHT) * winScale);
	cv::resizeWindow("Inversed", cap.get(cv::CAP_PROP_FRAME_WIDTH) * winScale, cap.get(cv::CAP_PROP_FRAME_HEIGHT) * winScale);

	cv::Mat frame, inversed;
	while (true) {
		if (!cap.read(frame))
			break;
		
		inversed = ~frame;

		cv::imshow("Basic", frame);
		cv::imshow("Inversed", inversed);
		if (cv::waitKey(delay) == 27)
			break;
	}
	cv::destroyAllWindows();
	
	//VideoCapture클래스는 소멸 될 때 소멸자에서 메모리 자동 해제
}

void OpencvPractice::Camera_In_Video_Out(cv::String savePath)
{
	cv::VideoCapture cap(0);

	if (!cap.isOpened()) {
		std::cerr << "Camera open failed!" << std::endl;
		return;
	}

	int w = cvRound(cap.get(cv::CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

	int fourcc = cv::VideoWriter::fourcc('F', 'M', 'P', '4');
	cv::VideoWriter outputVideo(savePath, fourcc, fps, cv::Size(w, h));

	cv::Mat frame, inversed;

	while (true) {
		if (!cap.read(frame)) {
			break;
		}
		inversed = ~frame;
		outputVideo.write(inversed);
		
		cv::imshow("frame", frame);
		cv::imshow("inversed", inversed);
		
		if (cv::waitKey(delay) == 27)
			break;
	}
	cv::destroyAllWindows();
}

void OpencvPractice::FaceScan()
{
	cv::VideoCapture cap(0); //0번째 카메라를 연다
	if (!cap.isOpened())
	{
		std::cerr << "Camera open failed!" << std::endl;
		return;
	}

	cv::Mat frame;
	cv::CascadeClassifier faceClassifier;
	faceClassifier.load("C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml");

	cv::namedWindow("webcam", 1);

	while (true) {
		if (!cap.read(frame))
			break;
		cv::Mat grayscale;
		cv::cvtColor(frame, grayscale, cv::COLOR_BGR2GRAY);
		cv::equalizeHist(grayscale, grayscale);
		std::vector<cv::Rect> faces;
		faceClassifier.detectMultiScale(grayscale, faces, 1.1, 3,
			0,
			//cv::CASCADE_FIND_BIGGEST_OBJECT | cv::CASCADE_SCALE_IMAGE, 
			cv::Size(30, 30));

		for (int i = 0; i < faces.size(); i++) {
			cv::Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			cv::Point tr(faces[i].x, faces[i].y);

			cv::rectangle(frame, lb, tr, cv::Scalar(0, 255, 0), 3, 4, 0);

			cv::imshow("webcam", frame);
		}

		if (cv::waitKey(200) == 27) //ESC 키
			break;
	}
	cv::destroyAllWindows();
}

void OpencvPractice::MatPrint(std::vector<cv::Mat>& trainingVec, std::vector<cv::uint8_t>& labelVec)
{
	std::cout << "읽어온 훈련 데이터 수 : " << trainingVec.size() << std::endl;
	std::cout << "읽어온 정답 데이터 수 : " << labelVec.size() << std::endl;

	cv::namedWindow("Window", cv::WINDOW_NORMAL);

	for (int i = 0; i < labelVec.size() && i < trainingVec.size(); i++) {
		imshow("Window", trainingVec[i]);
		//std::cout << i << "번째 이미지 정답 : " << (int)labelVec[i] <<std::endl;
		//아무 키나 누르면 다음
		/*if (cv::waitKey(0) != -1)
			continue;*/
	}
}

//32bit 정수형을 읽기 위해 리틀 엔디안 CPU에서 재배치하는 함수
//1바이트(8비트)씩 거꾸로 배열한 int를 반환
int OpencvPractice::ReverseInt(int i)
{
	unsigned char ch1, ch2, ch3, ch4;
	ch1 = i & 255;
	ch2 = (i >> 8) & 255;
	ch3 = (i >> 16) & 255;
	ch4 = (i >> 24) & 255;
	return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

//인자로 받은 vector에 Mnist 훈련 데이터를 파싱해 Matrix으로 저장
void OpencvPractice::MnistTrainingDataRead(std::string filePath, std::vector<cv::Mat>& vec, int readDataNum)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.is_open())
	{
		int magic_number = 0;
		int number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;

		//ifstream::read(str, count)로 count만큼 읽어 str에 저장
		//char은 1바이트, int는 4바이트이므로 int 1개당 char 4개의 정보만큼 가져옴
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);
		file.read((char*)&n_rows, sizeof(n_rows));
		n_rows = ReverseInt(n_rows);
		file.read((char*)&n_cols, sizeof(n_cols));
		n_cols = ReverseInt(n_cols);
		
		if (readDataNum > number_of_images || readDataNum <= 0)
			readDataNum = number_of_images;

		for (int i = 0; i < readDataNum; ++i)
		{
			cv::Mat tp = cv::Mat::zeros(n_rows, n_cols, ConvertCVGrayImageType(magic_number));
			for (int r = 0; r < n_rows; ++r)
			{
				for (int c = 0; c < n_cols; ++c)
				{
					//magicnumber에서 얻은 타입 정보가 unsigned byte 일 경우
					if (ConvertCVGrayImageType(magic_number) == CV_8UC1) {
						unsigned char temp = 0;
						file.read((char*)&temp, sizeof(temp));
						tp.at<uchar>(r, c) = (int)temp;
					}
				}
			}
			vec.push_back(tp);
		}
	}
}

void OpencvPractice::MnistLabelDataRead(std::string filePath, std::vector<uint8_t>& vec, int readDataNum)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.is_open())
	{
		int magic_number = 0;
		int number_of_images = 0;

		//ifstream::read(str, count)로 count만큼 읽어 str에 저장
		//char은 1바이트, int는 4바이트이므로 int 1개당 char 4개의 정보만큼 가져옴
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);
		if (readDataNum > number_of_images || readDataNum <= 0)
			readDataNum = number_of_images;

		for (int i = 0; i < readDataNum; ++i)
		{
			//magicnumber에서 얻은 타입 정보가 unsigned byte 일 경우
			if (ConvertCVGrayImageType(magic_number) == CV_8UC1) {
				uint8_t temp = 0;
				file.read((char*)&temp, sizeof(temp));
				vec.push_back(temp);
			}
		}
	}
}

int OpencvPractice::ConvertCVGrayImageType(int magicNumber)
{
	magicNumber = (magicNumber >> 8) & 255; //3번째 바이트(픽셀 타입)만 가져오기
	//리틀 엔디안 CPU에서 magicNumber = ((char*)&magicNumber)[1];와 같음
	//빅 엔디안 CPU에서 magicNumber = ((char*)&magicNumber)[2];와 같음

	switch (magicNumber) {
	case 0x08: return CV_8UC1;//unsigned byte, 흑백 채널 단일
	case 0x09: return CV_8SC1;//signed byte, 흑백 채널 단일
	case 0x0B: return CV_16SC1;//short(2 바이트), 흑백 채널 단일
	case 0x0C: return CV_32SC1;//int(4 바이트), 흑백 채널 단일
	case 0x0D: return CV_32FC1;//float(4 바이트), 흑백 채널 단일
	case 0x0E: return CV_64FC1;//double(8 바이트), 흑백 채널 단일
	default: return CV_8UC1;
	}
}
