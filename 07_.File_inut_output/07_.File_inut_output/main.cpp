#include<iostream>
#include<thread>
#include<fstream>
#include<mutex>
#include<windows.h>

using namespace std;

static bool isRecording = false;
static int remainTime = 0;
static thread recordThread;
static mutex mtx;

void saveRecord();

void startRecord() {
    if (recordThread.joinable()) return; // 이미 스레드 실행 중이면 시작 x
    isRecording = true;
    recordThread = thread(saveRecord);   // 녹화 스레드 시작
}

void saveRecord() {
    ofstream file("data.rec", ios::app); // 기존 파일 뒤에 이어쓰기

    while (true) {
        Sleep(1000); // 1초 대기
        mtx.lock();

        if (!isRecording || remainTime <= 0) { // 녹화 꺼지거나 시간 다 되면
            isRecording = false;
            mtx.unlock(); // break 전에 반드시 unlock
            break;
        }

        file << "Recording..." << remainTime << endl;
        remainTime--;
        mtx.unlock();
    }
}

void printMenu() {
    cout << "===== BlackBox Simulator =====" << endl;
    cout << "1. 녹화 ON/OFF  [[ 현재상태 : " << (isRecording ? "ON" : "OFF") << "]]" << endl;
    cout << "2. 잔여 녹화 시간 확인" << endl;
    cout << "3. 녹화 시간 설정" << endl;
    cout << "4. 프로그램 종료" << endl;
    cout << "기능 선택 =>";
}

void setRemainTime() {
    int sec;
    cout << "녹화 시간 입력 (초단위) -> ";
    cin >> sec;

    mtx.lock();
    remainTime = sec;
    mtx.unlock();

    if (sec > 0)
        startRecord(); // 양수면 녹화 시작
}

int main() {
    ofstream initFile("data.rec"); // 시작 시 파일 새로 생성 (덮어쓰기)
    initFile.close();

    int choice;

    do {
        printMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            // OFF -> ON
            if (!isRecording) {    
                mtx.lock();
                remainTime = 60; 
                mtx.unlock();
                startRecord();
            }
            // ON -> OFF
            else { 
                mtx.lock();
                isRecording = false;
                mtx.unlock();
                if (recordThread.joinable())
                    recordThread.join();
            }
            break;
        case 2:
            cout << "현재 잔여 녹화 시간 : " << remainTime << "초" << endl;
            break;
        case 3:
            setRemainTime();
            break;
        case 4:
            mtx.lock();
            isRecording = false;     // 녹화 중이면 강제 종료
            mtx.unlock();
            if (recordThread.joinable())
                recordThread.join(); // 스레드 끝날 때까지 대기
            cout << "종료" << endl;
            break;
        default:
            cout << "잘못된 입력 값 입니다" << endl;
            break;
        }
    } while (choice != 4);

    return 0;
}