// DumpScreenToVideo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "WinDesktopDup.h"
#include "WriteAVI.h"

int main()
{
    WinDesktopDup desktopDup;
    desktopDup.Initialize();
    desktopDup.CaptureNext();
    
    const int numberOfBitmaps = 60;
    const int frameRatePerSecond = 2;
    Bitmap bmp[numberOfBitmaps];

    for (int i = 0; i < numberOfBitmaps; i++)
    {
        bmp[i].Width = desktopDup.Latest.Width;
        bmp[i].Height = desktopDup.Latest.Height;
        bmp[i].Buf.resize(desktopDup.Latest.Buf.size());
    }

    int counter = 0;
    bool done = false;

    while (!done)
    {
        printf("Capturing frame %i / %i\r\n", counter, numberOfBitmaps);
        desktopDup.CaptureNext();
        std::copy(desktopDup.Latest.Buf.begin(), desktopDup.Latest.Buf.end(), bmp[counter].Buf.begin());

        counter++;
        if (counter >= numberOfBitmaps)
        {
            counter = 0;
            done = true;
        }
        //if (true) done = true;
        Sleep(1000 / frameRatePerSecond);
    }

    printf("Writing to AVI ...\r\n");

    // dump bitmaps to video
    wchar_t fileName[] = L"C:\\support\\test.avi";
    CAVIFile aviFile(fileName, desktopDup.Latest.Width, desktopDup.Latest.Height);
    
    BITMAPINFO  inf;
    memset(&inf, 0, sizeof(inf));
    inf.bmiHeader.biSize = sizeof(inf.bmiHeader);
    inf.bmiHeader.biWidth = desktopDup.Latest.Width;
    inf.bmiHeader.biHeight = -desktopDup.Latest.Height;
    inf.bmiHeader.biPlanes = 1;
    inf.bmiHeader.biBitCount = 32;
    inf.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HDC     srcDC = GetWindowDC(NULL);
    
    for (int i = 0; i < numberOfBitmaps; i++)
    {
        HBITMAP dib = CreateDIBSection(srcDC, &inf, 0, &bits, nullptr, 0);
        memcpy(bits, bmp[i].Buf.data(), bmp[i].Width * bmp[i].Height * 4);
        for (int j = 0; j < (15 / frameRatePerSecond); j++)
        {
            aviFile.AddFrame(dib);
        }
        DeleteObject(dib);
    }

    DeleteObject(srcDC);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
