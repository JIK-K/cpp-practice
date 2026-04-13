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
    if (recordThread.joinable()) return; 
    isRecording = true;
    recordThread = thread(saveRecord); 
}

void saveRecord() {
    ofstream file("data.rec", ios::app);

    while (true) {
        Sleep(1000); 
        mtx.lock();

        if (!isRecording || remainTime <= 0) { 
            isRecording = false;
            mtx.unlock(); 
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
        startRecord(); 
}

int main() {
    ofstream initFile("data.rec"); 
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
            isRecording = false;     
            mtx.unlock();
            if (recordThread.joinable())
                recordThread.join(); 
            cout << "종료" << endl;
            break;
        default:
            cout << "잘못된 입력 값 입니다" << endl;
            break;
        }
    } while (choice != 4);

    return 0;
}