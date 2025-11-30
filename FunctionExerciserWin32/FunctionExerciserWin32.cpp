// FunctionExerciserWin32.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <list>
#include <string>

int main()
{
    std::cout << "Hello World!\n";

	std::list<std::wstring> volumeguids;
	{
		wchar_t buffer[1024];
		HANDLE h = FindFirstVolumeW(buffer, sizeof(buffer) / sizeof(*buffer));
	
		if (h != INVALID_HANDLE_VALUE)
		{
			volumeguids.push_back(std::wstring(buffer));

			while (FindNextVolumeW(h, buffer, sizeof(buffer) / sizeof(*buffer)))
			{
				volumeguids.push_back(std::wstring(buffer));
			}

			{
				auto error = GetLastError();
				if (error != ERROR_NO_MORE_FILES)
				{
					std::cerr << "Failed enumerating " << error << "\n";
				}
			}

			BOOL closeok = FindVolumeClose(h);
			if (!closeok)
			{
				std::cerr << "Failed to close " << GetLastError() << "\n";
			}

			{
				for (auto it = volumeguids.begin(); it != volumeguids.end(); it++)
				{
					std::wcout << L"\"" << *it << L"\"\n";

					wchar_t b1[1024];
					DWORD VSN;
					DWORD MCL;
					DWORD FSF;
					wchar_t f1[1024];
					BOOL ok(GetVolumeInformationW(it->c_str(),
						b1, 1024,
						&VSN,
						&MCL,
						&FSF,
						f1, 1024));

					if (ok)
					{
						std::wcout << L"  \"" << b1 << L"\"\n";
					}
					else
					{
						std::cerr << "Failed getting volume information " << GetLastError() << "\n";
					}
				}
			}
		}
		else
		{
			std::cerr << "Failed " << GetLastError() << "\n";
		}
	}

    {
		HANDLE rr;
		DWORD retval = WNetOpenEnumW(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, NULL, &rr);

		if (retval == NO_ERROR)
		{
			NETRESOURCE nr;

			DWORD status;
			char buffer[1024];
			DWORD size = 1024;
			DWORD count = 1;
			while ((status = WNetEnumResourceW(rr, &count, buffer, &size)) == NO_ERROR)
			{
				NETRESOURCE* bnr = (NETRESOURCE*)(buffer);

				size = 1024; count = 1;
			}
		}
		else
		{
			std::cerr << "Failed " << GetLastError() << "\n";
		}
    }
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
