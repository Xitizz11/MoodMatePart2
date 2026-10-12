
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class MoodEntry
{
private:
    string date;
    int rating;
    string note;

public:
    MoodEntry();
    MoodEntry(string d, int r, string n);

    void setDate(string d);
    void setRating(int r);
    void setNote(string n);

    string getDate() const;
    int getRating() const;
    string getNote() const;

    string getMoodLabel() const;
    void printEntry() const;
};

// Default constructor
MoodEntry::MoodEntry()
{
    date = "Unspecified";
    rating = 3;
    note = "No note";
}

// Constructor with information
MoodEntry::MoodEntry(string d, int r, string n)
{
    setDate(d);
    setRating(r);
    setNote(n);
}

// Set the date
void MoodEntry::setDate(string d)
{
    if (d != "")
        date = d;
    else
        date = "Unspecified";
}

// Set the rating
void MoodEntry::setRating(int r)
{
    if (r >= 1 && r <= 5)
        rating = r;
    else
        rating = 3;
}

// Set the note
void MoodEntry::setNote(string n)
{
    if (n != "")
        note = n;
    else
        note = "No note";
}

// Get the date
string MoodEntry::getDate() const
{
    return date;
}

// Get the rating
int MoodEntry::getRating() const
{
    return rating;
}

// Get the note
string MoodEntry::getNote() const
{
    return note;
}

// Get the mood label
string MoodEntry::getMoodLabel() const
{
    if (rating == 1)
        return "Very Bad";
    else if (rating == 2)
        return "Bad";
    else if (rating == 3)
        return "Okay";
    else if (rating == 4)
        return "Good";
    else
        return "Great";
}

// Display one entry
void MoodEntry::printEntry() const
{
    cout << "Date: " << date << endl;
    cout << "Mood Rating: " << rating << endl;
    cout << "Mood: " << getMoodLabel() << endl;
    cout << "Note: " << note << endl;
}


// MoodTracker class
class MoodTracker
{
private:
    MoodEntry entries[20];
    int entryCount;

public:
    MoodTracker();

    void addEntry(const MoodEntry& entry);
    void displayEntries() const;
    double calculateAverage() const;
    MoodEntry getHighestMood() const;
    MoodEntry getLowestMood() const;
    int getEntryCount() const;
};

// Default constructor
MoodTracker::MoodTracker()
{
    entryCount = 0;
}

// Add a mood entry
void MoodTracker::addEntry(const MoodEntry& entry)
{
    if (entryCount < 20)
    {
        entries[entryCount] = entry;
        entryCount++;
        cout << "Mood entry added!" << endl;
    }
    else
    {
        cout << "The mood log is full." << endl;
    }
}

// Display all entries
void MoodTracker::displayEntries() const
{
    if (entryCount == 0)
    {
        cout << "No entries yet." << endl;
    }
    else
    {
        for (int i = 0; i < entryCount; i++)
        {
            cout << endl;
            cout << "Entry " << i + 1 << endl;
            entries[i].printEntry();
        }
    }
}

// Calculate average rating
double MoodTracker::calculateAverage() const
{
    if (entryCount == 0)
        return 0.0;

    int total = 0;

    for (int i = 0; i < entryCount; i++)
    {
        total = total + entries[i].getRating();
    }

    return (double)total / entryCount;
}

// Find highest mood
MoodEntry MoodTracker::getHighestMood() const
{
    if (entryCount == 0)
        return MoodEntry();

    int highest = 0;

    for (int i = 1; i < entryCount; i++)
    {
        if (entries[i].getRating() >
            entries[highest].getRating())
        {
            highest = i;
        }
    }

    return entries[highest];
}

// Find lowest mood
MoodEntry MoodTracker::getLowestMood() const
{
    if (entryCount == 0)
        return MoodEntry();

    int lowest = 0;

    for (int i = 1; i < entryCount; i++)
    {
        if (entries[i].getRating() <
            entries[lowest].getRating())
        {
            lowest = i;
        }
    }

    return entries[lowest];
}

// Get number of entries
int MoodTracker::getEntryCount() const
{
    return entryCount;
}


int main()
{
    MoodTracker tracker;
    int choice = 0;

    while (choice != 6)
    {
        cout << endl;
        cout << "=========================" << endl;
        cout << "       MOODMATE" << endl;
        cout << "=========================" << endl;
        cout << "1. Add Mood Entry" << endl;
        cout << "2. View All Entries" << endl;
        cout << "3. View Average Mood" << endl;
        cout << "4. View Highest Mood" << endl;
        cout << "5. View Lowest Mood" << endl;
        cout << "6. Exit" << endl;
        cout << "=========================" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid choice. Enter a number from 1 to 6." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Add entry
        if (choice == 1)
        {
            if (tracker.getEntryCount() == 20)
            {
                cout << "The mood log is full." << endl;
                continue;
            }

            string date;
            string note;
            int rating;

            cout << "Enter date: ";
            getline(cin, date);

            cout << "Enter mood rating (1-5): ";

            if (!(cin >> rating))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Invalid rating. Entry not added." << endl;
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter note: ";
            getline(cin, note);

            MoodEntry today(date, rating, note);
            tracker.addEntry(today);
        }

        // View all entries
        else if (choice == 2)
        {
            tracker.displayEntries();
        }

        // View average
        else if (choice == 3)
        {
            if (tracker.getEntryCount() == 0)
            {
                cout << "No entries to average yet." << endl;
            }
            else
            {
                cout << fixed << setprecision(1);
                cout << "Average Mood: "
                     << tracker.calculateAverage() << endl;
            }
        }

        // View highest mood
        else if (choice == 4)
        {
            if (tracker.getEntryCount() == 0)
            {
                cout << "No entries yet." << endl;
            }
            else
            {
                cout << "----- Highest Mood -----" << endl;
                tracker.getHighestMood().printEntry();
            }
        }

        // View lowest mood
        else if (choice == 5)
        {
            if (tracker.getEntryCount() == 0)
            {
                cout << "No entries yet." << endl;
            }
            else
            {
                cout << "----- Lowest Mood -----" << endl;
                tracker.getLowestMood().printEntry();
            }
        }

        // Exit
        else if (choice == 6)
        {
            cout << "Thank you for using MoodMate!" << endl;
        }

        // Invalid menu choice
        else
        {
            cout << "Invalid choice. Please choose 1 through 6." << endl;
        }
    }

    return 0;
}
