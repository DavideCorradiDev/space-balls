#include <GameplaySystem/ScoreRecord.hpp>
#include <GameplaySystem/GSConstants.hpp>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>

namespace mnk {


ScoreRecord::ScoreRecord() :
    mMaxScoreEntries(0) {}

ScoreRecord::ScoreRecord(std::size_t maxScoreEntries) :
    mMaxScoreEntries(maxScoreEntries) {}

bool compareScoreEntries(const ScoreRecord::ScoreEntry& se1, const ScoreRecord::ScoreEntry& se2);

bool compareScoreEntries(const ScoreRecord::ScoreEntry& se1, const ScoreRecord::ScoreEntry& se2) {
    return se1.score > se2.score;
}

void ScoreRecord::addEntry(const ScoreEntry& entry) {
    mEntries.push_back(entry);
    std::sort(mEntries.begin(), mEntries.end(), compareScoreEntries);
    while(mEntries.size() > mMaxScoreEntries) {
        mEntries.pop_back();
    }
}

void ScoreRecord::readFromFile(const std::string& filename) {
    std::ifstream iFile(filename);
    mEntries.clear();
    //Read Header line:
    if(iFile.good()) {
        std::string entryString;
        std::getline(iFile, entryString);
        assert(entryString == "ScoreFile");
    }
    while(iFile.good()) {
        std::string entryString;
        std::getline(iFile, entryString);
        std::istringstream iStringStream(entryString);
        while(iStringStream.good()) {
            std::string name;
            std::string scoreString;
            std::getline(iStringStream, name, ',');
            std::getline(iStringStream, scoreString, ',');
            addEntry(ScoreEntry(name, std::strtoul(scoreString.c_str(), nullptr, 10)));
        }
    }
    iFile.close();
}

void ScoreRecord::writeToFile(const std::string& filename) const {
    std::remove(filename.c_str());
    std::ofstream oFile(filename);
    oFile << "ScoreFile";
    for(std::size_t i = 0; i < mEntries.size(); i++) {
        oFile << std::endl << mEntries[i].name << ", " << mEntries[i].score;
    }
    oFile.close();
}

void ScoreRecord::print() const {
    for(std::size_t i = 0; i < mEntries.size(); ++i) {
        std::cout << i << ". " << mEntries[i].name << ": " << mEntries[i].score << std::endl;
    }
}

std::size_t ScoreRecord::getNumberOfEntries() const { return mEntries.size(); }

const ScoreRecord::ScoreEntry& ScoreRecord::operator[](std::size_t idx) const {
    assert(idx < mEntries.size());
    return mEntries[idx];
}

std::size_t ScoreRecord::getMaxScoreEntries() const { return mMaxScoreEntries; }
void ScoreRecord::setMaxScoreEntries(std::size_t value) { mMaxScoreEntries = value; }

ScoreRecord::ScoreEntry::ScoreEntry() :
    name(""),
    score(0) {}

ScoreRecord::ScoreEntry::ScoreEntry(const std::string& name, unsigned int score) :
    name(name),
    score(score) {}

}
