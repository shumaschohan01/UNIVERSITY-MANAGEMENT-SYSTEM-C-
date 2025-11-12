#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;


ref class mapper
{
protected:
    virtual String^ GetFilePath() = 0;
public:
    List<String^>^ ReadFile()
    {
        String^ filePath = GetFilePath();
        List<String^>^ lines = gcnew List<String^>();
        for each (String ^ line in File::ReadAllLines(filePath))
        {
            if (!String::IsNullOrWhiteSpace(line)) // Skip empty or whitespace lines
                lines->Add(line->Trim());
        }
        return lines;
    }
    void WriteFile(List<String^>^ lines)
    {
        String^ filePath = GetFilePath();
        File::WriteAllLines(filePath, lines->ToArray());
    }
    int FindEntryIndex(List<String^>^ lines, String^ id)
    {
        for (int i = 0; i < lines->Count; i++)
        {
            array<String^>^ parts = lines[i]->Split(',');
            if (parts->Length >= 3 && parts[2]->Trim()->Equals(id, StringComparison::OrdinalIgnoreCase)) // Match by ID
                return i;
        }
        return -1; // Not found
    }
    List<array<String^>^>^ Load()
    {
        auto lines = ReadFile();
        auto result = gcnew List<array<String^>^>();

        for each (String ^ line in lines)
        {
            array<String^>^ parts = line->Split(',');
            if (parts->Length <= 15)
                result->Add(parts);
        }

        return result;
    }
    List<array<String^>^>^ Load1()
    {
        // Read all lines from the file
        auto lines = ReadFile();
        auto result = gcnew List<array<String^>^>();

        // Process each line
        for each (String ^ line in lines)
        {
            // Split the line into parts
            array<String^>^ parts = line->Split(',');
            if (parts->Length <= 15)
            {
                result->Add(parts);
            }
            else
            {
                Console::WriteLine("Invalid entry: " + line);
            }
        }

        return result;
    }
    void LoadDataToGrid1(DataGridView^ dataGridView)
    {
        auto entries = Load1();  
        dataGridView->Rows->Clear();
        for each (auto entry in entries)
        {
            // Check if the entry has exactly 11 parts
            if (entry->Length == 12)
            {
                dataGridView->Rows->Add(entry[0], entry[1], entry[2], entry[3], entry[4], entry[5], entry[6], entry[7], entry[8], entry[9], entry[10], entry[11]);
            }
            else
            {
                MessageBox::Show("Invalid entry found, skipping: " + String::Join(",", entry), "Error");
            }
        }
    }
    void LoadDataToGrid(DataGridView^ dataGridView)
    {
        auto entries = Load();
        dataGridView->Rows->Clear();
        for each (auto entry in entries)
        {
            dataGridView->Rows->Add(entry[0], entry[1], entry[2], entry[3], entry[4], entry[5], entry[6]);
        }
    }

};

