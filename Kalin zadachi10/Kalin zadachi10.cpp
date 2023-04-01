#include <iostream>
#include <cassert>


class HistoryEntry {
private:
	char* Url;
	int Month;
public:
	HistoryEntry() {
		Url = new char{ 0 };
		Month = 0;
	}
	HistoryEntry(char* url1, int month1)
	{
		Url = new char[strlen(url1) + 1];
		strcpy_s(Url, strlen(url1) + 1, url1);
		Month = month1;
	}
	~HistoryEntry() {
		delete[] Url;
	}
	HistoryEntry& operator=(const HistoryEntry& other) {
		this->Url = other.Url;
		this->Month = other.Month;

		return *this;
	}
	char* getUrl() {
		return Url;
	}
	int getMonth() {
		return Month;
	}
	void setUrl() {
		std::cin >> Url;
	}
	void setMonth() {
		std::cin >> Month;
	}
	void setUrl(char* url)
	{
		Url = url;
	}
	void setMonth(unsigned month)
	{
		Month = month;
	}
};


class BrowserHistory {
private:
	HistoryEntry* Entries;
	int size = 0;
	int counter = 0;
	void copy(const BrowserHistory& other)
	{
		this->size = other.size;
		this->counter = other.counter;
		this->Entries = new HistoryEntry[other.counter];
		assert(this->counter <= this->size);
		for (size_t i = 0; i < other.counter; i++)
		{
			this->Entries[i] = other.Entries[i];

		}

	}
	void destroy() {
		delete[]this->Entries;
		this->Entries = nullptr;
	}
	void resize() {
		int newSize = size * 2;
		HistoryEntry* newEntries = new HistoryEntry[newSize];
		size = newSize;
		for (size_t i = 0; i < size; i++)
		{
			newEntries[i] = Entries[i];
		}
		delete[]Entries;
		Entries = newEntries;
	}
public:
	BrowserHistory(int N) {
		Entries = new HistoryEntry[N];
		size = N;
	}
	BrowserHistory(const BrowserHistory& other) {
		copy(other);
	}
	HistoryEntry* getEntries() {
		return Entries;
	}
	BrowserHistory() {
		Entries = new	HistoryEntry[0];
	}
	~BrowserHistory() {
		destroy();
	}
	int getSize() {
		return size;
	}
	int getCounter() {
		return counter;
	}
	void addNewEntry(HistoryEntry newEntry) {
		if (counter > size - 1)
		{
			resize();
		}
		Entries[counter] = newEntry;
		newEntry.setMonth();
		newEntry.setUrl();
		counter++;

	};
	void operator+=(const HistoryEntry& other)
	{
		if (counter > size - 1)
		{
			resize();
		}
		Entries[counter] = other;
		counter++;
	}	
	void printAllEntries()
	{
		for (size_t i = 0; i < counter; i++)
		{
			std::cout << Entries[i].getMonth() << ' ' << Entries[i].getUrl() << std::endl;
		}
	}
	void RemoveLastEntry() {
		Entries[--counter].~HistoryEntry();
	}
	int NumOfEntryDuringMonth(int month)
	{
		int MonthCounter = 0;
		for (size_t i = 0; i < counter; i++)
		{
			if (Entries[i].getMonth() == month) {
				MonthCounter++;
			}
		}
		return MonthCounter;
	}
	int MostFrequentMonth() {
		int MaxMonth = 1;
		for (size_t i = 1; i < 13; i++)
		{
			if (NumOfEntryDuringMonth(MaxMonth) < NumOfEntryDuringMonth(i))
			{
				MaxMonth = i;
			}

		}
		return MaxMonth;
	}
	BrowserHistory& operator+(const BrowserHistory& otherHistory)
	{
		BrowserHistory* NewHistory = new BrowserHistory(otherHistory.counter + this->counter);
		NewHistory->counter = counter;
		for (int i = 0; i < (this->counter); i++)
		{
			NewHistory->Entries[i] = this->Entries[i];
		}

		for (int i = 0; i < otherHistory.counter; i++)
		{
			NewHistory->Entries[i + this->counter] = otherHistory.Entries[i];
		}
		return *NewHistory;
	}
	BrowserHistory& operator+=(const BrowserHistory& otherHistory)
	{
		for (int i = 0; i < (otherHistory.counter); i++)
		{
			if (counter < size-1 )
			{
				resize();
			}
			Entries[counter] = otherHistory.Entries[i];
			counter++;
		}
		return *this;
	}
	BrowserHistory& operator=(const BrowserHistory& otherHistory)
	{
		if (this != &otherHistory)
		{
			destroy();
			copy(otherHistory);
		}
		return *this;
	}
};

int main() {
	BrowserHistory* History1 = new BrowserHistory(3);
	BrowserHistory* History2 = new BrowserHistory(3);
	char* url1 = new char[20] {"04/24124./123/412"};
	char* url2 = new char[20] {"05/312/4/2141241"};
	char* url3 = new char[20] {"08/3312313122/5"};
	char* url4 = new char[20] {"0235235213415"};
	char* url5 = new char[20] {"dfzgdgwef341241"};
	HistoryEntry site1(url1, 7);
	HistoryEntry site2(url2, 5);
	HistoryEntry site3(url3, 6);
	HistoryEntry site4(url4, 9);
	HistoryEntry site5(url5, 10);
	*History1 += site1;
	*History1 += site2;
	*History2 += site3;
	*History2 += site4;
	*History2 += site5;
	History1->printAllEntries();
	std::cout << "--------------------" << std::endl;
	History2->printAllEntries();
	std::cout << "--------------------" << std::endl;
	*History1 += *History2;
	History1->printAllEntries();
	std::cout << "--------------------" << std::endl;
	*History1 + *History2;
	History1->printAllEntries();
	std::cout << "--------------------" << std::endl;
	History1 = History2;
	History1->printAllEntries();

	return 0;
}