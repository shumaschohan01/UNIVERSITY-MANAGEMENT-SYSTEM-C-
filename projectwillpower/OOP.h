#pragma once
#include "mapper.h"
using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

ref class CRUDoperation : public mapper
{
protected:
    String^ DefaultPassword = "karachi@123";
public:

    void Add(String^ name, String^ fatherName, String^ id, String^ contactNo, String^ field1, String^ gender)
    {
        // Read all existing lines (entries) from the file
        auto lines = ReadFile();

        // Check if the ID already exists in any of the records
        for each (String ^ line in lines)
        {
            array<String^>^ parts = line->Split(',');

            // If the ID already exists, show an error and return
            if (parts->Length > 2 && parts[2]->Trim()->Equals(id->Trim()))
            {
                MessageBox::Show("Error: ID already exists. Please use a unique ID.");
                return;  // Exit the method to prevent adding the duplicate ID
            }
        }

        // If the ID is unique, add the new entry
        String^ newEntry = name + "," + fatherName + "," + id + "," + contactNo + "," + field1 + "," + gender + "," + DefaultPassword;
        lines->Add(newEntry);

        // Write the updated list back to the file
        WriteFile(lines);
        MessageBox::Show("Data added successfully.");
    }
    void Update(String^ oldID, String^ oldName, String^ oldFatherName, String^ oldContactNo, String^ oldField1, String^ oldGender,
    String^ newID, String^ newName, String^ newFatherName, String^ newContactNo, String^ newField1, String^ newGender)
    {
        // Read all lines from the file
        auto lines = ReadFile();

        // Find the index of the entry with the old ID (we assume ID is unique)
        int index = FindEntryIndex(lines, oldID);

        if (index != -1) // If the entry is found
        {
            // Update the line with the new values
            lines[index] = newName + "," + newFatherName + "," + newID + "," + newContactNo + "," + newField1 + "," + newGender + "," + DefaultPassword;

            // Write the updated lines back to the file
            WriteFile(lines);
        }
        else
        {
            // If the old ID was not found, show a message
            MessageBox::Show("No matching entry found for update.");
        }
    }
    void Delete(String^ id)
    {
        auto lines = ReadFile();
        int index = FindEntryIndex(lines, id);

        if (index != -1)
        {
            lines->RemoveAt(index);
            WriteFile(lines);
        }
    }

  };



