#pragma once
#include "person.h"
using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;


ref class Faculty : public person
{
protected:
    virtual String^ GetFilePath() override
    {
        return "C:\\Users\\kk\\OneDrive\\Desktop\\Final\\Faculty.txt";
    }
public:

    bool CanAddFaculty()
    {
        // Use the protected GetFilePath method to ensure consistency
        String^ facultyFilePath = GetFilePath();

        // Check if the file exists
        if (File::Exists(facultyFilePath))
        {
            // Read all lines from the file
            array<String^>^ lines = File::ReadAllLines(facultyFilePath);

            // Count only non-empty lines
            int validEntries = 0;
            for each (String ^ line in lines)
            {
                if (!String::IsNullOrWhiteSpace(line)) // Ignore empty or whitespace-only lines
                {
                    validEntries++;
                }
            }

            // If there are already 4 or more valid entries, return false
            if (validEntries >= 4)
            {
                return false; // Cannot add more faculty members
            }
        }

        return true; // If file doesn't exist or has less than 4 valid entries
    }
    void checkfaculty()
    {
        if (!CanAddFaculty())
        {
            MessageBox::Show("Cannot add more faculty members. Maximum of 4 faculty members allowed.");
            return;
        }
    }
   
    
    // Function to check the number of faculty members (lines in the Faculty.txt)
};


